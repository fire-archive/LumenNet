<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ---------------------------------------------
  Debugging disconnections or missing packets
  ---------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">How to trace and debug received datagrams |
| in RakNet</span>\                                                        |
|                                                                          |
| If your systems seem to get disconnected, or get no data, and all the    |
| usual debugging attempts have failed, here is an overview of how the     |
| RakNet handles incoming messages.                                        |
|                                                                          |
| **1. SocketLayer::RecvFromBlocking() in SocketLayer.cpp**                |
|                                                                          |
| RecvFromBlocking() is called from a thread RecvFromLoop that is created  |
| in RakPeer.cpp. Every datagram that arrives goes through this function - |
| therefore, if you get no data, this is the first place to put a          |
| breakpoint.                                                              |
|                                                                          |
| \*bytesReadOut = recvfrom( s, dataOutModified, dataOutSize, flag,        |
| sockAddrPtr, socketlenPtr );                                             |
|                                                                          |
| That function should return, and bytesReadOut should be greater than 0.  |
| If you put a breakpoint after that function, and the breakpoint does not |
| hit, then no datagrams arrived. At the bottom of the function the        |
| following code reads the address and port of the sender.                 |
|                                                                          |
| systemAddressOut-&gt;port=ntohs( sa.sin\_port );\                        |
| systemAddressOut-&gt;binaryAddress=sa.sin\_addr.s\_addr;                 |
|                                                                          |
| The datagram ends up in the rakPeer-&gt;bufferedPackets queue. The       |
| function SetEvent() is called on the rakPeer-&gt;quitAndDataEvents       |
| SignaledEvent class, which tells the UpdateNetworkLoop() thread to stop  |
| waiting and process the message.                                         |
|                                                                          |
| *If you do not even hit this breakpoint, then there is a bug in your     |
| network.*                                                                |
|                                                                          |
| **2. RakPeer::RunUpdateCycle()** **in RakPeer.cpp**                      |
|                                                                          |
| RunUpdateCycle() is an update function that the UpdateNetworkLoop calls, |
| many times per second. It's triggered by either time or by the           |
| rakPeer-&gt;quitAndDataEvents SignaledEvent class. For debugging message |
| flows, you want a breakpoint towards the top of the function here:       |
|                                                                          |
| if (socketListIndex!=socketList.Size())\                                 |
| ProcessNetworkPacket(recvFromStruct-&gt;systemAddress,                   |
| recvFromStruct-&gt;data, recvFromStruct-&gt;bytesRead, this,             |
| socketList\[socketListIndex\], recvFromStruct-&gt;timeRead);             |
|                                                                          |
| When a datagram is put in the rakPeer-&gt;bufferedPackets queue from     |
| step 1, it is processed here.                                            |
|                                                                          |
| *If you do not hit this breakpoint, then either the thread is not        |
| running (unlikely) or there is a bug with the SignaledEvent class, or    |
| else the thread has locked up somewhere.*                                |
|                                                                          |
| **3. void ProcessNetworkPacket(...) in RakPeer.cpp**                     |
|                                                                          |
| ProcessNetworkPacket is called for each incoming datagram. At the very   |
| top of the function a call is made to ProcessOfflineNetworkPacket().     |
| ProcessOfflineNetworkPacket() checks if the sender is banned and if the  |
| message is prefixed with an array of bytes corresponding to              |
| OFFLINE\_MESSAGE\_DATA\_ID. If the user is banned, the function returns  |
| and no further processing occurs. If the message is prefixed with        |
| OFFLINE\_MESSAGE\_DATA\_ID, then this is generally a handshaking         |
| message, and the caller ProcessNetworkPacket() does not process further. |
| For systems that are already connected, ProcessOfflineNetworkPacket()    |
| should return false. For debugging loss of messages for systems I        |
| already know are connected, I would step over the call to                |
| ProcessOfflineNetworkPacket, and only trace into it if it returns true.  |
|                                                                          |
| The next operation in ProcessNetworkPacket() is to look up the structure |
| representing the remote system from the systemAddress (the IP address)   |
| by calling rakPeer-&gt;GetRemoteSystemFromSystemAddress( systemAddress,  |
| true, true );. A remoteSystem structure should be returned. If not, then |
| the sender's IP address is unknown, and the message is not tagged as an  |
| offline message, so the datagram is ignored.                             |
|                                                                          |
| Generally, you should expect ProcessNetworkPacket() to proceed to        |
|                                                                          |
| remoteSystem-&gt;reliabilityLayer.HandleSocketReceiveFromConnectedPlayer |
| (\                                                                       |
| data, length, systemAddress, rakPeer-&gt;messageHandlerList,             |
| remoteSystem-&gt;MTUSize,\                                               |
| rakNetSocket-&gt;s, &rnr,                                                |
| rakNetSocket-&gt;remotePortRakNetWasStartedOn\_PS3, timeRead);           |
|                                                                          |
| *If HandleSocketReceiveFromConnectedPlayer() does not get called, then   |
| either the sender is not connected, the sender is banned, the sender was |
| recently disconnected, there is a bug with                               |
| GetRemoteSystemFromSystemAddress(), or the connected datagram encoding   |
| happened to match OFFLINE\_MESSAGE\_DATA\_ID which shouldn't happen      |
| except due to bugs.*                                                     |
|                                                                          |
| **4. ReliabilityLayer::HandleSocketReceiveFromConnectedPlayer(...)**     |
|                                                                          |
| This function handles processing a datagram from a connected player.     |
| Each datagram roughly follows the DatagramHeaderFormat structure at the  |
| top of the file. A datagram is either an acknowledgement of datagrams    |
| this system had previously sent, a negative acknowledgement of datagrams |
| that didn't arrive, or one or more messages that the user had generated  |
| from the RakPeer::Send() call.                                           |
|                                                                          |
| This function is large and complex, but you generally do not need to     |
| deal with ACKs or NAKs, and can skip to the part that reads:             |
|                                                                          |
| InternalPacket\* internalPacket = CreateInternalPacketFromBitStream(     |
| &socketData, timeRead );                                                 |
|                                                                          |
| ReliabilityLayer::CreateInternalPacketFromBitStream(...) reads the       |
| header for each user message. The header contains data such as how long  |
| the message is, if the message had to be fragmented, and if it needs to  |
| be ordered. If the format of the message is invalid, the function will   |
| return 0. Otherwise, the InternalPacket structure is allocated and       |
| return with the user data filled in.                                     |
|                                                                          |
| If the very first call to the function fails, that is a bug. However, a  |
| datagram can contain more than one message, so the function is called in |
| a loop until failure.                                                    |
|                                                                          |
| while ( internalPacket )\                                                |
| {\                                                                       |
| ...\                                                                     |
| // Parse the bitstream to create an internal packet\                     |
| internalPacket = CreateInternalPacketFromBitStream( &socketData,         |
| timeRead );\                                                             |
| }                                                                        |
|                                                                          |
| Immediately inside that loop is this block of code:                      |
|                                                                          |
| for (unsigned int messageHandlerIndex=0; messageHandlerIndex &lt;        |
| messageHandlerList.Size(); messageHandlerIndex++)\                       |
| {\                                                                       |
| \#if CC\_TIME\_TYPE\_BYTES==4\                                           |
| messageHandlerList\[messageHandlerIndex\]-&gt;OnInternalPacket(internalP |
| acket,                                                                   |
| receivePacketCount, systemAddress, timeRead, false);\                    |
| \#else\                                                                  |
| messageHandlerList\[messageHandlerIndex\]-&gt;OnInternalPacket(internalP |
| acket,                                                                   |
| receivePacketCount, systemAddress,                                       |
| (RakNet::TimeMS)(timeRead/(CCTimeType)1000), false);\                    |
| \#endif\                                                                 |
| }                                                                        |
|                                                                          |
| OnInternalPacket() is used for the PacketLogger plugin. If you think     |
| messages are being sent, but they are not listed by the PacketLogger,    |
| then it didn't get this far.                                             |
|                                                                          |
| The next block of code checks if this is a duplicate message.            |
|                                                                          |
| holeCount =                                                              |
| (DatagramSequenceNumberType)(internalPacket-&gt;reliableMessageNumber-re |
| ceivedPacketsBaseIndex);\                                                |
| const DatagramSequenceNumberType typeRange =                             |
| (DatagramSequenceNumberType)(const uint32\_t)-1;                         |
|                                                                          |
| That is the start of a major chunk of code. <span                        |
| class="RakNetCode">receivedPacketsBaseIndex</span> is a number that is   |
| incremented by one for each message that arrives from the remote system. |
| As long as messages arrive in order, holeCount would be 0. If a message  |
| skipped one index, holeCount would be one. If a message was an immediate |
| duplicate, holeCount would be negative 1 and be ignored.                 |
| hasReceivedPacketQueue is a queue of booleans that indicates if we got a |
| message for a given index. One potential failure point is this code:     |
|                                                                          |
| if (holeCount &gt; (DatagramSequenceNumberType) 1000000)\                |
| {\                                                                       |
| RakAssert("Hole count too high. See ReliabilityLayer.h" && 0);\          |
| ...\                                                                     |
| }                                                                        |
|                                                                          |
| To avoid memory attacks, the queue size is limited to that number. In    |
| practice a message should never be out of order by that much, even on a  |
| LAN.                                                                     |
|                                                                          |
| If the message was split by the sender,                                  |
| ReliabiltyLayer::InsertIntoSplitPacketList(...) is called. When all      |
| parts of a message has arrived, then                                     |
| ReliabiltyLayer::BuildPacketFromSplitPacketList() will return the        |
| reassembled message.                                                     |
|                                                                          |
| From HandleSocketReceiveFromConnectedPlayer zero or more messages may be |
| returned to the user. They are pushed to the outputQueue queue, for      |
| example:                                                                 |
|                                                                          |
| outputQueue.Push( internalPacket, \_FILE\_AND\_LINE\_ );                 |
|                                                                          |
| *The most likely failure point here should you not get data is a bug     |
| with the packet format in CreateInternalPacketFromBitStream().*          |
|                                                                          |
| **5. ReliabilityLayer::Receive( unsigned char \*\*data )**               |
|                                                                          |
| This function returns messages pushed to the outputQueue queue. It is    |
| called from RakPeer::RunUpdateCycle() and should be called on a regular  |
| interval, once for each connected system.                                |
|                                                                          |
| **6. bool RakPeer::RunUpdateCycle( RakNet::TimeUS timeNS, RakNet::Time   |
| timeMS )**                                                               |
|                                                                          |
| // Does the reliability layer have any packets waiting for us?\          |
| // To be thread safe, this has to be called in the same thread as        |
| HandleSocketReceiveFromConnectedPlayer\                                  |
| bitSize = remoteSystem-&gt;reliabilityLayer.Receive( &data );            |
|                                                                          |
| As described in step 5, the above code is called on a regular interval,  |
| once for each connected system. If bitSize is greater than 0, then we    |
| have a message from a connected system. This is probably a user message, |
| although as you can see from the code in RakPeer it also checks for      |
| messages the user should not send, such as ID\_CONNECTION\_REQUEST. This |
| is because part of the handshaking process is done reliably.             |
|                                                                          |
| Assuming that this is indeed a user message, the message is pushed to a  |
| queue here:<span class="RakNetCode"></span>                              |
|                                                                          |
| if (data\[0\]&gt;=(MessageID)ID\_TIMESTAMP &&\                           |
| remoteSystem-&gt;isActive\                                               |
| )\                                                                       |
| {\                                                                       |
| packet=AllocPacket(byteSize, data, \_FILE\_AND\_LINE\_);\                |
| packet-&gt;bitSize = bitSize;\                                           |
| packet-&gt;systemAddress = systemAddress;\                               |
| packet-&gt;systemAddress.systemIndex = ( SystemIndex )                   |
| remoteSystemIndex;\                                                      |
| packet-&gt;guid = remoteSystem-&gt;guid;\                                |
| packet-&gt;guid.systemIndex=packet-&gt;systemAddress.systemIndex;\       |
| AddPacketToProducer(packet);\                                            |
| }                                                                        |
|                                                                          |
| This adds the message to the packetReturnQueue queue found in RakPeer.   |
|                                                                          |
| **7. Packet\* RakPeer::Receive( void )**                                 |
|                                                                          |
| Receive() is called by the user. The Update() function is called for all |
| plugins. Then the packetReturnQueue is checked to see if a message       |
| should be returned to the user.                                          |
|                                                                          |
|                                                                          |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ---------------------------------------------------
  [Index](index.html)\
  [UML Diagram](RakNetUML.jpg)[](swigtutorial.html)
  ---------------------------------------------------


