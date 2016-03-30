<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -----------------------------------
  Directory Delta Transfer Overview
  -----------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Send file differences between directories |
| automatically</span>\                                                    |
| \                                                                        |
| DirectoryDeltaTransfer.h is useful if you allow user-moddable content.   |
| For example, if each server has a /skins directory, you could run this   |
| plugin to upload that directory to the clients. Each client that does    |
| not already have a particular skin will get it. You will get download    |
| progress notifications via a user-supplied callback.                     |
| DirectoryDeltaTransfer relies on the FileListTransfer plugin to actually |
| transmit hte files.                                                      |
|                                                                          |
| Usage:                                                                   |
|                                                                          |
| 1.  Attach the plugin and connect to the remote system                   |
| 2.  Server and client: Call                                              |
|     directoryDeltaTransfer.SetFileListTransferPlugin(&fileListTransfer); |
| 3.  Server: set the application directory: <span                         |
|     class="style1">` directoryDeltaTransfer.SetApplicationDirectory("c:\ |
| myGame");`</span>                                                        |
| 4.  Server: set the download directory: <span                            |
|     class="RakNetCode">directoryDeltaTransfer.AddUploadsFromSubdirectory |
| ("skins");</span>                                                        |
| 5.  Client: to download call: <span                                      |
|     class="RakNetCode">directoryDeltaTransfer.DownloadFromSubdirectory(" |
| skins",                                                                  |
|     "downloaded\\skins", true, serverAddress, &transferCallback,         |
|     HIGH\_PRIORITY, 0);</span>                                           |
| 6.  Client: Wait for the callback member <span                           |
|     class="RakNetCode">OnFileProgress()</span>. When                     |
|     onFileStruct-&gt;fileIndex is equal to onFileStruct-&gt;setCount     |
|     this download is done.                                               |
|                                                                          |
| For full details on all parameters and other available functions, see    |
| the header file DirectoryDeltaTransfer.h and the sample at               |
| *Samples/DirectoryDeltaTransfer*                                         |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  --------------------------------------------
  [Index](index.html)\
  [FileListTransfer](filelisttransfer.html)\
  --------------------------------------------


