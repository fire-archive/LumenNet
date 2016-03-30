<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -----------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}NAT Traversal Architecture
  -----------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">How to use combine MasterServer2, UPNP,   |
| NAT type detection, FullyConnectedMesh2, and NAT punchthrough for P2P    |
| games</span>                                                             |
|                                                                          |
| Systems involved for peer to peer game listing and connectivity on the   |
| PC, Mac, Linux, or mobiles.                                              |
|                                                                          |
| [MasterServer2](http://masterserver2.raknet.com/): A free server we host |
| that can hold lists of games, and data describing those games\           |
| [UPNP](http://miniupnp.free.fr/): Tells the router to create a port      |
| mapping, in order to allow incoming connections. This a programmatic way |
| of the user manually editing the router configuration\                   |
| [NAT type detection](nattypedetection.html): (Optional) Find out if we   |
| have a router, and how restrictive that router is\                       |
| [FullyConnectedMesh2](fullyconnectedmesh2.html): Manages the complexity  |
| of joining a group of systems at the same time\                          |
| [NAT punchthrough](natpunchthrough.html): Attempt to connect systems for |
| cases where UPNP fails\                                                  |
| [Router2](router.html) (Optional) - Use other player's bandwidth for     |
| routers that cannot connect\                                             |
| [UDPProxyClient](natpunchthrough.html) (Optional) - Route failed         |
| connections through your own servers                                     |
|                                                                          |
| **Step 1: Attempt to connect to the free NAT punchthrough server**       |
|                                                                          |
| rakPeer-&gt;Connect("natpunch.jenkinssoftware.com", 61111, 0, 0);        |
|                                                                          |
| Upon ID\_CONNECTION\_REQUEST\_ACCEPTED, you have connected.\             |
| Upon ID\_NO\_FREE\_INCOMING\_CONNECTIONS,                                |
| ID\_CONNECTION\_ATTEMPT\_FAILED, ID\_INCOMPATIBLE\_PROTOCOL\_VERSION you |
| have failed to connect. You may wish to abort online play at this stage, |
| although this is not technically an absolute failure case.               |
|                                                                          |
| **Step 3 (Optional): Detect NAT type**                                   |
|                                                                          |
| Provided you connected to the NAT punchthrouhg server, you may wish to   |
| detect what type of router you have, or if you have any at all. This can |
| improve the experience for your players by speeding up later steps.\     |
| <span                                                                    |
| class="RakNetCode">natTypeDetectionClient-&gt;DetectNATType(natPunchServ |
| erAddress);</span>\                                                      |
| \                                                                        |
| Upon ID\_NAT\_TYPE\_DETECTION\_RESULT, your NAT type is held in          |
| packet-&gt;data\[1\]\                                                    |
| <span class="RakNetCode">printf("NAT Type is %s (%s)\\n",                |
| NATTypeDetectionResultToString(packet-&gt;data\[1\]),                    |
| NATTypeDetectionResultToStringFriendly(packet-&gt;data\[1\]));</span>    |
|                                                                          |
| The list of results can be see in NATTypeDetectionResult in              |
| NatTypeDetectionCommon.cpp                                               |
|                                                                          |
| The NAT type will not generally change during play, so this step only    |
| needs to be done once per executable session.                            |
|                                                                          |
| **Step 3: Execute UPNP if necessary**                                    |
|                                                                          |
| UPNP is the best way to resolve NAT issues, because it means many other  |
| steps are unnecessary, or will always succeed. If NAT type detection     |
| returned NAT\_TYPE\_NONE, you can skip this step.                        |
|                                                                          |
| DataStructures::List&lt;RakNetSocket2\* &gt; sockets;\                   |
| rakPeer-&gt;GetSockets(sockets);\                                        |
| UPNPOpenAsynch(sockets\[0\]-&gt;GetBoundAddress().GetPort(), 2000,       |
| UPNPProgressCallback, UPNPResultCallback, 0);                            |
|                                                                          |
| Asynch example code:\                                                    |
| *See Samples\\ComprehensivePCGame\\ComprehensivePCGame.cpp*\             |
| RAK\_THREAD\_DECLARATION(UPNPOpenWorker) and related code                |
|                                                                          |
| Library located at:\                                                     |
| *DependentExtensions\\miniupnpc-1.6.20120410*                            |
|                                                                          |
| If UPNP succeeds, the forwarding entry will stay open for a large period |
| of time (perhaps indefinitely), so this step only needs to be done once  |
| per executable session.                                                  |
|                                                                          |
| **Step 4 (Optional): FullyConnectedMesh2::ResetHostCalculation()**       |
|                                                                          |
| FullyConnectedMesh2 will attempt to determine the host of the peer to    |
| peer session based on who has been running the longest.                  |
| ResetHostCalculation() updates the timer of how long the multiplayer     |
| session has been active. If you do not call this, then time spent in     |
| single player, menus, loading screens, etc. will be counted which is     |
| should normally not be. If you do care if the host is kept in order of   |
| players joining the session, you can skip this step.                     |
|                                                                          |
| **Step 5A: Joining - Download from Master Server 2**                     |
|                                                                          |
| To join a game in progress, you can download from the [Master Server     |
| 2](masterserver2.raknet.com) what game sessions have been posted         |
|                                                                          |
| \#define MASTER\_SERVER\_ADDRESS "masterserver2.raknet.com"\             |
| \#define MASTER\_SERVER\_PORT 80                                         |
|                                                                          |
| tcp = TCPInterface::GetInstance();\                                      |
| tcp-&gt;AttachPlugin(httpConnection2);\                                  |
| tcp-&gt;Start(0,0,1);\                                                   |
| RakString rsRequest = RakString::FormatForGET(\                          |
| MASTER\_SERVER\_ADDRESS "/testServer?\_\_gameId=myGameId");\             |
| httpConnection2-&gt;TransmitRequest(rsRequest, MASTER\_SERVER\_ADDRESS,  |
| MASTER\_SERVER\_PORT);                                                   |
|                                                                          |
| SystemAddress sa;\                                                       |
| sa = tcp-&gt;HasCompletedConnectionAttempt();\                           |
| for (packet = tcp-&gt;Receive(); packet;                                 |
| tcp-&gt;DeallocatePacket(packet), packet = tcp-&gt;Receive())\           |
| ;\                                                                       |
| sa = tcp-&gt;HasFailedConnectionAttempt();\                              |
| sa = tcp-&gt;HasLostConnection();\                                       |
| RakString stringTransmitted;\                                            |
| RakString hostTransmitted;\                                              |
| RakString responseReceived;\                                             |
| SystemAddress hostReceived;\                                             |
| int contentOffset;\                                                      |
| if (httpConnection2-&gt;GetResponse(stringTransmitted, hostTransmitted,  |
| responseReceived, hostReceived, contentOffset))\                         |
| {\                                                                       |
| // Parse JSON results here\                                              |
| }                                                                        |
|                                                                          |
| Example code:\                                                           |
| See Samples\\ComprehensivePCGame\\ComprehensivePCGame.cpp                |
|                                                                          |
| In ComprehensivePCGame.cpp, I use jansson included at                    |
| DependentExtensions\\jansson-2.4 to parse the json returned from the     |
| master server.                                                           |
|                                                                          |
| If tcp-&gt;HasFailedConnectionAttempt() returns something other than     |
| UNASSIGNED\_SYSTEM\_ADDRESS, then masterserver2.raknet.com is offline.   |
|                                                                          |
| **Step 5B: Joining - Connect to the session host**                       |
|                                                                          |
| The results from the master server will include a field \_\_addr (the ip |
| address that uploaded the row) and if you follow what I do in step 6,    |
| the RakNetGuid of that system in \_\_rowId. It may also include a field  |
| 'routerIsOpen' if you did that in step 6.                                |
|                                                                          |
| If 'routerIsOpen' is there and the value is non-zero, then you can just  |
| use rakPeer-&gt;Connect(...) to connect the host directly because either |
| UPNP succeeded, they already have a forwarding entry for your game, or   |
| they do not have a router.                                               |
|                                                                          |
| If 'routerIsOpen' is zero, then it is required that you previously       |
| connected to the NAT punchthrough server in step 1, and you use          |
| [NATPunchthroughClient](natpunchthrough.html) to connect.                |
|                                                                          |
| In ComprehensivePCGame.cpp this code starts NAT punchthrough to the      |
| host:\                                                                   |
| <span class="RakNetCode">if (clientGUID!=rakPeer-&gt;GetMyGUID())\       |
| natPunchthroughClient-&gt;OpenNAT(clientGUID,                            |
| game-&gt;natPunchServerAddress);</span>                                  |
|                                                                          |
| NAT punchthrough, if it succeeds, will return                            |
| ID\_NAT\_PUNCHTHROUGH\_SUCCEEDED. In this case, call                     |
| rakPeer-&gt;Connect(...) to actually connect to the host, and wait for   |
| ID\_CONNECTION\_REQUEST\_ACCEPTED, or a failure message                  |
| (ID\_NO\_FREE\_INCOMING\_CONNECTION, ID\_CONNECTION\_ATTEMPT\_FAILED).   |
|                                                                          |
| NAT punchthrough, if it fails, wll return                                |
| ID\_NAT\_TARGET\_NOT\_CONNECTED, ID\_NAT\_TARGET\_UNRESPONSIVE,          |
| ID\_NAT\_CONNECTION\_TO\_TARGET\_LOST, ID\_NAT\_ALREADY\_IN\_PROGRESS,   |
| or ID\_NAT\_PUNCHTHROUGH\_FAILED. Upon failure, remove this server from  |
| the list of servers returned to the user and display an appropriate      |
| error message.                                                           |
|                                                                          |
| **Step 5C: Joining - Connect as a fully connected mesh**                 |
|                                                                          |
| Provided that your game uses a fully connected mesh topology, then upon  |
| ID\_CONNECTION\_REQUEST\_ACCEPTED, you should try to connect to the      |
| peers in the session. FullyConnectedMesh2 has a feature 'verified joins' |
| to faciliate this. First, ask the host to join the game session using    |
| your own game logic. In ComprehensivePCGame I send                       |
| ID\_USER\_PACKET\_ENUM to do so. If the game is joinable at the time the |
| HOST should execute StartVerifiedJoin()                                  |
|                                                                          |
| case ID\_USER\_PACKET\_ENUM:\                                            |
| if (game-&gt;phase &gt; Game::SEARCH\_FOR\_GAMES)\                       |
| {\                                                                       |
| printf("Got request from client to join session.\\nExecuting             |
| StartVerifiedJoin()\\n");\                                               |
| fullyConnectedMesh2-&gt;StartVerifiedJoin(packet-&gt;guid);\             |
| }\                                                                       |
| else\                                                                    |
| {\                                                                       |
| BitStream bsOut;\                                                        |
| bsOut.Write((MessageID)(ID\_USER\_PACKET\_ENUM+1));\                     |
| rakPeer-&gt;Send(&bsOut,HIGH\_PRIORITY,RELIABLE\_ORDERED,0,packet-&gt;gu |
| id,false);\                                                              |
| }\                                                                       |
| break;                                                                   |
|                                                                          |
| StartVerifiedJoin() sends ID\_FCM2\_VERIFIED\_JOIN\_START to the client  |
| along with the list of participants using FullyConnectedMesh2. The       |
| CLIENT, upon getting this list, should perform NAT punchthrough and      |
| subsequently connect to each of these systems.                           |
|                                                                          |
| case ID\_FCM2\_VERIFIED\_JOIN\_START:\                                   |
| {\                                                                       |
| DataStructures::List&lt;SystemAddress&gt; addresses;\                    |
| DataStructures::List&lt;RakNetGUID&gt; guids;\                           |
| fullyConnectedMesh2-&gt;GetVerifiedJoinRequiredProcessingList(packet-&gt |
| ;guid,                                                                   |
| addresses, guids);\                                                      |
| for (unsigned int i=0; i &lt; guids.Size(); i++)\                        |
| natPunchthroughClient-&gt;OpenNAT(guids\[i\],                            |
| game-&gt;natPunchServerAddress);\                                        |
| }\                                                                       |
| break;\                                                                  |
| case ID\_NAT\_PUNCHTHROUGH\_SUCCEEDED:\                                  |
| {\                                                                       |
| rakPeer-&gt;Connect(packet-&gt;systemAddress.ToString(false),            |
| packet-&gt;systemAddress.GetPort(), 0, 0);\                              |
| }\                                                                       |
| break;                                                                   |
|                                                                          |
| FullyConnectedMesh2 will automatically handle details such as NAT        |
| punchthrough failing to some peers, new peers joining while NAT          |
| punchthrough is in progress, peers disconnecting, etc. If the client has |
| connected to all the peers existing in the session, the host will get    |
| ID\_FCM2\_VERIFIED\_JOIN\_CAPABLE. According to your game logic, you may |
| at this point accept or reject the potential new player:                 |
|                                                                          |
| if (game-&gt;lockGame)\                                                  |
| {\                                                                       |
| RakNet::BitStream bsOut;\                                                |
| bsOut.Write("Game is locked");\                                          |
| fullyConnectedMesh2-&gt;RespondOnVerifiedJoinCapable(packet, false,      |
| &bsOut);\                                                                |
| }\                                                                       |
| else\                                                                    |
| {\                                                                       |
| fullyConnectedMesh2-&gt;RespondOnVerifiedJoinCapable(packet, true, 0);\  |
| }                                                                        |
|                                                                          |
| The CLIENT will get ID\_FCM2\_VERIFIED\_JOIN\_ACCEPTED or                |
| ID\_FCM2\_VERIFIED\_JOIN\_REJECTED based on the 2nd parameter to         |
| RespondOnVerifiedJoinCapable() that the HOST executed. If you get        |
| ID\_FCM2\_VERIFIED\_JOIN\_ACCEPTED, you can consider yourself in the     |
| game session - already connected to all other peers in the session.      |
|                                                                          |
| The CLIENT may also get ID\_FCM2\_VERIFIED\_JOIN\_FAILED. This means     |
| that either NAT punchthrough or the connection attempt failed to one of  |
| the systems in the group. In this case, you cannot join this session as  |
| a fully connected mesh.                                                  |
|                                                                          |
| If you do not need a fully-connected mesh, but can play with a partial   |
| mesh, you may wish to derive from                                        |
| FullyConnectedMesh2::OnVerifiedJoinFailed() to not call                  |
| CloseConnection() if it was called due to                                |
| ID\_FCM2\_VERIFIED\_JOIN\_FAILED, and still treat                        |
| ID\_FCM2\_VERIFIED\_JOIN\_FAILED as join success in your game logic.     |
|                                                                          |
| **Step 6: Creating - Post to Master Server 2**                           |
|                                                                          |
| New game sessions should be posted to [Master Server                     |
| 2](masterserver2.raknet.com). In the following code I post the name of   |
| the game, how long until the row times out, my RakPeer GUID, and whether |
| or not my router is open to incoming connections (optional).             |
|                                                                          |
| \#define MASTER\_SERVER\_ADDRESS "masterserver2.raknet.com"\             |
| \#define MASTER\_SERVER\_PORT 80                                         |
|                                                                          |
| int routerIsOpen = natType == NAT\_TYPE\_NONE || upnpSucceeded;          |
|                                                                          |
| tcp = TCPInterface::GetInstance();\                                      |
| tcp-&gt;AttachPlugin(httpConnection2);\                                  |
| tcp-&gt;Start(0,0,1);\                                                   |
| RakString rsRequest = RakString::FormatForPOST(\                         |
| (const char\*) MASTER\_SERVER\_ADDRESS "/testServer",\                   |
| "text/plain; charset=UTF-8",\                                            |
| RakString("{'\_\_gameId': myGameId, '\_\_clientReqId': '0',              |
| '\_\_timeoutSec': '30', '\_\_rowId': %I64u, 'routerIsOpen': %i }",       |
| rakPeer-&gt;GetMyGUID().g, routerIsOpen );                               |
|                                                                          |
| // POST the room again slightly less than every 30 seconds\              |
| game-&gt;whenToNextUpdateMasterServer = RakNet::GetTime() + 30000 -      |
| 1000;                                                                    |
|                                                                          |
| <span class="RakNetCode"> httpConnection2-&gt;TransmitRequest(rsRequest, |
| MASTER\_SERVER\_ADDRESS, MASTER\_SERVER\_PORT);</span>                   |
|                                                                          |
| **Step 7: Update Master Server 2 while the session is joinable**         |
|                                                                          |
| One of the systems in the game session must be responsible for updating  |
| Master Server 2. Otherwise, the session will be delisted since master    |
| server 2 will assume that system crashed with no further updates. If you |
| use FullyConnectedMesh2, then the current host can do this every n       |
| seconds, based on \_\_timeoutSec.                                        |
|                                                                          |
| // This system has become host\                                          |
| case ID\_FCM2\_NEW\_HOST:\                                               |
| {\                                                                       |
| RakNet::BitStream bs(packet-&gt;data,packet-&gt;length,false);\          |
| bs.IgnoreBytes(1);\                                                      |
| RakNetGUID oldHost;\                                                     |
| bs.Read(oldHost);\                                                       |
| if (packet-&gt;guid==rakPeer-&gt;GetMyGUID() &&                          |
| oldHost!=UNASSIGNED\_RAKNET\_GUID)\                                      |
| PostRoomToMaster();\                                                     |
| }                                                                        |
|                                                                          |
| // Time has elasped while the game is joinable\                          |
| RakNet::Time t = RakNet::GetTime();\                                     |
| if (((fullyConnectedMesh2-&gt;IsConnectedHost() ||                       |
| game-&gt;users.Size()==1) &&\                                            |
| t &gt; game-&gt;whenToNextUpdateMasterServer) &&\                        |
| game-&gt;phase == Game::IN\_LOBBY\_WITH\_HOST ||\                        |
| game-&gt;phase == Game::IN\_GAME\                                        |
| )\                                                                       |
| {\                                                                       |
| PostRoomToMaster();\                                                     |
| }                                                                        |
|                                                                          |
| Updating a room is identical to posting a new room (step 6).             |
|                                                                          |
| **Step 8: Delist the game if and when the session is no longer           |
| joinable**                                                               |
|                                                                          |
| If at some point in your game new players are not accepted, you can      |
| delist the game from Master Server 2. This will also happen automaticaly |
| if you just stop updating.                                               |
|                                                                          |
| RakString rsRequest = RakString::FormatForDELETE(\                       |
| RakString(MASTER\_SERVER\_ADDRESS                                        |
| "/testServer?\_\_gameId=myGameId&\_\_rowId=%I64u",                       |
| rakPeer-&gt;GetMyGUID().g));\                                            |
| httpConnection2-&gt;TransmitRequest(rsRequest, MASTER\_SERVER\_ADDRESS,  |
| MASTER\_SERVER\_PORT);                                                   |
|                                                                          |
| You may also disconnect from the NAT PunchthroughServer at this time,    |
| provided you reconnect when you need it again. It will save bandwidth if |
| you do this.                                                             |
|                                                                          |
| **Step 9 (Optional): Router2 or UDPProxyClient as a backup**             |
|                                                                          |
| For players that failed NATPunchthrough, you can route their connections |
| through players that did not fail, using the [Router2](router.html)      |
| plugin. You can also use the [UDPProxyClient](natpunchthrough.html)      |
| while you are running your own UDPProxyServer to forward those           |
| connections through a server.                                            |
|                                                                          |
| Router2 will return ID\_ROUTER\_2\_FORWARDING\_NO\_PATH if forwarding is |
| not possible and ID\_ROUTER\_2\_FORWARDING\_ESTABLISHED on success.      |
|                                                                          |
| UDPPRoxyClient will return ID\_UDP\_PROXY\_GENERAL. Byte 1 indicates the |
| return value. Success is returned on                                     |
| ID\_UDP\_PROXY\_FORWARDING\_SUCCEEDED. The remote system will get        |
| ID\_UDP\_PROXY\_FORWARDING\_NOTIFICATION on success. Anything else means |
| failure.                                                                 |
|                                                                          |
| If these solutions fail, or you do not use them, then it is not possible |
| to complete a peer to peer gaming session. Leave the game session on the |
| server. You should show a dialog box to the user that they need to       |
| manually open ports on their router before they can play. Or you can     |
| just try a different session.                                            |
|                                                                          |
| See the sample *\\Samples\\NATCompleteClient* for Router2 and            |
| UDPProxyClient**                                                         |
+--------------------------------------------------------------------------+

  -----------------
  The simpler way
  -----------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Just UPNP and                             |
| NatPunchthroughClient</span>                                             |
|                                                                          |
| UPNP enabled routers are common these days. Therefore, this simpler      |
| solution will work in nearly all cases, and is recommended unless you    |
| are writing a back-end service with multiple fallbacks.                  |
|                                                                          |
| 1.  Connect to a hosting server running NATPunchthroughServer. For       |
|     example, [our free                                                   |
|     server](http://www.jenkinssoftware.com/forum/index.php?topic=5006.0) |
| .                                                                        |
| 2.  Call the OpenUPNP() function in step 3 above. It doesn't matter if   |
|     the function succeeds or not, because you do the next                |
|     steps regardless.                                                    |
| 3.  When you find which game server you want to connect to, call <span   |
|     class="RakNetCode">natPunchthroughClient-&gt;OpenNAT(gameServerGuid, |
|     masterServerAddress);</span>                                         |
| 4.  If you get ID\_NAT\_PUNCHTHROUGH\_SUCCEEDED, connect to that server. |
|     For a client/server game, you are done.                              |
| 5.  For a peer to peer game, you will also need to connect to the other  |
|     peers after connecting to the server. Using the plugin               |
|     FullyConnectedMesh2, call                                            |
|     fullyConnectedMesh2-&gt;StartVerifiedJoin(gameServerGuid);           |
| 6.  As described in the documentation                                    |
|     for FullyConnectedMesh2::StartVerifiedJoin,() you will get           |
|     ID\_FCM2\_VERIFIED\_JOIN\_START which contains a list of all peers   |
|     in the session. Call NatPunchthroughClient::OpenNAT() on each of     |
|     those peers, and connect on success, similar to step 3.              |
|     FullyConnectedMesh2 internally tracks which systems failed or        |
|     passed, and you will get ID\_FCM2\_VERIFIED\_JOIN\_ACCEPTED once     |
|     negotation has completed.                                            |
|                                                                          |
| See the sample *\\Samples\\ComprehensivePCGame*                          |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [MiniUPnP](http://miniupnp.free.fr/)\                                    |
| [NAT punchthrough](natpunchthrough.html)\                                |
| [NAT type detection](nattypedetection.html)\                             |
| [Router2](router.html)\                                                  |
+--------------------------------------------------------------------------+


