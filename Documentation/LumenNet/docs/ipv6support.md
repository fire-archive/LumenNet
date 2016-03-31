<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ------------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}<span class="RakNetWhiteHeader">IPV6 support</span>
  ------------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| IPV6 addresses                                                           |
| and the difference between IPV4.                                         |
| IPV6 is the next-generation of IP address. IPV6 was developed because of |
| all available IPV4 addresses have been allocated. Over time the industry |
| will transition to use IPV6 so it is necessary to support this for       |
| future-generation appplications.                                         |
|                                                                          |
| IPV4 represents IP addresses with 4 bytes, in the notation 127.0.0.1.    |
| IPV6 uses 16 bytes, with a notation such as fe80::7c:31f7:fec4:27de.     |
| When RAKNET\_SUPPORT\_IPV6 is set to 1 in RakNetDefines.h, which it is   |
| by default, support for IPV6 will be built into RakNet.                  |
|                                                                          |
| The loopback address with IPV4 is 127.0.0.1. The loopback address with   |
| IPV6 is ::1. The broadcast address with IPV4 is 255.255.255.255. IPV6    |
| does not support broadcast. It does support multicast if you configure   |
| your router to do so. There is no default multicast address for IPV6,    |
| meaning LANServerDiscovery will not work without manual configuration by |
| the end-user.                                                            |
|                                                                          |
| NAT Punchthrough is not necessary when using IPV6 exclusively. Provided  |
| that you know the IP address of the system, you can connect to that      |
| system directly even if that system is behind a router.                  |
|                                                                          |
| IPV4 sockets / IP addresses cannot connect to IPV6 sockets / IP          |
| addresses and vice-versa.                                                |
|                                                                          |
| It is valid to start two sockets on the same port if one socket is used  |
| for IPV4 and the other IPV6, as you can see in the code fragment below.  |
|                                                                          |
| **Supporting IPV6**                                                      |
|                                                                          |
| This code is from the project ChatExampleServer. It starts two sockets   |
| if possible, the second of which supports IPV6. Not all operating        |
| systems support IPV6 by default or necessarily at all, so the fallback   |
| is necessary.                                                            |
|                                                                          |
| RakNet::SocketDescriptor socketDescriptors\[2\];\                        |
| socketDescriptors\[0\].port=atoi(portstring);\                           |
| socketDescriptors\[0\].socketFamily=AF\_INET; // Test out IPV4\          |
| socketDescriptors\[1\].port=atoi(portstring);\                           |
| socketDescriptors\[1\].socketFamily=AF\_INET6; // Test out IPV6\         |
| bool b = server-&gt;Startup(4, socketDescriptors, 2                      |
| )==RakNet::RAKNET\_STARTED;\                                             |
| server-&gt;SetMaximumIncomingConnections(4);\                            |
| if (!b)\                                                                 |
| {\                                                                       |
| printf("Failed to start dual IPV4 and IPV6 ports. Trying IPV4            |
| only.\\n");\                                                             |
| // Try again, but leave out IPV6\                                        |
| b = server-&gt;Startup(4, socketDescriptors, 1                           |
| )==RakNet::RAKNET\_STARTED;\                                             |
| if (!b)\                                                                 |
| {\                                                                       |
| puts("Server failed to start. Terminating.");\                           |
| exit(1);\                                                                |
| }\                                                                       |
| }                                                                        |
|                                                                          |
| As you can see, the process to enable IPV6 is to set the socketFamily    |
| member in the SocketDescriptor structure to AF\_INET6. The default is    |
| AF\_INET, which is to say IPV4.                                          |
|                                                                          |
| RakNet's console platforms do not support IPV6 at the time of this       |
| writing.                                                                 |
+--------------------------------------------------------------------------+

  --------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}<span class="RakNetWhiteHeader">See Also</span>
  --------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)                                                      |
+--------------------------------------------------------------------------+


