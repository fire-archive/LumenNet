<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ---------------------------
  FileListTransfer Overview
  ---------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Send and receive file(s) more             |
| easily</span>\                                                           |
|                                                                          |
| The FileListTransfer plugin is designed to send a list of files that     |
| have been read into the **FileList** class. It is similar to the         |
| [DirectoryDeltaTransfer](directorydeltatransfer.html) plugin, except     |
| that it doesn't send deltas based on pre-existing files or actually      |
| write the files to disk. It solely handles the networking part of        |
| sending files.                                                           |
|                                                                          |
| Usage:                                                                   |
|                                                                          |
| 1.  Server: Call SetupReceive(...) with the address of a system to allow |
|     a file send, and a **FileListTransferCBInterface** derived callback  |
|     handler to be called as the data arrives.                            |
| 2.  Client: Encode the files you want to send into the                   |
|     **FileList** class.                                                  |
| 3.  Client: Call Send(...) with your **FileList** class instance, a      |
|     user-defined ID to identify this set of files, parameters to pass    |
|     to RakPeerInterface::Send() or TCPInterface::Send(), and a boolean   |
|     indicating if the files should be compressed or not. Compression is  |
|     not very fast, so it's best to leave that off unless bandwidth is at |
|     a premium.                                                           |
+--------------------------------------------------------------------------+

  -------------------
  FileList Overview
  -------------------

+--------------------------------------------------------------------------+
| The FileList class stores a list of files and data, and also contains    |
| utility functions for dealing with the harddrive in general. It was      |
| originally written for the [Autopatcher](autopatcher.html), but can be   |
| used for your own purposes as well.                                      |
|                                                                          |
| See FileList.h for a complete description of all functions and           |
| parameters.                                                              |
|                                                                          |
| /// Add all the files at a given directory.\                             |
| void AddFilesFromDirectory(const char \*applicationDirectory, const char |
| \*subDirectory, bool writeHash, bool writeData, bool recursive, unsigned |
| char context);                                                           |
|                                                                          |
| /// Deallocate all memory\                                               |
| void Clear(void);                                                        |
|                                                                          |
| /// Write all encoded data into a bitstream\                             |
| void Serialize(RakNet::BitStream \*outBitStream);                        |
|                                                                          |
| /// Read all encoded data from a bitstream. Clear() is called before     |
| deserializing.\                                                          |
| bool Deserialize(RakNet::BitStream \*inBitStream);                       |
|                                                                          |
| /// Given the existing set of files, search applicationDirectory for the |
| same files.\                                                             |
| /// For each file that is missing or different, add that file to         |
| missingOrChangedFiles. Note: the file contents are not written, and only |
| the hash if written if alwaysWriteHash is true\                          |
| void ListMissingOrChangedFiles(const char \*applicationDirectory,        |
| FileList \*missingOrChangedFiles, bool alwaysWriteHash, bool             |
| neverWriteHash);                                                         |
|                                                                          |
| /// Return the files that need to be written to make \\a input match     |
| this current FileList.\                                                  |
| void GetDeltaToCurrent(FileList \*input, FileList \*output, const char   |
| \*dirSubset, const char \*remoteSubdir);                                 |
|                                                                          |
| /// Assuming FileList contains a list of filenames presumably without    |
| data, read the data for these filenames\                                 |
| void PopulateDataFromDisk(const char \*applicationDirectory, bool        |
| writeFileData, bool writeFileHash, bool removeUnknownFiles);             |
|                                                                          |
| /// Write all files to disk, prefixing the paths with                    |
| applicationDirectory\                                                    |
| void WriteDataToDisk(const char \*applicationDirectory);                 |
|                                                                          |
| /// Add a file, given data already in memory\                            |
| void AddFile(const char \*filename, const char \*data, const unsigned    |
| dataLength, const unsigned fileLength, unsigned char context);           |
|                                                                          |
| /// Add a file, reading it from disk\                                    |
| void AddFile(const char \*filepath, const char \*filename, unsigned char |
| context);                                                                |
|                                                                          |
| /// Delete all files stored in the file list\                            |
| void DeleteFiles(const char \*applicationDirectory);                     |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [Delta Directory Transfer](directorydeltatransfer.html)\                 |
+--------------------------------------------------------------------------+


