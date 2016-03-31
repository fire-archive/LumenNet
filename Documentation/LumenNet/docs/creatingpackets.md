![Oculus VR, Inc.](RakNet_Icon_Final-copy.jpg){width="150"
height="150"}\
\
  -------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Creating Packets
  -------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">How to encode your game data into         |
| packets</span>\                                                          |
| \                                                                        |
| Systems that run RakNet, and in fact all systems on the internet,        |
| communicate through what is commonly known as packets. Or more           |
| accurately in the case of UDP, datagrams. Each datagram is created by    |
| RakNet and contains one or more messages. Messages could be created by   |
| you, such as position or health, or sometimes are created by RakNet      |
| internally, such as pings. By convention, the first byte of messages     |
| contain a numerical identifier from 0 to 255 which is used to indicate   |
| what type of message it is. RakNet already has a large set of messages   |
| it uses internally, or for plugins. These can be viewed in the file      |
| MessageIdentifiers.h.\                                                   |
| \                                                                        |
| For this example, lets set the position of a timed mine in the           |
| gameworld. We'll need the following data:\                               |
| -   The position of the mine, which is 3 floats. float x, float y,       |
|     float z. You may have your own vector type which you can use intead. |
| -   Some way to refer to the mine that all systems agree on. The         |
|     [NetworkIDObject](networkidobject.html) class is perfect for that.   |
|     Lets assume class Mine inherits from NetworkIDObject. Then all we    |
|     have to store is get the NetworkID of the mine (for more information |
|     see [Receiving Packets](receivingpackets.html), [Sending             |
|     Packets](sendingpackets.html).                                       |
| -   Who owns the mine. That way if someone steps on it we know who to    |
|     give credit to. The built in reference to players, SystemAddress,    |
|     is perfect.. You can use GetExternalID() to get the SystemAddress.   |
| -   When the mine was placed. Lets say after 10 seconds the mine is      |
|     automatically disintegrated, so it's important that we get the time  |
|     correct so the mine doesn't disintegrate at different times on       |
|     different computers. Fortunately the RakNet has the built-in ability |
|     to handle this using [Timestamping](timestamping.html).              |
|                                                                          |
| <span class="RakNetBlueHeader">Use a structure or a bitstream?</span>\   |
| \                                                                        |
| Ultimately, anytime you send data you will send a stream of characters.  |
| There are two easy ways to encode your data into this. One is to create  |
| a structure and cast it to a (char\*) the other is to use the built-in   |
| [BitStream](bitstreams.html) class.\                                     |
| \                                                                        |
| The advantage of creating a structure and casting is that it is very     |
| easy to change the structure and to see what data you are actually       |
| sending. Since both the sender and the recipient can share the same      |
| source file defining the structure, you avoid casting mistakes. There is |
| also no risk of getting the data out of order, or using the wrong types. |
| The disadvantage of creating a structure is that you often have to       |
| change and recompile many files to do so. You lose the compression you   |
| can automatically perform with the bitstream class. And RakNet cannot    |
| automatically endian-swap the structure members.\                        |
| \                                                                        |
| The advantage of using a bitstream is that you don't have to change any  |
| external files to use it. Simply create the bitstream, write the data    |
| you want in whatever order you want, and send it. You can use the        |
| 'compressed' version of the read and write methods to write using fewer  |
| bits and it will write bools using only one bit. You can write data out  |
| dynamically, writing certain values if certain conditions are true or    |
| false. BitStream will automatically endian-swap members written with     |
| Serialize(), Write(), or Read(). The disadvantage of a bitstream is you  |
| are now susceptible to make mistakes. You can read data in a way that    |
| does not complement how you wrote it - the wrong order, a wrong data     |
| type, or other mistakes.\                                                |
| \                                                                        |
| We will cover both ways of creating packets here.\                       |
+--------------------------------------------------------------------------+

  --------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Creating Packets with structs
  --------------------------------------------------------------------

+--------------------------------------------------------------------------+
| \                                                                        |
| As I’ve probably mentioned earlier, RakNet uses a convention on how      |
| packets (Packet) types are identified. The first byte of the data field  |
| is a single byte enumeration that specifies type, followed by the        |
| transmitted data. In packets that include a time stamp, the first byte   |
| contains ID\_TIMESTAMP, the following 4 bytes the actual time stamp      |
| value, then the byte that identifies the packet, and only then the       |
| actual data transmitted.\                                                |
| \                                                                        |
| <span class="RakNetBlueHeader">Without Timestamping</span> <span         |
| class="RakNetCode">\                                                     |
| </span>                                                                  |
|                                                                          |
| \#pragma pack(push, 1)\                                                  |
| struct structName\                                                       |
| {\                                                                       |
| unsigned char typeId; // Your type here\                                 |
| // Your data here\                                                       |
| };\                                                                      |
| \#pragma pack(pop)                                                       |
|                                                                          |
| Noticed the \#pragma pack(push,1) and \#pragma pack(pop) ? These force   |
| your compiler (in this case VC++), to pack the structure as              |
| byte-aligned. Check your compiler documentation to learn more.           |
|                                                                          |
| With Timestamping                                                        |
|                                                                          |
| \#pragma pack(push, 1)\                                                  |
| struct structName\                                                       |
| {\                                                                       |
| unsigned char useTimeStamp; // Assign ID\_TIMESTAMP to this\             |
| RakNet::Time timeStamp; // Put the system time in here returned by       |
| RakNet::GetTime() or some other method that returns a similar value\     |
| unsigned char typeId; // Your type here\                                 |
| // Your data here\                                                       |
| };\                                                                      |
| \#pragma pack(pop)                                                       |
|                                                                          |
| Note that when sending structures, RakNet assumes the timeStamp is in    |
| network order. You would have to use the function                        |
| BitStream::EndianSwapBytes() on the timeStamp field to make this happen. |
| To then read the timestamp on the receiving system, use if               |
| (bitStream-&gt;DoEndianSwap()) bitStream-&gt;ReverseBytes(timeStamp,     |
| sizeof(timeStamp). This step is not necessary if using BitStreams.       |
|                                                                          |
| Fill out your packet. For our timed mine, we want the form that uses     |
| timestamping. So the end result should look like the following...        |
|                                                                          |
| <span class="RakNetCode"> \#pragma pack(push, 1)\                        |
| struct structName\                                                       |
| {\                                                                       |
| unsigned char useTimeStamp; // Assign ID\_TIMESTAMP to this\             |
| RakNet::Time timeStamp; // Put the system time in here returned by       |
| RakNet::GetTime()\                                                       |
| unsigned char typeId; // You should put here an enum you defined after   |
| the last one defined in MessageIdentifiers.h, lets say                   |
| ID\_SET\_TIMED\_MINE\                                                    |
| float x,y,z; // Mine position\                                           |
| NetworkID networkId; // NetworkID of the mine, used as a common method   |
| to refer to the mine on different computers\                             |
| SystemAddress systemAddress; // The SystenAddress of the player that     |
| owns the mine\                                                           |
| };\                                                                      |
| \#pragma pack(pop)</span>                                                |
| As I wrote in the comment above, we have to define enums for our own     |
| packets types, so when the data stream arrives in a Receive call we know |
| what we are looking at. You should define your enums as starting at      |
| ID\_USER\_PACKET\_ENUM, like this:                                       |
|                                                                          |
| <span class="RakNetCode">\                                               |
| // Define our custom packet ID's\                                        |
| enum {\                                                                  |
| ID\_SET\_TIMED\_MINE = ID\_USER\_PACKET\_ENUM,\                          |
| // More enums....\                                                       |
| };\                                                                      |
| </span>\                                                                 |
| NOTE THAT YOU CANNOT INCLUDE POINTERS DIRECTLY OR INDIRECTLY IN THE      |
| STRUCTS.\                                                                |
| \                                                                        |
| It seems to be a fairly common mistake that people include a pointer or  |
| a class with a pointer in the struct and think that the data pointed to  |
| by the pointer will be sent over the network. This is not the case - all |
| it would send is the pointer address\                                    |
| \                                                                        |
| Nested Structures\                                                       |
| \                                                                        |
| There is no problem with nesting structures. Just keep in mind that the  |
| first byte is always what determines the packet type.\                   |
| <span class="RakNetCode">\                                               |
| \#pragma pack(push, 1)\                                                  |
| struct A\                                                                |
| {\                                                                       |
| unsigned char typeId; // ID\_A\                                          |
| };\                                                                      |
| struct B\                                                                |
| {\                                                                       |
| unsigned char typeId; // ID\_A\                                          |
| };\                                                                      |
| struct C // Struct C is of type ID\_A\                                   |
| {\                                                                       |
| A a;\                                                                    |
| B b;\                                                                    |
| }\                                                                       |
| struct D // Struct D is of type ID\_B\                                   |
| {\                                                                       |
| B b;\                                                                    |
| A a;\                                                                    |
| }\                                                                       |
| \#pragma pack(pop)</span>\                                               |
+--------------------------------------------------------------------------+

  --------------------------------------------------------------------------
  <span class="RakNetWhiteHeader"> Creating Packets with Bitstreams</span>
  --------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Write less data with bitstreams </span>\  |
| \                                                                        |
| Lets take our mine example above and use a bitstream to write it out     |
| instead. We have all the same data as before.\                           |
| \                                                                        |
| <span class="RakNetCode"> MessageID useTimeStamp; // Assign this to      |
| ID\_TIMESTAMP\                                                           |
| RakNet::Time timeStamp; // Put the system time in here returned by       |
| RakNet::GetTime()\                                                       |
| MessageID typeId; // This will be assigned to a type I've added after    |
| ID\_USER\_PACKET\_ENUM, lets say ID\_SET\_TIMED\_MINE\                   |
| useTimeStamp = ID\_TIMESTAMP;\                                           |
| timeStamp = RakNet::GetTime();\                                          |
| typeId=ID\_SET\_TIMED\_MINE;\                                            |
| Bitstream myBitStream;\                                                  |
| myBitStream.Write(useTimeStamp);\                                        |
| myBitStream.Write(timeStamp);\                                           |
| myBitStream.Write(typeId);\                                              |
| // Assume we have a Mine\* mine object\                                  |
| myBitStream.Write(mine-&gt;GetPosition().x);\                            |
| myBitStream.Write(mine-&gt;GetPosition().y);\                            |
| myBitStream.Write(mine-&gt;GetPosition().z);\                            |
| myBitStream.Write(mine-&gt;GetNetworkID()); // In the struct this is     |
| NetworkID networkId\                                                     |
| myBitStream.Write(mine-&gt;GetOwner()); // In the struct this is         |
| SystemAddress systemAddress\                                             |
| </span>\                                                                 |
| If we were to send myBitStream to RakPeerInterface::Send it would be     |
| identical internally to a casted struct at this point. Now lets try some |
| improvements. Lets assume that a good deal of the time mines are at      |
| 0,0,0 for some reason. We can then do this instead:\                     |
| <span class="RakNetCode">\                                               |
| unsigned char useTimeStamp; // Assign this to ID\_TIMESTAMP\             |
| RakNet::Time timeStamp; // Put the system time in here returned by       |
| RakNet::GetTime()\                                                       |
| unsigned char typeId; // This will be assigned to a type I've added      |
| after ID\_USER\_PACKET\_ENUM, lets say ID\_SET\_TIMED\_MINE\             |
| useTimeStamp = ID\_TIMESTAMP;\                                           |
| timeStamp = RakNet::GetTime();\                                          |
| typeId=ID\_SET\_TIMED\_MINE;\                                            |
| Bitstream myBitStream;\                                                  |
| myBitStream.Write(useTimeStamp);\                                        |
| myBitStream.Write(timeStamp);\                                           |
| myBitStream.Write(typeId);\                                              |
| // Assume we have a Mine\* mine object\                                  |
| // If the mine is at 0,0,0, use 1 bit to represent this\                 |
| if (mine-&gt;GetPosition().x==0.0f && mine-&gt;GetPosition().y==0.0f &&  |
| mine-&gt;GetPosition().z==0.0f)\                                         |
| {\                                                                       |
| myBitStream.Write(true);\                                                |
| }\                                                                       |
| else\                                                                    |
| {\                                                                       |
| myBitStream.Write(false);\                                               |
| myBitStream.Write(mine-&gt;GetPosition().x);\                            |
| myBitStream.Write(mine-&gt;GetPosition().y);\                            |
| myBitStream.Write(mine-&gt;GetPosition().z);\                            |
| }\                                                                       |
| myBitStream.Write(mine-&gt;GetNetworkID()); // In the struct this is     |
| NetworkID networkId\                                                     |
| myBitStream.Write(mine-&gt;GetOwner()); // In the struct this is         |
| SystemAddress systemAddress\                                             |
| </span>\                                                                 |
| This can potentially save us sending 3 floats over the network, at the   |
| cost of 1 bit.\                                                          |
| \                                                                        |
| <span class="RakNetBlueHeader">Common mistake!</span>\                   |
| \                                                                        |
| When writing the first byte to a bitstream, be sure to cast it to        |
| (MessageID) or (unsigned char). If you just write the enumeration        |
| directly you will be writing a full integer (4 bytes).<span              |
| style="font-style: italic;">\                                            |
| </span>\                                                                 |
| Right:\                                                                  |
| <span                                                                    |
| class="RakNetCode">bitStream-&gt;Write((MessageID)ID\_SET\_TIMED\_MINE); |
| </span>                                                                  |
|                                                                          |
| Wrong:\                                                                  |
| <span                                                                    |
| class="RakNetCode">bitStream-&gt;Write(ID\_SET\_TIMED\_MINE);</span>     |
|                                                                          |
| In the second case, RakNet will see the first byte is 0, which is        |
| reserved internally to ID\_INTERNAL\_PING, and you will never get it.    |
|                                                                          |
| \                                                                        |
| **Writing strings**\                                                     |
| \                                                                        |
| It is possible to write strings using the array overload of the          |
| BitStream. One way to do it would be to write the length, then the data  |
| such as:                                                                 |
|                                                                          |
| <span class="RakNetCode">void WriteStringToBitStream(char \*myString,    |
| BitStream \*output)\                                                     |
| {\                                                                       |
| output-&gt;Write((unsigned short) strlen(myString));\                    |
| output-&gt;Write(myString, strlen(myString);\                            |
| }</span>                                                                 |
|                                                                          |
| Decoding is similar. However, that is not very efficient. RakNet comes   |
| with a built in StringCompressor called... stringCompressor. It is a     |
| global instance. With it, WriteStringToBitStream becomes:                |
|                                                                          |
| <span class="RakNetCode">void WriteStringToBitStream(char \*myString,    |
| BitStream \*output)\                                                     |
| {\                                                                       |
| stringCompressor-&gt;EncodeString(myString, 256, output);\               |
| }</span>                                                                 |
|                                                                          |
| Not only does it encode the string, so the string can not easily be read |
| by packet sniffers, but it compresses it as well. To decode the string   |
| you would use:                                                           |
|                                                                          |
| <span class="RakNetCode">void WriteBitStreamToString(char \*myString,    |
| BitStream \*input)\                                                      |
| {\                                                                       |
| stringCompressor-&gt;DecodeString(myString, 256, input);\                |
| }</span>                                                                 |
|                                                                          |
| The 256 in this case is the maximum number of bytes to write and read.   |
| In EncodeString, if your string is less than 256 it will write the       |
| entire string. If it is greater than 256 characters it will truncate it  |
| such that it would decode to an array with 256 characters, including the |
| null terminator.                                                         |
|                                                                          |
| RakNet also has a string class, RakNet::RakString, found in RakString.h  |
|                                                                          |
| RakNet::RakString rakString("The value is %i", myInt);                   |
|                                                                          |
| <span class="RakNetCode">bitStream-&gt;write(rakString);</span>\         |
| \                                                                        |
| RakString is approximately 3X faster than std::string.                   |
|                                                                          |
| Use RakWString for Unicode support.                                      |
|                                                                          |
| *Programmer's notes:*\                                                   |
| \                                                                        |
| 1. You can also write structs directly into a Bitstream simply by        |
| casting it to a (char\*). It will copy your structs using memcpy. As     |
| with structs, it will not dereference pointers so you should not write   |
| pointers into the bitstream.\                                            |
| 2. If you use a string very commonly, you can use the StringTable class  |
| instead. It works the same way as StringCompressor, but can send two     |
| bytes to represent a known string.\                                      |
+--------------------------------------------------------------------------+

  -----------
   See Also
  -----------

  ---------------------------------------------
  [Index](index.html)\
  [Sending Packets](sendingpackets.html)\
  [Receiving Packets](receivingpackets.html)\
  [Timestamping](timestamping.html)\
  ---------------------------------------------


