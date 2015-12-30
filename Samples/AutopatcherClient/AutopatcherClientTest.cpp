/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

// Common includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#ifdef _WIN32
#include <filesystem>
#else
#include <experimental/filesystem>
#endif
#include "Kbhit.h"

#include "GetTime.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "StringCompressor.h"
#include "PacketizedTCP.h"

// Client only includes
#include "FileListTransferCBInterface.h"
#include "FileListTransfer.h"
#include "AutopatcherClient.h"
#include "AutopatcherPatchContext.h"
#include "Gets.h"
#include "RakSleep.h"

std::experimental::filesystem::path WORKING_DIRECTORY;
std::experimental::filesystem::path PATH_TO_XDELTA_EXE;

class TestCB : public RakNet::AutopatcherClientCBInterface
{
public:
	virtual bool OnFile(OnFileStruct *onFileStruct)
	{
		if (onFileStruct->context.op==PC_HASH_1_WITH_PATCH || onFileStruct->context.op==PC_HASH_2_WITH_PATCH)
			printf("Patched: ");
		else if (onFileStruct->context.op==PC_WRITE_FILE)
			printf("Written: ");
		else if (onFileStruct->context.op==PC_ERROR_FILE_WRITE_FAILURE)
			printf("Write Failure: ");
		else if (onFileStruct->context.op==PC_ERROR_PATCH_TARGET_MISSING)
			printf("Patch target missing: ");
		else if (onFileStruct->context.op==PC_ERROR_PATCH_APPLICATION_FAILURE)
			printf("Patch process failure: ");
		else if (onFileStruct->context.op==PC_ERROR_PATCH_RESULT_CHECKSUM_FAILURE)
			printf("Patch checksum failure: ");
		else if (onFileStruct->context.op==PC_NOTICE_WILL_COPY_ON_RESTART)
			printf("Copy pending restart: ");
		else if (onFileStruct->context.op==PC_NOTICE_FILE_DOWNLOADED)
			printf("Downloaded: ");
		else if (onFileStruct->context.op==PC_NOTICE_FILE_DOWNLOADED_PATCH)
			printf("Downloaded Patch: ");
		else
			RakAssert(0);


		printf("%i. (100%%) %i/%i %s %ib / %ib\n", onFileStruct->setID, onFileStruct->fileIndex+1, onFileStruct->numberOfFilesInThisSet,
			onFileStruct->fileName, onFileStruct->byteLengthOfThisFile,
			onFileStruct->byteLengthOfThisSet);

		// Return false for the file data to be deallocated automatically
		return false;
	}

	virtual void OnFileProgress(FileProgressStruct *fps)
	{
		printf("Downloading: %i. (%i%%) %i/%i %s %ib/%ib %ib/%ib total\n", fps->onFileStruct->setID,
			(int) (100.0*(double)fps->onFileStruct->bytesDownloadedForThisFile/(double)fps->onFileStruct->byteLengthOfThisFile),
			fps->onFileStruct->fileIndex+1, fps->onFileStruct->numberOfFilesInThisSet, fps->onFileStruct->fileName,
			fps->onFileStruct->bytesDownloadedForThisFile,
			fps->onFileStruct->byteLengthOfThisFile,			
			fps->onFileStruct->bytesDownloadedForThisSet,
			fps->onFileStruct->byteLengthOfThisSet
			);
	}

