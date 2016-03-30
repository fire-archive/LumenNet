![Oculus VR, Inc.](RakNet_Icon_Final-copy.jpg){width="150"
height="150"}\
\
  --------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Detailed Implementation
  --------------------------------------------------------------

  -----------------------------------------------------------------------------------------------------
  Implementation\
  \
  For basic network communication, all you have to do is get an instance of RakPeer in your program.\
  \
  These are the most common headers you'll need:
  -----------------------------------------------------------------------------------------------------

  ----------------------------------------------
  ![](spacer.gif){width="8" height="1"}Headers
  ----------------------------------------------

  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  \#include "MessageIdentifiers.h"\
  \#include "RakPeerInterface.h"\
  \#include "RakNetTypes.h"\
  \
  MessageIdentifiers.h contains a giant enumeration representing the native message identifiers that RakNet uses to send you messages, such as disconnection notifications. Since you will probably want to define your own message identifiers, your enumerations should start at the highest enumeration in MessageIdentifiers.h + 1RakPeerInterface.h is an interface for the RakPeer class. RakNetTypes.h defines the structures used in RakNet, including *SystemAddress* - a unique identifier for systems, and *Packet* which the API returns to you when you get data or when it needs to send you a message.
  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  -------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Instancing
  -------------------------------------------------

  -------------------------------------------------------------------------------------------------------------------
  \
  RakNet::RakPeerInterface\* peer = RakNet::RakPeerInterface::GetInstance();\
  \
  That code would give you one instance of the peer. Usually you would only want one of these in a particular exe.\
  \
  The next step is to connect, either as client or as a server.\
  \
  For example:\
  -------------------------------------------------------------------------------------------------------------------

  -----------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Connection as Client
  -----------------------------------------------------------

  --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  peer-&gt;Startup(1, &SocketDescriptor(), 1)\
  peer-&gt;Connect(serverIP, serverPort, 0, 0);\
  \
  The call to Startup starts the network threads.\
  The first parameter is the maximum mumber of connections. For a pure client, we use 1.\
  The second parameter (SocketDescriptor()), specifies the ports/addresses to listen on . Since we want a client, we don't need to specify anything.\
  \
  The call to Connect connects to the server.\
  The first parameter, serverIP, is the IP address or domain of the server. If you want to connect to your own system, such as when running two copies of the same program, use "127.0.0.1" or "localhost" which is accepted notation for your own system. For IPV6, this is "::1".\
  The next parameter in Connect is the serverPort. This is the port you want to try to connect to on the server. If you specify a port the server is not expecting data on you won't be able to connect just like if you had entered the wrong IP. The IP and the port always work together in this fashion to form the complete address. How do you know what port to connect to? Well as the programmer you decide this ahead of time and then just hardcode it into your program. How do you choose a port? You can choose whatever you want as long as no one else is using it and its within the range of 2\^16 (0 to 65535). However, certain ports are reserved for use by established programs, such as your web browser, telnet, and FTP. You can look up these port assignments on the internet, but the quick and dirty answer is most ports under 32000 are reserved and ports over 32000 are open to whoever wants them.\
  \
  In practice ports are generally set with \#define per program and not changed. For example:\
  \
  \#define SERVER\_PORT 60005\
  \#define CLIENT\_PORT 60006\
  \
  This way the server will always know what port to respond to and the clients will always know what port to connect to. It also saves end-users the trouble of typing the ports in.\
  \
  Note that connection attempts are asynchronous. The function will return CONNECTION\_ATTEMPT\_STARTED immediately if it succeeded in the attempt to connect, but it does not mean your connection succeeded. You know your connection succeeded when you call RakPeerInterface::Receive() and a Packet is returned with the first byte ID\_CONNECTION\_ACCEPTED.\
  You get a network message ID\_CONNECTION\_ATTEMPT\_FAILED when the connection fails.\
  RakNet connects quickly so if you don't connect within a few seconds it's not going to connect. ID\_CONNECTION\_ATTEMPT\_FAILED will be returned to inform you of this.\
  \
  Starting as a server is similar.
  --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  -----------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Connection as Server
  -----------------------------------------------------------

