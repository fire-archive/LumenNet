<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -----------------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}<span class="RakNetWhiteHeader">Reliability Types</span>
  -----------------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| Control how and when with packet priority and reliability types          |
| ``` {.RakNetCode}                                                        |
| /// These enumerations are used to describe when packets are delivered.  |
| enum PacketPriority                                                      |
| {                                                                        |
|     IMMEDIATE_PRIORITY, /// The highest possible priority. These message |
|  trigger sends immediately, and are generally not buffered or aggregated |
|  into a single datagram.                                                 |
|     Messages at HIGH_PRIORITY priority and lower are buffered to be sent |
|  in groups at 10 millisecond intervals                                   |
|     HIGH_PRIORITY,   /// For every 2 IMMEDIATE_PRIORITY messages, 1 HIGH |
| _PRIORITY will be sent.                                                  |
|     MEDIUM_PRIORITY,   /// For every 2 HIGH_PRIORITY messages, 1 MEDIUM_ |
| PRIORITY will be sent.                                                   |
|     LOW_PRIORITY,   /// For every 2 MEDIUM_PRIORITY messages, 1 LOW_PRIO |
| RITY will be sent.                                                       |
|     NUMBER_OF_PRIORITIES                                                 |
| };                                                                       |
| ```                                                                      |
|                                                                          |
| PacketPriority is simple. High priority packets go out before medium     |
| priority packets and medium priority packets go out before low priority  |
| packets do. Originally I raised the priority of packets that took a long |
| time to get out, but in practice this would disrupt games in progress as |
| unimportant data to new connections (such as the map data) would get in  |
| the way of the game data.\                                               |
| \                                                                        |
| ``` {.RakNetCode}                                                        |
|                                                                          |
| /// These enumerations are used to describe how packets are delivered.   |
| enum PacketReliability                                                   |
| {                                                                        |
|     UNRELIABLE,                                                          |
|     UNRELIABLE_SEQUENCED,                                                |
|     RELIABLE,                                                            |
|     RELIABLE_ORDERED,                                                    |
|     RELIABLE_SEQUENCED                                                   |
|  UNRELIABLE_WITH_ACK_RECEIPT,                                            |
|  UNRELIABLE_SEQUENCED_WITH_ACK_RECEIPT,                                  |
|  RELIABLE_WITH_ACK_RECEIPT,                                              |
|  RELIABLE_ORDERED_WITH_ACK_RECEIPT,                                      |
|  RELIABLE_SEQUENCED_WITH_ACK_RECEIPT,                                    |
| };                                                                       |
| ```                                                                      |
|                                                                          |
| *Unreliable*\                                                            |
| Unreliable packets are sent by straight UDP. They may arrive out of      |
| order, or not at all. This is best for data that is unimportant, or data |
| that you send very frequently so even if some packets are missed newer   |
| packets will compensate.\                                                |
| Advantages - These packets don't need to be acknowledged by the network, |
| saving the size of a UDP header in acknowledgment (about 50 bytes or     |
| so). The savings can really add up.\                                     |
| Disadvantages - No packet ordering, packets may never arrive, these      |
| packets are the first to get dropped if the send buffer is full.\        |
| \                                                                        |
| *Unreliable sequenced*\                                                  |
| Unreliable sequenced packets are the same as unreliable packets, except  |
| that only the newest packet is ever accepted. Older packets are ignored. |
| Advantages - Same low overhead as unreliable packets, and you don't have |
| to worry about older packets changing your data to old values.\          |
| Disadvantages - A LOT of packets will be dropped since they may never    |
| arrive because of UDP and may be dropped even when they do arrive. These |
| packets are the first to get dropped if the send buffer is full. The     |
| last packet sent may never arrive, which can be a problem if you stop    |
| sending packets at some particular point.\                               |
| \                                                                        |
| Note that the transmission of one of the three reliable packets types is |
| required for the detection of lost connections. If you never send        |
| reliable packets you need to implement lost connection detection         |
| manually.\                                                               |
| \                                                                        |
| *Reliable*\                                                              |
| Reliable packets are UDP packets monitored by a reliablilty layer to     |
| ensure they arrive at the destination.\                                  |
| Advantages - You know the packet will get there. Eventually...\          |
| Disadvantages - Retransmissions and acknowledgments can add significant  |
| bandwidth requirements. Packets may arrive very late if the network is   |
| busy. No packet ordering.\                                               |
| \                                                                        |
| *Reliable ordered*\                                                      |
| Reliable ordered packets are UDP packets monitored by a reliability      |
| layer to ensure they arrive at the destination and are ordered at the    |
| destination. Advantages - The packet will get there and in the order it  |
| was sent. These are by far the easiest to program for because you don't  |
| have to worry about strange behavior due to out of order or lost         |
| packets.\                                                                |
| Disadvantages - Retransmissions and acknowledgments can add significant  |
| bandwidth requirements. Packets may arrive very late if the network is   |
| busy. One late packet can delay many packets that arrived sooner,        |
| resulting in significant lag spikes. However, this disadvantage can be   |
| mitigated by the clever use of ordering streams .\                       |
| \                                                                        |
| *Reliable sequenced*\                                                    |
| Reliable sequenced packets are UDP packets monitored by a reliability    |
| layer to ensure they arrive at the destination and are sequenced at the  |
| destination.\                                                            |
| Advantages - You get the reliability of UDP packets, the ordering of     |
| ordered packets, yet don't have to wait for old packets. More packets    |
| will arrive with this method than with the unreliable sequenced method,  |
| and they will be distributed more evenly. The most important advantage   |
| however is that the latest packet sent will arrive, where with           |
| unreliable sequenced the latest packet sent may not arrive.\             |
| Disadvantages - Wasteful of bandwidth because it uses the overhead of    |
| reliable UDP packets to ensure late packets arrive that just get ignored |
| anyway.\                                                                 |
|                                                                          |
| **Acknowledgment recipts**                                               |
|                                                                          |
| *\*\_<span class="RakNetCode">WITH\_ACK\_RECEIPT</span>*                 |
|                                                                          |
| By specifying one of the PacketReliability types that contain            |
| \_WITH\_ACK\_RECEIPT, you can request that RakPeerInterface notify you   |
| when a message has been acknowledged by the remote system, or delivery   |
| has timed out.                                                           |
|                                                                          |
| Calls to RakPeerInterface::Send() or RakPeerInterface::SendLists()       |
| return a 4 byte unsigned integer representing an ID for the message      |
| sent. When using \_WITH\_ACK\_RECEIPT, this same ID will be returned to  |
| you when you call RakPeerInterface::Receive(). In the packet, byte 0     |
| will be either ID\_SND\_RECEIPT\_ACKED or ID\_SND\_RECEIPT\_LOSS. Bytes  |
| 1-4 inclusive will contain the same number returned to you from Send()   |
| or SendLists().                                                          |
|                                                                          |
| ID\_SND\_RECEIPT\_ACKED means that the message arrived. For reliable     |
| sends, this is all you will ever get.                                    |
|                                                                          |
| ID\_SND\_RECEIPT\_LOSS is only returned for                              |
| UNRELIABLE\_WITH\_ACK\_RECEIPT and                                       |
| UNRELIABLE\_SEQUENCED\_WITH\_ACK\_RECEIPT. It means that an ack for the  |
| message did not arrive within the threshhold given for message resends   |
| (roughly a multiple of your ping). It could mean any of the following:   |
|                                                                          |
| -   The message was lost in transmission                                 |
| -   The message arrived, but the ack was lost in transmission            |
| -   The message arrived, and the ack arrived, but arrived later than the |
|     threshhold (a ping spike)                                            |
|                                                                          |
| It usually means one of the first two.                                   |
|                                                                          |
| Here's an example of reading out the return receipt:                     |
|                                                                          |
| packet = rakPeer-&gt;Receive();\                                         |
| while (packet)\                                                          |
| {\                                                                       |
| switch(packet-&gt;data\[0\])\                                            |
| {\                                                                       |
| case ID\_SND\_RECEIPT\_ACKED:\                                           |
| memcpy(&msgNumber, packet-&gt;data+1, 4);\                               |
| printf("Msg \#%i was delivered.\\n", msgNumber);\                        |
| break;\                                                                  |
| case ID\_SND\_RECEIPT\_LOSS:\                                            |
| memcpy(&msgNumber, packet-&gt;data+1, 4);\                               |
| printf("Msg \#%i was probably not delivered.\\n", msgNumber);\           |
| break;\                                                                  |
| }\                                                                       |
| sender-&gt;DeallocatePacket(packet);\                                    |
| packet = sender-&gt;Receive();\                                          |
| }                                                                        |
|                                                                          |
| The typical reason you would want to use this is to know if unreliable   |
| messages arrived or not. Sometimes you want to resend unreliable         |
| messages, but with more up-to-date data, rather than relying on RELIABLE |
| to just resend the old data until it arrives. To do so, when you send    |
| you unreliable data you would internally create a mapping between the    |
| number returned by Send() or SendLists() and reference that number when  |
| the return receipt arrives. If the receipt is ID\_SND\_RECEIPT\_LOSS,    |
| you can resend whatever message that Send() or SendLists() call          |
| contained.                                                               |
|                                                                          |
| **Advanced send types**                                                  |
|                                                                          |
| *Send most recent values on resends*                                     |
|                                                                          |
| When RakNet resends a message, it can only send what you gave to it      |
| originally. For data that changes continually (position for example) you |
| may only want to resend the most recent value. To do so, send the data   |
| using UNRELIABLE\_WITH\_ACK\_RECEIPT. Call RakPeer::GetNextSendReceipt() |
| and pass the value to RakPeer::Send(). And in memory store an            |
| association between what type of message that was, and the send receipt. |
| If you get ID\_SND\_RECEIPT\_ACKED, delete the association (the message  |
| was delivered). If you get ID\_SND\_RECEIPT\_LOSS, resend the message    |
| using the most current values.                                           |
|                                                                          |
| If you want the data to also be sequenced, then write your own sequence  |
| number along with the message. The remote side should store the highest  |
| sequenced number received. If the incoming message has a lower sequence  |
| number than the highest received, it is an old message and can be        |
| ignored.                                                                 |
|                                                                          |
| Here is code using an unsigned char sequence number. It will work as     |
| long as you do not send more than 127 messages out of order:             |
|                                                                          |
| typedef unsigned char SequenceNumberType;                                |
|                                                                          |
| bool GreaterThan(SequenceNumberType a, SequenceNumberType b)\            |
| {\                                                                       |
| // a &gt; b?\                                                            |
| const SequenceNumberType halfSpan =(SequenceNumberType)                  |
| (((SequenceNumberType)(const                                             |
| SequenceNumberType)-1)/(SequenceNumberType)2);\                          |
| return b!=a && b-a&gt;halfSpan;\                                         |
| }                                                                        |
|                                                                          |
| *Sequenced data, rather than sequenced messages*                         |
|                                                                          |
| RakNet's sequencing only works on the entire message. However, sometimes |
| you want to sequence data at a higher level of granularity. For example, |
| suppose you had both position and health sequenced.                      |
|                                                                          |
| Message A contains health\                                               |
| Message B contains both health and position\                             |
| Message C contains position                                              |
|                                                                          |
| Using normal sequencing, if the messages arrived in the order A,C,B,     |
| message B would be discarded. However, you lose useful information,      |
| since message B contains a more recent health value and could have been  |
| used.                                                                    |
|                                                                          |
| You can subsequence on data manually by writing your own sequence number |
| per variable that you are serializing (as described above). Then send    |
| the data using a non-sequenced send type depending on your needs,        |
| UNRELIABLE, UNRELIABLE\_WITH\_ACK\_RECEIPT, RELIABLE, etc. While this    |
| does incur more bandwidth and processing overhead, it has the advantage  |
| that every update can be processed as soon as possible.                  |
+--------------------------------------------------------------------------+

  --------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}<span class="RakNetWhiteHeader">See Also</span>
  --------------------------------------------------------------------------------------

  ----------------------------------------
  [Index](index.html)\
  [Sending Packets](sendingpackets.html)
  ----------------------------------------