	virtual PatchContext ApplyPatchBase(const char *oldFilePath, char **newFileContents, unsigned int *newFileSize, char *patchContents, unsigned int patchSize, uint32_t patchAlgorithm)
	{
		if (patchAlgorithm==0)
		{
			return ApplyPatchBSDiff(oldFilePath, newFileContents, newFileSize, patchContents, patchSize);
		}
		else
		{
			std::string buff;
			RakNet::TimeUS time = RakNet::GetTimeUS();
			buff = time;
			std::experimental::filesystem::path pathToPatch1, pathToPatch2;
			std::experimental::filesystem::path commandLine;
			commandLine = WORKING_DIRECTORY;
			commandLine /= commandLine.concat("patchClient_" + buff + ".tmp");
			auto pathToPatch1U8 = pathToPatch1.u8string();
			auto pathToPatch2U8 = pathToPatch2.u8string();
			FILE *fpPatch = fopen(pathToPatch1U8.c_str(), "wb");
			if (fpPatch==0)
				return PC_ERROR_PATCH_TARGET_MISSING;
			fwrite(patchContents, 1, patchSize, fpPatch);
			fclose(fpPatch);

			// Invoke xdelta
			// See https://code.google.com/p/xdelta/wiki/CommandLineSyntax
			std::string xdeltaCommandLine;
			xdeltaCommandLine = "-d -f -s " + std::string(oldFilePath) + " patchClient_" + std::string(buff) + ".tmp  newFile_" + std::string(buff) + ".tmp";

			std::string shellExecute;
			shellExecute = "cd " + WORKING_DIRECTORY.string() + " && " + PATH_TO_XDELTA_EXE.string() + commandLine.string();
			system(shellExecute.c_str());

			// ShellExecute(NULL, "open", PATH_TO_XDELTA_EXE, commandLine, WORKING_DIRECTORY, SW_SHOWNORMAL);

			pathToPatch2 = WORKING_DIRECTORY;
			pathToPatch2 /= pathToPatch2.concat("newFile_" + buff + ".tmp");
			fpPatch = fopen(pathToPatch2U8.c_str(), "r+b");
			RakNet::TimeUS stopWaiting = time + 60000000;
			while (fpPatch==0 && RakNet::GetTimeUS() < stopWaiting)
			{
				RakSleep(1000);
				fpPatch = fopen(pathToPatch2U8.c_str(), "r+b");
			}
			if (fpPatch==0)
			{
				auto commandLineString = commandLine.string();
				printf("\nERROR: Could not open %s.\nerr=%i (%s)\narguments=%s\n", pathToPatch2, errno, strerror(errno), commandLineString.c_str());
				return PC_ERROR_PATCH_TARGET_MISSING;
			}
		
			fseek(fpPatch, 0, SEEK_END);
			*newFileSize = ftell(fpPatch);
			fseek(fpPatch, 0, SEEK_SET);
			*newFileContents = (char*) rakMalloc_Ex(*newFileSize, _FILE_AND_LINE_);
			fread(*newFileContents, 1, *newFileSize, fpPatch);
			fclose(fpPatch);

			std::error_code errorCode1;
			std::error_code errorCode2;

			int unlinkRes1 = std::experimental::filesystem::remove(pathToPatch1, errorCode1);
			int unlinkRes2 = std::experimental::filesystem::remove(pathToPatch2, errorCode2);

			while ((unlinkRes1 == false || unlinkRes2) && RakNet::GetTimeUS() < stopWaiting)
			{
				RakSleep(1000);
				if (unlinkRes1 == false)
					unlinkRes1 = std::experimental::filesystem::remove(pathToPatch1, errorCode1);
				if (unlinkRes2 == false)
					unlinkRes2 = std::experimental::filesystem::remove(pathToPatch2, errorCode2);
			}
			auto errorCode1String = errorCode1.message();
			auto errorCode2String = errorCode2.message();
			if (unlinkRes1 == false)
				printf("\nWARNING: unlink %s failed.\nerr=%i (%s)\n", pathToPatch1U8.c_str(), errorCode1.value(), errorCode1String.c_str());
			if (unlinkRes2 == false)
				printf("\nWARNING: unlink %s failed.\nerr=%i (%s)\n", pathToPatch2U8.c_str(), errorCode1.value(), errorCode2String.c_str());

			return PC_WRITE_FILE;
		}
	}

} transferCallback;

#define USE_TCP

