<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -------------------
   Router2 Overview
  -------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Send messages through intermediate        |
| systems</span>\                                                          |
|                                                                          |
| Router2 routes datagrams between two systems that are not directly       |
| connected by using the bandwidth of a third system, to which the other   |
| two systems were connected. It is of benefit when a fully connected mesh |
| topology is desired, but could not be completely established due to      |
| routers and/or firewalls. As the system address of a remote system will  |
| be the system address of the intermediary, it is necessary to use the    |
| RakNetGUID object to refer to systems, including with other plugins      |
|                                                                          |
| To use                                                                   |
|                                                                          |
| Attach one instance of the Router2 plugin to each system..               |
|                                                                          |
| Call EstablishRouting with the RakNetGUID of the destination system.     |
|                                                                          |
| A message will be broadcast to all connected instances of RakPeer. For   |
| each of those that are running the Router2 plugin, the connection list   |
| will be queried to see who, if anyone is connected to the target system. |
|                                                                          |
| After all systems are queried, the system with the lowest total ping,    |
| that is also already forwarding the fewest connections, will start the   |
| UDPForwarder system and return ID\_ROUTER\_2\_FORWARDING\_ESTABLISHED.   |
| If no path is available, ID\_ROUTER\_2\_FORWARDING\_NO\_PATH will be     |
| returned instead.                                                        |
|                                                                          |
| Once a path is established, you should attempt to connect to the target  |
| system as usual. The following code should be used:                      |
|                                                                          |
| RakNet::BitStream bs(packet-&gt;data, packet-&gt;length, false);\        |
| bs.IgnoreBytes(sizeof(MessageID));\                                      |
| RakNetGUID endpointGuid;\                                                |
| bs.Read(endpointGuid);\                                                  |
| unsigned short sourceToDestPort;\                                        |
| bs.Read(sourceToDestPort);\                                              |
| char ipAddressString\[32\];\                                             |
| packet-&gt;systemAddress.ToString(false, ipAddressString);\              |
| rakPeerInterface-&gt;EstablishRouting(ipAddressString, sourceToDestPort, |
| 0,0);                                                                    |
|                                                                          |
| Note that rerouting happens automatically. When a connection is          |
| rerouted, you will get ID\_ROUTER\_2\_REROUTED. While the SystemAddress  |
| will have changed, the RakNetGUID will not. Therefore, you must only     |
| refer to the target system using RakNetGUID when using this plugin.      |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  --------------------------------------------------------------
  [Index](index.html)\
  [NAT Traversal architecture](nattraversalarchitecture.html)\
  --------------------------------------------------------------


