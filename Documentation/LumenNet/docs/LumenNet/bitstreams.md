<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ---------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Bitstream Overview
  ---------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Description</span>\                       |
| \                                                                        |
| The bitstream class is a helper class under the namespace RakNet that is |
| used to wrap a dynamic array for the purpose of packing and unpacking    |
| bits. Its main four benefits are:                                        |
| 1.  Creating packets dynamically                                         |
| 2.  Compression                                                          |
| 3.  Writing Bits                                                         |
| 4.  Endian swapping                                                      |
|                                                                          |
| With structs you have to predefine your structures and cast them to a    |
| (char\*). With a bitstream, you can choose to write blocks at runtime,   |
| depending on the context. Bitstreams can compress the native types using |
| the SerializeBitsFromIntegerRange and SerializeFloat16().\               |
| \                                                                        |
| You can also write bits. Most of the time you will not care about this.  |
| However, when writing booleans it will automatically only write one bit. |
| This can also be very useful for encryption since your data will no      |
| longer be byte aligned.\                                                 |
| \                                                                        |
| **Writing Data**                                                         |
|                                                                          |
| Bitstream is templated to take any type of data. If this is a built-in   |
| type, such as NetworkIDObject, it uses partial template specialization   |
| to write the type more efficiently. If it's a native type, or a          |
| structure, it writes the individual bits, similar to memcpy. You can     |
| pass structs containing multiple data members to bitstreams. However,    |
| you may wish to serialize each individual element to do correct          |
| [endian](http://en.wikipedia.org/wiki/Endianness) swapping (needed for   |
| communication between PCs and Macs, for example).\                       |
| \                                                                        |
| <span class="RakNetCode"> struct MyVector\                               |
| {\                                                                       |
| float x,y,z;\                                                            |
| } myVector;\                                                             |
| \                                                                        |
| // No endian swapping\                                                   |
| bitStream.Write(myVector);\                                              |
| \                                                                        |
| // With endian swapping\                                                 |
| \#undef \_\_BITSTREAM\_NATIVE\_END\                                      |
| bitStream.Write(myVector.x);\                                            |
| bitStream.Write(myVector.y);\                                            |
| bitStream.Write(myVector.z);\                                            |
| \                                                                        |
| // You can also override operator left shift and right shift</span>\     |
| <span class="RakNetCode">// Shift operators have to be in the namespace  |
| RakNet or they might use the default one in BitStream.h instead. Error   |
| occurs with std::string\                                                 |
| namespace RakNet\                                                        |
| {</span>                                                                 |
|                                                                          |
| <span class="RakNetCode"> RakNet::BitStream& operator &lt;&lt;           |
| (RakNet::BitStream& out, MyVector& in)\                                  |
| {\                                                                       |
| out.WriteNormVector(in.x,in.y,in.z);\                                    |
| return out;\                                                             |
| }\                                                                       |
| RakNet::BitStream& operator &gt;&gt; (RakNet::BitStream& in, MyVector&   |
| out)\                                                                    |
| {\                                                                       |
| bool success = in.ReadNormVector(out.x,out.y,out.z);\                    |
| assert(success);\                                                        |
| return in;\                                                              |
| }</span>                                                                 |
|                                                                          |
| <span class="RakNetCode">} // namespace RakNet\                          |
| \                                                                        |
| // Read from bitstream\                                                  |
| myVector &lt;&lt; bitStream;\                                            |
| // Write to bitstream\                                                   |
| myVector &gt;&gt; bitStream;\                                            |
| </span>\                                                                 |
| Optional - One of the constructor versions takes a length in bytes as a  |
| parameter. If you have an idea of the size of your data you can pass     |
| this number when creating the bitstream to avoid internal                |
| reallocations.\                                                          |
| \                                                                        |
| See [Creating Packets](creatingpackets.html) for more details.\          |
| \                                                                        |
| **Reading Data**\                                                        |
| \                                                                        |
| Reading data is equally simple. Create a bitstream, and in the           |
| constructor assign it your data.\                                        |
| \                                                                        |
| <span class="RakNetCode"> // Assuming we have a Packet \*\               |
| BitStream myBitStream(packet-&gt;data, packet-&gt;length, false);\       |
| struct MyVector\                                                         |
| {\                                                                       |
| float x,y,z;\                                                            |
| } myVector;\                                                             |
| \                                                                        |
| // No endian swapping\                                                   |
| bitStream.Read(myVector);\                                               |
| \                                                                        |
| // With endian swapping (\_\_BITSTREAM\_NATIVE\_END should just be       |
| commented in RakNetDefines.h)\                                           |
| \#undef \_\_BITSTREAM\_NATIVE\_END\                                      |
| \#include "BitStream.h" bitStream.Read(myVector.x);\                     |
| bitStream.Read(myVector.y);\                                             |
| bitStream.Read(myVector.z);\                                             |
| \                                                                        |
| </span> See [Receiving Packets](receivingpackets.html) for a more        |
| complete example.\                                                       |
| \                                                                        |
| **Serializing Data**\                                                    |
| \                                                                        |
| You can have the same function read and write, by using                  |
| BitStream::Serialize() instead of Read() or Write().\                    |
| \                                                                        |
| <span class="RakNetCode"> struct MyVector\                               |
| {\                                                                       |
| float x,y,z;\                                                            |
| // writeToBitstream==true means write, writeToBitstream==false means     |
| read\                                                                    |
| void Serialize(bool writeToBitstream, BitStream \*bs)\                   |
| {\                                                                       |
| bs-&gt;Serialize(writeToBitstream, x);\                                  |
| bs-&gt;Serialize(writeToBitstream, y);\                                  |
| bs-&gt;Serialize(writeToBitstream, z);\                                  |
| }\                                                                       |
| } myVector;\                                                             |
| </span>\                                                                 |
| See [Receiving Packets](receivingpackets.html) for a more complete       |
| example.\                                                                |
| \                                                                        |
+--------------------------------------------------------------------------+

  -------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Useful functions
  -------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">See BitStream.h for a full list of        |
