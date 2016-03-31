<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ---------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}NAT Type detection
  ---------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Determine in advance if you can complete  |
| NAT punchthroug</span>                                                   |
|                                                                          |
| [NAT                                                                     |
| punchthrough](http://www.jenkinssoftware.com/raknet/manual/natpunchthrou |
| gh.html)                                                                 |
| success rates is based on what kind of algorithm the NAT uses.           |
| **Full cone NAT**: Accepts any datagrams to a port that has been         |
| previously used. Will accept the first datagram from the remote peer.    |
|                                                                          |
| **Address-Restricted cone NAT**: Accepts datagrams to a port as long as  |
| the datagram source IP address is a system we have already sent to. Will |
| accept the first datagram if both systems send simultaneously.           |
| Otherwise, will accept the first datagram after we have sent one         |
| datagram.                                                                |
|                                                                          |
| **Port-Restricted cone NAT**: Same as address-restricted cone NAT, but   |
| we had to send to both the correct remote IP address and correct remote  |
| port. The same source address and port to a different destination uses   |
| the same mapping.                                                        |
|                                                                          |
| **Symmetric NAT**: A different port is chosen for every remote           |
| destination. The same source address and port to a different destination |
| uses a different mapping. Since the port will be different, the first    |
| external punchthrough attempt will fail. For this to work it requires    |
| port-prediction (MAX\_PREDICTIVE\_PORT\_RANGE&gt;1) and that the router  |
| chooses ports sequentially.                                              |
|                                                                          |
| **Success Graph**                                                        |
|   ------------------------------- ----------------- -------------------- |
| ----------- ---------------------------- -----------------               |
|   Router Type                     *Full cone NAT*   *Address-Restricted  |
| cone NAT*   *Port-Restricted cone NAT*   *Symmetric NAT*                 |
|   *Full cone NAT*                 YES               YES                  |
|             YES                          YES                             |
|   *Address-Restricted cone NAT*   YES               YES                  |
|             YES                          YES                             |
|   *Port-Restricted cone NAT*      YES               YES                  |
|             YES                          NO                              |
|   *Symmetric NAT*                 YES               YES                  |
|             NO                           NO                              |
|   ------------------------------- ----------------- -------------------- |
| ----------- ---------------------------- -----------------               |
|                                                                          |
|                                                                          |
|                                                                          |
| The NatTypeDetection plugins allow you to determine which type of NAT    |
| you have, and therefore if NAT punchthrough is likely to complete or     |
| not. This can be determined in advance of joining a game.                |
|                                                                          |
| <span class="RakNetBlueHeader">NAT Type Detection algorithm</span>       |
|                                                                          |
| 1.  Client opens two ports on the same IP address. In                    |
|     NatTypeDetectionClient, the RakNet socket is the first port, c2 is   |
|     the socket on the second port, created                               |
|     in NatTypeDetectionClient::DetectNATType()                           |
| 2.  Server opens two ports on one IP address, and one port on three      |
|     additional IP addresses. This is done                                |
|     in NatTypeDetectionServer::Startup(). The first port on the first IP |
|     address is the normal RakNet socket. The second port on the first IP |
|     address is s1p2. The other three addresses are bound to the sockets  |
|     s2p3, s3p4, and s4p5.                                                |
| 3.  Client connects to the server on the first IP address normally       |
| 4.  Client requests NAT type detection begins                            |
| 5.  Server attempts to send to client's second port. This was a port     |
|     that was never opened previously on the client, therefore if         |
|     received, then the client is not behind a NAT. This is done in       |
|     NatTypeDetectionServer::Update(), defined by STATE\_TESTING\_NONE\_1 |
|     and STATE\_TESTING\_NONE\_2. The reason for 2 attempts is that every |
|     attempt occurs twice. The time for each attempt is the ping \* 3 +   |
|     50 milliseconds. s4p5 is used for this.                              |
| 6.  Server sends from a different IP address to client's first port, the |
|     port that RakNet is connected on. If received, then the client will  |
|     accept datagrams from any source IP address to a port already        |
|     in use. This is therefore full-cone NAT. s2p3 is used for this.      |
| 7.  Server sends from the second port on the already-connected IP        |
|     address, s1p2. If received, then the client is using                 |
|     address-restricted cone NAT.                                         |
| 8.  Client sends to another IP address on the server, from its first     |
|     (already connected) port. If the IP address and port is the same,    |
|     then the client uses the same external IP address and port to all    |
|     connections from the same source address. This is                    |
|     port-restricted NAT.                                                 |
| 9.  Else symmetric NAT.                                                  |
|                                                                          |
| <span class="RakNetBlueHeader">Client Implementation</span>              |
|                                                                          |
| 1.  Create an instance of the plugin: <span                              |
|     class="RakNetCode">NatTypeDetectionServer                            |
|     nayTypeDetectionClient;</span>                                       |
| 2.  Attach the plugin to an instance of RakPeerInterface: <span          |
|     class="RakNetCode">rakPeer-&gt;AttachPlugin(&nayTypeDetectionClient) |
| ;</span>                                                                 |
| 3.  Connect to the server, and wait                                      |
|     for ID\_CONNECTION\_REQUEST\_ACCEPTED. Use the following line to use |
|     the free server provided by RakNet: <span                            |
|     class="RakNetCode">rakPeer-&gt;Connect("8.17.250.34", 60481, 0,      |
|     0);</span>                                                           |
| 4.  Call DetectNATType with the SystemAddress of the server.             |
| 5.  Wait for ID\_NAT\_TYPE\_DETECTION\_RESULT<span                       |
|     class="RakNetCode"></span>                                           |
| 6.  Byte 1 contains the type of NAT that you have. See the enumeration   |
|     NATTypeDetectionResult in NATTypeDetectionCommon.h                   |
| 7.  Various utility functions are provided for this enumeration: <span   |
|     class="RakNetCode">CanConnect(),                                     |
|     NATTypeDetectionResultToString(), NATTypeDetectionResultToStringFrie |
| ndly()</span>                                                            |
|                                                                          |
| <span class="RakNetBlueHeader">Server Implementation</span>              |
|                                                                          |
| 1.  Host a server somewhere, not using NAT / e.g. behind a firewall.     |
|     (RakNet provides a free one at 8.17.250.34:60481, however you may    |
|     wish to host your own for consistent uptime). The server must have   |
|     enough external IP addresses, as described in **NAT Type Detection   |
|     Algorithm**.                                                         |
| 2.  Create an instance of the plugin: <span                              |
|     class="RakNetCode">NatTypeDetectionServernatTypeDetectionServer;</sp |
| an>                                                                      |
| 3.  Attach the plugin: <span                                             |
|     class="RakNetCode">rakPeer-&gt;AttachPlugin(&natTypeDetectionServer) |
| ;</span>                                                                 |
| 4.  Get a list of IP addresses on your system\                           |
|     <span class="RakNetCode">char ipList\[                               |
|     MAXIMUM\_NUMBER\_OF\_INTERNAL\_IDS \]\[ 16 \];\                      |
|     unsigned int binaryAddresses\[MAXIMUM\_NUMBER\_OF\_INTERNAL\_IDS\];\ |
|     SocketLayer::Instance()-&gt;GetMyIP( ipList, binaryAddresses         |
|     );</span>                                                            |
| 5.  Call <span                                                           |
|     class="RakNetCode">natTypeDetectionServer.Startup(ip2,ip3,ip4); //   |
|     ip2,ip3,ip4 must be ip addresses not already in use. If you bound    |
|     RakNet to ip1 in the call to RakPeer::Startup(), then use the 2nd to |
|     4th indices in ipList.</span>                                        |
|                                                                          |
| <span class="RakNetBlueHeader">Sample </span>\                           |
| \                                                                        |
| See the sample *\\Samples\\NATCompleteClient*                            |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [NAT Traversal architecture](nattraversalarchitecture.html)\             |
| [NAT Punchthrough](natpunchthrough.html)                                 |
+--------------------------------------------------------------------------+


