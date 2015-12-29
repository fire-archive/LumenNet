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
#include "Kbhit.h"

#include "GetTime.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "StringCompressor.h"
#include "FileListTransfer.h"
#include "FileList.h" // FLP_Printf
#include "PacketizedTCP.h"
#include "Gets.h"
#ifdef _WIN32
#include <filesystem>
#else
#include <experimental/filesystem>
#endif

// Server only includes
#include "AutopatcherServer.h"
// Replace this repository with your own implementation if you don't want to use PostgreSQL
#include "AutopatcherPostgreRepository.h"
#include <iostream>

#ifdef _WIN32
#include "WindowsIncludes.h" // Sleep
#else
#include <unistd.h> // usleep
#endif

#define USE_TCP
#define LISTEN_PORT 60000
#define MAX_INCOMING_CONNECTIONS 128

// The default AutopatcherPostgreRepository2 uses bsdiff which takes too much memory for large files.
// I override MakePatch to use XDelta in this case
class AutopatcherPostgreRepository2_WithXDelta : public RakNet::AutopatcherPostgreRepository2
{
public:
	AutopatcherPostgreRepository2_WithXDelta(std::experimental::filesystem::path& workingDirectory, std::experimental::filesystem::path& pathToXdelta)
		: workingDirectory(workingDirectory), pathToXdelta(pathToXdelta)
	{
	}

private:
	int MakePatch(const char* oldFile, const char* newFile, char** patch, unsigned int* patchLength, int* patchAlgorithm)
	{
		FILE* fpOld = fopen(oldFile, "rb");
		fseek(fpOld, 0, SEEK_END);
		int contentLengthOld = ftell(fpOld);
		FILE* fpNew = fopen(newFile, "rb");
		fseek(fpNew, 0, SEEK_END);
		int contentLengthNew = ftell(fpNew);

		if ((contentLengthOld < 33554432 && contentLengthNew < 33554432) || pathToXdelta.empty())
		{
			// Use bsdiff, which does a good job but takes a lot of memory based on the size of the file
			*patchAlgorithm = 0;
			bool b = MakePatchBSDiff(fpOld, contentLengthOld, fpNew, contentLengthNew, patch, patchLength);
			fclose(fpOld);
			fclose(fpNew);
			return b;
		}
		else
		{
			*patchAlgorithm = 1;
			fclose(fpOld);
			fclose(fpNew);

			std::string buff;
			RakNet::TimeUS time = RakNet::GetTimeUS();
			buff = time;

			// Invoke xdelta
			// See https://code.google.com/p/xdelta/wiki/CommandLineSyntax
			std::string commandLine;
			commandLine = "-f -s " + std::string(oldFile) + " " + std::string(newFile) + " patchServer_" + std::string(buff) + ".tmp";

			std::string shellExecute;
			shellExecute = "cd " + workingDirectory.string() + " && " + pathToXdelta.string() + commandLine;
			system(shellExecute.c_str());
			//ShellExecute(NULL, "open", PATH_TO_XDELTA_EXE, commandLine, WORKING_DIRECTORY, SW_SHOWNORMAL);

			std::experimental::filesystem::path pathToPatch;
			pathToPatch = workingDirectory;
			pathToPatch = pathToPatch.concat("patchServer_" + buff + ".tmp");
			auto pathToPatchU8 = pathToXdelta.u8string();
			// r+ instead of r, because I want exclusive access in case xdelta is still working
			FILE* fpPatch = fopen(pathToPatchU8.c_str(), "r+b");
			RakNet::TimeUS stopWaiting = time + 60000000 * 5;
			while (fpPatch == 0 && RakNet::GetTimeUS() < stopWaiting)
			{
				RakSleep(1000);
				fpPatch = fopen(pathToPatchU8.c_str(), "r+b");
			}
			if (fpPatch == 0)
				return false;
			fseek(fpPatch, 0, SEEK_END);
			*patchLength = ftell(fpPatch);
			fseek(fpPatch, 0, SEEK_SET);
			*patch = (char*)rakMalloc_Ex(*patchLength, _FILE_AND_LINE_);
			fread(*patch, 1, *patchLength, fpPatch);
			fclose(fpPatch);

			int unlinkRes = std::experimental::filesystem::remove(pathToPatch);
			while (unlinkRes != 0 && RakNet::GetTimeUS() < stopWaiting)
			{
				RakSleep(1000);
				unlinkRes = std::experimental::filesystem::remove(pathToPatch);
			}
			if (unlinkRes != 0)
				printf("\nWARNING: unlink %s failed.\nerr=%i (%s)\n", pathToPatchU8.c_str(), errno, strerror(errno));

			return true;
		}
	}
	std::experimental::filesystem::path workingDirectory;
	std::experimental::filesystem::path pathToXdelta;
};

