![Oculus VR, Inc.](RakNetLogo.jpg)\
\
  ---------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Revision Log
  ---------------------------------------------------

+--------------------------------------------------------------------------+
|     1.00 Initial release                                                 |
|     1.01 Updated documentation                                           |
|     1.02 Fixed a rare thread related crash with large numbers of players |
| .  Improved reliable packet performance by 30%                           |
|     1.03 Increased demo player support to 31.  Improved performance unde |
| r high server loads.  Added security parameter to server and improved pa |
| cket encryption.  Allowed specification of domain name for client connec |
| tions.  Fixed rare crash with sending multiple large packets at the same |
|  time.  Decreased overhead for all packets.                              |
|     1.031 Fixed a bug with sending more than 255 ordered packets         |
|     1.032 Added master server and master client support.  Added GetConne |
| ctionTime method to both the server and the client.  Added port to GetPl |
| ayerIPFromID                                                             |
|     1.04 Modified source code to build under Unix / Linux.  Requires a s |
| ource code license to make builds.                                       |
|     1.041 IO completion port implemented for outgoing packets to avoid d |
| elays caused by sendto blocking under high loads.  Fixed two minor bugs  |
| related to high load processing.                                         |
|     1.042 Fixed a bug where timestamps were not updated quickly enough a |
| fter connecting                                                          |
|     1.043 Updated documentation, source code release for all versions.   |
| Removed demo player limit.  Added DemonBattle game to examples           |
|     1.044 Added a couple of simple access functions and made the templat |
| es compile on newer versions.                                            |
|     1.1 First beta leading to version 2.0.  Partial support for bitstrea |
| ms and support for automatic variable synchronization.                   |
|     1.2 Second beta leading to version 2.0.  Full support for bitstreams |
| , rewritten reliability layer, and the compression layer added.          |
|     1.3 Third beta leading to version 2.0.  Remote procedure calls imple |
| mented                                                                   |
|     1.4 Improved Linux compatibility.  Fixed a problem on Windows where  |
| threads didn't terminate even with an explict call.  Removed signaled ev |
| ents.  Thanks to Michael Long for helping me test this.                  |
|     1.401 Fixed declaring variables inside for loops by moving them to t |
| he top of the scope.                                                     |
|     1.402 Fixed two bugs concerning "orderingList" in the reliability la |
| yer.  Thanks to Jeremy Stieglitz for providing the excellent bug report. |
|     1.403 Added _INTERNET_SIMULATOR define.  Various bug and memory leak |
|  fixes.  I now close the SocketLayer thread upon server and/or client di |
| sconnection.                                                             |
|     1.404 Fixed a bug with reused data stream corruption (such as with t |
| he compression layer) and large packets never being sent in a frame unde |
| r extreme high stress conditions.  Added the automatic memory synchroniz |
| ation sample.  Added sample projects files (sorry, visual studio.net onl |
| y).                                                                      |
|     1.405 Players connecting from the same IP/Port when that IP/Port is  |
| already considered a connected player will reconnect rather than have th |
| e connection request ignored.                                            |
|     1.406 Rerelease of 1.405 with a bug fix                              |
|     1.407 Ping time relaying fixed, compression and timestamps fixed wit |
| h broadcasting, RPC has full parameter set, other small fixes.           |
|     1.408 Compressed / encrypted the header portion of RPC calls.  SetSt |
| aticClientData, SetStaticServerData, GetStaticClientData, GetStaticServe |
| rData now deal with raw data (BitStreams) and no longer internally deal  |
| with the actual structure the end user users to hold the data.  Enumerat |
| ion data code sample and Hangman game sample added.                      |
|     1.409 Fixed a bug where ordered packets would be long delayed during |
|  data overruns.  Added the BitStream sample.                             |
|     1.41 Added a parameter for the bitstream class to point to a copy of |
|  the data passed to its constructor rather than always making a copy.    |
|     1.411 Fixed a bug with the last partial byte being pre-shifted when  |
| sending bitstream data with RPC                                          |
|     1.42 SetPassword method added to both the client and the server. Upd |
| ated documentation. Improved performance.                                |
|     1.43 Implemented IO completion ports.  Numerous bug fixes.           |
|     1.431 Fixed a bug with the server rejecting clients without a passwo |
| rd when the server didn't use one itself.  Reintegrated Unix compatibili |
| ty.                                                                      |
|     1.432 Increased maximum split packet size from about 1.2 megs to abo |
| ut 32 megs.  Improved flow control.  Fixed several Unix problems.        |
|     1.44 Huge performance increase and further Unix fixes.  Thanks to Ed |
|  Williams for pointing out the Unix problems and the bottleneck.  Added  |
| the SetMTUSize method.                                                   |
|     1.441 Better mutex use resulting in a slight performance increase.   |
| Several potential deadlocks fixed.                                       |
|     1.442 Huge recieve bottleneck fixed, resulting in an 80X increase in |
|  the rate of receipt of user packets!                                    |
|     1.443 Numerous optimizations, especially in regards to packet rate a |
| nd reliable packet types.  This is roughly a further 5X to 10X speed imp |
| rovement. Also fixed an unreported bug in the compression layer.         |
|     1.444 Implemented a new windowing algorithm. Further speed improveme |
| nts.  Added the function GetTransmittedFrameCount to the client and serv |
| er.                                                                      |
|     1.445 Minor bug fixes.  Reduced memory allocations and deallocations |
|  via pools, improving speed consistency.  Removed unnecessary memory all |
| ocations and copies in the user interface thread, decreasing processing  |
| time.  Improved windowing algorithm.  #ifdef'ed most of the asserts so U |
| nix would not run them in release.  Changed all examples to use regular  |
| priority threads.                                                        |
|     1.446 Minor efficiency improvements. Fixed bug with sending packets  |
| over 3 megabytes and large files using SHA-1 security headers.           |
|     1.45 Fixed a problem with pings.  Improved timestamp accuracy.       |
|     1.5 Put data structures inside namespace BasicDataStructures.  Added |
|  VC6 projects.  Updated DemonBattle to use the newest RakNet version.    |
|     1.501 Changed the Queue and List templates to work for VC6 users.    |
|     1.51 Added RakVoice and a sample that uses RakVoice.  Added GetMTUSi |
| ze method.  Improved automatic memory synchronization.  Improved timesta |
| mp accuracy (thanks to Chris Taylor). linuxBuild.tgz included in the bas |
| e directory (thanks to NathanH).  Fixed bug with reconnecting clients th |
| at the server thinks is still active.                                    |
|     1.52 The high priority thread boolean was replaced with an int.  0 f |
| or regular priority, 1 for high priority, 2 for ultra high priority.     |
|     2.0 Implemented RakPeer and changed RakServer and RakClient to use i |
| t.  Numerous interface changes.  See 2.0UpgradeInstructions.txt for conv |
| ersion instructions.                                                     |
|     2.001 Removed the const qualifier when you read bitstreams.          |
|     2.002 Fixed using domain names with clients                          |
|     2.003 Removed feedback loop test code with RakVoice                  |
|     2.01 Added ID_REMOTE_EXISTING_CONNECTION (client only).  This is sen |
| t to clients that have just connected to a server, one message per exist |
| ing client on the network.  Also fixed a bug where static data was not s |
| ent to new clients from existing clients.                                |
|     2.011 Specifying UNASSIGNED_PLAYER_ID for SendStaticData wasn't broa |
| dcasting when it should have been.                                       |
|     2.012 Fixed a case where ID_REMOTE_CONNECTION_LOST was reported inco |
| rrectly.  THe connection was not actually lost, just the report was wron |
| g.                                                                       |
|     2.013 Fixed ID_REMOTE_EXISTING_CONNECTION.                           |
|     2.1 Added distributed objects.  General update to and improved the s |
| tructure of the documentation.  Adjusted Sleep times in RakPeer.         |
|     2.11 Added the ability to ping systems we are not connected to from  |
| the client and peer.                                                     |
|     2.12 Repackaged everything to be much more sensible and fixed DemonB |
| attle so it would compile with the newest version of DirectX.            |
|     2.121 Fixed a bug with timestamps.  Added timestamping sample.       |
|     2.122 Fixed a client bug with broadcasted remote pings.  Fixed a cli |
| ent bug where it wouldn't send when using IO completion ports.           |
|     2.13 The RPC function can now handle timestamps.  Fixed several bugs |
|  with static data relaying between the client and server.  Dropped autom |
| atic memory synchronization.                                             |
|     2.131 Moved the global REGISTER_DISTRIBUTED_NETWORK_OBJECT code to m |
| ain()                                                                    |
|     2.132 Added MasterServerAndClient sample project to clarify how the  |
| Master Server works.  Also made a few changes to the interface for it.   |
|     2.133 Made more compatible with Dev-CPP.                             |
|     2.2 Added autopatcher.  Added tutorial. Fixed bug where ID_NO_FREE_I |
| NCOMING_CONNECTIONS wasn't coming up.  Removed file size restriction for |
|  a single packet.                                                        |
|     2.201 Changed the data structure classes to compile on Borland.  Fix |
| ed a copy/paste bug with the DistributedNetworkObjectHeader when using 6 |
|  elements.                                                               |
|     2.21 Fixed a bug with the autopatcher sending the full file even whe |
| n compressed.  Added the concept of client update ownership to the Distr |
| ibuted Network Object system.  Changed chat example to use separate clie |
| nt and servers.  Added the string compressor class, so you can write com |
| pressed strings to bitstreams. Rewrite of the master server.             |
|     2.22 Increased default list and queue allocation sizes to avoid real |
| locations. Corrected oversight where the master client was not pinging s |
| ervers. Added ability to add runtime synchronized variables to the DNO.  |
|     2.221 Fixed memory leaks with the DNO system. Implemented automatic  |
| ban lists.                                                               |
|     2.23 Security updated.  Added ID_RSA_PUBLIC_KEY_MISMATCH. Added Init |
| ializeSecurity.  Added DisableSecurity.  Removed secured parameter from  |
| Send.                                                                    |
|     2.231 Improved Linux compatibility.                                  |
|     2.232 Added DNO functions ReadCreationData, WriteCreationData.  Repl |
| aced the RSA code with faster stuff.                                     |
|     2.233 Improved VC6 compatibility with the RSA code.  Updated the sys |
| tem overview documentation.  Put the BitStream class in the RakNet names |
| pace.                                                                    |
|     2.234 Improved VC6 compatibility with the RSA code again.            |
|     2.24 Eliminated one of two threads greatly improving performance.  F |
| ixed a bug with packetloss reporting and reduced by 10X the mandatory de |
| lay with reliable packet resends.                                        |
|     2.241 Improved flow control algorithm                                |
|     2.25 Massive performance increase by rearranging threaded calls and  |
| eliminating related mutexes - Roughly 25X faster.  Added DroppedConnecti |
| onTest.  Renamed FlowControl to FlowControlTest.                         |
|     2.26 Order of magnitude throughput and performance increase.  Added  |
| loopback performance test project.  Added RakNetStatistics.  Added syste |
| m priority level.  Added wait timer to disconnect and close connections. |
|     2.261 Renamed getTime RakNetGetTime.  Changed the high priority bool |
|  for the client and server to a sleep timer.  Added stats, samples, and  |
| secure connections section to help.  Fixed linux builds.                 |
|     2.262 Fixed a bug when sending partial bytes with the BitStream clas |
| s when using RPC.  Fixed a bug where the huffman tree pointer was not se |
| t to 0 in the string compressor constructor.                             |
|     2.263 Fixed secure connections. Put in a playerIndex member to the P |
| acket struct (backwards compatiblity).  Fixed disconnection messages not |
|  showing up.  Fixed rapidly changing who you connect to.  Moved RPC call |
| s into the user thread space where they belong(oops!).                   |
|     2.27 Using DNO, clients now know the ClientOwnerID so you can tell w |
| ho made an object. Split packets can be sent unreliably.  Added server q |
| uery function for LAN broadcast discovery.                               |
|     2.271 Minor Linux fixes.                                             |
|     2.272 Fixed a stupid mistake with the LAN discovery.                 |
|     2.273 Added the reliable ordered test project.                       |
|     2.274 Fixed a cut and paste error with timestamps.  Thanks to Jarno  |
| for catching it.                                                         |
|     2.28 Added the ability to run RakNet single threaded.  Use -1 for th |
| e sleep timer to do this.                                                |
|     2.29 Changed to an adaptive thread utilization model which works in  |
| conjunction with the user thread to ensure consistent responsiveness wit |
| h fewer context switches and less overhead.                              |
|     2.291 Call OnDistributedObjectCreation when an object is created loc |
| ally by the server                                                       |
|     2.292 Improved adapative thread takeover timers.  Improved responsiv |
| eness of ID_DISCONNECTION_NOTIFICATION packets.                          |
|     2.293 Temporary disabled adapative threading due to problems under h |
| igh loads.                                                               |
|     2.3 Improved client file verification sample.  Renamed streams to ch |
| annels.                                                                  |
|     2.301 Can pass 0 for the data for RPC.  Minor Linux stuff.           |
|     2.302 New data structures from Giblet.  Fixed a bug with the reliabl |
| e ordered test.                                                          |
|     2.303 Fixed BigTypes.h for the latest version of gcc.                |
|     2.304 Added AllowConnectionResponseIPMigration.  Fixed switched nami |
| ng of p,q,e,n for RSA keys.  Fixed chat example client to show port unre |
| achable message properly.                                                |
|     2.305 Implemented NAT punch-through support via the master server. A |
| dded functions SetOfflinePingResponse and AdvertiseSystem.  Fixed incorr |
| ect naming of public key encryption variables.                           |
|     2.306 Added an assert against passing a memory size of 0 to Synchron |
| izeMemory.  Fixed a crash when calling RPC with an empty data string.    |
|     2.31 Fixed bug in SynchronizeMemory for distributed network objects. |
|     2.311 Servers will no longer send back to the sending client for dis |
| tributed network object updates. Fixed a bug with ID_RECEIVED_STATIC_DAT |
| A on the server.  Thanks whitlark!                                       |
|     2.32 Replaced Sleep with WaitForSingleObject on a timer (Windows onl |
| y) if you define _WIN32_WINNT=0x0400 or higher.  Also fixed a problem wi |
| th passwords.                                                            |
|     2.33 Now includes DOxygen commenting.  Thanks for Dalfy for doing th |
| is.                                                                      |
|     2.331 Fix not detecting socket errors.  Thanks to Dong-Yeon Hwang    |
|     2.332 Reverted the simple mutex class to actually use a mutex rather |
|  than a critical section, since the critical section gives much worse pe |
| rformance                                                                |
|     2.333 AMD 64 fixes.  Changed back to Critical Section. Although the  |
| responsiveness is worse, it threads better.                              |
|     2.4 Make duplicate packet tracking memory dynamic, reducing average  |
| memory use by 25X. Fixed bug with secure connections not responding to o |
| ut of order replies. Cirilo Bernardo made the BitStream class and most t |
| ests endian complaint. Fixed handling ordered packets that arrived more  |
| than 2 out of order. Fixed formatting broken by a contributor. Fixed res |
| end queue counting "Holes" towards the overall size, blocking sends if a |
|  single packet was lost with subsequent packets not lost.                |
|     2.401 Fixed contributor bug causing the first PlayerIndex to use an  |
| invalid value on the client.                                             |
|     2.402 Fixed a rare case where if a player disconnected and another p |
| layer connected right away you could still read leftover packets from th |
| e disconnected player.                                                   |
|     2.41 Order of magnitude performance improvement. Reduced memory requ |
| irement by about 25%. Added plugin system, with a fully connected mesh p |
| lugin. Fixed bug with not detecting duplicate packets when the packet co |
| unter wrapped.                                                           |
|     2.411 Fixed lost connection being reported if no data sent by the us |
| er for 10 seconds.                                                       |
|     2.412 Fixed data not copied when switching from the stack to the hea |
| p in the bitstream.                                                      |
|     2.413 Fixed minor memory leak.                                       |
|     2.414 Renamed Queue.h to RakNetQueue.h to fix DevCPP compile errors. |
|   Fixed memory corruption when generating frequency tables.  Made RPC ca |
| lls more efficient - now use less than 1 extra byte after the first call |
| .  Got AdvertiseSystem and offline pings working again.  Got compression |
|  working.                                                                |
|     2.415 Added parameter to RPC to indicate which system is calling it. |
|  Fixed various memory leaks and memory corruptions. Fixed getting invali |
| d split packet data when doing user sends before the connection process  |
| was complete. Fixed buffer overrun vulnerability with split packets. Fix |
| ed rare crash when calling GetStatistics while shutting down at the same |
|  time. Added ComprehensiveTest project. Fixed bug with timedstamped RPCs |
|  not updating timestamps.                                                |
|     2.416 Fixed secure connections                                       |
|     2.417 Reorganized connection process to prevent sends from undetecte |
| d dropped connections reaching new connections from the same player.  Ch |
| anged RPC header to take a structure (Sorry!).  Added automatic memory s |
| ynchronization message handler.  Added class member RPC calls.  Added ab |
| ility to pass data with Advertise System. Re-fixed memory leak in Array  |
| class. No longer include DemonBattle sample to cut down on download size |
| .                                                                        |
|     2.418 Made changes so it would compile under DevCPP and hopefully Li |
| nux.                                                                     |
|     2.419 Replaced AES128.h/.cpp with Rijndael.h/Rijndael.cpp to hopeful |
| ly be different-endian portable.  Updated NetworkIDGenerator so you can  |
| include it as a member object to generate IDs rather than inheritance.   |
|     2.42 Bunch of minor changes thanks to pinniped. Also a preliminary v |
| ersion of my data replication plugin.                                    |
|     2.43 Added PacketLogger plugin. Renamed MessageHandlerInterface Plug |
| inInterface. Renamed DataReplication DataReplicatorTest. Updated Doxygen |
|  documentation. Revamped DataReplicator plugin (work in progress).       |
|     2.431 Added HelloWorld video tutorial.  Revised DataReplication syst |
| em to where it's stable enough to release without a warning.  Depreciate |
| d DistributedNetworkObject class and sample, which is now superceded by  |
| the DataReplication system.                                              |
|     2.432 Improved flow control, especially for file transfers. Upgraded |
|  zlib to 1.2.3. Added KBits/sec for statistics. Improved release perform |
| ace for file transfers. Added Write and Read functions to bitstream for  |
| matrices, vectors, and quaternions. Added current time parameter to data |
|  replicator memory callback (because calling RakNet::GetTime is slow).   |
|     2.44 Added WriteDelta and WriteCompressedDelta to BitStream class.   |
| Changed BitStream class to use template and template specialization for  |
| native types.  Bitstreams can now read and write PlayerIDs directly.  Ad |
| ded replyFromTarget parameter to RPC so you can now use RPC as a blockin |
| g function that takes a reply from a remote system.  Improved performanc |
| e of SingleProducerConsumer class and fixed a small chance of overrun or |
|  underruns on multiprocessor systems. Improved documentation for DataRep |
| licatorSystem. Clarified ObjectMemberRPC example.  Replaced critical sec |
| tion lock on incoming packet queue with a single producer consumer, impr |
| oving read throughput rate by about 200%.                                |
|     2.444 Updated all header file documentation for Doxygen.  Tweaks to  |
| the data replicator system.                                              |
|     2.45 Fix Linux compatibility.  Simplified data replicator by removin |
| g property flags. Increased size of OrderingIndexType to unsigned short  |
| so you can reorder more than 256 out-of-order ordered packets on the sam |
| e channel at a time.  This fixes the rare bug report where ordered packe |
| ts arrive out of order due to extreme send rates with high packetloss.   |
|     2.451 Fixed bug where dropped connections were not detected as long  |
| as you kept sending to the dropped system.  WriteVector, etc. in the Bit |
| Stream class can now take doubles as well as floats.  Fixed an invalid a |
| ssert when passing 0 to the fully connected mesh as the password.        |
|     2.452 Fixed not detecting dropped connections when only one packet w |
| as being resent.                                                         |
|     2.453 Improve template compatibility.                                |
|     2.454 Master server / Master client now uses Plugin interface. Fixed |
|  bug that appeared on Linux where out of older order packets were incorr |
| ectly treated as duplicate and dropped.  Same fix reduces memory usage b |
| y about 400 bytes per player. Reorganized packet resend loop to hopefull |
| y fix a reported infinite loop. Added define _COMPATIBILITY_1 to exclude |
|  compilation of code that uses alloca, FormatMessage, the security layer |
| , gethostbyname, #include                                                |
|     and inet_ntoa.  This define also changes the default MTU to 1492. Up |
| dated documentation for memory synchronization of DataReplicator. Update |
| d FAQ. Added OnDetatch to the PluginInterface.                           |
|     2.455 Fixed many gcc warnings.  Fixed error where alloca wouldn't co |
| mpile under Code::Blocks                                                 |
|     2.456 Add channel parameter to functions RakPeer::Disconnect and Rak |
| Peer::CloseConnection. Added RakPeer::SetTimeoutTime and removed constan |
| t TIMEOUT_TIME. Optimized network thread playerID lookup from O(n) to O( |
| log2(n)), which will improve directed send speeds when a server or peer  |
| has many connected systems. Added SetNetworkSimulator procedure so the n |
| etwork simulator can be activated, deactivated, and be adjusted by users |
|  at runtime.  Added checking for _FINAL define, to exclude code that wou |
| ld never be used in release builds.  Currently only applies to the Netwo |
| rkSimulator                                                              |
|     2.457 Fixed harmless assert on startup in ReliabilityLayer::SetPing. |
|  Fixed uninitialized variable read when sending ID_ADVERTISE_SYSTEM with |
|  no user data. Fixed search indexing bug in OrderedList causing performa |
| nce loss. Increased DataReplicator memory registration limit from 255 to |
|  65535.                                                                  |
|     2.46 Added IsObjectListPushComplete to the DataReplicator system.  T |
| he DataReplicator class factory now has access to the creation send and  |
| request data.  Added CommandConsoleServer and CommandConsoleClient. Padd |
| ed single byte packets to 2 bytes to fix some router issues.             |
|     2.461 Exported most of the user classes, so if you are using a DLL y |
| ou don't have to include the source. Added more functions to RakNetworkF |
| actory to new and delete those classes. Fixed an assert in DataReplicato |
| r. Added const to StringCompressor::EncodeString and AdvertiseSystem. Fi |
| xed projects so they all build.                                          |
|     2.47 Released first iteration of ReplicaManager, which replaces Data |
| Replicator, which I will no longer include in distributions.  Added Repl |
| icaManagerCS and ReplicaManagerP2P samples.  Added missing *identifierFo |
| und=true in GetServerListRuleAsInt.  Added OnCloseConnection to PluginIn |
| terface. The NetworkID generator system now supports peer to peer. Added |
|  StringTable class.                                                      |
|     2.48 Fixed critical bug where if an unreliable packet was lost all f |
| urther data would be considered duplicate. In the ReplicaManager you can |
|  now use objects without calling construct first.  The BitStream class f |
| or VC6 reverts to the old BitStream that didn't use templates.  Renamed  |
| ObjectID NetworkID and renamed UNASSIGNED_OBJECT_ID UNASSIGNED_NETWORK_I |
| D.                                                                       |
|     2.481 All changes to the ReplicaManager: Added ReferencePointer. Usi |
| ng a default scope of true will no longer trigger SendScopeChange and Re |
| ceiveScopeChange calls for that true default value. Functions now use th |
| e return type ReplicaReturnResult.  All 3 callbacks now include a Replic |
| aManager * to the manager. Fixed bug setting bitwise enumerations for co |
| mmands for the ReplicaManager.                                           |
|     2.482 Removed mutex locks for incoming and outgoing password. Bug fi |
| xes for ReplicaManager. Added 64 bit time support.                       |
|     2.483 (04/19/06) Replaced %8 with &7 in BitStream.cpp.  Thanks to Ol |
| iver Smith for pointing this out. Changed offline pings to be totally of |
| fline, rather than connecting and then disconnecting.  This might fix th |
| e reported bug with pinging and not being able to reconnect. Reordered p |
| acket enumerations so that the most commonly used ones are first.  Updat |
| ed readme.txt.                                                           |
|     2.484 (04/21/06) Fixed stack overflow problem when sending RPC packe |
| ts with more data than the stack can hold (via define MAX_ALLOCA_STACK_A |
| LLOCATION).  Added PlayerID::ToString(). Converted Bitstream constructor |
|  char *'s to unsigned char *'s so you can pass Packet::data to it withou |
| t casting. Fixed memory leak if you disconnected with unread packets wai |
| ting (Thanks to "riley" and "Greg" in the forums).  Removed various warn |
| ings.  Updated Linux ChatExample (thanks to Oliver Stone for sending me  |
| the files).                                                              |
|     2.485 (04/27/06) Fixed bug with not being able to do cross-connectio |
| ns.  Renamed all data structures with DS_ and changed namespace to DataS |
| tructure.                                                                |
|     2.486 (05/03/06) Improved support for cross connections.  Added ID_* |
|  strings to packet logger.  Fixed devCPP compatibility.  Made certain fu |
| nctions inline for improved performance.  Added RakNetDefines.h as a glo |
| bal control panel.  Bugs in tutorial html files fixed (Thanks to Laurens |
|  Simonis).                                                               |
|     2.487 (05/05/06) You can now call DeallocatePacket in any order you  |
| want.  Added PerformanceAnalysis and ThreadTest projects.  Fixed memory  |
| leak if sending an RPC to a system that disconnected between the user ca |
| ll and the network thread doing the send. Removed maximum message size l |
| imit of (formerly) 91 megabytes, improved CPU efficiency of message reas |
| sembly, and decreased per-split bandwidth usage by 2 bytes. Fixed bug wh |
| ere you could get recursive RPC calls with blocking RPCs. Added _RAKNET_ |
| THREADSAFE to support multiple writer and reader threads using the same  |
| instance of RakPeer. BitStream.h should now compile on Visual Studio 200 |
| 5.                                                                       |
|     2.49 (05/22/06) Added help text to all samples. Added ConnectionGrap |
| h and Router plugins. Rewrote RakVoice and made it a plugin. The bitstre |
| am write function that takes another bitstream now also takes the number |
|  of bits to write.                                                       |
|     2.5 (06/23/06) Fixed order channel heap deletion.  Added Rewritten A |
| utopatcher.  Added DirectoryDeltaTransfer.  Added CrashReporter and Cras |
| hRelauncher.  Moved samples up one directory.  Fix bug with plugins only |
|  processing one message.                                                 |
|     2.51 (06/24/06) Improved crash reporter.  Finished EmailSender.  Ban |
| ned ID now sent to banned players. Replaced flow control method in relia |
| bility layer (experimental!).                                            |
|     2.511 (06/26/06) Increased time resolution to nanoseconds, greatly i |
| mproving the granularity of the send speeds.                             |
|     2.512 (06/26/06) Fixed bug with nanoseconds overflowing after a few  |
| hours.                                                                   |
|     2.513 (06/26/06) Fixed GetTime bug on a machines with a certain cloc |
| k hertz that caused all new connections to be considered timed out immed |
| iately.  Added NAT Punchthrough plugin.                                  |
|     2.514 (07/02/06) Fixed DevCPP compatibility.  Slight throughput incr |
| ease.  Still working on BPlusTree to improve it further.                 |
|     2.515 (07/06/06) Fixed bug with overflowing the buffer when resendin |
| g reliable messages.  Added BPlus tree data structure and used it for re |
| sends. Fixed bug where timestamped messages were not sent to plugins.    |
|     2.516 (07/12/06) Fixed Linux compatibility due to a bug in GetTime.c |
| pp.  Working on table data structure (incomplete).                       |
|     2.517 (08/24/06) Commented out unused macros in Types.h. Added DS_Ta |
| ble class and LightweightDatabaseServer/LightweightDatabaseClient plugin |
| s. Improved flow control algorithm to detect connection speed more quick |
| ly and increased maximum throughput by about 4 times. Fixed Linux compat |
| ibility problems. Added _RAKNET_LIB and _RAKNET_DLL to Exports.h and cha |
| nged projects accordingly. Fixed memory leak in the memory pool class. F |
| ixed DLL compile problems. Commented RakVoice.                           |
|     2.518 (09/01/06) Changed return value of OnReceive for plugins. Furt |
| her fixes for Linux and Mac compatibility. Optimize Bitstream writes of  |
| other Bitstreams. Added ThreadPool class and made the autopatcher use it |
|  so that queries run in a thread rather than blocking the main thread.   |
|     2.519 (09/05/06) Fixed 1 byte memory leak on ID_DISCONNECTION_NOTIFI |
| CATION.  Thanks knox!                                                    |
|     2.52 (09/22/06) Fixed a bug where a system that disconnected couldn' |
| t always reconnect. Fixed a bug where a system couldn't connect rapidly  |
| with secure connections. Changed file path backslash to forward slash. F |
| ixed Linux usage of findfirst. Fixed problem where packet format error d |
| etection code was incorrectly #ifdefed out in Release.                   |
|     2.521 (10/14/06) Added ID_DOWNLOAD_PROGRESS and had all the plugins  |
| which transfer files use it. Added SetUnreliableTimeout to drop unreliab |
| le messages that took to long to send.  Fixed bugs sending the wrong MS  |
| vs NS unit of time to SendImmediate.                                     |
|     3.0 (11/15/07) Too many changes to list, see 2.x to 3.x upgrade.txt  |
|     3.001 (11/16/07) Fixed router plugin problems when using ID_TIMESTAM |
| P, not determining throughput when using unreliable messages, and increa |
| sing throughput detection speed.                                         |
|     3.002 (12/11/07) Fixes bad flow control with Reliability Layer.      |
|     3.004 (12/14/07) Last version was bad due to source control problems |
| .  Rereleasing, again with reliability layer fixed.                      |
|     3.006 (12/19/07) Refixed the bug with Router.cpp. Made a new Linux m |
| akefile and added a Netbeans project directory. Also added a CMake file. |
|     3.007 (12/21/07) Fixed a flow control problem where it normalized on |
|  high pings, thus increasing throughput when it should not and causing p |
| acketloss. Changed transmitted ping time to use nanoseconds to fix an ov |
| erflow bug when converting to milliseconds on Linux.                     |
|     3.008 (01/06/08) Changed Linux calls to GetTime to be offset by the  |
| first call. This alllows proper division by 1000 to convert to RakNetTim |
| e from RakNetTimeNS                                                      |
|     3.009 (01/12/08) Change GetTime to only check the processor affinity |
|  once on Windows. This might fix leap-ahead and disconnect issues people |
|  are having. Added RankingServer project. Refactored parts of the autopa |
| tcher. Added FunctionThread/Functor system.                              |
|     3.01 (1/30/08) Improved flow control. Faster send times during low b |
| andwidth. Added first revision of the lobby server for the PC.           |
|     3.02 (2/17/08) Finished out missing feature prototypes on the lobby  |
| server. Improved compatibility. Improved NAT punchthrough. Lightweight d |
| atabase server can now update a single row by using the system address,  |
| rather than requiring a row ID.                                          |
|     3.03 (2/28/08) Added Replicamanager2. Fixed a minor bug with the aut |
| opatcher.                                                                |
|     3.04 (3/02/08) Added interpolation demo "Ogre3DInterpDemo" for Ogre3 |
| D. Fixed Linux crash in SocketLayer.cpp for looking up host names.       |
|     3.05 (3/06/08) Updated documentation. Fix crash that could occur if  |
| receiving offline messages with data at the same time you are connected  |
| to the system sending it.                                                |
|     3.06 (3/10/08) Fix bug causing flow control to overcompensate by 8X. |
|  Resulted in taking 8X longer to find bandwidth, and 8X greater minimum  |
| latency.                                                                 |
|     3.07 (3/16/08) Added RakMemoryOverride class for memory tracking for |
|  consoles. Fixed Packetlogger crash. Verified that all samples run.      |
|     3.08 (3/23/08) Added AutoRPC plugin. Fixed some crashes and memory p |
| roblems with TCPInterface                                                |
|     3.1 (3/31/08) Added SetSendPrefix and SetSendSuffix to TelnetTranspo |
| rt. Fixed memory allocation crashes in TelnetTransport and the logger pl |
| ugin. Added depreciated tag to old RPC system. Readded BitStream_NoTempl |
| ate. Support for GCC assembly code in AutoRPC. Added RakString class, an |
| d changed lobby system to use this instead of std::string. Added DemoBin |
| aries.zip to DependentExtensions\Ogre3DInterpDemo so users can run witho |
| ut having Ogre installed. AutoRPC is now in the namespace RakNet. Code:: |
| Blocks fails to build AutoRPC due to what appears to be a compiler bug.  |
|     3.11 (4/10/08) AutoRPC may now work on 64 bit systems and the Power  |
| PC. AutoRPC will automatically dereference pointers. Rename UserIdOrHand |
| le to RowIdOrHandle. Add clan support to lobby database (in progress). F |
| ix RakString (was broken for lobby). Fix include paths for VC8 for speex |
| . Many warnings removed for non-windows users. ReadyEvent system now sup |
| ports going back to unready. Disabled sample PerformanceTest.            |
|     3.2 (4/15/08) NAT Punch through now uses duplex symmetric port predi |
| ction, resulting in a vastly higher success rate. Fixed a bug in SingleP |
| roducerConsumer resulting in a 12 byte memory leak per message sent or r |
| eceived in release. Thanks to cmusch in the forums for finding this.     |
|     3.21 (4/20/08) Reverted to speex-1.1.12 to fix broken voice activity |
|  detection. Turned on voice activity detection by default to fix a bug w |
| here the voice latency increases over time. Add "SuperFastHash" to speed |
|  up DirectoryDeltaTransfer and Autopatcher file scans by 30%. Add file R |
| akThread for easier cross-platform thread creation.                      |
|     3.22 (05/04/08) Fixed TTL send not working for NAT punch through. TC |
| PInterface now has a nonblocking option for connections. Lobby system no |
| w takes the handle of a friend, not just ID, for friend operations, and  |
| returns the handle and ID used in the callbacks. BitStream class can now |
|  hold up to rangeof(unsigned int)/8 bytes. Fixed bug with connection seq |
| uence so FullyConnectedMesh should always complete connections. Fixed Pa |
| cketlogger output. Added RakPeerInterface::SendLists(), used by FileList |
| Transfer for better efficiency. Increase connection attempt failure time |
|  to 4 seconds so users with software firewalls have a chance to click ac |
| cept. Fixed RakString::Replace. Fixed Table::GetAvailableRowId. Added PH |
| PDirectoryServer project.                                                |
|     3.23 (05/11/08) Fix subtraction underflow caused by bad GetTime() va |
| lues for ReliabilityLayer. This could cause reliable packets that were l |
| ost due to packetloss to never be resent. Added RakPeerInterface::IsLoca |
| lIP(). Fixed PostgreSQL implementation of autopatcher. Added MySQL imple |
| mentation of autopatcher. Fixed SQL injection security holes with autopa |
| tcher server. Add TLS support to TCPInterface, allowing the EmailSender  |
| class to send through Gmail. Fixed infinite recursive call under DevCPP  |
| and MinGW caused by #define with stricmp.                                |
|     3.24 (06/16/08) Autopatcher: optimized MySQL queries, fixed file lis |
| t transfer callback, improved Linux compatibility. ReplicaManager2: Adde |
| d SEND_SERIALIZATION_CONSTRUCTION_TO_SYSTEM, fixed bug with sending scop |
| e changes. AutoRPC: Fixed passing a boolean as the last parameter. Fixed |
|  encoding error when doing directed sends. Fixed race condition in Threa |
| dPool.h. NAT punchthrough will now try the local IP sooner. Return ID_DI |
| SCONNECTION_NOTIFICATION when CloseConnection is called with sendDisconn |
| ectionNotification==false. Fixed parsing error when passing domain names |
|  to RakPeer::Connect(). PHPDirectoryServer will now update the correct r |
| ow based on the system address key.                                      |
|     3.25 (07/27/08) Added RPC3 plugin and video. The second and later re |
| sends of reliable messages now occur one second apart (fixes flooding/di |
| sconnects at low pings). Added templated GET_OBJECT_FROM_ID to NetworkID |
| Manager.h which will work with multiple inheritance when NetworkIDObject |
|  is not the firstmost derived class. Added char *firstDataChunk paramete |
| r to FileListTransferCBInterface::OnFileProgress callback. Fix FileListT |
| ransfer when doing endian swapping. Fixes for Linux FileOperations.cpp a |
| nd FindFirst (fixes autopatcher). ReplicaManager2: Added GetTimeToNextAu |
| toSerialize, fix timestamp endian swapping, multiple instances now suppo |
| rted on the same instance of RakPeerInterface (must use AutoAddConnectio |
| ns(false)). Added static SocketLayer::IsPortInUse(). Virtual function an |
| d multiple inheritance fixes for AutoRPC.  Various fixes and updates for |
|  PHPDirectoryServer. Change GetExternalID(UNASSIGNED_SYSTEM_ADDRESS) so  |
| that it returns a consistent external address. Add boolean parameter inc |
| ludeDisconnecting to RakPeerInterface::IsConnected(). RakPeerInterface:: |
| CloseConnection() now cancels connection attempts in progress immediatel |
| y and reliably. Ready event fixes. Add operator << and operator >> to Bi |
| tstream. BitStream now supports Read functions for other bitstreams.     |
|     3.26 (08/28/08) Add IsSendingVoiceData to RakVoice. Remove GetTickCo |
| unt() call in GetTime.cpp. On Vista it was found to frequently return a  |
| past result off by rangeof(unsigned int), causing all connections to be  |
| dropped. Workaround Vista bug returning WSAEADDRINUSE when binding a soc |
| ket after previously closing one on the same port. Add OnConstructionCom |
| plete to Replica2. Add ExecVaridic to PostgreSQLInterafce. Fix for sendi |
| ng offline messages using an unknown hostname. Add WSAStartupSingleton.h |
|  for SocketLayer.cpp and TCPInterface.cpp. Support incremental sends for |
|  FileListTransfer, reducing memory use for large file sends. Add Connect |
| ion_RM2::SortInitialDownload so users can control the order objects are  |
| sent to new connections. Tweak reliable message resend timers.           |
|     3.261 (09/07/08) Rewrite of lobby system, Lobby2, is now in beta. Ra |
| nking and Clans not yet implemented. Changed printf to RAKNET_DEBUG_PRIN |
| TF and added #define to RakNetDefines.h. RPC3 should now compile on Linu |
| x. Fixed internet simulator treating extraPingVarious as microseconds ra |
| ther than milliseconds. Endian support fixed for FileListTransfer when u |
| sing SuperFastHash. Speed up AutopatcherMySQLRepository with indices. Th |
| anks for varmint from the forums for the last two tips.                  |
|     3.3 (10/24/08) ID_CONNECTION_REQUEST_ACCEPTED is now RELIABLE_ORDERE |
| D on channel 0.                                                          |
|     Added a threadsafe version of SystemAddress::ToString().             |
|     Secure connections code has been rewritten for better speed (Thanks  |
| Catid).                                                                  |
|     RakVoice will now check for initialization before accepting remote c |
| hat requests.                                                            |
|     Added RakNetGUID to uniquely identify instances of RakPeer. Use RakP |
| eer::GetGuidFromSystemAddress() and RakPeer::GetSystemAddressFromGuid. G |
| UIDs are contained in the Packet structure and within offline messages.  |
|     Fixed bug with BitStream::WriteVector().                             |
|     NATPunchthrough now supports cross connections. Reciever will now pr |
| operly open all attempted connection addresses, rather than only the fir |
| st one.                                                                  |
|     Added RAKNET_PROTOCOL_VERSION and ID_INCOMPATIBLE_PROTOCOL_VERSION,  |
| returned for incompatible RakNet versions on Connect() calls.            |
|     Fixed EmailSender failing 1/3 of the time with base 64 encoding.     |
|     Fixed crash with deleting TCPInterface before calling TCPInterface:: |
| Stop().                                                                  |
|     _USE_RAK_MEMORY_OVERRIDE will now work for all allocations, via plac |
| ement new.                                                               |
|     Throughput will now backoff globally on unresponsive remote systems, |
|  rather than for specific messages.                                      |
|     AutopatcherServer will no longer crash when sending to multiple conn |
| ections (fixed bug introduced in 3.26).                                  |
|     SimpleMutex and RakString can now be instantiated globally.          |
|     3.4 (02/17/09) Add RakPeer::CancelConnectionAttempt.                 |
|     Fix NatPunchthrough to use CancelConnectionAttempt.                  |
|     If available bandwidth drops, but later has no packetloss for 5 seco |
| nds, bandwidth utilization increases much faster.                        |
|     DeltaDirectoryTransfer plugin now supports IncrementalReadInterface, |
|  to reduce concurrent memory utilization for large files if desired.     |
|     Fix missing RakNet::OP_New in DS_WeightedGraph.                      |
|     Add extern "C" to RakMemoryOverride.                                 |
|     3.5 (04/01/09) Fix delta directory transfer not able to read file co |
| ntents on incremental reads because only the relative path was stored on |
|  the sender                                                              |
|     NAT punchthrough rewritten, tested with nearly every manufacturer.   |
|     LightweightDatabaseServer will no longer incorrectly remove a row if |
|  you do not call RakPeer::Update() for a long time.                      |
|     Various ReplicaManager2 fixes for non-authoritative client created o |
| bjects.                                                                  |
|     Packet logger now shows acks and RakPeer::PushBackPacket commands. A |
| lso, now shows the correct messageID for regular sends.                  |
|     Add DS_Multilist for use in future data structures, to replace DS_Li |
| st, DS_Queue, DS_OrderedList.                                            |
|     Fixed Bitstream type mismatch in RakVoice, causing plugin to not wor |
| k at all.                                                                |
|     The RakVoice sample with Portaudio now supports NAT Punchthrough.    |
|     ReliabilityLayer now uses fast backoff on real or anticipated packet |
| loss, reducing packetloss from about 16% to 2% for large data transfers. |
|     Fixed returning the wrong emailId with Lobby2 GetEmail function for  |
| PostgreSQL                                                               |
|     Switch plugins to use PluginInterface2, replacing PluginInterface, i |
| n order to support TCP.                                                  |
|     Add PacketizedTCP class, sending discrete messages through TCP.      |
|     Support PacketizedTCP with the Autopatcher and FileListTransfer. Usi |
| ng TCP, the autopatcher can self-update even when RakNet's protocol chan |
| ges.                                                                     |
|     3.51 (04/17/09) Added UDPProxy feature, to forward datagrams in case |
|  of NATPunchthrough failure.                                             |
|     Added ReplicaManager3 plugin. ReplicaManager2 is now depreciated.    |
|     Minor fixes in RoomsPlugin. Added RakNetGUID support to rooms and Lo |
| bby2.                                                                    |
|     Allow updating automatic system address and GUID fields if onlyUpdat |
| eOwnRows is false for LightweightDatabaseServer.                         |
|     Improve flow control for poor quality connections.                   |
|     Fix denial of service exploit caused by sending many connection atte |
| mpts to use up all connection slots. Now, only 10 connections can be mad |
| e from an identical IP address per second.                               |
|     3.52 (04/30/09) Various fixes and protocol change for NATPunchthroug |
| hServer. Punchthrough recipient now gets ID_NAT_TARGET_UNRESPONSIVE and  |
| ID_NAT_CONNECTION_TO_TARGET_LOST at the same time it is sent to the send |
| er.                                                                      |
|     Added ConnectionGraph2 and FullyConnectedMesh2 plugins.              |
|     RakNetTransport2 plugin added, which works as a plugin instead of cr |
| eating its own instance of RakPeer. RakNetTransport, which did that, is  |
| now depreciated.                                                         |
|     Deleted FCMHost plugin (replaced by FullyConnectedMesh2).            |
|     ReplicaManager3 fix for not sending serialization to new connections |
|  when using identical serialization.                                     |
|     Various fixes for Lobby2 system.                                     |
|     Fix crash in LightweightDatabaseServer if not automatically storing  |
| system address.                                                          |
|     Added DependentExtensions\IrrlichtDemo                               |
|     Disallow reconnecting when the remote system thinks you are still co |
| nnected, if using a different IP but the same RakNetGUID.                |
|     Added RakPeerInterface::GetSystemList to return connected SystemAddr |
| ess and RakNetGUID in a list.                                            |
|     Various fixes for DirectoryServer.php. PHPDirectoryServer::ProcessHT |
| TPRead now returns an enumeration, rather than a string, to indicate res |
| ults.                                                                    |
|     RakNetTime is now 64 bit by default. Comment __GET_TIME_64BIT in Rak |
| NetDefines.h to change to 32 bit.                                        |
|     UDP proxy system now automatically chooses best server. If more than |
|  one server is available, and both source and target relay systems are r |
| unning RakNet, then source and target will ping all available servers. T |
| he servers will be attempted in order of lowest ping sum to highest.     |
|     Updated FAQ. Updated manual for NATPunchthrough.                     |
|     3.6 (05/26/09) Fixed define bug with BIG_ENDIAN to __BIG_ENDIAN__ in |
|  BigInt.                                                                 |
|     Fixed FullyConnectedMesh2.                                           |
|     Bind whichever address a message came in on, so we always reply on t |
| he same address. This fixes an issue where you have multiple IP addresse |
| s and reply on a different address than what the sender used. This also  |
| means RakNet no longer necessarily uses a single socket for all communic |
| ations.                                                                  |
|     Added RakNetSocket structure, with GetSockets accessor in RakPeerInt |
| erface. This can be used to find out which ports and IP addresses you ha |
| ve locally bound.                                                        |
|     Added ConnectWithSocket to RakPeerInterface. Removed RebindSocket.   |
|     Added UPNP implementation from Codeproject to Samples, with fixes. A |
| dded to NATPunchthrough sample.                                          |
|     NATPunchthrough now supports 0 for the MAXIMUM_NUMBER_OF_INTERNAL_ID |
| S_TO_CHECK parameter.                                                    |
|     Fixed ReplicaManager3 serialization bugs with RM3SR_SERIALIZED_IDENT |
| ICALLY, and with serializing to more than 3 systems. Also validate conne |
| ctions before using them, so we know the other system has created the co |
| nnection first.                                                          |
|     ReplicaManager3 QueryConstruction is now only called when the object |
|  does not already exist. If it does already exist, QueryDestruction is c |
| alled instead.                                                           |
|     Added RakPeerInterface::GetTimeoutTime()                             |
|     Added time row was written to PacketLogger.                          |
|     UDPForwarder, and thus the proxy server, now runs in its own thread. |
|     UDPForwarder does not set the source or destination port until the f |
| irst message arrives, to handle symmetric NATs changing ports.           |
|     UDPForwarder now returns a result enumeration indicating success, ba |
| d parameters, in progress, or failed                                     |
|     Flow control will now subtract average times between thread updates  |
| from pings. This fixes a problem where uneven times between thread conte |
| xt switches caused reported pings to fluctuate constantly, resulting in  |
| flow control dropping to the minimum level. This should fix an issue enc |
| ountered by Stardock, with messages buffered and taking a long time to s |
| end.                                                                     |
|     Fix issue with UDPProxyCoordinator, where two systems would simultan |
| eously start forwarding to each other, but one system report success bef |
| ore the other knew about it, resulting in two forwarding entries.        |
|     Add modified UDT source to RakNet distribution, under DependentExten |
| sions\udt4. Comment out _USE_RAKNET_FLOW_CONTROL in RakNetDefines.h to u |
| se (Still has bugs, do not use for now).                                 |
|     Fix TCPInterface with DeltaDirectoryTransfer                         |
|     Fixed bug introducted by checking RakNetGUID on new connections from |
|  3.52, where connection replies were only sent once, rather than on each |
|  request.                                                                |
|     Added parameter to CloseConnection to select priority on which to se |
| nd ID_DISCONNECTION_NOTIFICATION.                                        |
|     Added SQLLite3Plugin to DependentExtensions\SQLite3Plugin. This allo |
| ws you to do database calls over the internet with SQLLite3, which is no |
| rmally only supported with networked file handles. This replaces Lightwe |
| ightDatabase, which is now depreciated.                                  |
|     3.61 (07/21/2009) Fix memory leak in single producer single consumer |
| .                                                                        |
|     Fix RakNetGUID initilization where only the first 4 ints were initia |
| lized.                                                                   |
|     Fix RakNet::OP_NEW mistmatch in DS_Table, causing a crash.           |
|     Fix crash in Lobby code from destroying binary data with some functo |
| rs. Add ability to query clan list. Lobby will now log you off if you lo |
| g in while already logged in (preventing multiple logins from the same u |
| ser). Added per-user per-title storage.                                  |
|     Update Doxygen comment syntax to produce better Doxygen output.      |
|     Fix misspelling of Variadic.                                         |
|     Depreciate PHPDirectoryServer due to unreliable replies. Now supplan |
| ted with PHPDirectoryServer2                                             |
|     Rooms plugin can now send arbitrary bitstreams through the server.   |
|     Near rewrite of ReplicaManager3. Optimized from O(n^3) to O(n). Now  |
| supports multiple serialization channels.                                |
|     Autopatcher source files moved from /DependentExtensions to Dependen |
| tExtensions\Autopatcher . Also the samples use TCP by default now.       |
|     Fix endian swapping with OFFLINE_MESSAGE_DATA_ID                     |
|     FullyConnectedMesh2 host determination rewritten for better consiste |
| ncy and reliability from unresponsive hosts.                             |
|     Updated samples with new IP address of free server.                  |
|     Disabled forced port bindings. This apparently causes the Vista to r |
| eject the reply messages, which is a more serious bug than getting a rep |
| ly on a different port.                                                  |
|     FileListTransferCBInterface::OnFileStruct renamed members: finalData |
| Length to byteLengthOfThisFile, totalDownloadedLength to bytesDownloaded |
| ForThisFile, setCount to numberOfFilesInThisSet, setTotalFinalLength to  |
| byteLengthOfThisSet, setTotalDownloadedLength to bytesDownloadedForThisS |
| et.                                                                      |
|     Fix NatPunchthroughServer not working on linux due to time subtracti |
| on, and hence underflow. Also made static string buffers larger to suppo |
| rt 6 integer RakNetGUID.                                                 |
|     Change gmail port for email sender sample.                           |
|     Added critical section locks to the referenced counted pointers in R |
| akString, to support multithreaded use.                                  |
|     BitStream will now use memcpy if possible when writing other bitstre |
| ams.                                                                     |
|     Fix crash in AutopatcherServer due to mismatch of calls to malloc an |
| d OP_DELETE.                                                             |
|     3.611 (07/23/2009) Fix bug with serialization not sent to reconnecti |
| ng system with ReplicaManager3. Release Scaleform GFx autopatcher integr |
| ation.                                                                   |
|     3.62 (08/05/2009) RakNet is now threadsafe by default in RakNetDefin |
| es.h, and more optimized for the threadsafe case. Reduce size of RakNetG |
| uid to int64_t to save bandwidth. Update OgreInterpSample to use Replica |
| Manager3. Add parameter to ReplicaManager3::AllocReplica. Add OnDownload |
| Started and OnDownloadComplete callbacks to Connection_RM3. Add NatTypeD |
| etection sample and code.                                                |
|     3.7 RC1 (08/27/2009) Fixed memory leak in RSACrypt. Fix RoomQuery::S |
| erialize when doing more than one query at a time. Reduce CPU by 20%. Sw |
| itch congestion control to UDT based algorithm. Fix NatPunchthroughClien |
| t::OpenNAT, so you can connect to a system more than once. Fix Lobby2 Ge |
| tAccountDetails. Add SQLImageBuffer test, and jpeg-7 to DependentExtensi |
| ons. Forgot ResetWritePointer in Connection_RM3::SendConstruction. Fix L |
| obby2 bugs with PerTitleIntegerStorage. Fix RM3 not serializing preexist |
| ing objects that don't change to new connections.                        |
|     3.7 RC2 (09/10/2009) Fixed 32 to 64 bit connection problem for all v |
| ersions. Fix endian swapping connection problem from RC1. There is now o |
| ne thread per receive socket to increase timestamp accuracy for congesti |
| on control. Fix crash on shutdown when using ban lists. Improve bandwidt |
| h estimation. Linux now pthread_cond_timedwait rather than sleep, for be |
| tter performance.                                                        |
|     3.7 (9/23/2009) Send() function player lookup is now O(1) in most ca |
| ses, rather than O(log2(n)); Added SQLiteServerLogger, SQLiteClientLogge |
| r, SQLiteClientLogger_RakNetStatistics, and SQLiteClientLogger_PacketLog |
| ger. Fixed TCPInterface low transfer speed. Fixed PacketizedTCP not upda |
| ting plugins correctly. Fixed SignaledEvent usage on Linux (bug from 3.7 |
|  RC2)                                                                    |
|     3.702 (10/15/2009) Speed up lookup on RakPeer::Send() from O(log2n)  |
| to O(1) by using systemIndex automatically when available. Reduce number |
|  of RakStrings allocated at once to 128 from 1024. Sped up TCPInterface. |
|  Return ID_CONNECTION_LOST if calling CloseConnection with sendDisconnec |
| tionNotification false.                                                  |
|     3.704 (10/22/2009) Autopatcher: Workaround for design flaw in Postgr |
| eSQL and possibly MySQL, where calls on a connection are not threadsafe  |
| across different threads. Instead of calling SetAutopatcherRepositoryInt |
| erface, you must now call StartThreads(), with an array of AutopatcherRe |
| positoryInterface, 1 per thread. StartThreads() must also be called now  |
| before AutopatcherServer will process any messages. This was previously  |
| causing crashes/corrupted data if a transfer was in progress through Fil |
| eListTransfer at the same time that the old autopatcher thread was query |
| ing the database for a different connection. Additionally, the autopatch |
| er now supports multiple simultaneous threads. Previously it only ran on |
| e thread at a time. Also sped up FileListTransfer for incremental reads  |
| in the case when there are many files and more than one connection. Repl |
| icaManager3: Add lastSentBitstream pointer to SerializeParameters. Fix U |
| DPForwarder not setting timeout parameter.                               |
|     3.705 (10/29/2009) Added ResetHostCalculation to FullyConnectedMesh2 |
| . Increased default memory usage to avoid datagram index overflowing on  |
| a LAN. Made this value customizable in RakNetDefines.h, and added RakNet |
| DefinesOverrides.h to make overriding easier. Update IsPortInUse to acco |
| unt for multiple IP addresses. Added default implementation of dlmalloc. |
|  Use by defining _RAKNET_SUPPORT_DL_MALLOC and _USE_RAK_MEMORY_OVERRIDE. |
|  Added Demo_BspCollision from Ogre3D to for SQLiteClientLogger sample.   |
|     3.7051 (11/07/2009) Reduce memory usage. Fix FileListTransfer bytesD |
| ownloadedForThisFile.                                                    |
|     3.71 (11/16/2009) Note: This version is not network compatible with  |
| 3.7051 or earlier due to reordering of packet enumerations.              |
|     Bug fixes: Fix MySQL autopatcher not working (bug from 3.704). Fix b |
| ug in RakPeer::Shutdown() where used sockets were never freed. Fixed a b |
| ug where the MTU size was always set at the lowest value, causing needle |
| ss fragmentation.                                                        |
|     Congestion control: Change tolerance algorithm for ping variations.  |
| The old algorithm was designed for a LAN, and was causing excess packetl |
| oss over long-distance internet connections.                             |
|     Performance: Remove all but 1 memory allocation per send and per rec |
| eive, in order to reduce memory fragmentation. With messages larger than |
|  the MTU, reference the original data block rather than allocating and c |
| opying fragments. Expose the thread priority in RakPeer::Startup() and T |
| CPInterface::Startup(), for Linux based systems that do not define a def |
| ault normal thread priority.                                             |
|     New features: Add connection failure enumeration ID_IP_ALREADY_CONNE |
| CTED. ID_IP_ALREADY_CONNECTED is returned if RakPeer::SetLimitIPConnecti |
| onFrequency() was set. Packet priorities now schedule sends, where each  |
| lower priority level is sent half as frequently as the priority level ab |
| ove. Updated Irrlicht 3D demo to Irrlicht 1.6.                           |
|     3.711 Fix messages of certain size combinations causing further send |
| s to never go out.                                                       |
|     Add ability to pass GUID to UDPProxyClient::RequestForwarding, and u |
| se this by default in the samples.                                       |
|     Reduce memory usage.                                                 |
|     Improve randomness of random number for FullyConnectedMesh2          |
|     3.712 Improve security for client-specified RakNetGUID. UDPForwarder |
| : Fix uninitialized variables.                                           |
|     3.713 Use hash lookup instead of sorted list lookup for packets from |
|  remote systems, since speed is so important for that. Ping based conges |
| tion control.                                                            |
|     3.714 (12/06/2009) Fix random crash in ReliabilityLayer. Possible fi |
| x for ID_ALREADY_CONNECTED, and increased randomization of GUID.         |
|     3.715 (12/11/2009) Fix bug returning ID_ALREADY_CONNECTED. You can n |
| ow also pass a RakNetGuid to most places in RakPeer you previously passe |
| d a SystemAddress. Change disconnect timeout method.                     |
|     3.716 (12/29/2009) Fix bug introduced in 3.714 causing players to ge |
| t disconnected. FileListTransfer now supports incremental writes in addi |
| tion to incremental reads. Reduce per-datagram overhead by 4 bytes once  |
| the bandwidth capacity has been determined.                              |
|     3.717 (1/05/2010) Fix a hashing bug affecting players reconnecting.  |
| Add RakPeerInterface::IsConnectionAttemptPending                         |
|     3.718 (02/04/2010) 64 bit to 32 bit network communication fixes. Low |
| er second attempt MTU detection to 1200. Skip MTU sends that will fail a |
| nyway. Add TeamBalancer plugin. Add signals and slots support for RPC3.  |
| Fixed autopatcher. Add Router2 plugin, to route messages in a fully conn |
| ected mesh, when two peers cannot directly connect. Add IMMEDIATE_PRIORI |
| TY, above HIGH_PRIORITY. With IMMEDIATE_PRIORITY, messages will be sent  |
| immediately, rather than joined with other messages for more efficient b |
| andwidth usage. RakVoice now refers to other systems by RakNetGUID, rath |
| er than SystemAddress, in order to work properly with NAT punchthrough.  |
| Fixed various warnings for Linux. Fixed pure virtual function call in Lo |
| bby2Server when shutting down. Fixed Client_GetAccountDetails for lobby2 |
| . Changed implementation of BitStream::WriteNormVector to handle small n |
| umbers. Added UPNPPortForwarder as a replacement nonblocking interface t |
| o the old UPNP system.                                                   |
|     3.72 (02/27/2010)                                                    |
|     PS3: Added dice sample                                               |
|     FileListTransfer: Fixed divide by 0 crash when using incremental rea |
| ds.                                                                      |
|     Cmake: Fixed, all other projects and makefiles removed for Linux.    |
|     UPNP: Fixed                                                          |
|     BitStream: Added WriteRef, and use with the shift left operator, so  |
| that RPC3 does not do a pass-by-value on object writes. This fixes a pro |
| blem where the pass-by-value caused the destructor to be called on the c |
| opied object.                                                            |
|     ReplicaManager3: Replace AutoConstructByQuery with QueryConstruction |
| Mode, and added QueryReplicaList, for better performance for massively m |
| ultiplayer games.                                                        |
|     TelnetTransport: You can now press the up arrow key to repeat the la |
| st command.                                                              |
|     RakPeer: Fix IMMEDIATE_PRIORITY to send right away when called by th |
| e user.                                                                  |
|     Router2: Various bugs fixed.                                         |
|     3.73 (04/09/2010)                                                    |
|     Fix bug where packetloss during slow start could cause retransmissio |
| ns to stop.                                                              |
|     Add Lobby2Client_Steam plugin and corresponding sample, to support S |
| team published games using the Steamworks SDK.                           |
|     Fix RPC3 with writing bitstream pointers.                            |
|     ReplicaManager3 now supports different send modes per bitstream chan |
| nel. Also now stores store lastSerializationResult when using RM3SR_SERI |
| ALIZED_ALWAYS.                                                           |
|     Update ConnectionGraph2 to also store the remote system connection l |
| ist in memory, and allow access by the user.                             |
|     PacketLogger will now log internal message receive errors.           |
|     Consolodate NAT traversal plugins into NATCompleteServer and NATComp |
| leteClient samples. Remove old NAT samples.                              |
|     3.731 (05/01/2010) Document TeamBalancer and Steam lobby plugins. Fi |
| x crash with calling RakPeer::DetachPlugin(). Fix bug to return ID_SND_R |
| ECEIPT_ACKED only once for messages over the MTU. Rewrite RakNetStatisti |
| cs to return more relevant and up to date information, including metrics |
|  per second. Add VariableDeltaSerializer, an optional helper class with  |
| ReplicaManager3 that can serialize changes per-variable, rather than rel |
| ying on the default of serializing the entire object.                    |
|     3.80 (05/27/2010) Disabled UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT, RE |
| LIABLE_SEQUENCED_WITH_ACK_RECEIPT.                                       |
|     Fixed GetMyIP, Modify HTTPConnection to use SSL if defined, and to s |
| pecify the port.                                                         |
|     Support WorldID with ReplicaManager3.                                |
|     Add NativeFeatureIncludes.h and NativeFeatureIncludesOverrides.h, so |
|  the user can exclude code they do not want more easily.                 |
|     Improve/fix Router2 and UDPForwarder.                                |
|     Add to BitStream functions SerializeCasted (Same as just casting the |
|  type you read/write, but uses a template), SerializeBitsFromIntegerRang |
| e, WriteBitsFromIntegerRange, and ReadBitsFromIntegerRange.              |
|     Fix not threadsafe call to BPS tracker, caused crash when calling Ge |
| tStatistics with version 3.731 or later.                                 |
|     Increased tolerance for ping spikes with congestion control, speeds  |
| will increase more quickly on average now.                               |
|     Fixed RakPeer::SendOutOfBand, hould always return as the first byte  |
| ID_OUT_OF_BAND_INTERNAL.                                                 |
|     Allow Set() and constructor functions in RakString to take any size  |
| input.                                                                   |
|     Fixed ConnectionGraph2 basically not working at all.                 |
|     Fixed http://www.jenkinssoftware.com/forum/index.php?topic=3216.0 wh |
| ere HTTPConnection would fail because TCP packets were still waiting whi |
| le CloseConnection was called.                                           |
|     Encode ping/pong in handshaking so a ping is always available when I |
| D_CONNECTION_REQUEST_ACCEPTED or ID_NEW_INCOMING_CONNECTION arrives. Thi |
| s changes the protocol, so connections to prior versions are not possibl |
| e.                                                                       |
|     Fixed cross connections so both systems return ID_CONNECTION_REQUEST |
| _ACCEPTED, and neither system returns ID_NEW_INCOMING_CONNECTION.        |
|     3.81 (07/01/2010)                                                    |
|     Fix congestion control bug that caused all data transmission to stop |
| , although the connection was not dropped.                               |
|     Fix UDPForwarder crash.                                              |
|     Improve congestion control for LAN settings.                         |
|     Add GET_TIME_SPIKE_LIMIT to RakNetDefines, as an option, disabled by |
|  default, to prevent http://support.microsoft.com/kb/274323.             |
|     Fix SimpleMutex failure caused by initializing the same instance fro |
| m multiple threads at the same time.                                     |
|     Fix packetlogger logging error when using timestamps.                |
|     Fix assert in RoomsPlugin.                                           |
|     Update tutorial in manual.                                           |
|     3.82 (9/17/2010)                                                     |
|     UDPForwarder now uses a single port                                  |
|     Fixes to Router2                                                     |
|     Add Get to HTTPConnection class                                      |
|     Fix ReplicaManager3 when using send type other than RELIABLE_ORDERED |
|     Update Ogre3DInterpDemo to Ogre 1.7.1                                |
|     Make SendOutOfBand work also when RakNet wasn't started              |
|     Test sendto call for MTU detection, if it blocks, drop to the lowest |
|  MTU                                                                     |
|     Tweak CCRakNetUDT::IncreaseTimeBetweenSends to reduce backoff, to be |
| tter handle random ping spikes                                           |
|     3.9 (10/15/2010)                                                     |
|     New sliding window congestion control algorithm. Define USE_SLIDING_ |
| WINDOW_CONGESTION_CONTROL to something other than 1 to use old algorithm |
| .                                                                        |
|     Additional Router2 fixes                                             |
|     Call QueryPerformanceFrequency() in GetTime.cpp every call to GetTim |
| eUS(), to fix bug caused By Ludashi changing the reported CPU frequency. |
|     Make SocketLayer static so it can be exported through a DLL.         |
|     Nat punchthrough fix - when testing internal IPs, the remote system  |
| may report loopback. This prevents testing internal IP connectivity on t |
| he loopback.                                                             |
|     Fix logging errors with packet logger.                               |
|     Assert against virtual call in destructor of ReplicaManager3.        |
|     Fix NatTypeDetection only returning port restricted. Expand boolean  |
| array in NatTypeDetectionCommon.                                         |
|     Fix Linux warnings.                                                  |
|     Return last error with UPNP status update.                           |
|     ReplicaManager3::Connection_RM3 now supports QueryGroupDownloadMessa |
| ges() feature, to give all construction and serialization messages in a  |
| single tick after initial download, rather than the download potentially |
|  spread over many ticks.                                                 |
|     Fix lockup with isActiveMutex in TCPInterface::CloseConnection().    |
|     Fix bug where packets with higher priorities sent later than ones wi |
| th lower priorities caused them to still send in order.                  |
|     3.901 (6/16/2011)                                                    |
|     RakNetStatistics.cpp: Multiply packetloss by 100                     |
|     ReliabilityLayer.cpp: Fix bug with reported per-second statistics ov |
| erreporting packetloss                                                   |
|     CCRakNetSlidingWindow: Improve congestion control algorithm to decre |
| ase average packetloss in the steady state                               |
|     TCPInterface: Fix RemoteClient::Send returning 0 instead of bytes wr |
| itten when using SSL.                                                    |
|     ReliabilityLayer.cpp: Fix broken RELIABLE_WITH_ACK_RECEIPT           |
|     ReliabilityLayer.cpp: Bugfix: If a duplicate ack arrived and more th |
| an DATAGRAM_MESSAGE_ID_ARRAY_LENGTH (512 by default) reliable messages h |
| ad been sent or resent between the first ack and the duplicate, the wron |
| g reliable message would be flagged as delivered. This would result in n |
| o further reliable messages would be returned to the user, although the  |
| connection would not be lost due to lost connection detection pings bein |
| g unreliable.                                                            |
|     SocketLayer.cpp: Comment out printf                                  |
|     4.0 (1/1/2011)                                                       |
|     See 3.x_to_4.x_upgrade.txt in base directory for conversion notes.   |
|     SWIG and C# is now officially supported.                             |
|     Consoles are now officially supported.                               |
|     Autopatcher can now serve more users at a time than there are thread |
| s. AutopatcherServer has a callback to inform the user of the current ap |
| plication load. FileListTransfer now supports incremental reads in a thr |
| ead.                                                                     |
|     NAT punchthrough now has a punch with TTL step to get past dual port |
| -restricted routers                                                      |
|     Added CloudServer/CloudClient plugins                                |
|     4.01 (2/8/2011)                                                      |
|     Note: This version is not network traffic backwards compatible with  |
| 4.0.                                                                     |
|     Added IPV6 support and corresponding documentation.                  |
|     In most cases SystemAddress is now passed by const reference. Users  |
| of ReplicaManager3 may need to match the function definitions of derived |
|  functions.                                                              |
|     Unused connection slots are now skipped during RakPeer thread ticks. |
|     Added OpenNATGroup feature to NatPunchthroughClient, enabling NATPun |
| chthrough to not report completion until until all desired remote system |
| s have been punched.                                                     |
|     Replaced old Codeproject based UPNP implementation with miniupnpc 1. |
| 5 for NATCompleteClient.                                                 |
|     RakNetGUID::ToInteger() renamed to RakNetGUID::ToUint32().           |
|     PS3: Fixed accessing deallocated memory when searching rooms         |
|     PS3: Fix Console_SearchRooms and Console_GetRoomDetails not returnin |
| g integer and binary properties                                          |
|     XBOX 360: Fixed RakVoice_360, was previously not working.            |
|     4.013 (2/21/2011)                                                    |
|     IPV6: Fix domain name lookup. RakNetDefines.h now disables IPV6 by d |
| efault to save bandwidth.                                                |
|     RPC3: Fix not reading enough bytes on receive()                      |
|     Lobby (All): Rename SendMessage() to SendMsg() for consistency among |
|  platforms.                                                              |
|     Lobby (PS3): Console_JoinRoom_PS3 now returns only the room, for con |
| sistency                                                                 |
|     Lobby (PS3): Notification_Console_RoomMemberConnectivityUpdate remov |
| ed. Use Notification_Console_MemberJoinedRoom, Lobby2Room_PS3::GetValidR |
| oomMembers() instead.                                                    |
|     Lobby (360,PS3): Console_SearchRooms and Console_SetRoomSearchProper |
| ties has optional new unified properties and contexts system             |
|     Lobby (360): Fix sending when not using VDP                          |
|     Lobby (360): Now automatically transmits SystemAddress of other peer |
| s in room for P2P                                                        |
|     Documentation: ID_SND_RECEIPT_LOSS only returned on UNRELIABLE_WITH_ |
| ACK_RECEIPT                                                              |
|     Documentation: Update how to use static objects with ReplicaManager3 |
|     RakPeerInterface: Fix not returning ID_SND_RECEIPT_ACKED and ID_SND_ |
| RECEIPT_LOSS                                                             |
|     RakWString: Added for Unicode support. Currently assumes UTF-16.     |
|     OpenSSL: Update included version to 1.0.0d                           |
|     4.014 (2/28/2011)                                                    |
|     Fix bug introduced in 4.013 with RPC3, causing failure on receipt.   |
|     Lobby (360): Numerous fixes.                                         |
|     Lobby (PS3): Expose thread priority for cellSysutilAvc2Load.         |
|     Update Lobby2 for Steam so that steam_api.h is not included from any |
|  RakNet files, in order to take steam_types.h out of the global namespac |
| e due to type conflicts.                                                 |
|     4.015 (3/6/2011)                                                     |
|     Lobby (360): Added Console_GetRoomDetails_360                        |
|     Lobby (360): Added RoomMemberInfo::roomMemberName                    |
|     Lobby (PS3): Exposed supportHostMigration parameter when creating ro |
| oms.                                                                     |
|     Autopatcher: Add CacheMostRecentPatch() to AutopatcherServer. This k |
| eeps the most recent patch operation in memory, as well as the start and |
|  end date the most recent patch occurred. When the lastUpdateDate is pas |
| sed to AutopatcherClient::PatchApplication() and the corresponding patch |
|  is the most recent, disk access is not needed on the server, greatly im |
| proving performance.                                                     |
|     4.016 (3/14/2011)                                                    |
|     Add GetLowestAveragePingSystem to ConnectionGraph2.                  |
|     Add to manual about cloud hosting.                                   |
|     4.017 (3/23/2011)                                                    |
|     Fix CloudServer returning wrong port to CloudClient when using force |
| d addresses.                                                             |
|     Fix wrong connection count from CloudServerHelper                    |
|     Fix bug with FCM2 not being processed by other plugins.              |
|     Return Notification_Console_RoomOwnerChanged on all systems, not onl |
| y host, on xbox lobby.                                                   |
|     Disconnection notification right away on 360.                        |
|     4.018 (4/2/2011)                                                     |
|     Congestion control fix: Fixed bug with overagressive recovery using  |
| excessive bandwidth, which would cause packetloss in the usual case and  |
| dropped connections in the extreme case.                                 |
|     High data-rate fix: If a duplicate ack arrived and more than DATAGRA |
| M_MESSAGE_ID_ARRAY_LENGTH (512 by default) reliable messages had been se |
| nt or resent between the first ack and the duplicate, the wrong reliable |
|  message would be flagged as delivered. This would result in no further  |
| reliable messages would be returned to the user, although the connection |
|  would not be lost due to lost connection detection pings being unreliab |
| le.                                                                      |
|     Speed optimization: Add a 128 byte stack block to InternalPacket whi |
| ch is used for outgoing packets to avoid a malloc. Make some DS_Heap ope |
| rations inline.                                                          |
|     USE_THREADED_SEND: Now supported if added to RakNetDefines.h. The de |
| fine creates a separate thread for calling sendto() for very high outgoi |
| ng data-rates.                                                           |
|     Documentation: Added NAT Traversal architecture, detailing how to us |
| e NAT traversal components together.                                     |
|     Statistics: Fixed packetloss not being multiplied by 100 in Statisti |
| csToString. Fix overreported packetloss.                                 |
|     TCPInterface: Added WasStarted(). Return correct SystemAddress for b |
| locking connections. Fixed sends not working when using Open SSL (affect |
| s EmailSender class).                                                    |
|     RakString: Add SplitURI function.                                    |
|     RELIABLE_WITH_ACK_RECEIPT: Fixed transmissing wrong value, causing d |
| atastream corruption when used.                                          |
|     Rackspace: Added Rackspace.h, a C++ interface to Rackspace cloud ser |
| vers.                                                                    |
|     XBOX 360: Serialize room member names.                               |
|     PS3: Public and private slot counts now returned per room. Added GUI |
|  invites.                                                                |
|     Added LocklessTypes.h, LocklessTypes.cpp to /Source to fix reported  |
| bug http://www.jenkinssoftware.com/forum/index.php?topic=4466.0 where Ra |
| kPeer::Startup() would block forever.                                    |
|     4.019 (4/12/2011)                                                    |
|     Fixed Console_CreateRoom_Steam not using public slots setting.       |
|     Updated bzip to 1.0.6                                                |
|     Fixed binary data when returning more than one result for Lobby2Mess |
| age_PGSQL                                                                |
|     PS3: public and private slot fixed.                                  |
|     4.020 (4/21/2011)                                                    |
|     NATPunchthroughClient: Fixed internal IP addresses incorrectly repor |
| ted, sometimes causing failed LAN connections.                           |
|     XBOX: Allow localization of SignIn dialog.                           |
|     32 to 64 bit communications: Have stringCompressor not use unsigned  |
| int for 32/64 bit network support.  Fix error with BitStream writing Sys |
| temAddress using unsigned long, caused incorrect RakNetGUID values.      |
|     Linux (LIBCAT): Reduce entropy gathering rate to once a second.  For |
|  Linux, move vmstat -s polling to the invariant sources so it isn't run  |
| periodically.                                                            |
|     PS3: Added Console_ShowGUIInvitationsToRooms.                        |
|     PS3: Renamed Notification_Console_Got_Room_Invite_PS3 to Notificatio |
| n_Console_Accepted_Room_Invite_PS3                                       |
|     PS3: Added working implementation of  Notification_Console_Got_Room_ |
| Invite_PS3                                                               |
|     4.021 (5/20/2011)                                                    |
|     XBOX: Added CallLocalized_IncorrectProfilesSignedIn to override lang |
| uage for sign-in. Fixed updating room parameters. Fixed Console_EndGame_ |
| 360 never returning. Added Notification_Console_Game_Ending_360 for writ |
| ing sessions stats. Fixed process flow so that host arbitrates last. Fix |
| ed double pointer deletion crash from ending the game. Added workaround  |
| for sign-in API bug that would disconnect one user if another user signe |
| d in.                                                                    |
|     IPV6: Fixed compile error                                            |
|     SteamLobby: Fix bug causing some plugins to not work, including Full |
| yConnectedMesh2.                                                         |
|     RPC4: Support blocking calls with return values. Support global regi |
| stration of methods. User data is now aligned.                           |
|     PS3: Added support for checking for reboots due to game invites.     |
|     Documentation: Expand multiplayergamecomponents.html to describe com |
| mon tasks to add multiplayer to a single player game. Added technical do |
| cumentation about bluetooth.                                             |
|     4.022 (6/29/2011)                                                    |
|     ReplicaManager3: Added Replica3Composite to ReplicaManager3.h, to ma |
| ke it easier to use composition instead of deriving from Replica3. Repli |
| ca3::PostDeserializeConstruction function signature changed. PostSeriali |
| zeConstruction added. PostDeserializeConstruction() is now called after  |
| all objects have been created in a ReplicaManager3 construction tick. Re |
| plica3::PostSerializeConstruction has been added with an output bitstrea |
| m that is sent to Replica3::PostDeserializeConstruction. This enables th |
| e user to resolve pointer linkages at a time when all other objects are  |
| known to have been created and initialized.                              |
|     ReplicaManager3: SetAutoSerializeInterval now accepts 0 to serialize |
|  every time RakPeer::Update is called. Use a negative value to disable a |
| utoSerialize.                                                            |
|     RakPeer: Fixed GetInternalID not working (Affects NATPunchthrough on |
|  LAN). Fix crash in GetConnectionList.                                   |
|     XBOX: Notification_Console_Got_Room_Invite now returns user index of |
|  which user was invited. Inviting users with an index higher than 0 now  |
| works. Use XUserSetContextEx when joining rooms to prevent XONLINE_E_SES |
| SION_REQUIRES_ARBITRATION error. Fix for more than 2 members in a room.  |
| Error returned on room full.                                             |
|     PS3: Added L2MID_Console_EnableDisableRoomVoiceChat. Add password su |
| pport to Join_Room. Add option to init network utilities to Client_Login |
| .                                                                        |
|     LibCat security: Removed dependency on GetLogicalProcessorInformatio |
| n to support Windows versions older than XP with SP3                     |
|     RPC4: Signal and slot support added. Existing Call functions marked  |
| deprecated.                                                              |
|     IrrlichtDemo: Updated to Irrlicht 1.7.2. PostDeserializeConstruction |
|  modified to match new function signature.                               |
|     Games for Windows Live support: Added                                |
|     FullyConnectedMesh2: Added GetHostOrder                              |
|     Other: Remove Code blocks and Dev-CPP project files.                 |
|     StringTable: Fixed                                                   |
|     4.023 (7/19/2011)                                                    |
|     RakPeer: Fix for random connection loss on slow systems. This is due |
|  to threading causing the last time an ack was received to be higher tha |
| n the current time, thereby falsely returning true for the ReliabilityLa |
| yer::AckTimeout() function. GetConnectionState() no longer returns IS_LO |
| OPBACK.                                                                  |
|     Marmalade SDK: (Formerly called Airplay) Support added. See http://w |
| ww.madewithmarmalade.com                                                 |
|     ReplicaManager3: Add RM3CS_ALREADY_EXISTS_REMOTELY_DO_NOT_CONSTRUCT. |
|  Remove SerializeConstructionRequestAccepted, DeserializeConstructionReq |
| uestAccepted, SerializeConstructionRequestRejected, DeserializeConstruct |
| ionRequestRejected. If needed, manually send a construction request pack |
| et for an object.                                                        |
|     XBOX: Add showGameInviteUI parameter to Console_SendGUIInvitationToR |
| oom_360                                                                  |
|     RakVoiceXBOX360Plugin: Now only transmits according to the most rest |
| rictive talker signed onto the system                                    |
|     SteamLobby: Console_CreateRoom_Steam now returns L2RC_GENERAL_ERROR  |
| on failure.                                                              |
|     NetworkID: Add conflict avoidance                                    |
|     RPC4: Fix missing 'else' for processing signals and slots.           |
|     Manual: General revisions and improvements, particularly FullyConnec |
| tedMesh2, RPC4, ReplicaManager3                                          |
|     4.03 (8/15/2011)                                                     |
|     RakPeer: Sequenced and ordered messages now share ordering channels, |
|  and will arrive in the order sent on the same channel. Ping times for r |
| etransmit are now continuously recalculated without additional overhead, |
|  in order to adapt to changing bandwidth conditions.                     |
|     XBOX: Added option to disable XNotifyCreateListener( XNOTIFY_LIVE )  |
| through the createLiveListener parameter added to Client_Login_360. Fixe |
| d RakVoiceXBOX360 for TRC issues of transmitting to friends only.        |
|     NatPunchthroughClient: OpenNATGroup rewritten to take an explicit li |
| st of systems to punch.                                                  |
|     ReplicaManager3: Added PostSerializeConstructionExisting, PostDeseri |
| alizeConstructionExisting. Also, static objects are now processed in ord |
| er of registration, the same as non-static objects. Previously, all stat |
| ic objects were sent first. Documentation for static objects clarified.  |
| The Update() function is now public.                                     |
|     Steam Lobby: Fixed for more than 2 users at a time.                  |
|     RPC3: Document that left and right shift operator overloads for BitS |
| tream have to be in the namespace RakNet                                 |
|     RPC4: Now invokes local function immediately from Signal() if invoke |
| Local is true, rather than the next time RakPeer::Receive is called().   |
|     HTTPConnection: GET command fixed for some webservers.               |
|     Misc project changes: Fix RakVoice FMOD sample. Link against PGSQL 9 |
| .0 by default. Fix SQLite3Plugin Matrices project.                       |
|     4.031 (8/18/2011)                                                    |
|     ReplicaManager3: Fix BroadcastDestructionList. Objects were not bein |
| g deleted due to a change in 4.03.                                       |
|     RakPeer: Fix memory leak introduced in 4.03 with discarded sequenced |
|  messages that were split (larger than the MTU).                         |
|     SystemAddress: Fixed comparison between a value set from a string an |
| d an internal value with the same IP.                                    |
|     4.033 (9/15/2011)                                                    |
|     RakPeer: Reduced default memory usage. Fixed ID_ADVERTISE_SYSTEM all |
| ocating 1 byte too long. UNRELIABLE_WITH_ACK_RECEIPT now works.          |
|     XBOX 360: Host migration caused by unplugging router is now asynch ( |
| TCR fix). Console_SearchRoom now has a minOpenSlots parameter.           |
|     ReplicaManager3: Increased RM3_NUM_OUTPUT_BITSTREAM_CHANNELS to 16   |
|     ConnectionGraph2: Fix crash on connection lost                       |
|     PS3: Add hasInvitationInfo to Notification_Console_Accepted_Room_Inv |
| ite_PS3                                                                  |
|     Vita: Stopped using ultthread, which was causing threading errors.   |
|     4.034 (11/15/2011)                                                   |
|     BitStream: Read/Write BitsFromIntegerRange fixed.                    |
|     RakPeer: GetConnectionList() now sets number of systems to 0 when Ra |
| kPeer is not started.                                                    |
|     FullyConnectedMesh2: Fix potential assert caused by receiving ID_FCM |
| 2_INFORM_FCMGUID before ID_FCM2_REQUEST_FCMGUID or ID_FCM2_RESPOND_CONNE |
| CTION_COUNT.                                                             |
|     SteamLobby: Fixed bug where only one message was read per execution  |
| of RunUpdateCycle()                                                      |
|     DirectoryDeltaTransfer: Refactor so user can scan files in a thread  |
| if they wish.                                                            |
|     ReplicaManager3: Added to manual page instructions on how to combine |
|  it with FullyConnectedMesh2                                             |
|     XBOX: Fix logic error with XBOXAynchOps where it would lockup on a f |
| ailed operation. Fix deleting rooms on cable disconnect.                 |
|     TeamBalancer: Fixed setting team size limits. Now supports multiple  |
| players per computer.                                                    |
|     Other: VariadicSQLParser::ExtractArguments make %f act like %d.      |
|     4.035 (11/28/2011)                                                   |
|     TeamBalancer: Add DeleteMember()                                     |
|     XCode: Fix compilation for newest version by removing DS_Multilist.h |
| .  Added compilersetup_xcode.html.                                       |
|     XBOX 360: Fix bug that occured if two systems were to join a room at |
|  the same time.                                                          |
|     PS3: Clear event buffer on callbacks                                 |
|     Postgresql: Updated to 9.1                                           |
|     4.036 (2/1/2012)                                                     |
|     RakPeer: Fixed assert in SendOutOfBand(). Fix duplicate datagram cra |
| sh in ReliabilityLayer where holeCount > typeRange/(DatagramSequenceNumb |
| erType) 2. Added PluginInterface::UsesReliabilityLayer(). All plugins ex |
| cept packetLogger are now safe to add and remove while RakPeer is active |
| .                                                                        |
|     ReplicaManager3: Fix crash with existing object construction for an  |
| object that cannot be found. Updated QueryConstruction_PeerToPeer() and  |
| QuerySerialization_PeerToPeer() parameter lists. BroadcastDestructionLis |
| t now automatically ignores replicas currently being deallocated by Repl |
| icaManager3 itself. Added QueryRelayDestruction(). User can override Que |
| ryRelayDestruction() to return false to reduce unnecessary event broadca |
| sting for a peer to peer game.                                           |
|     XBOX 360: Fixed crash on cable disconnect.                           |
|     PS3: Fixed sending to multiple recipients for Console_SendGUIInvitat |
| ionToRoom_PS3. Also used RakString::TruncateUTF8() instead of RakString: |
| :Truncate().                                                             |
|     Vita: Added missing library termination call in RakPeer destructor.  |
|     AutopatcherServer: Fixed problem where a user disconnecting while a  |
| thread was working on that user would result in that thread being unavai |
| lable for use from then on                                               |
|     FileListTransfer: Fixed showing 0% for OnFileProgress for the last p |
| art of a file                                                            |
|     UDPProxy: Added targetGuid to the callbacks that didn't already have |
|  it in UDPProxyClientResultHandler                                       |
|     RakString: Added GetLengthUTF8 and TruncateUTF8                      |
|     Irrlicht demo: Updated to Irrlicht 1.7.2                             |
|     4.037 (4/4/2012)                                                     |
|     RakPeer: Fixed bad memory access in GetClientPublicKeyFromSystemAddr |
| ess(). Fixed incorrectly sending to self through loopback when sending t |
| hrough UDPForwader.                                                      |
|     ReplicaManager3: Now supports multiple worlds with one instance of t |
| he plugin, as opposed to requiring one instance per world before. This i |
| mproves world lookup speed per packet from O(n) to O(1) when using multi |
| ple worlds. Added Connection_RM3::QuerySerializationList() so the user c |
| an control in what order and how many Replica3 instances are serialized  |
| for a ReplicaManager3::Update() cycle. Can be used to prioritize what Re |
| plica3 instances are serialized while under limited bandwidth by checkin |
| g SerializeParameters::bitsWrittenSoFar                                  |
|     Vita: Lobby2Client_Vita now completed for basic operations.          |
|     PS3: Use npId.handle.data to support cross-play with Vita.           |
|     TeamManager: New feature added to manage teams in games. Plugin, sam |
| ple, manual page added. Replaces TeamBalancer, which is now obsolete.    |
|     AutopatcherServer: Fixed crash that could occur on a client disconne |
| ct while data was moving between threads. Clarified output from sample A |
| utopatcherClient sample.                                                 |
|     LibCat: Source/cat moved to DependentExtensions/cat. Removed FastDel |
| egate to improve compilation compatibility                               |
|     TCP Interface: Changed SSLv2_client_method to SSLv23_client_method() |
| . Fixes samples for EmailSender class and to Rackspace.                  |
|     FileListTransfer: Ensure each thread only works on one system at a t |
| ime. Previously, subsequent calls would add files to the thread already  |
| working causing shared memory errors. Changed reported value for byteLen |
| gthOfThisSet to actual bytes sent, not just total size of files. Return  |
| transport layer based progress notification on incremental read chunks.  |
| Clarified output from sample.                                            |
|     Swig / C#: Exposed GetTime(). Fixed compilation on Linux.            |
|     FullyConnectedMesh2: Changed to return UNASSIGNED_RAKNET_GUID as las |
| t host on first ID_FCM2_NEW_HOST notification                            |
|     Encryption: Fixed sample when using two-way authentication           |
|     CloudServer: Fixed bad check of OnReleaseRequest                     |
|     Lobby2Client_Steam: Fixed steam integration to cancel an operation w |
| hen the callback object had already been destroyed.                      |
|     4.04 (5/10/2012)                                                     |
|     ReplicaManager3: Fix incorrectly calling PostDeserializeConstruction |
|  when PostDeserializeConstructionExisting should be called.              |
|     UDPForwarder: Fix unnecessary assert                                 |
|     FullyConnectedMesh2: Added StartVerifiedJoin()                       |
|     NatPunchthroughClient: Removed OpenNATGroup(). Use FullyConnectedMes |
| h2::StartVerifiedJoin() instead.                                         |
|     Added ComprehensivePCGame sample                                     |
|     Fixed RakNetGUID::ToString not returning UNASSIGNED_RAKNET_GUID      |
|     Fixed crash in PerGameRoomsContainer::DestroyRoomIfDead              |
|     4.05 (7/12/2012)                                                     |
|     RakPeerInterface: Fixed ApplyNetworkSimulator only sending one datag |
| ram an update tick. Fixed bug where if the packetloss caused receipt of  |
| a duplicated RELIABLE_SEQUENCED or UNRELIABLE_SEQUENCED datagram, it cou |
| ld be returned to the user twice. Account for time variable overflow if  |
| a system had been running a very long time.                              |
|     FullyConnectedMesh2: Fixed StartVerifiedJoin when multiple systems j |
| oin at the same time.                                                    |
|     ReplicaManager3: Fixed SerializeParameters::whenLastSerialized not b |
| eing set. Assert if you reference the same thing twice.                  |
|     UDPForwarder: Rewritten to fix unknown thread-related problems causi |
| ng forwarding to fail                                                    |
|     Rooms: Fixed NetworkedQuickJoinUser::Serialize. JoinedRoomResult now |
|  serializes joiningMemberGuid.                                           |
|     FileListTransfer: Fixed RemoveReceiver if more than one set of files |
|  are transferred to the same system simultaneously.                      |
|     TeamManager: Can now be used in a limited sense in single player (wh |
| en not attached to RakPeerInterface)                                     |
|     UDPProxyClient: Now returns server ip and port when returning ID_UDP |
| _PROXY_IN_PROGRESS so the user can take over an existing forwarding port |
| .                                                                        |
|     RakString: Added FormatForPOST() and FormatForGet() in order to redu |
| ce reliance on HTTPConnection class.                                     |
|     PS3 / Vita: Console_SendDataMessageToUser_PS3 now asserts if message |
|  size exceeds max for the target platform                                |
|     New plugin: StatisticsHistory. Detailed tracking of connection stati |
| stics for use in bandwidth optimization by the user.                     |
|     New plugin: LibVoice, can cross compile to PS3 and Vita to support v |
| oice chat. Replaces AVC2 when turned on in NativeFeatureIncludes.h.      |
|     4.051 (7/29/2012)                                                    |
|     Fix SWIG build broken in 4.05                                        |
|     Remove unnecessary call to SendUnifiedToMultiple in Lobby2Server::Ex |
| ecuteCommand                                                             |
|     ThreadPool will sleep on non-windows platforms to reduce CPU usage   |
|     Fix bus error when calling CloseConnection in TCPInterface on 64 bit |
|  Linux.                                                                  |
|     Lobby2Server will now call callbacks added with Lobby2Plugin::AddCal |
| lbackInterface                                                           |
|     Crash fix when binding additional sockets at runtime in RakPeer      |
|     Fixed RakWString when serialzing between systems that have different |
|  sizes for wchar_t                                                       |
|     TeamManager: Now ignores duplicate team member insertions            |
|     StatisticsHistory: Fix sorting values, add ability to merge entries  |
| with the same timestamp                                                  |
|     ReplicaManager3: Change signature for OnSerializeTransmission        |
|     4.06 (10/11/2012)                                                    |
|     RakPeer: Improve congestion control being too sensitive to latency v |
| ariation, reducing bandwidth by about 50% on megabyte and faster connect |
| ions.                                                                    |
|     PS3, Vita: Marshal system callbacks to happen on user thread. Was pr |
| eviously causing thread corruption of rooms list.                        |
|     XBOX 360: Fix crash on disconnect when XnetQosServiceLookup fails.   |
|     ReplicaManager3: Fix QueryReplicaList not passing arguments by refer |
| ence. Fix QUERY_CONNECTION_FOR_REPLICA_LIST when destroying Replicas.    |
|     RoomsPlugin: Fixed being able to issue commands for any user, rather |
|  than just the one(s) you have logged in with.                           |
|     Native Client support: Added beta support for Native Client. Require |
| s define RAKPEER_USER_THREADED and for the user to execute RakPeer::RunR |
| ecvFromOnce() and RakPeer::RunUpdateCycle() from the main thread.        |
|     Team Manager: Fix JoinRequestHelperComp function.                    |
|     RPC4Plugin: Fix sending return value when using CallBlocking().      |
|     Cmake: Simplified in order to fix build errors.                      |
|     4.061 (11/15/12)                                                     |
|     Windows Phone 8: Now supported.                                      |
|     ReadyEvent: Updated to use RakNetGUID instead of SystemAddress.      |
|     RakPeer: Fixed assert in ReliabilityLayer.cpp if you are debugging o |
| ne system while a connected system is running.                           |
|     RakNetSocket: Now used to pass around a socket variable. Used to mak |
| e supporting Native Client and Windows Store easier. RakPeerInterface no |
|  longer uses RakNetSmartPtr.                                             |
|     4.062 (11/23/12)                                                     |
|     TCPInterface: Now supports PluginInterface2                          |
|     HTTPConnection2 added. Deprecated HTTPConnection. Updated Comprehens |
| ivePCGame sample to use HTTPConnection2 instead of CloudClient           |
|     Added jansson-2.4 to DependentExtensions                             |
|     Chrome: Updated to PPB_UDPSocket_Private_0_4.                        |
|     Many updates to the manual.                                          |
|     4.063 (12/4/12)                                                      |
|     Internal SocketLayer and RakNetSocket classes now deprecated. Using  |
| RakNetSocket2 for most operations. This is an internal architectual chan |
| ge in order to better support native client and add support for Windows  |
| 8 store.                                                                 |
|     4.064 (12/17/12)                                                     |
|     Fix PacketizedTCP not working.                                       |
|     Autopatcher: Fixed cached sends improperly implemented. No longer st |
| ore full files in cache when a patch is available. Added Add allowDownlo |
| adOfOriginalUnmodifiedFiles.                                             |
|     Added RelayPlugin.                                                   |
|     Added nackl_sdk solution and project.                                |
|     4.065 (12/19/12)                                                     |
|     Fixed SWIG not working, by removing usage of RakNetSocket.           |
|     Use natpunch.jenkinssoftware.com instead of a hardcoded IP for the p |
| ublic test server.                                                       |
|     4.066 (1/10/13)                                                      |
|     Added windows store 8 support. No TCP support, RakPeer only. IPV4 on |
| ly. See readme.txt for information on this.                              |
|     Renamed the output of the LibStatic and DLL projects.                |
|     IOS fixes.                                                           |
|     BitStream now has a private assigment operator.                      |
|     4.067 (1/26/13)                                                      |
|     Fix PS3 which was broken in 4.066.                                   |
|     Update Vita project to VS2010, and fix functionality, which was brok |
| en at an unknown time by a prior SDK release.                            |
|     Fix RNS2_Berkley::SetNonBlockingSocket for non-windows platforms.    |
|     Added CFSocket when __APPLE__ to wakeup 3g antenna (may not work).   |
|     Added RakNet_IOS_XCode.                                              |
|     Added RakPeer::SetIncomingDatagramEventHandler() so that an can appl |
| ication can selectively prevent RakPeer from handling datagrams, for exa |
| mple datagrams from an external application. When used in conjunction wi |
| th RakPeer::GetSockets() for sendto calls, the same socket can be shared |
|  between RakPeer and an external application.                            |
|     Add AddParticipantRequestFromClient to RelayPlugin.                  |
|     Add missing Windows Store 8 files to DependentExtensions.            |
|     Updated readme.txt about Unreal Engine integrations                  |
|     4.068 (2/6/13)                                                       |
|     FullyConnectedMesh2; Fix verified joins from outside a LAN.          |
|     NATTypeDetectionClient: Fix crash on shutdown.                       |
|     RakString: Fix FormatForDelete                                       |
|     4.069 (3/10/13)                                                      |
|     FileListTransfer: (TCP) will now continually print download progress |
|  notifications for smooth progress bar notifications in a UI.            |
|     RakPeer: Fixed potential ID_OUT_OF_BAND_INTERNAL crash if sending a  |
| message with too short of a length. Fix memory leak when using ApplyNetw |
| orkSimulator.                                                            |
|     PS3: Added callSceNpBasicRegisterContextSensitiveHandler. Fixed memo |
| ry leak with Lobby2Client_PS3. Added termnp2 to Client_Logoff_PS3        |
|     Autopatcher: Now supports large files. AutopatcherPostgreRepository2 |
|  was added to keep files on disk, rather than store in the repository. T |
| his is because PostgreSQL fails to store files above several hundred meg |
| abytes. Additionally, the database table now stores a column patchAlgori |
| thm. Both the client and server can override the method used to create a |
| nd apply patches. This was done becuase bsdiff takes excessive memory to |
|  generate patches. The sample shows how to use xdelta on the server, ins |
| tead of bsdiff, if the file is larger than 33554432 bytes.               |
|     RelayPlugin: Added for internal use. A simple implementation of chat |
|  messages between systems, and chat rooms.                               |
|     NATTypeDetectionServer: Reduced CPU usage for non-blocking recvfrom  |
|     PS4: Support added                                                   |
|     Lib: Names of binaries under /lib changed to include $(SolutionName) |
|  because the VS2008 version is not compatible later versions of Visual S |
| tudio. See http://stackoverflow.com/questions/2896754/link-error-after-u |
| pdate-from-vs2008-to-vs2010                                              |
|     SHA: Prior code didn't work, updated to current version. Also added  |
| SHA1HMAC                                                                 |
|     APPLE: Fix crash on failing to create socket.                        |
|     4.07 (5/30/13)                                                       |
|     RakPeer: Enforce MAXIMUM_MTU_SIZE for incoming connections, even if  |
| the network allows a larger datagram. Add packet->guid to ID_UNCONNECTED |
| _PING and ID_UNCONNECTED_PING_OPEN_CONNECTIONS. Added virtual void SetIn |
| ternalID(SystemAddress systemAddress, int index=0)=0;                    |
|     Autopatcher: Send patches incrementally if they are larger than 1 me |
| gabyte.                                                                  |
|     ReplicaManager3: Calling Reference twice on the same Replica3 will n |
| o longer assert, will just ignore the 2nd call. Added AutoCreateConnecti |
| onList.                                                                  |
|     StatisticsHistory: Fix recent sum of squares                         |
|     HTTPConnection2: Fix IPV6                                            |
|     ComprehensivePCGame: now uses asynch UPNP check                      |
|     4.08 (7/9/13)                                                        |
|     NatPunchthroughServer: Fixed crash when the sender guid is equal to  |
| the recipient guid                                                       |
|     HTTPConnection2: Now supports chunked responses                      |
|     Lobby2: Fix always returning resultCode=L2RC_UNSUPPORTED_PLATFORM; o |
| n the PC                                                                 |
|     MasterServer2: Use JSON_PRESERVE_ORDER when using SSL                |
|     PS4: Updated sample to work with current SDK. Fixed incorrect endian |
|  reporting                                                               |
|     FullyConnectedMesh2: Add SkipToVJCUserData(), WriteVJCUserData() in  |
| case the user wants to add data to verified join responses               |
|     NATPuncthroughClient: Detect port stride and better estimate future  |
| router port mappings                                                     |
|     NetworkIDManager: Add Clear() function                               |
|     RakSleep (affects RakPeer and others): Fix memory leak on Linux      |
|     RandSync: Added, use with ReplicaManager3 to synch random number gen |
| erators                                                                  |
|     ReplicaManager3: Minor fixes                                         |
|     SocketLayer: Add #include netdb.h for Linux compilation              |
|     Documentation: Improved NAT traversal architecture                   |
|                                                                          |
| \                                                                        |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ----------------------
  [Index](index.html)\
  ----------------------