+--------------------------------------------------------------------------+
| peer-&gt;Startup(maxConnectionsAllowed, &SocketDescriptor(serverPort,0), |
| 1);\                                                                     |
| peer-&gt;SetMaximumIncomingConnections(maxPlayersPerServer);             |
|                                                                          |
| The first parameter to Startup is how many simultaneous client           |
| connections to allow. The second and third parameter tells what port to  |
| listen on.\                                                              |
| The call to SetMaximumIncomingConnections sets how many incoming         |
| connections are allowed.\                                                |
| Keep in mind that the actual number of players you could have playing is |
| one more than the number of clients you support if you program your game |
| to allow the server to act as a player. If your server is a dedicated    |
| server or if you program your game to have both a client and a server on |
| the same system then obviously the number of people who could play would |
| change accordingly.\                                                     |
| \                                                                        |
+--------------------------------------------------------------------------+

  ---------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Peer to peer connections
  ---------------------------------------------------------------

  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  RakNet::SocketDescriptor sd(serverPort,0);\
  peer-&gt;Startup(maxConnectionsAllowed, &sd, 1);\
  peer-&gt;SetMaximumIncomingConnections(4);\
  \
  Startup sets 10 allowable connections. An allowable connection is either incoming or outgoing. It uses port 60000 to receive data.\
  SetMaximumIncomingConnections is necessary if you want to allow other peers to connect to you, but is not necessary if you only plan to connect to others. In this case, it sets the value to 4. This is a maximum value rather than a reserved value, so it is still possible to say connect to 8 peers - you would then only be able to accept 2 incoming connections until you disconnected from one or more of those peers.
  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  ------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Reading Packets
  ------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetCode">RakNet::Packet \*packet =                       |
