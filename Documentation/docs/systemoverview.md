![Oculus VR, Inc.](RakNet_Icon_Final-copy.jpg){width="150"
height="150"}\
\
  ---------------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}<span class="RakNetWhiteHeader">System Overview</span>
  ---------------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| **System Architecture**                                                  |
| RakNet has code that falls into three categories: network communication, |
| plugins that use network communication, and general game functionality.  |
|                                                                          |
| Network communication is provided by two user classes. RakPeerInterface, |
| and TCPInterface. RakPeerInterface is the primary class that games will  |
| use and is based on UDP. It provides functionality such as connections,  |
| connection management, congestion control, remote server detection, out  |
| of band messaging, connection statistics, latency and packetloss         |
| simulation, ban lists, and secure connectivity.                          |
|                                                                          |
| TCPInterface is a wrapper for TCP, and is used to communicate with       |
| external systems that are based on TCP. For example, the                 |
| [EmailSender](emailsender.html) class, used to report crashes from       |
| remote servers, interfaces with TCP. It is also supported by most plugin |
| modules, and is suggested for file transfers such as with the            |
| autopatcher.                                                             |
|                                                                          |
| Plugins in RakNet are classes that you 'attach' to an instance of        |
| RakPeer or PacketizedTCP. This uses [chain of                            |
| responsibility](http://en.wikipedia.org/wiki/Chain-of-responsibility_pat |
| tern)                                                                    |
| design pattern. Attached plugins update automatically when Receive() is  |
| called on the attachee, and filter or inject messages into the network   |
| stream. Functionality includes host determination in a peer to peer      |
| enviroment, file transfers, NAT traversal, voice communication, remote   |
| procedure calls, and game object replication.                            |
|                                                                          |
| General game functionality includes the [master                          |
| server](http://masterserver2.raknet.com/), crash reporting, email        |
| sending through Gmail pop servers, and an SQL logging server.            |
|                                                                          |
| RakPeer internal architecture                                            |
|                                                                          |
| **RakPeer.h** provides the base functionality for UDP communication, and |
| it is expected that most applications will use RakPeer as opposed to     |
| TCP.  On start, RakPeer starts two threads - one thread to wait for      |
| incoming datagrams, and another to perform periodic updates, such as     |
| determing lost connections, or pings. The user specifies the maximum     |
| number of connections and an array of RemoteSystem structures is         |
| internally allocated to this size. Each connection or connection attempt |
| is assigned to a Remote System structure, which contains a class to      |
| manage congestion control between the two systems. Connections are       |
| identified by SystemAddress or RakNetGuid, the latter of which is        |
| randomly generated and unique per instance of RakPeer.                   |
|                                                                          |
| Connections are established through UDP messages that contain a          |
| connection request payload, and an 'offline message' identifier. The     |
| 'offline message' identifier is used to differentiate between actual     |
| offline messages, and connected messages that happen to match the        |
| profile of an offline message. Connection requests are sent repeatedly   |
| over a short timeframe to account for packetloss, and if supported uses  |
| a decreasing MTU for path MTU detection.                                 |
|                                                                          |
| When a connection requests arrives, RakPeer transmits internal state     |
| data, such as the RakNetGUID, and checks this connection against the ban |
| list, repeat connection list, and other security measures. If the        |
| connection was flagged as secure, the secure connection protocol         |
| activates and additional data is sent. On success, the user is informed  |
| about this, either with ID\_CONNECTION\_REQUEST\_ACCEPTED, or            |
| ID\_NEW\_INCOMING\_CONNECTION. Failure conditions are also returned in a |
| similar fashion.                                                         |
|                                                                          |
| Outgoing messages from the user to connected systems are copied and      |
| internally buffered. If the outgoing message plus the header is larger   |
| than the MTU, the message is fragmented internally. On a periodic        |
| interval, outgong messages are aggreggated into a single datagram and    |
| sent according to the transmission contraints of congestion control and  |
| the MTU size. Datagrams that do not get an ACK are resent. NAKs are sent |
| for missing datagram sequence numbers. Messages sent unreliably and      |
| cannot be sent within a user-defined threshold are deleted. Messages are |
| sent in order of priority. Acks are not congestion controlled. However,  |
| resends and new sends are, with resends taking priority over new sends.  |
|                                                                          |
| As stated, incoming datagrams arrive on a blocking recvfrom thread. When |
| a datagram arrives, the timestamp is immediately recorded, and the       |
| datagram is pushed into a thread-safe queue for the processing thread to |
| manage. The processing thread is signaled, such that it will either      |
| immediately process the message (if sleeping) or process the message at  |
| the next available time.                                                 |
|                                                                          |
| Incoming datagrams are checked for the byte sequence that indicates if   |
| the sender thought it was connected or not. In addition, the source IP   |
| address is checked. If a message is flagged as unconnected, and the      |
| sender is not connected to us, the message is checked against a narrow   |
| range of accepted types, such as connection requests, or out of band     |
| messaging capabilities. If a message is flagged as connected, and the    |
| sender is connected to us, then it is processed through the              |
| ReliabilityLayer class, for congestion control and other communication   |
| related information (ACKS, NAKS, resends, encryption, reassembly of      |
| large messages).                                                         |
|                                                                          |
| Connected messages are first processed by RakPeer. This is currently     |
| only used for periodic pings and to detect lost connections should the   |
| user not send data within a given threshhold. All other messages are     |
| processed by plugins, or returned to the user. Calling                   |
| RakPeer::Receive() ticks all plugins' update functions one time, and     |
| returns one message. Message returned to the user are returned from      |
| RakPeer::Receive(), one message per call. It is necessary to call        |
| Receive() in a loop to get all messages, until no further messages are   |
| returned.                                                                |
|                                                                          |
| Other systems                                                            |
|                                                                          |
| The **NetworkIDObject** class provides the ability for systems to refer  |
| to common objects and is used by object member remote function calls.    |
| Each object has a 64 bit random number assigned and can be used to       |
| lookup pointers through a hash.                                          |
|                                                                          |
| The **[SystemAddress](systemaddresses.html)** structure is what RakNet   |
| uses to represent remote systems.  It is the binary encoding of the IP   |
| address along with the port of that system, supporting both IPV4 and     |
| IPV6.                                                                    |
|                                                                          |
| The **[BitStream](bitstreams.html)** class, located in BitStream.h, is   |
| natively supported by RakNet.  This is both a user class and an internal |
| class.  It is primarily used to write single bits to a stream and for    |
| automatic endian swapping, which can be enabled by commenting out        |
| \_\_BITSTREAM\_NATIVE\_END in RakNetDefines.h.                           |
|                                                                          |
| For a visual representation of the architecture, refer to the [UML       |
| Diagram](RakNetUML.jpg)\                                                 |
| \                                                                        |
| Next page: [Detailed Implementation](detailedimplementation.html)        |
+--------------------------------------------------------------------------+

  ---------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Bandwidth overhead
  ---------------------------------------------------------

+--------------------------------------------------------------------------+
| Post 3.6201, using new congestion control                                |
|                                                                          |
| **Per datagram:**\                                                       |
| 1 byte for bitflags\                                                     |
| 4 bytes for timestamp, used to calculate RTT for congestion control.     |
| RakNet version 4 does not transmit this field.\                          |
| 3 bytes for sequence number, used to lookup datagrams for ACKs           |
|                                                                          |
| **Per message:**\                                                        |
| 1 byte for bitflags\                                                     |
| 2 bytes for message length\                                              |
| if (RELIABLE,RELIABLE\_SEQUENCED,RELIABLE\_ORDERED)\                     |
| A. 3 bytes for sequence number, used to prevent returning to the user    |
| duplicated messages\                                                     |
| if (UNRELIABLE\_SEQUENCED,RELIABLE\_SEQUENCED,RELIABLE\_ORDERED)\        |
| A. 3 bytes for sequence number, used to reorganize messages on the same  |
| channel in order\                                                        |
| B. 1 byte for ordering channel\                                          |
| if (message over MTU)\                                                   |
| A. 4 bytes for number of splits, not compressed to improve performance\  |
| B. 2 bytes for identifier for which split this is\                       |
| C. 4 bytes for index into number of splits, not compressed to improve    |
| performance                                                              |
|                                                                          |
| 3.6201 and earlier in the 3.x series                                     |
|                                                                          |
| **Per datagram:**\                                                       |
| 1 bit for bitflags\                                                      |
| 8 bytes for timestamp, used to calculate RTT for congestion control      |
|                                                                          |
| **Per message:**\                                                        |
| 4 bytes for message length\                                              |
| 4 bytes for sequence number, used to prevent returning to the user       |
| duplicated messages\                                                     |
| 4 bits for bitflags\                                                     |
| if (UNRELIABLE\_SEQUENCED,RELIABLE\_SEQUENCED,RELIABLE\_ORDERED)\        |
| A. 4 bytes for sequence number, used to reorganize messages in order\    |
| B. 5 bits for ordering channel\                                          |
| if (message over MTU)\                                                   |
| A. 4 bytes for number of splits, but compressed, so used 1-2 bytes on    |
| average\                                                                 |
| B. 4 bytes for identifier for which split this is\                       |
| C. 4 bytes for index into number of splits, but compressed, so used 1-2  |
| bytes on average                                                         |
|                                                                          |
| \                                                                        |
| A message is the data you send from the game. All messages you send to   |
| RakNet between RakNet update ticks are grouped together in one datagram. |
| So if you send 1 message only, then the overhead is 1 datagram + 1       |
| message. If you send 5 messages, then it's 1 datagram + 5 messages. If   |
| you send 1 message, but it's 10 times bigger than the MTU, then it sends |
| 10 datagrams, each containing 1 message (the message gets split up)      |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ---------------------------------------------------------
  [Index](index.html)\
  [Compiler Setup](compilersetup.html)\
  [Detailed Implementation](detailedimplementation.html)\
  [Tutorial](tutorial.html)\
  [UML Diagram](RakNetUML.jpg)\
  ---------------------------------------------------------


