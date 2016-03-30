<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Network Messages
  -------------------------------------------------------

+--------------------------------------------------------------------------+
| Messages from the network engine\                                        |
| \                                                                        |
| Certain packets that you get will not be from your code, using your      |
| defined types, but are instead from the network engine. However, you     |
| have to know what they are to handle them properly. The first byte of    |
| each packet that originated from the API will map to one of the          |
| following enumerations. Possible recipient systems are in brackets. To   |
| convert these enumerations to a string, use                              |
| PacketLogger::BaseIDTOString()                                           |
|                                                                          |
| //\                                                                      |
| // RESERVED TYPES - DO NOT CHANGE THESE\                                 |
| // All types from RakPeer\                                               |
| //\                                                                      |
| /// These types are never returned to the user.\                         |
| /// Ping from a connected system. Update timestamps (internal use only)\ |
| ID\_CONNECTED\_PING,\                                                    |
| /// Ping from an unconnected system. Reply but do not update timestamps. |
| (internal use only)\                                                     |
| ID\_UNCONNECTED\_PING,\                                                  |
| /// Ping from an unconnected system. Only reply if we have open          |
| connections. Do not update timestamps. (internal use only)\              |
| ID\_UNCONNECTED\_PING\_OPEN\_CONNECTIONS,\                               |
| /// Pong from a connected system. Update timestamps (internal use only)\ |
| ID\_CONNECTED\_PONG,\                                                    |
| /// A reliable packet to detect lost connections (internal use only)\    |
| ID\_DETECT\_LOST\_CONNECTIONS,\                                          |
| /// C2S: Initial query: Header(1), OfflineMesageID(16), Protocol         |
| number(1), Pad(toMTU), sent with no fragment set.\                       |
| /// If protocol fails on server, returns                                 |
| ID\_INCOMPATIBLE\_PROTOCOL\_VERSION to client\                           |
| ID\_OPEN\_CONNECTION\_REQUEST\_1,\                                       |
| /// S2C: Header(1), OfflineMesageID(16), server GUID(8), HasSecurity(1), |
| Cookie(4, if HasSecurity)\                                               |
| /// , public key (if do security is true), MTU(2). If public key fails   |
| on client, returns ID\_PUBLIC\_KEY\_MISMATCH\                            |
| ID\_OPEN\_CONNECTION\_REPLY\_1,\                                         |
| /// C2S: Header(1), OfflineMesageID(16), Cookie(4, if HasSecurity is     |
| true on the server), clientSupportsSecurity(1 bit),\                     |
| /// handshakeChallenge (if has security on both server and client),      |
| remoteBindingAddress(6), MTU(2), client GUID(8)\                         |
| /// Connection slot allocated if cookie is valid, server is not full,    |
| GUID and IP not already in use.\                                         |
| ID\_OPEN\_CONNECTION\_REQUEST\_2,\                                       |
| /// S2C: Header(1), OfflineMesageID(16), server GUID(8), mtu(2),         |
| doSecurity(1 bit), handshakeAnswer (if do security is true)\             |
| ID\_OPEN\_CONNECTION\_REPLY\_2,\                                         |
| /// C2S: Header(1), GUID(8), Timestamp, HasSecurity(1), Proof(32)\       |
| ID\_CONNECTION\_REQUEST,\                                                |
| /// RakPeer - Remote system requires secure connections, pass a public   |
| key to RakPeerInterface::Connect()\                                      |
| ID\_REMOTE\_SYSTEM\_REQUIRES\_PUBLIC\_KEY,\                              |
| /// RakPeer - We passed a public key to RakPeerInterface::Connect(), but |
| the other system did not have security turned on\                        |
| ID\_OUR\_SYSTEM\_REQUIRES\_SECURITY,\                                    |
| /// RakPeer - Wrong public key passed to RakPeerInterface::Connect()\    |
| ID\_PUBLIC\_KEY\_MISMATCH,\                                              |
| /// RakPeer - Same as ID\_ADVERTISE\_SYSTEM, but intended for internal   |
| use rather than being passed to the user.\                               |
| /// Second byte indicates type. Used currently for NAT punchthrough for  |
| receiver port advertisement. See ID\_NAT\_ADVERTISE\_RECIPIENT\_PORT\    |
| ID\_OUT\_OF\_BAND\_INTERNAL,\                                            |
| /// If RakPeerInterface::Send() is called where PacketReliability        |
| contains \_WITH\_ACK\_RECEIPT, then on a later call to\                  |
| /// RakPeerInterface::Receive() you will get ID\_SND\_RECEIPT\_ACKED or  |
| ID\_SND\_RECEIPT\_LOSS. The message will be 5 bytes long,\               |
| /// and bytes 1-4 inclusive will contain a number in native order        |
| containing a number that identifies this message.\                       |
| /// This number will be returned by RakPeerInterface::Send() or          |
| RakPeerInterface::SendList(). ID\_SND\_RECEIPT\_ACKED means that\        |
| /// the message arrived\                                                 |
| ID\_SND\_RECEIPT\_ACKED,\                                                |
| /// If RakPeerInterface::Send() is called where PacketReliability        |
| contains \_WITH\_ACK\_RECEIPT, then on a later call to\                  |
| /// RakPeerInterface::Receive() you will get ID\_SND\_RECEIPT\_ACKED or  |
| ID\_SND\_RECEIPT\_LOSS. The message will be 5 bytes long,\               |
| /// and bytes 1-4 inclusive will contain a number in native order        |
| containing a number that identifies this message. This number\           |
| /// will be returned by RakPeerInterface::Send() or                      |
| RakPeerInterface::SendList(). ID\_SND\_RECEIPT\_LOSS means that an ack   |
| for the\                                                                 |
| /// message did not arrive (it may or may not have been delivered,       |
| probably not). On disconnect or shutdown, you will not get\              |
| /// ID\_SND\_RECEIPT\_LOSS for unsent messages, you should consider      |
| those messages as all lost.\                                             |
| ID\_SND\_RECEIPT\_LOSS,\                                                 |
|                                                                          |
| //\                                                                      |
| // USER TYPES - DO NOT CHANGE THESE\                                     |
| //                                                                       |
|                                                                          |
| /// RakPeer - In a client/server environment, our connection request to  |
| the server has been accepted.\                                           |
| ID\_CONNECTION\_REQUEST\_ACCEPTED,\                                      |
| /// RakPeer - Sent to the player when a connection request cannot be     |
| completed due to inability to connect.\                                  |
| ID\_CONNECTION\_ATTEMPT\_FAILED,\                                        |
| /// RakPeer - Sent a connect request to a system we are currently        |
| connected to.\                                                           |
| ID\_ALREADY\_CONNECTED,\                                                 |
| /// RakPeer - A remote system has successfully connected.\               |
| ID\_NEW\_INCOMING\_CONNECTION,\                                          |
| /// RakPeer - The system we attempted to connect to is not accepting new |
| connections.\                                                            |
| ID\_NO\_FREE\_INCOMING\_CONNECTIONS,\                                    |
| /// RakPeer - The system specified in Packet::systemAddress has          |
| disconnected from us. For the client, this would mean the\               |
| /// server has shutdown.\                                                |
| ID\_DISCONNECTION\_NOTIFICATION,\                                        |
| /// RakPeer - Reliable packets cannot be delivered to the system         |
| specified in Packet::systemAddress. The connection to that\              |
| /// system has been closed.\                                             |
| ID\_CONNECTION\_LOST,\                                                   |
| /// RakPeer - We are banned from the system we attempted to connect to.\ |
| ID\_CONNECTION\_BANNED,\                                                 |
| /// RakPeer - The remote system is using a password and has refused our  |
| connection because we did not set the correct password.\                 |
| ID\_INVALID\_PASSWORD,\                                                  |
| // RAKNET\_PROTOCOL\_VERSION in RakNetVersion.h does not match on the    |
| remote system what we have on our system\                                |
| // This means the two systems cannot communicate.\                       |
| // The 2nd byte of the message contains the value of                     |
| RAKNET\_PROTOCOL\_VERSION for the remote system\                         |
| ID\_INCOMPATIBLE\_PROTOCOL\_VERSION,\                                    |
| // Means that this IP address connected recently, and can't connect      |
| again as a security measure. See\                                        |
| /// RakPeer::SetLimitIPConnectionFrequency()\                            |
| ID\_IP\_RECENTLY\_CONNECTED,\                                            |
| /// RakPeer - The sizeof(RakNetTime) bytes following this byte represent |
| a value which is automatically modified by the difference\               |
| /// in system times between the sender and the recipient. Requires that  |
| you call SetOccasionalPing.\                                             |
| ID\_TIMESTAMP,\                                                          |
| /// RakPeer - Pong from an unconnected system. First byte is             |
| ID\_UNCONNECTED\_PONG, second sizeof(RakNet::TimeMS) bytes is the ping,\ |
| /// following bytes is system specific enumeration data.\                |
| /// Read using bitstreams\                                               |
| ID\_UNCONNECTED\_PONG,\                                                  |
| /// RakPeer - Inform a remote system of our IP/Port. On the recipient,   |
| all data past ID\_ADVERTISE\_SYSTEM is whatever was passed to\           |
| /// the data parameter\                                                  |
| ID\_ADVERTISE\_SYSTEM,\                                                  |
| // RakPeer - Downloading a large message. Format is                      |
| ID\_DOWNLOAD\_PROGRESS (MessageID), partCount (unsigned int),\           |
| /// partTotal (unsigned int),\                                           |
| /// partLength (unsigned int), first part data (length &lt;=             |
| MAX\_MTU\_SIZE). See the three parameters partCount, partTotal\          |
| /// and partLength in OnFileProgress in FileListTransferCBInterface.h\   |
| ID\_DOWNLOAD\_PROGRESS,\                                                 |
| \                                                                        |
| /// ConnectionGraph2 plugin - In a client/server environment, a client   |
| other than ourselves has disconnected gracefully.\                       |
| /// Packet::systemAddress is modified to reflect the systemAddress of    |
| this client.\                                                            |
| ID\_REMOTE\_DISCONNECTION\_NOTIFICATION,\                                |
| /// ConnectionGraph2 plugin - In a client/server environment, a client   |
| other than ourselves has been forcefully dropped.\                       |
| /// Packet::systemAddress is modified to reflect the systemAddress of    |
| this client.\                                                            |
| ID\_REMOTE\_CONNECTION\_LOST,\                                           |
| /// ConnectionGraph2 plugin: Bytes 1-4 = count. for (count items)        |
| contains {SystemAddress, RakNetGUID}\                                    |
| ID\_REMOTE\_NEW\_INCOMING\_CONNECTION,                                   |
|                                                                          |
| /// FileListTransfer plugin - Setup data\                                |
| ID\_FILE\_LIST\_TRANSFER\_HEADER,\                                       |
| /// FileListTransfer plugin - A file\                                    |
| ID\_FILE\_LIST\_TRANSFER\_FILE,\                                         |
| // Ack for reference push, to send more of the file\                     |
| ID\_FILE\_LIST\_REFERENCE\_PUSH\_ACK,                                    |
|                                                                          |
| /// DirectoryDeltaTransfer plugin - Request from a remote system for a   |
| download of a directory\                                                 |
| ID\_DDT\_DOWNLOAD\_REQUEST,\                                             |
| \                                                                        |
| /// RakNetTransport plugin - Transport provider message, used for remote |
| console\                                                                 |
| ID\_TRANSPORT\_STRING,                                                   |
|                                                                          |
| /// ReplicaManager plugin - Create an object\                            |
| ID\_REPLICA\_MANAGER\_CONSTRUCTION,\                                     |
| /// ReplicaManager plugin - Changed scope of an object\                  |
| ID\_REPLICA\_MANAGER\_SCOPE\_CHANGE,\                                    |
| /// ReplicaManager plugin - Serialized data of an object\                |
| ID\_REPLICA\_MANAGER\_SERIALIZE,\                                        |
| /// ReplicaManager plugin - New connection, about to send all world      |
| objects\                                                                 |
| ID\_REPLICA\_MANAGER\_DOWNLOAD\_STARTED,\                                |
| /// ReplicaManager plugin - Finished downloading all serialized objects\ |
| ID\_REPLICA\_MANAGER\_DOWNLOAD\_COMPLETE,\                               |
| /// Serialize construction for an object that already exists on the      |
| remote system\                                                           |
| ID\_REPLICA\_MANAGER\_3\_SERIALIZE\_CONSTRUCTION\_EXISTING,\             |
| ID\_REPLICA\_MANAGER\_3\_LOCAL\_CONSTRUCTION\_REJECTED,\                 |
| ID\_REPLICA\_MANAGER\_3\_LOCAL\_CONSTRUCTION\_ACCEPTED,                  |
|                                                                          |
| /// RakVoice plugin - Open a communication channel\                      |
| ID\_RAKVOICE\_OPEN\_CHANNEL\_REQUEST,\                                   |
| /// RakVoice plugin - Communication channel accepted\                    |
| ID\_RAKVOICE\_OPEN\_CHANNEL\_REPLY,\                                     |
| /// RakVoice plugin - Close a communication channel\                     |
| ID\_RAKVOICE\_CLOSE\_CHANNEL,\                                           |
| /// RakVoice plugin - Voice data\                                        |
| ID\_RAKVOICE\_DATA,                                                      |
|                                                                          |
| /// Autopatcher plugin - Get a list of files that have changed since a   |
| certain date\                                                            |
| ID\_AUTOPATCHER\_GET\_CHANGELIST\_SINCE\_DATE,\                          |
| /// Autopatcher plugin - A list of files to create\                      |
| ID\_AUTOPATCHER\_CREATION\_LIST,\                                        |
| /// Autopatcher plugin - A list of files to delete\                      |
| ID\_AUTOPATCHER\_DELETION\_LIST,\                                        |
| /// Autopatcher plugin - A list of files to get patches for\             |
| ID\_AUTOPATCHER\_GET\_PATCH,\                                            |
| /// Autopatcher plugin - A list of patches for a list of files\          |
| ID\_AUTOPATCHER\_PATCH\_LIST,\                                           |
| /// Autopatcher plugin - Returned to the user: An error from the         |
| database repository for the autopatcher.\                                |
| ID\_AUTOPATCHER\_REPOSITORY\_FATAL\_ERROR,\                              |
| /// Autopatcher plugin - Finished getting all files from the             |
| autopatcher\                                                             |
| ID\_AUTOPATCHER\_FINISHED\_INTERNAL,\                                    |
| ID\_AUTOPATCHER\_FINISHED,\                                              |
| /// Autopatcher plugin - Returned to the user: You must restart the      |
| application to finish patching.\                                         |
| ID\_AUTOPATCHER\_RESTART\_APPLICATION,                                   |
|                                                                          |
| /// NATPunchthrough plugin: internal\                                    |
| ID\_NAT\_PUNCHTHROUGH\_REQUEST,\                                         |
| /// NATPunchthrough plugin: internal\                                    |
| ID\_NAT\_CONNECT\_AT\_TIME,\                                             |
| /// NATPunchthrough plugin: internal\                                    |
| ID\_NAT\_GET\_MOST\_RECENT\_PORT,\                                       |
| /// NATPunchthrough plugin: internal\                                    |
| ID\_NAT\_CLIENT\_READY,                                                  |
|                                                                          |
| /// NATPunchthrough plugin: Destination system is not connected to the   |
| server. Bytes starting at offset 1 contains the\                         |
| /// RakNetGUID destination field of NatPunchthroughClient::OpenNAT().\   |
| ID\_NAT\_TARGET\_NOT\_CONNECTED,\                                        |
| /// NATPunchthrough plugin: Destination system is not responding to      |
| ID\_NAT\_GET\_MOST\_RECENT\_PORT. Possibly the plugin is not installed.\ |
| /// Bytes starting at offset 1 contains the RakNetGUID destination field |
| of NatPunchthroughClient::OpenNAT().\                                    |
| ID\_NAT\_TARGET\_UNRESPONSIVE,\                                          |
| /// NATPunchthrough plugin: The server lost the connection to the        |
| destination system while setting up punchthrough.\                       |
| /// Possibly the plugin is not installed. Bytes starting at offset 1     |
| contains the RakNetGUID destination\                                     |
| /// field of NatPunchthroughClient::OpenNAT().\                          |
| ID\_NAT\_CONNECTION\_TO\_TARGET\_LOST,\                                  |
| /// NATPunchthrough plugin: This punchthrough is already in progress.    |
| Possibly the plugin is not installed.\                                   |
| /// Bytes starting at offset 1 contains the RakNetGUID destination field |
| of NatPunchthroughClient::OpenNAT().\                                    |
| ID\_NAT\_ALREADY\_IN\_PROGRESS,\                                         |
| /// NATPunchthrough plugin: This message is generated on the local       |
| system, and does not come from the network.\                             |
| /// packet::guid contains the destination field of                       |
| NatPunchthroughClient::OpenNAT(). Byte 1 contains 1 if you are the       |
| sender, 0 if not\                                                        |
| ID\_NAT\_PUNCHTHROUGH\_FAILED,\                                          |
| /// NATPunchthrough plugin: Punchthrough suceeded. See                   |
| packet::systemAddress and packet::guid. Byte 1 contains 1 if you are the |
| sender,\                                                                 |
| /// 0 if not. You can now use RakPeer::Connect() or other calls to       |
| communicate with this system.\                                           |
| ID\_NAT\_PUNCHTHROUGH\_SUCCEEDED,                                        |
|                                                                          |
| /// ReadyEvent plugin - Set the ready state for a particular system\     |
| /// First 4 bytes after the message contains the id\                     |
| ID\_READY\_EVENT\_SET,\                                                  |
| /// ReadyEvent plugin - Unset the ready state for a particular system\   |
| /// First 4 bytes after the message contains the id\                     |
| ID\_READY\_EVENT\_UNSET,\                                                |
| /// All systems are in state ID\_READY\_EVENT\_SET\                      |
| /// First 4 bytes after the message contains the id\                     |
| ID\_READY\_EVENT\_ALL\_SET,\                                             |
| /// \\internal, do not process in your game\                             |
| /// ReadyEvent plugin - Request of ready event state - used for pulling  |
| data when newly connecting\                                              |
| ID\_READY\_EVENT\_QUERY,                                                 |
|                                                                          |
| /// Lobby packets. Second byte indicates type.\                          |
| ID\_LOBBY\_GENERAL,                                                      |
|                                                                          |
| // RPC3, RPC4Plugin error\                                               |
| ID\_RPC\_REMOTE\_ERROR,\                                                 |
| /// Plugin based replacement for RPC system\                             |
| ID\_RPC\_PLUGIN,                                                         |
|                                                                          |
| /// FileListTransfer transferring large files in chunks that are read    |
| only when needed, to save memory\                                        |
| ID\_FILE\_LIST\_REFERENCE\_PUSH,\                                        |
| /// Force the ready event to all set\                                    |
| ID\_READY\_EVENT\_FORCE\_ALL\_SET,                                       |
|                                                                          |
| /// Rooms function\                                                      |
| ID\_ROOMS\_EXECUTE\_FUNC,\                                               |
| ID\_ROOMS\_LOGON\_STATUS,\                                               |
| ID\_ROOMS\_HANDLE\_CHANGE,                                               |
|                                                                          |
| /// Lobby2 message\                                                      |
| ID\_LOBBY2\_SEND\_MESSAGE,\                                              |
| ID\_LOBBY2\_SERVER\_ERROR,                                               |
|                                                                          |
| /// Informs user of a new host GUID. Packet::Guid contains this new host |
| RakNetGuid. The old host can be read out using                           |
| BitStream-&gt;Read(RakNetGuid) starting on byte 1\                       |
| ID\_FCM2\_NEW\_HOST,\                                                    |
| /// \\internal For FullyConnectedMesh2 plugin\                           |
| ID\_FCM2\_REQUEST\_FCMGUID,\                                             |
| /// \\internal For FullyConnectedMesh2 plugin\                           |
| ID\_FCM2\_RESPOND\_CONNECTION\_COUNT,\                                   |
| /// \\internal For FullyConnectedMesh2 plugin\                           |
| ID\_FCM2\_INFORM\_FCMGUID,                                               |
|                                                                          |
| /// UDP proxy messages. Second byte indicates type.\                     |
| ID\_UDP\_PROXY\_GENERAL,                                                 |
|                                                                          |
| /// SQLite3Plugin - execute\                                             |
| ID\_SQLite3\_EXEC,\                                                      |
| /// SQLite3Plugin - Remote database is unknown\                          |
| ID\_SQLite3\_UNKNOWN\_DB,\                                               |
| /// Events happening with SQLiteClientLoggerPlugin\                      |
| ID\_SQLLITE\_LOGGER,                                                     |
|                                                                          |
| /// Sent to NatTypeDetectionServer\                                      |
| ID\_NAT\_TYPE\_DETECTION\_REQUEST,\                                      |
| /// Sent to NatTypeDetectionClient. Byte 1 contains the type of NAT      |
| detected.\                                                               |
| ID\_NAT\_TYPE\_DETECTION\_RESULT,                                        |
|                                                                          |
| /// Used by the router2 plugin\                                          |
| ID\_ROUTER\_2\_INTERNAL,\                                                |
| /// No path is available or can be established to the remote system\     |
| /// Packet::guid contains the endpoint guid that we were trying to       |
| reach\                                                                   |
| ID\_ROUTER\_2\_FORWARDING\_NO\_PATH,\                                    |
| /// \\brief You can now call connect, ping, or other operations to the   |
| destination system.\                                                     |
| ///\                                                                     |
| /// Connect as follows:\                                                 |
| ///\                                                                     |
| /// RakNet::BitStream bs(packet-&gt;data, packet-&gt;length, false);\    |
| /// bs.IgnoreBytes(sizeof(MessageID));\                                  |
| /// RakNetGUID endpointGuid;\                                            |
| /// bs.Read(endpointGuid);\                                              |
| /// unsigned short sourceToDestPort;\                                    |
| /// bs.Read(sourceToDestPort);\                                          |
| /// char ipAddressString\[32\];\                                         |
| /// packet-&gt;systemAddress.ToString(false, ipAddressString);\          |
| /// rakPeerInterface-&gt;Connect(ipAddressString, sourceToDestPort,      |
| 0,0);\                                                                   |
| ID\_ROUTER\_2\_FORWARDING\_ESTABLISHED,\                                 |
| /// The IP address for a forwarded connection has changed\               |
| /// Read endpointGuid and port as per                                    |
| ID\_ROUTER\_2\_FORWARDING\_ESTABLISHED\                                  |
| ID\_ROUTER\_2\_REROUTED,                                                 |
|                                                                          |
| /// \\internal Used by the team balancer plugin\                         |
| ID\_TEAM\_BALANCER\_INTERNAL,\                                           |
| /// Cannot switch to the desired team because it is full. However, if    |
| someone on that team leaves, you will\                                   |
| /// get ID\_TEAM\_BALANCER\_SET\_TEAM later. Byte 1 contains the team    |
| you requested to join.\                                                  |
| ID\_TEAM\_BALANCER\_REQUESTED\_TEAM\_CHANGE\_PENDING,\                   |
| /// Cannot switch to the desired team because all teams are locked.      |
| However, if someone on that team leaves,\                                |
| /// you will get ID\_TEAM\_BALANCER\_SET\_TEAM later. Byte 1 contains    |
| the team you requested to join.\                                         |
| ID\_TEAM\_BALANCER\_TEAMS\_LOCKED,\                                      |
| /// Team balancer plugin informing you of your team. Byte 1 contains the |
| team you requested to join.\                                             |
| ID\_TEAM\_BALANCER\_TEAM\_ASSIGNED,                                      |
|                                                                          |
| /// Gamebryo Lightspeed integration\                                     |
| ID\_LIGHTSPEED\_INTEGRATION,                                             |
|                                                                          |
| /// XBOX integration\                                                    |
| ID\_XBOX\_LOBBY,                                                         |
|                                                                          |
| /// The password we used to challenge the other system passed, meaning   |
| the other system has called TwoWayAuthentication::AddPassword() with the |
| same password we passed to TwoWayAuthentication::Challenge()\            |
| /// You can read the identifier used to challenge as follows:\           |
| /// RakNet::BitStream bs(packet-&gt;data, packet-&gt;length, false);     |
| bs.IgnoreBytes(sizeof(RakNet::MessageID)); RakNet::RakString password;   |
| bs.Read(password);\                                                      |
| ID\_TWO\_WAY\_AUTHENTICATION\_INCOMING\_CHALLENGE\_SUCCESS,\             |
| ID\_TWO\_WAY\_AUTHENTICATION\_OUTGOING\_CHALLENGE\_SUCCESS,\             |
| /// A remote system sent us a challenge using                            |
| TwoWayAuthentication::Challenge(), and the challenge failed.\            |
| /// If the other system must pass the challenge to stay connected, you   |
| should call RakPeer::CloseConnection() to terminate the connection to    |
| the other system.\                                                       |
| ID\_TWO\_WAY\_AUTHENTICATION\_INCOMING\_CHALLENGE\_FAILURE,\             |
| /// The other system did not add the password we used to                 |
| TwoWayAuthentication::AddPassword()\                                     |
| /// You can read the identifier used to challenge as follows:\           |
| /// RakNet::BitStream bs(packet-&gt;data, packet-&gt;length, false);     |
| bs.IgnoreBytes(sizeof(MessageID)); RakNet::RakString password;           |
| bs.Read(password);\                                                      |
| ID\_TWO\_WAY\_AUTHENTICATION\_OUTGOING\_CHALLENGE\_FAILURE,\             |
| /// The other system did not respond within a timeout threshhold. Either |
| the other system is not running the plugin or the other system was       |
| blocking on some operation for a long time.\                             |
| /// You can read the identifier used to challenge as follows:\           |
| /// RakNet::BitStream bs(packet-&gt;data, packet-&gt;length, false);     |
| bs.IgnoreBytes(sizeof(MessageID)); RakNet::RakString password;           |
| bs.Read(password);\                                                      |
| ID\_TWO\_WAY\_AUTHENTICATION\_OUTGOING\_CHALLENGE\_TIMEOUT,\             |
| /// \\internal\                                                          |
| ID\_TWO\_WAY\_AUTHENTICATION\_NEGOTIATION,                               |
|                                                                          |
| /// CloudClient / CloudServer\                                           |
| ID\_CLOUD\_POST\_REQUEST,\                                               |
| ID\_CLOUD\_RELEASE\_REQUEST,\                                            |
| ID\_CLOUD\_GET\_REQUEST,\                                                |
| ID\_CLOUD\_GET\_RESPONSE,\                                               |
| ID\_CLOUD\_UNSUBSCRIBE\_REQUEST,\                                        |
| ID\_CLOUD\_SERVER\_TO\_SERVER\_COMMAND,\                                 |
| ID\_CLOUD\_SUBSCRIPTION\_NOTIFICATION,                                   |
|                                                                          |
| // So I can add more without changing user enumerations\                 |
| ID\_RESERVED\_1,\                                                        |
| ID\_RESERVED\_2,\                                                        |
| ID\_RESERVED\_3,\                                                        |
| ID\_RESERVED\_4,\                                                        |
| ID\_RESERVED\_5,\                                                        |
| ID\_RESERVED\_6,\                                                        |
| ID\_RESERVED\_7,\                                                        |
| ID\_RESERVED\_8,\                                                        |
| ID\_RESERVED\_9,                                                         |
|                                                                          |
| // For the user to use. Start your first enumeration at this value.\     |
| ID\_USER\_PACKET\_ENUM,                                                  |
|                                                                          |
|                                                                          |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ----------------------
  [Index](index.html)\
  ----------------------