| peer-&gt;Receive();</span>\                                              |
| \                                                                        |
| It's that easy. If packet is 0 then there was nothing to read and you    |
| can go on with your game. Otherwise you got some data. You should        |
| normally call this in a loop, for example:                               |
|                                                                          |
| <span class="RakNetCode">RakNet::Packet \*packet;\                       |
| for (packet=peer-&gt;Receive(); packet;                                  |
| peer-&gt;DeallocatePacket(packet), packet=peer-&gt;Receive()) {\         |
| } </span>\                                                               |
| \                                                                        |
| You can get two kinds of data:\                                          |
| Messages from the engine\                                                |
| Messages from other instances of RakNet, on the same computer or from    |
| other computers\                                                         |
| Both are handled the same way.\                                          |
| \                                                                        |
| Lets look at the Packet struct:                                          |
|                                                                          |
| nam<span class="RakNetCode">espace RakNet\                               |
| {\                                                                       |
| </span>struct Packet\                                                    |
| {\                                                                       |
| /// The system that send this packet.\                                   |
| SystemAddress systemAddress;\                                            |
| /// A unique identifier for the system that sent this packet, regardless |
| of IP address (internal / external / remote system)\                     |
| /// Only valid once a connection has been established                    |
| (ID\_CONNECTION\_REQUEST\_ACCEPTED, or ID\_NEW\_INCOMING\_CONNECTION)\   |
| /// Until that time, will be UNASSIGNED\_RAKNET\_GUID\                   |
| RakNetGUID guid;\                                                        |
| /// The length of the data in bytes\                                     |
| unsigned int length;\                                                    |
| /// The length of the data in bits\                                      |
| BitSize\_t bitSize;\                                                     |
| /// The data from the sender\                                            |
| unsigned char\* data;\                                                   |
| } // Namespace                                                           |
|                                                                          |
| systemAddress specifies the origin of the packet. Every connected system |
| has a unique SystemAddress which is assigned automatically. Note that    |
| the system address will be constant over the lifetime of the connection. |
| Certain native network messages use the systemAddress member- for        |
| example ID\_REMOTE\_DISCONNECTION\_NOTIFICATION tells you as a client    |
| that another client has disconnected. systemAddress in that case         |
| specifies which client. UNASSIGNED\_SYSTEM\_ADDRESS is a reserved value  |
| for "Unknown". You should not use systemAddress as a unique identifier   |
| for a remote computer. This is because the same computer can have a      |
| different systemAddress to every other connection. Use RakNetGUID as a   |
| unique identifier for a particular instance of RakPeerInterface.\        |
| \                                                                        |
| bitSize tells you how many bits long the data field of the struct is.\   |
| \                                                                        |
| Now that you got a packet you need to determine what the data means.     |
| Usually the first byte of the data is an enum that specifies type (see   |
| creating packets for more information). This is not always the case as   |
| you'll later learn, because with some packets, you might get a           |
| TimeStamp. To make things easy here it is a function to get the          |
| identifier when the packet has a TimeStamp:\                             |
| \                                                                        |
| <span class="RakNetCode">unsigned char GetPacketIdentifier(Packet \*p)\  |
| {\                                                                       |
| if ((unsigned char)p-&gt;data\[0\] == ID\_TIMESTAMP)\                    |
| return (unsigned char) p-&gt;data\[sizeof(MessageID) +                   |
| sizeof(RakNet::Time)\];\                                                 |
| else\                                                                    |
| return (unsigned char) p-&gt;data\[0\];\                                 |
| }\                                                                       |
| </span>\                                                                 |
| This will return an unsigned char, which corresponds to an enum          |
| specified in MessageIdentifiers.h.\                                      |
| \                                                                        |
| The network engine will return certain messages only for the client,     |
| certain messages only for the server, and certain messages for both. For |
| a full explanation of the messages refer to MessageIdentifiers.h. The    |
| important ones to worry about are ID\_NEW\_INCOMING\_CONNECTION and      |
| ID\_CONNECTION\_REQUEST\_ACCEPTED. These mean that the server or a peer  |
| got a new incoming client, and the client or a peer has successfully     |
| connected respectively. At this point you can send your own messages.\   |
| \                                                                        |
| If the packet identifier is NOT one of the pre-defined identifiers then  |
| you got user data which was sent by another system. You can then decode  |
| the data and handle it in your game as appropriate. See [creating        |
| packets](creatingpackets.html) for information on encoding and decoding  |
| data.\                                                                   |
| \                                                                        |
| *IMPORTANT!*\                                                            |
| When you are done with your data, don't forget to deallocate the packet! |
| Just pass it to DeallocatePacket.\                                       |
| \                                                                        |
| peer-&gt;DeallocatePacket(p);                                            |
+--------------------------------------------------------------------------+

  ---------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Sending Data
  ---------------------------------------------------

+--------------------------------------------------------------------------+
| The best way to illustrate sending data is with an example:\             |
| const char\* message = "Hello World";\                                   |
| \                                                                        |
| To all connected systems:\                                               |
| peer-&gt;Send((char\*)message, strlen(message)+1, HIGH\_PRIORITY,        |
| RELIABLE, 0, UNASSIGNED\_RAKNET\_GUID, true);\                           |
| \                                                                        |
| The first parameter is your data and must be a byte stream. Since we're  |
| sending a string, and a string is a byte stream, we can send it directly |
| without any casting.\                                                    |
| \                                                                        |
| The second parameter is how many bytes to send. In this example we send  |
| the length of the string and one more for the null terminator.\          |
| \                                                                        |
| The third parameter is the priority of the packet. This takes one of     |
| three values:\                                                           |
| IMMEDIATE\_PRIORITY,\                                                    |
| HIGH\_PRIORITY\                                                          |
| MEDIUM\_PRIORITY\                                                        |
| LOW\_PRIORITY\                                                           |
| \                                                                        |
| IMMEDIATE\_PRIORITY messages signal RakNet's update thread to update     |
| immediately. Assuming bandwidth is available, they get sent immediately. |
| HIGH\_PRIORITY, MEDIUM\_PRIORITY, and LOW\_PRIORITY messages are put     |
| into a buffer. The next time RakNet's update thread ticks (which is      |
| every 10 milliseconds) those messages get sent. Those 3 priorities can   |
| be more efficient for bandwidth, because if multiple messages can be     |
| aggregated into a single datagram, RakNet will transparently do so       |
|                                                                          |
| Twice as many messages get sent out for each higher priority. So if      |
| messages of all priorities were waiting to go out, 8                     |
| IMMEDIATE\_PRIORITY, 4 HIGH\_PRIORITY, 2 MEDIUM\_PRIORITY, and 1         |
| LOW\_PRIORITY would be sent. Obviously however, if only LOW\_PRIORITY    |
| messages were waiting at all, then those messages would all go out as    |
| fast as possible.\                                                       |
| \                                                                        |
| The fourth parameter takes one of five major values. Lets say you send   |
| data 1,2,3,4,5,6. Here's the order and substance of what you might get   |
| back:\                                                                   |
| \                                                                        |
| UNRELIABLE - 5, 1, 6\                                                    |
| UNRELIABLE\_SEQUENCED - 5 (6 was lost in transit, 1,2,3,4 arrived later  |
| than 5)\                                                                 |
| RELIABLE - 5, 1, 4, 6, 2, 3\                                             |
| RELIABLE\_ORDERED - 1, 2, 3, 4, 5, 6\                                    |
| RELIABLE\_SEQUENCED - 5, 6 (1,2,3,4 arrived later than 5)\               |
| \                                                                        |
| For more details on this refer to PacketPriority.h.\                     |
| \                                                                        |
| The fifth parameter to Send() (0 in this example) is which ordering      |
| stream to use. This is used for relative ordering of packets in relation |
| to other packets on the same stream. It's not important for now, but for |
| more information on this refer to the [Sending                           |
| Packets](sendingpackets.html) section.                                   |
|                                                                          |
| The sixth parameter (UNASSIGNED\_RAKNET\_GUID), is the remote system to  |
| send to. UNASSIGNED\_RAKNET\_GUID is a reserved value meaning "no-one in |
| particular". This parameter means one of two things : either who you     |
| want to send the packet to, or who you don't want to send the packet to, |
| depending on the value of broadcast, which is the last parameter.\       |
| \                                                                        |
| The seventh parameter (true in this example) is whether to broadcast to  |
| all connected systems or not. This parameter works with the sixth        |
| parameter. If broadcast is true, then the sixth parameter specifies who  |
| not to send to. If it is false, then it specifies who to send to. If we  |
| want to broadcast to everyone, then we just specify                      |
| UNASSIGNED\_RAKNET\_GUID. This works out when relaying packets, because  |
| the Packet::systemAddress field in the packet you get will specify who   |
| the sender is. We can relay the packet to everyone BUT the sender, which |
| makes sense since we usually don't want to send the same information     |
| back to the person who just sent it to us.                               |
+--------------------------------------------------------------------------+

  ----------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Shutting Down
  ----------------------------------------------------

  -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  \
  Shutting down is easy and nearly instantaneous. Just call Shutdown() on your peer object, and then destroy it\
  \
  somePeer-&gt;Shutdown(300);\
  \
  Shutdown stops the network threads. If you specify a higher than 0 parameter to Shutdown(), Shutdown() will block for up to this amount of time to notify connected systems (if any) to inform them of the connection dropping. 0 will cause a slient Shutdown(), and remote systems will detect the disconnection within about 10 seconds, returning ID\_CONNECTION\_LOST.
  -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  --------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Cleaning Up
  --------------------------------------------------

  --------------------------------------------------------------------------------------------------------------------------------------------------------------
  Just pass the instance that the factory gave you to the DestroyRakPeerInterface. You may want to do this mid-program to free memory but it is not required.\
  \
  RakNet::RakPeerInterface::DestroyInstance(rakPeer);
  --------------------------------------------------------------------------------------------------------------------------------------------------------------

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| \                                                                        |
| Next page: [Step by step tutorial](tutorial.html)                        |
|                                                                          |
| [Index](index.html)\                                                     |
| [Introduction](introduction.html)\                                       |
| [System Overview](systemoverview.html)\                                  |
| [Tutorial](tutorial.html)\                                               |
| [Compiler Setup](compilersetup.html)\                                    |
+--------------------------------------------------------------------------+

+--------------------------------------------------------------------------+
| \                                                                        |
+--------------------------------------------------------------------------+