int main(int argc, char** argv)
{
	printf("Server starting... ");
	std::experimental::filesystem::path workingDirectory;
	std::experimental::filesystem::path pathToXdelta;
	RakNet::AutopatcherServer autopatcherServer;
	// RakNet::FLP_Printf progressIndicator;
	RakNet::FileListTransfer fileListTransfer;
	static const int workerThreadCount = 4;			// Used for checking patches only
	static const int sqlConnectionObjectCount = 32; // Used for both checking patches and downloading
	AutopatcherPostgreRepository2_WithXDelta connectionObject[sqlConnectionObjectCount]{
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta},
		{workingDirectory, pathToXdelta}};
	RakNet::AutopatcherRepositoryInterface* connectionObjectAddresses[sqlConnectionObjectCount];
	for (int i = 0; i < sqlConnectionObjectCount; i++)
		connectionObjectAddresses[i] = &connectionObject[i];
	//	fileListTransfer.AddCallback(&progressIndicator);
	autopatcherServer.SetFileListTransferPlugin(&fileListTransfer);
	// PostgreSQL is fast, so this may not be necessary, or could use fewer threads
	// This is used to read increments of large files concurrently, thereby serving users downloads as other users read from the DB
	fileListTransfer.StartIncrementalReadThreads(sqlConnectionObjectCount);
	autopatcherServer.SetMaxConurrentUsers(MAX_INCOMING_CONNECTIONS); // More users than this get queued up
	RakNet::AutopatcherServerLoadNotifier_Printf loadNotifier;
	autopatcherServer.SetLoadManagementCallback(&loadNotifier);
#ifdef USE_TCP
	RakNet::PacketizedTCP packetizedTCP;
	if (packetizedTCP.Start(LISTEN_PORT, MAX_INCOMING_CONNECTIONS) == false)
	{
		printf("Failed to start TCP. Is the port already in use?");
		return 1;
	}
	packetizedTCP.AttachPlugin(&autopatcherServer);
	packetizedTCP.AttachPlugin(&fileListTransfer);
#else
	RakNet::RakPeerInterface* rakPeer;
	rakPeer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor socketDescriptor(LISTEN_PORT, 0);
	rakPeer->Startup(MAX_INCOMING_CONNECTIONS, &socketDescriptor, 1);
	rakPeer->SetMaximumIncomingConnections(MAX_INCOMING_CONNECTIONS);
	rakPeer->AttachPlugin(&autopatcherServer);
	rakPeer->AttachPlugin(&fileListTransfer);
#endif
	printf("started.\n");

	printf("Enter database password:\n");
	const int kMaxPasswordSize = 128;
	const int kMaxConnectionStringSize = 256;
	char connectionString[kMaxConnectionStringSize], password[kMaxPasswordSize];
	char username[kMaxConnectionStringSize];
	strcpy(username, "postgres");
	fgets(password, kMaxPasswordSize, stdin);
	if (password[0] == 0)
		strcpy(password, "aaaa");
	strcpy(connectionString, "user=");
	strcat(connectionString, username);
	strcat(connectionString, " password=");
	strcat(connectionString, password);
	for (int conIdx = 0; conIdx < sqlConnectionObjectCount; conIdx++)
	{
		if (connectionObject[conIdx].Connect(connectionString) == false)
		{
			printf("Database connection failed.\n");
			return 1;
		}
	}

	printf("Database connection suceeded.\n");
	printf("Starting threads\n");
	// 4 Worker threads, which is CPU intensive
	// A greater number of SQL connections, which read files incrementally for large downloads
	autopatcherServer.StartThreads(workerThreadCount, sqlConnectionObjectCount, connectionObjectAddresses);
	autopatcherServer.CacheMostRecentPatch(0);
	// autopatcherServer.SetAllowDownloadOfOriginalUnmodifiedFiles(false);
	printf("System ready for connections\n");

	// https://code.google.com/p/xdelta/downloads/list
	printf("Optional: Enter path to xdelta.exe: ");
	std::string input;
	std::getline(std::cin, input);
	pathToXdelta /= input;

#ifdef _WIN32
	if (pathToXdelta.empty())
		pathToXdelta /= "./xdelta3-x86_64-3.0.10.exe";