int main(int argc, char **argv)
{
	printf("A simple client interface for the advanced autopatcher.\n");
	printf("Use DirectoryDeltaTransfer for a simpler version of an autopatcher.\n");
	printf("Difficulty: Intermediate\n\n");

	printf("Client starting...");
	RakNet::SystemAddress serverAddress=RakNet::UNASSIGNED_SYSTEM_ADDRESS;
	RakNet::AutopatcherClient autopatcherClient;
	RakNet::FileListTransfer fileListTransfer;
	autopatcherClient.SetFileListTransferPlugin(&fileListTransfer);
	unsigned short localPort=0;
	if (argc>=6)
	{
		localPort=atoi(argv[5]);
	}
#ifdef USE_TCP
	RakNet::PacketizedTCP packetizedTCP;
	if (packetizedTCP.Start(localPort,1)==false)
	{
		printf("Failed to start TCP. Is the port already in use?");
		return 1;
	}
	packetizedTCP.AttachPlugin(&autopatcherClient);
	packetizedTCP.AttachPlugin(&fileListTransfer);
#else
	RakNet::RakPeerInterface *rakPeer;
	rakPeer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor socketDescriptor(localPort,0);
	rakPeer->Startup(1,&socketDescriptor, 1);
	// Plugin will send us downloading progress notifications if a file is split to fit under the MTU 10 or more times
	rakPeer->SetSplitMessageProgressInterval(10);
	rakPeer->AttachPlugin(&autopatcherClient);
	rakPeer->AttachPlugin(&fileListTransfer);
#endif
	printf("started\n");
	char buff[512];
	if (argc<2)
	{
		printf("Enter server IP: ");
		Gets(buff,sizeof(buff));
		if (buff[0]==0)
			//strcpy(buff, "natpunch.jenkinssoftware.com");
			strcpy(buff, "127.0.0.1");
	}
	else
		strcpy(buff, argv[1]);

#ifdef USE_TCP
	packetizedTCP.Connect(buff,60000,false);
#else
	rakPeer->Connect(buff, 60000, 0, 0);
#endif

	printf("Connecting...\n");
	char appDir[512];
	if (argc<3)
	{
		printf("Enter application directory: ");
		Gets(appDir,sizeof(appDir));
		if (appDir[0]==0)
		{
			auto temp = std::experimental::filesystem::temp_directory_path().u8string();
			if (appDir[0] == 0)
				strcpy(appDir, temp.c_str());
		}
	}
	else
		strcpy(appDir, argv[2]);
	char appName[512];
	if (argc<4)
	{
		printf("Enter application name: ");
		Gets(appName,sizeof(appName));
		if (appName[0]==0)
			strcpy(appName, "TestApp");
	}
	else
		strcpy(appName, argv[3]);

	bool patchImmediately=argc>=5 && argv[4][0]=='1';
	
	if (patchImmediately==false)
	{
		printf("Optional: Enter path to xdelta exe: ");
		std::experimental::filesystem::path input;
		std::string temp;
		std::getline(std::cin, temp);
		input /= temp;
		PATH_TO_XDELTA_EXE = input;
		// https://code.google.com/p/xdelta/downloads/list
		if (PATH_TO_XDELTA_EXE.empty())
		{
#ifdef _WIN32
			if (PATH_TO_XDELTA_EXE.empty())
				PATH_TO_XDELTA_EXE /= "./xdelta3-x86_64-3.0.10.exe";
#else
			if (PATH_TO_XDELTA_EXE.empty())
				PATH_TO_XDELTA_EXE /= "/usr/local/bin/xdelta";
#endif
		}

		if (!PATH_TO_XDELTA_EXE.empty())
		{
			printf("Enter working directory to store temporary files: ");
			std::getline(std::cin, temp);
			WORKING_DIRECTORY = std::experimental::filesystem::path(temp);
			if (WORKING_DIRECTORY.empty())
				WORKING_DIRECTORY = std::experimental::filesystem::temp_directory_path();
		}

		printf("Hit 'q' to quit, 'p' to patch, 'f' to full scan. 'c' to cancel the patch. 'r' to reconnect. 'd' to disconnect.\n");
	}
	else
		printf("Hit 'q' to quit, 'c' to cancel the patch.\n");

	char ch;
	RakNet::Packet *p;
	while (1)
	{
#ifdef USE_TCP
		RakNet::SystemAddress notificationAddress;
		notificationAddress=packetizedTCP.HasCompletedConnectionAttempt();
		if (notificationAddress!=RakNet::UNASSIGNED_SYSTEM_ADDRESS)
		{
			printf("ID_CONNECTION_REQUEST_ACCEPTED\n");
			serverAddress=notificationAddress;
		}
		notificationAddress=packetizedTCP.HasNewIncomingConnection();
		if (notificationAddress!=RakNet::UNASSIGNED_SYSTEM_ADDRESS)
			printf("ID_NEW_INCOMING_CONNECTION\n");
		notificationAddress=packetizedTCP.HasLostConnection();
		if (notificationAddress!=RakNet::UNASSIGNED_SYSTEM_ADDRESS)
			printf("ID_CONNECTION_LOST\n");


		p=packetizedTCP.Receive();
		while (p)
		{
			if (p->data[0]==ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR)
			{
				char buff[256];
				RakNet::BitStream temp(p->data, p->length, false);
				temp.IgnoreBits(8);
				RakNet::StringCompressor::Instance()->DecodeString(buff, 256, &temp);
				printf("ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR\n");
				printf("%s\n", buff);
			}
			else if (p->data[0]==ID_AUTOPATCHER_CANNOT_DOWNLOAD_ORIGINAL_UNMODIFIED_FILES)
			{
				printf("ID_AUTOPATCHER_CANNOT_DOWNLOAD_ORIGINAL_UNMODIFIED_FILES\n");
			}			
			else if (p->data[0]==ID_AUTOPATCHER_FINISHED)
			{
				printf("ID_AUTOPATCHER_FINISHED with server time %f\n", autopatcherClient.GetServerDate());
				double srvDate=autopatcherClient.GetServerDate();
				FILE *fp = fopen("srvDate", "wb");
				fwrite(&srvDate,sizeof(double),1,fp);
				fclose(fp);
			}
			else if (p->data[0]==ID_AUTOPATCHER_RESTART_APPLICATION)
				printf("Launch \"AutopatcherClientRestarter.exe autopatcherRestart.txt\"\nQuit this application immediately after to unlock files.\n");

			packetizedTCP.DeallocatePacket(p);
			p=packetizedTCP.Receive();
		}
#else
		p=rakPeer->Receive();
		while (p)
		{
			if (p->data[0]==ID_DISCONNECTION_NOTIFICATION)
				printf("ID_DISCONNECTION_NOTIFICATION\n");
			else if (p->data[0]==ID_CONNECTION_LOST)
				printf("ID_CONNECTION_LOST\n");
			else if (p->data[0]==ID_CONNECTION_REQUEST_ACCEPTED)
			{
				printf("ID_CONNECTION_REQUEST_ACCEPTED\n");
				serverAddress=p->systemAddress;
			}
			else if (p->data[0]==ID_CONNECTION_ATTEMPT_FAILED)
				printf("ID_CONNECTION_ATTEMPT_FAILED\n");
			else if (p->data[0]==ID_NO_FREE_INCOMING_CONNECTIONS)
				printf("ID_NO_FREE_INCOMING_CONNECTIONS\n");
			else if (p->data[0]==ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR)
			{
				char buff[256];
				RakNet::BitStream temp(p->data, p->length, false);
				temp.IgnoreBits(8);
				RakNet::StringCompressor::Instance()->DecodeString(buff, 256, &temp);
				printf("ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR\n");
				printf("%s\n", buff);
			}
			else if (p->data[0]==ID_AUTOPATCHER_CANNOT_DOWNLOAD_ORIGINAL_UNMODIFIED_FILES)
			{
				printf("ID_AUTOPATCHER_CANNOT_DOWNLOAD_ORIGINAL_UNMODIFIED_FILES\n");
			}
			else if (p->data[0]==ID_AUTOPATCHER_FINISHED)
			{
				printf("ID_AUTOPATCHER_FINISHED with server time %f\n", autopatcherClient.GetServerDate());
				double srvDate=autopatcherClient.GetServerDate();
				FILE *fp = fopen("srvDate", "wb");
				fwrite(&srvDate,sizeof(double),1,fp);
				fclose(fp);
			}
			else if (p->data[0]==ID_AUTOPATCHER_RESTART_APPLICATION)
				printf("Launch \"AutopatcherClientRestarter.exe autopatcherRestart.txt\"\nQuit this application immediately after to unlock files.\n");

			rakPeer->DeallocatePacket(p);
			p=rakPeer->Receive();
		}
#endif

		if (kbhit())
			ch=getch();
		else
			ch=0;

		if (ch=='q')
			break;
		else if (ch=='r')
		{
#ifdef USE_TCP
			packetizedTCP.Connect(buff,60000,false);
#else
			rakPeer->Connect(buff, 60000, 0, 0);
#endif
		}
		else if (ch=='d')
		{
#ifdef USE_TCP
			packetizedTCP.CloseConnection(serverAddress);
#else
			rakPeer->CloseConnection(serverAddress, true);
#endif
		}
		else if (ch=='p' || (serverAddress!=RakNet::UNASSIGNED_SYSTEM_ADDRESS && patchImmediately==true) || ch=='f')
		{
			patchImmediately=false;
			char restartFile[512];
			strcpy(restartFile, appDir);
			strcat(restartFile, "/autopatcherRestart.txt");

			double lastUpdateDate;
			if (ch=='f')
			{
				lastUpdateDate=0;
			}
			else
			{
				FILE *fp = fopen("srvDate", "rb");
				if (fp)
				{
					fread(&lastUpdateDate, sizeof(lastUpdateDate), 1, fp);
					fclose(fp);
				}
				else
					lastUpdateDate=0;
			}

			if (autopatcherClient.PatchApplication(appName, appDir, lastUpdateDate, serverAddress, &transferCallback, restartFile, argv[0]))
			{
				printf("Patching process starting.\n");
			}
			else
			{
				printf("Failed to start patching.\n");
			}
		}
		else if (ch=='c')
		{
			autopatcherClient.Clear();
			printf("Autopatcher cleared.\n");
		}

		RakSleep(30);
	}

	// Dereference so the destructor doesn't crash
	autopatcherClient.SetFileListTransferPlugin(0);

#ifdef USE_TCP
	packetizedTCP.Stop();
#else
	rakPeer->Shutdown(500,0);
	RakNet::RakPeerInterface::DestroyInstance(rakPeer);
#endif
	return 1;
}
