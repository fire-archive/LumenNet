![Oculus VR, Inc.](RakNet_Icon_Final-copy.jpg){width="150"
height="150"}\
\
  ------------------------------------------------------
  <span class="RakNetWhiteHeader"> Introduction</span>
  ------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Manual Last Updated 11/19/2012. See       |
| readme.txt for the current version number.</span>                        |
|                                                                          |
| RakNet is a high-performance network API designed for games or other     |
| high-performance network applications. RakNet is intended to provide     |
| most to all features modern games need, such as a master server,         |
| autopatcher, voice chat, and cross-platform capabilities. RakNet         |
| currently supports Windows, PlayStation 3, XBOX 360, PlayStation Vita,   |
| Linux, Mac, the iPhone, Android, and Windows Phone 8.                    |
+--------------------------------------------------------------------------+

  -----------------------------------------------------
   <span class="RakNetWhiteHeader">Quick Start</span>
  -----------------------------------------------------

+--------------------------------------------------------------------------+
| [Components of a multiplayer game](multiplayergamecomponents.html)\      |
| [System Overview](systemoverview.html)\                                  |
| [Detailed Implementation](detailedimplementation.html)\                  |
| [Tutorial](tutorial.html)\                                               |
| [Compiler Setup (Visual Studio)](compilersetup.html)\                    |
| [Compiler Setup (XCode)](compilersetup_xcode.html)\                      |
| [Optional 3rd party dependencies](dependencies.html)\                    |
| [HowTo](http://www.jenkinssoftware.com/forum/index.php?topic=584.0)\     |
+--------------------------------------------------------------------------+

  ------------------
   Training Videos
  ------------------

+--------------------------------------------------------------------------+
| [Introduction:Major                                                      |
| Features](http://www.youtube.com/watch?v=sez3o00uCqU)\                   |
| [Tutorial 1:                                                             |
| RPC3](http://www.jenkinssoftware.com/raknet/manual/RPC3Video.htm)\       |
| [Tutorial 2:                                                             |
| ReplicaManager3](http://www.jenkinssoftware.com/raknet/manual/ReplicaMan |
| ager3Video.htm)\                                                         |
| [Tutorial 3:                                                             |
| Autopatcher](http://www.jenkinssoftware.com/raknet/manual/AutopatcherVid |
| eo.htm)\                                                                 |
| [Tutorial 4: A complete sample covering object replication, teams,       |
| player hosted rooms and lobbies, NAT traversal, and host                 |
| migration](http://www.youtube.com/watch?v=w4OUGeLKcss)\                  |
+--------------------------------------------------------------------------+

  -----------------
   Feature Videos
  -----------------

+--------------------------------------------------------------------------+
| [Networked logging with                                                  |
| SQLiteClientLoggerPlugin](http://www.jenkinssoftware.com/raknet/manual/S |
| QLite3LoggerPluginVideo.html)\                                           |
+--------------------------------------------------------------------------+

  ----------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}<span class="RakNetWhiteHeader">The Basics</span>
  ----------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| [Startup](startup.html)\                                                 |
| - Starting up RakPeerInterface, and the thread sleep timer explained     |
|                                                                          |
| [Connecting](connecting.html)\                                           |
| - How to find and connect to other systems, and what to do if there are  |
| problems                                                                 |
|                                                                          |
| [Creating Packets](creatingpackets.html)\                                |
| - How to create custom packets using structures and bitstreams, and how  |
| to encode timestamps.\                                                   |
| \                                                                        |
| [Sending Packets](sendingpackets.html)\                                  |
| - How to send packets already prepared, and what parameters to use.\     |
| \                                                                        |
| [Receiving Packets](receivingpackets.html)\                              |
| - How to converting raw data back to a packet you can read via a         |
| structure or bitstream.                                                  |
|                                                                          |
| [SystemAddress](systemaddresses.html)\                                   |
| - Describes the purpose and use of the SystemAddress structure used in   |
| packets and in some function parameters.                                 |
|                                                                          |
| [Bitstreams](bitstreams.html)\                                           |
| - An overview of RakNet's bitstream class, used throughout the API.      |
|                                                                          |
| [Reliability types](reliabilitytypes.html)\                              |
| - Covers parameters you can use to control how data gets sent.           |
|                                                                          |
| [Network Messages](networkmessages.html)\                                |
| - Gives an overview of the messages the API will send to the user. This  |
| is also listed in MessageIdentifiers.h.                                  |
|                                                                          |
| [Timestamping your packets](timestamping.html)\                          |
| - Covers the purpose of timestamps.\                                     |
| \                                                                        |
| [NetworkIDObject](networkidobject.html)\                                 |
| - A Utility class to give each class instance a unique identifier that   |
| all systems can share.                                                   |
|                                                                          |
| [Statistics](statistics.html)\                                           |
| - The statistics that RakNet provides.\                                  |
| \                                                                        |
| [Secure connections](secureconnections.html)\                            |
| - How to activate and use secure connections.                            |
|                                                                          |
| [Master server](http://masterserver2.raknet.com/)\                       |
| - Our hosted master server service, to find other games on the internet. |
|                                                                          |
| [Cloud hosting](cloudhosting.html)\                                      |
| - Setting up RakNet with cloud-hosted services                           |
|                                                                          |
| [Rackspace interface](rackspaceinterface.html)\                          |
| - C++ interface to Rackspace, allowing you to programatically create,    |
| delete, reboot, image, and perform other operations on servers.          |
|                                                                          |
| [NAT traversal architecture](nattraversalarchitecture.html)\             |
| - How to use combine UPNP, NAT type detection, NAT punchthrough, and     |
| Router2 so P2P connections complete quickly and efficiently.\            |
| \                                                                        |
| [Preprocessor Directives](preprocessordirectives.html)\                  |
| - Enables you to rebuild the library with different code settings.       |
|                                                                          |
| [Custom Memory Management](custommemorymanagement.html)\                 |
| - For consoles, memory tracking, etc.                                    |
|                                                                          |
| [IPV6 support](ipv6support.html)\                                        |
| - The next-generation IP address format.                                 |
|                                                                          |
| [Marmalade integration](marmalade.html)\                                 |
| - Integration with the Marmalade SDK for the IOS and Android platforms.  |
+--------------------------------------------------------------------------+

  -----------------------------------------------------
  **<span class="RakNetWhiteHeader"> Plugins</span>**
  -----------------------------------------------------

+--------------------------------------------------------------------------+
| [Plugin Interface 2](plugininterface.html)\                              |
| - The base class of all plugins\                                         |
| [Autopatcher](autopatcher.html)\                                         |
| - Overview of the autopatcher included with RakNet.                      |
|                                                                          |
| [RPC3](RPC3Video.htm)\                                                   |
| - Call C and C++ functions with native parameter lists, using Boost for  |
| additional functionality.                                                |
|                                                                          |
| [RPC4](rpc4.html)\                                                       |
| - Call C functions, no external dependencies.                            |
|                                                                          |
| [Connection Graph](connectiongraph.html)\                                |
| - A plugin-in that maintains a graph of the entire network.              |
|                                                                          |
| [Directory Delta Transfer](directorydeltatransfer.html)\                 |
| - Send changed or missing files between directories. In essence, a       |
| simple autopatcher that can be used for transmitting levels, skins,      |
| etc.\                                                                    |
| \                                                                        |
| [File List Transfer](filelisttransfer.html)\                             |
| - Plugin to send a list of files, encoded in the FileList structure\     |
| \                                                                        |
| [Fully Connected Mesh 2](fullyconnectedmesh2.html)\                      |
| - A plug-in for peer to peer games, for host determination and verified  |
| connectivity to the mesh.                                                |
|                                                                          |
| [Lobby2Client - PC](lobby.html)\                                         |
| - PostgreSQL backed database for game data, including users, friends,    |
| clans, messages                                                          |
|                                                                          |
| [Lobby2Client - Steam](steamlobby.html)\                                 |
| - Steamworks powered backend, using the Lobby2 interface.                |
|                                                                          |
| [Lobby2Client - PS3\                                                     |
| ](ps3lobby.html)- PS3 NP backend, using the Lobby2 interface.            |
|                                                                          |
| [Lobby2Client - XBOX 360](xbox360lobby.html)\                            |
| - LIVE backend and voice chat support, using the Lobby2 interface with   |
| support for RakVoiceXBOX360Plugin and FullyConnectedMesh2                |
|                                                                          |
| [Lobby2Client - Games for Windows Live](gfwllobby.html)\                 |
| - Same as XBOX 360 backend but runs on Windows                           |
|                                                                          |
| [Message Filter](messagefilter.html)\                                    |
| - Prevent unwanted network messages based on sender for added security.  |
|                                                                          |
| [NAT type detection](nattypedetection.html)\                             |
| - Find out what kind of NAT you are behind to keep users that will       |
| probably not be able to connect separate                                 |
|                                                                          |
| [NAT punchthrough](natpunchthrough.html)\                                |
| - Connect users behind NAT. Required for peer to peer, voice             |
| communication, or to allow players to host their own servers.            |
|                                                                          |
| [Packet Logger](packetlogger.html)\                                      |
| - Print network traffic to the screen, file, or elsewhere.               |
|                                                                          |
| [RakVoice](rakvoice.html)\                                               |
| - Overview of RakVoice. Refer to RakVoice.h for full implementation and  |
| function details.                                                        |
|                                                                          |
| [Ready Event](readyevent.html)\                                          |
| - Synchronize when a group of systems are all ready on a common          |
| identifier, useful in peer to peer enviroments to start games at the     |
| same time, or progress turns in a turn based game.                       |
|                                                                          |
| [Replica Manager 3](replicamanager3.html)\                               |
| - A plug-in that provides management for your game objects and players   |
| to make serialization, scoping, and object creation and destruction      |
| easier.\                                                                 |
| \                                                                        |
| [Router2](router.html)\                                                  |
| - Send network messages to one or more remote systems we are not         |
| directly connected to\                                                   |
| \                                                                        |
| [SQLite3LoggerPlugin](sqlite3loggerplugin.html)\                         |
| - Create networked log files using SQLite. Based on                      |
| [SQLite3Plugin](sqlite3plugin.html)                                      |
|                                                                          |
| [SQLite3Plugin](sqlite3plugin.html)\                                     |
| - Execute statements over the network with SQLite (replacement for       |
| LightweightDatabase)                                                     |
|                                                                          |
| [TeamManager](teammanager.html)\                                         |
| - Manages lists of teams and team members. Supports client/server and    |
| peer to peer                                                             |
|                                                                          |
| [TwoWayAuthentication](twowayauthentication.html)\                       |
| - Implements [Two Way                                                    |
| Authentication](http://en.wikipedia.org/wiki/Mutual_authentication),     |
| validating a predesignated password without transmitting the password.   |
+--------------------------------------------------------------------------+

  ----------------------------------------------------------
   **<span class="RakNetWhiteHeader">C\# and SWIG</span>**
  ----------------------------------------------------------

+--------------------------------------------------------------------------+
| [Swig Tutorial](swigtutorial.html)\                                      |
| - How to run RakNet from C\# using SWIG and possibly Mono.               |
|                                                                          |
| [Unity Integration](csharpunity.html)\                                   |
| - How RakNet is used with Unity, and how to upgrade to version 4.x       |
+--------------------------------------------------------------------------+

  -------------------------------------------------------
   **<span class="RakNetWhiteHeader">Utilities</span>**
  -------------------------------------------------------

+--------------------------------------------------------------------------+
| [Crash Reporter](crashreporter.html)\                                    |
| - Sends mini-dumps when your application crashes, writing to disk and/or |
| sending an email.                                                        |
|                                                                          |
| [Console Server](consoleserver.html)\                                    |
| - Text based backdoor to a server using either secure RakNet or telnet,  |
| allowing execution of predesignated commands or arbitrary command        |
| strings.                                                                 |
|                                                                          |
| [Email Sender](emailsender.html)\                                        |
| - Used by the crash reporter to send emails via TCP                      |
|                                                                          |
| [String Compressor / String Table](stringcompressor.html)\               |
| - Used to encode strings with less bandwidth and more security.          |
|                                                                          |
| [TCP Interface](tcpinterface.html)\                                      |
| - Wrapper class for TCP connections                                      |
+--------------------------------------------------------------------------+

  ------------------------------------------------------
  **<span class="RakNetWhiteHeader"> 3D Demos</span>**
  ------------------------------------------------------

+--------------------------------------------------------------------------+
| [Ogre 3D Interpolation Demo](ogre3dinterpdemo.html)\                     |
| - Use [Ogre 3D](http://www.ogre3d.org/) to show a demo of popping        |
| popcorn over a client/server network, using                              |
| [ReplicaManager3](replicamanager3.html)                                  |
|                                                                          |
| [Irrlicht FPS Demo](irrlichtfpsdemo.html)\                               |
| - Use [Irrlicht](http://irrlicht.sourceforge.net/) to show a 3D FPS demo |
| using peer to peer with NAT punchthrough. Also uses                      |
| [ReplicaManager3](replicamanager3.html)                                  |
+--------------------------------------------------------------------------+

  ------------------------------------------------------------------------
  **<span class="RakNetWhiteHeader"> Technical Design Documents</span>**
  ------------------------------------------------------------------------

  -----------------------------------------------
  [UML Diagram](RakNetUML.jpg)\
  [Potential Bluetooth support](bluetooth.html)
  -----------------------------------------------

  -------------------------------------------------------------
  **<span class="RakNetWhiteHeader"> Data Structures</span>**
  -------------------------------------------------------------

+--------------------------------------------------------------------------+
| DS\_BinarySearchTree.h - [Binary search                                  |
| tree](http://en.wikipedia.org/wiki/Binary_search_tree), and an [AVL      |
| balanced](http://en.wikipedia.org/wiki/AVL_tree) binary search tree.\    |
| DS\_BPlusTree.h - [BPlus tree](http://en.wikipedia.org/wiki/B%2B_tree)   |
| for fast lookup, delete, and insert.\                                    |
| DS\_BytePool.h - Returns data blocks at certain size thresholds to       |
| reduce memory fragmentation.\                                            |
| DS\_ByteQueue.h - A queue specialized for reading and writing bytes.\    |
| DS\_Heap.h - [Heap data                                                  |
| structure](http://en.wikipedia.org/wiki/Heap_%28data_structure%29),      |
| includes both minheap and maxheap.\                                      |
| DS\_HuffmanEncodingTree.h - [Huffman encoding                            |
| tree](http://en.wikipedia.org/wiki/Huffman_coding), used to find the     |
| minimal bitwise representation given a frequency table.\                 |
| DS\_HuffmanEncodingTreeFactory.h - Creates instances of the Huffman      |
| encoding tree.\                                                          |
| DS\_HuffmanEncodingTreeNode.h - Node in the Huffman encoding tree.\      |
| DS\_LinkedList.h - Standard [linked                                      |
| list](http://en.wikipedia.org/wiki/Linked_list).\                        |
| DS\_List.h - Dynamic [array](http://en.wikipedia.org/wiki/Array)         |
| (sometimes improperly called a vector). Also doubles as a                |
| [stack](http://en.wikipedia.org/wiki/Stack_%28data_structure%29).\       |
| DS\_Map.h - ([Associative                                                |
| array](http://en.wikipedia.org/wiki/Associative_array)) Ordered list     |
| with an per-element sort key.\                                           |
| DS\_MemoryPool.h - Allocate and free reused instances of a fixed size    |
| structure, used to reduce memory fragmentation.\                         |
| DS\_Multilist\_h - (Added 4/8/2009) Combines a list, stack, queue, and   |
| ordered list into one class with a common interface.\                    |
| DS\_OrderedChannelHeap.h - Maxheap which returns a node based on the     |
| relative weight of the node's associated channel. Used for task          |
| scheduling with priorities.\                                             |
| DS\_OrderedList.h - List ordered by an arbitrary key via                 |
| [quicksort](http://en.wikipedia.org/wiki/Quicksort).\                    |
| DS\_Queue.h - Standard                                                   |
| [queue](http://en.wikipedia.org/wiki/Queue_%28data_structure%29)         |
| implemented with an array\                                               |
| DS\_QueueLinkedList.h - Standard queue implemented with a [linked        |
| list](http://en.wikipedia.org/wiki/Linked_list)\                         |
| DS\_RangeList.h - Stores a list of numerical values, and when the values |
| are sequential, represents them as a range rather than individual        |
| elements. Useful when storing many values that are usually sequential.\  |
| DS\_Table.h - [Table](http://en.wikipedia.org/wiki/Table_%28database%29) |
| with columns and rows, and operations on that table.\                    |
| DS\_Tree.h - Noncyclic                                                   |
| [graph](http://en.wikipedia.org/wiki/Graph_%28data_structure%29)\        |
| DS\_WeightedGraph.h - Graph with weighted edges, used for routing via    |
| [Dijkstra's                                                              |
| algorithm](http://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)\         |
| RakString - String implementation, up to 4.5 times faster than           |
| std::string                                                              |
+--------------------------------------------------------------------------+

  ----------
   Support
  ----------

  --------------------------------------------------------
  [FAQ](faq.html)\
  [Debugging Disconnections](debuggingdisconnects.html)\
  [Programming Tips](programmingtips.html)\
  [Revision Log](revisionlog.html)\
  --------------------------------------------------------