| functions.</span>\                                                       |
| \                                                                        |
| **Reset**\                                                               |
| Restart the bitstream, clearing all data.                                |
|                                                                          |
| **Write functions**\                                                     |
| The write functions write data to the bitstream at the end of the        |
| bitstream. You should use the analogous Read to get the data back out.\  |
| \                                                                        |
| **Read functions**\                                                      |
| The read functions read data already in the bitstream, in order from     |
| beginning to end. The read function returns false if there is no more    |
| data in the bitstream.                                                   |
|                                                                          |
| **WriteBitsFromIntegerRange, ReadBitsFromIntegerRange,                   |
| SerializeBitsFromIntegerRange\                                           |
| **If a number only uses a specific range of values (such as 10-20) this  |
| function will determine automatically the number of bits needed to write |
| that range of values.                                                    |
|                                                                          |
| **WriteCasted, ReadCasted**\                                             |
| Write a variable of one type as if it were casted to another type. For   |
| example, WriteCasted&lt;char&gt;(5); is equivalent to char c=5;          |
| Write(c);                                                                |
|                                                                          |
| **WriteNormVector, ReadNormVector**\                                     |
| Writes a normalized vector where each component ranges from -1 to +1.    |
| Each component is written with 16 bites.                                 |
|                                                                          |
| **WriteFloat16, ReadFloat16\                                             |
| **Given a min and max value for a floating point number, divide the      |
| range by 65535 and write the result in 16 bytes (lossy)..                |
|                                                                          |
| **WriteNormQuat, ReadNormQuat**\                                         |
| Write a quaternion in 16\*3+4 bits (lossy).                              |
|                                                                          |
| **WriteOrthMatrix, ReadOrthMatrix**\                                     |
| Convert an orthonormal matrix to a quaternion, then call                 |
| WriteNormQuat/ReadNormQuat.                                              |
|                                                                          |
| **GetNumberOfBitsUsed**\                                                 |
| **GetNumberOfBytesUsed**\                                                |
| Gives you the number of bytes or bits written.\                          |
| \                                                                        |
| **GetData**\                                                             |
| Gives you a pointer to the internal data of the bitstream. This is a     |
| (char\*) allocated with malloc and is presented in case you need direct  |
| assess to the data.                                                      |
|                                                                          |
| \                                                                        |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ---------------------------------------------
  [Index](index.html)\
  [Creating Packets](creatingpackets.html)\
  [Receiving Packets](receivingpackets.html)\
  ---------------------------------------------


