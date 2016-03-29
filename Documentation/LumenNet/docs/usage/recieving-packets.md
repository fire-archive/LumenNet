---
title: "Receiving Packets"
excerpt: ""
---
<table>
<colgroup>
<col width="100%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left"><p><span style="font-variant: normal"><span style="font-style: normal"><strong>Receiving a packet</strong></span></span><br /><br /> When a packet comes in on the network, i.e. Receive returns non-zero, there are three steps involved in handling it:<br /><br /> 1. Determine the packet type. This is returned by the following code</p>
<pre class="raknetcode"><code>unsigned char GetPacketIdentifier(Packet *p)
{
        if ((unsigned char)p-&gt;data[0] == ID_TIMESTAMP)
                return (unsigned char) p-&gt;data[sizeof(unsigned char) + sizeof(unsigned long)];
        else
                return (unsigned char) p-&gt;data[0];
}</code></pre>
<p>2. Process the data<br /><br /> <span style="font-variant: normal"><span style="font-style: normal"><strong>Receiving a structure</strong></span></span><br /><br /> If you originally sent a structure, you can cast it back as follows:</p>
<pre class="raknetcode"><code>if (GetPacketIdentifier(packet)==/* User assigned packet identifier here */)
        DoMyPacketHandler(packet);

// Put this anywhere you want.  Inside the state class that handles the game is a good place
void DoMyPacketHandler(Packet *packet)
{
        // Cast the data to the appropriate type of struct
        MyStruct *s = (MyStruct *) packet-&gt;data;
        assert(p-&gt;length == sizeof(MyStruct)); // This is a good idea if you’re transmitting structs.
        if (p-&gt;length != sizeof(MyStruct))
                return;

        // Perform the functionality for this type of packet, with your struct,  MyStruct *s
}</code></pre>
<p><em>Usability Comments</em></p>
<ul>
<li></li>
<li></li>
<li></li>
</ul>
<p><span style="font-variant: normal"><span style="font-style: normal"><strong>Receiving a bitstream</strong></span></span><br /><br /> If you originally sent a bitstream, we create a bitstream to unparse the data in the same order we wrote it. We create a bitstream, using the data and the length of the packet. We then use the Read functions where we formerly used the Write functions, the ReadCompressed functions where we formerly used WriteCompressed, and follow the same logical branching if we wrote any data conditionally. This is all shown in the following example which would read in the data for the mine we created in <a href="creatingpackets.html">creating packets</a>.</p>
<pre class="raknetcode"><code>void DoMyPacketHandler(Packet *packet)
{
        Bitstream myBitStream(packet-&gt;data, packet-&gt;length, false); // The false is for efficiency so we don&#39;t make a copy of the passed data
        myBitStream.Read(useTimeStamp);
        myBitStream.Read(timeStamp);
        myBitStream.Read(typeId);
        bool isAtZero;
        myBitStream.Read(isAtZero);
        if (isAtZero==false)
        {
                x=0.0f;
                y=0.0f;
                z=0.0f;
        } else {
                myBitStream.Read(x);
                myBitStream.Read(y);
                myBitStream.Read(z);
        }
        
        myBitStream.Read(networkID); // In the struct this is NetworkID networkId
        myBitStream.Read(systemAddress); // In the struct this is SystemAddress systemAddress
}</code></pre>
<p>3. Deallocate the packet by passing it to DeallocatePacket(Packet *packet) of the RakPeerInterface instance that you got it from.</p></td>
</tr>
</tbody>
</table>

<table>
<colgroup>
<col width="100%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left"><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAMAAAAoyzS7AAAADFBMVEX////8A/sAAAD///9gBn0RAAAAAnRSTlP/AOW3MEoAAAAKSURBVHicY2AEAAADAAJL9d3qAAAAAElFTkSuQmCC" /> <strong>See Also</strong></p></td>
</tr>
</tbody>
</table>

<table>
<colgroup>
<col width="100%" />
</colgroup>
<tbody>
<tr class="odd">
<td align="left"><p><a href="index.html">Index</a><br /> <a href="creatingpackets.html">Creating Packets</a><br /> <a href="sendingpackets.html">Sending Packets</a></p></td>
</tr>
</tbody>
</table>