#else
	if (pathToXdelta.empty())
		pathToXdelta /= "/usr/local/bin/xdelta";
#endif

	if (!pathToXdelta.empty())
	{
		printf("Enter working directory to store temporary files: ");
		std::string input;
		std::getline(std::cin, input);
		std::experimental::filesystem::path temp;
		temp /= input;
		workingDirectory = temp;
		if (!workingDirectory.empty())
			workingDirectory = std::experimental::filesystem::temp_directory_path();
	}
	workingDirectory = std::experimental::filesystem::canonical(workingDirectory);
	printf("(D)rop database\n(C)reate database.\n(A)dd application\n(U)pdate revision.\n(R)emove application\n(Q)uit\n");

	char ch;
	RakNet::Packet* p;
	while (1)
	{
#ifdef USE_TCP
		RakNet::SystemAddress notificationAddress;
		notificationAddress = packetizedTCP.HasCompletedConnectionAttempt();
		if (notificationAddress != RakNet::UNASSIGNED_SYSTEM_ADDRESS)
			printf("ID_CONNECTION_REQUEST_ACCEPTED\n");
		notificationAddress = packetizedTCP.HasNewIncomingConnection();
		if (notificationAddress != RakNet::UNASSIGNED_SYSTEM_ADDRESS)
			printf("ID_NEW_INCOMING_CONNECTION\n");
		notificationAddress = packetizedTCP.HasLostConnection();
		if (notificationAddress != RakNet::UNASSIGNED_SYSTEM_ADDRESS)
			printf("ID_CONNECTION_LOST\n");

		p = packetizedTCP.Receive();
		while (p)
		{
			packetizedTCP.DeallocatePacket(p);
			p = packetizedTCP.Receive();
		}
#else
		p = rakPeer->Receive();
		while (p)
		{
			if (p->data[0] == ID_NEW_INCOMING_CONNECTION)
				printf("ID_NEW_INCOMING_CONNECTION\n");
			else if (p->data[0] == ID_DISCONNECTION_NOTIFICATION)
				printf("ID_DISCONNECTION_NOTIFICATION\n");
			else if (p->data[0] == ID_CONNECTION_LOST)
				printf("ID_CONNECTION_LOST\n");

			rakPeer->DeallocatePacket(p);
			p = rakPeer->Receive();
		}
#endif

		if (kbhit())
		{
			ch = getch();
			if (ch == 'q')
				break;
			else if (ch == 'c')
			{
				if (connectionObject[0].CreateAutopatcherTables() == false)
					printf("%s", connectionObject[0].GetLastError());
			}
			else if (ch == 'd')
			{
				if (connectionObject[0].DestroyAutopatcherTables() == false)
					printf("%s", connectionObject[0].GetLastError());
			}
			else if (ch == 'a')
			{
				printf("Enter application name to add: ");
				char appName[512];
				Gets(appName, sizeof(appName));
				if (appName[0] == 0)
					strcpy(appName, "TestApp");

				if (connectionObject[0].AddApplication(appName, username) == false)
					printf("%s", connectionObject[0].GetLastError());
				else
					printf("Done\n");
			}
			else if (ch == 'r')
			{
				printf("Enter application name to remove: ");
				char appName[512];
				Gets(appName, sizeof(appName));
				if (appName[0] == 0)
					strcpy(appName, "TestApp");

				if (connectionObject[0].RemoveApplication(appName) == false)
					printf("%s", connectionObject[0].GetLastError());
				else
					printf("Done\n");
			}
			else if (ch == 'u')
			{
				printf("Enter application name: ");
				char appName[512];
				Gets(appName, sizeof(appName));
				if (appName[0] == 0)
					strcpy(appName, "TestApp");

				printf("Enter application directory: ");
				char appDir[512];
				Gets(appDir, sizeof(appDir));
				auto temp = std::experimental::filesystem::temp_directory_path().u8string();
				if (appDir[0] == 0)
					strcpy(appDir, temp.c_str());

				if (connectionObject[0].UpdateApplicationFiles(appName, appDir, username, 0) == false)
				{
					printf("%s", connectionObject[0].GetLastError());
				}
				else
				{
					printf("Update success.\n");
					autopatcherServer.CacheMostRecentPatch(appName);
				}
			}
		}

		RakSleep(30);
	}

#ifdef USE_TCP
	packetizedTCP.Stop();
#else
	RakNet::RakPeerInterface::DestroyInstance(rakPeer);
#endif

	return 0;
}
