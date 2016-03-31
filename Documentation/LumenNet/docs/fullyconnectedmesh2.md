<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  --------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Fully Connected 2 Mesh Plugin
  --------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Consistently join a fully connected mesh. |
| Automatically determine who is host.</span>                              |
|                                                                          |
| FullyConnectedMesh2 solves two problems with peer to peer games. First,  |
| how to connect to a list of systems maintained by the session host, with |
| correct behavior on a failed connection. Secondly, to determine and      |
| automatically migrate a session host. A session host is needed for       |
| authoritative behavior, for example the host may send out game end       |
| notifications or may control the AI.                                     |
|                                                                          |
| **Properly joining a fully connected mesh:**                             |
|                                                                          |
| 1.  All systems: Call SetConnectOnNewRemoteConnection(false, "");        |
| 2.  All systems: Call SetAutoparticipateConnections(false);              |
| 3.  Host: When a new system connects and is allowed to join,             |
|     call StartVerifiedJoin() to send ID\_FCM2\_VERIFIED\_JOIN\_START to  |
|     that system.                                                         |
| 4.  Client: On ID\_FCM2\_VERIFIED\_JOIN\_START,                          |
|     call fullyConnectedMesh2-&gt;GetVerifiedJoinRequiredProcessingList() |
|     to get a list of systems to connect to.                              |
| 5.  Client: Attempt to connect to each of the system returned            |
|     from GetVerifiedJoinRequiredProcessingList(). Use                    |
|     NATPunchthroughClient and/or UPNP as necessary. Once all connections |
|     have failed or succeeded, the host is informed automatically.        |
| 6.  Client: On ID\_FCM2\_VERIFIED\_JOIN\_FAILED, either you lost         |
|     connection to the host, or the host required you to connect to a     |
|     participant you were not able to. Inform the player via the UI.      |
| 7.  Host: On ID\_FCM2\_VERIFIED\_JOIN\_CAPABLE,                          |
|     call RespondOnVerifiedJoinCapable() to accept or reject the join     |
|     based on game logic.                                                 |
| 8.  Client: On ID\_FCM2\_VERIFIED\_JOIN\_REJECTED, the host rejected the |
|     join for gameplay reasons. Disconnect from the host if the           |
|     connection is no longer needed.                                      |
|     Use GetVerifiedJoinRejectedAdditionalData() to determine why the     |
|     join was rejected, and inform the player via the UI.                 |
| 9.  Client: On ID\_FCM2\_VERIFIED\_JOIN\_ACCEPTED, the host accepted     |
|     the join. AddParticipant() has automatically been called on all      |
|     systems, and you have joined the mesh.                               |
|     Call GetVerifiedJoinAcceptedAdditionalData() if desired.             |
|                                                                          |
| StartVerifiedJoin() is of significant benefit when using                 |
| NatPunchthroughClient because if a connection fails, previously          |
| successful connections are closed automatically. Also, because           |
| NatPunchthroughClient takes a significant amount of time, a valid game   |
| session may no longer valid by the time it completes. However, even when |
| not using NatPunchthroughClient this system is useful because you may    |
| still not fully connect due to firewalls or because sessions are full.   |
| Ignoring this means you may only connect partially to the mesh,          |
| resulting in some players not able to see other players.                 |
| **Determining who is host of the fully connected mesh**                  |
|                                                                          |
| 1.  If NOT using StartVerifiedJoin(), call AddParticipant() on every     |
|     system, for every new connection. Note: this is done automatically   |
|     by default, and is controlled                                        |
|     by SetAutoparticipateConnections(true).                              |
| 2.  Use GetHostSystem() and IsHostSystem() to query who is the host      |
| 3.  Do not start gameplay until the host has been calculated. This is    |
|     known once you get ID\_FCM2\_NEW\_HOST at least once.                |
| 4.  Do host migration if necessary when you get ID\_FCM2\_NEW\_HOST      |
|     during gameplay                                                      |
|                                                                          |
| Host calculation starts automatically once one or more remote            |
| connections have been added with AddParticipant(). Until host            |
| calculation has completed, GetHostSystem() will return your own guid and |
| GetConnectedHost() will return UNASSIGNED\_RAKNET\_GUID. You will get    |
| ID\_FCM2\_NEW\_HOST as soon as the host is known. The host will          |
| generally be whichever system has been running the longest of all        |
| systems added with AddParticipant().                                     |
|                                                                          |
| GetParticipantList() and GetHostOrder() can be used to find out which    |
| systems were added with AddParticipant().                                |
|                                                                          |
| If the game does not immediately start networked, you should call        |
| ResetHostCalculation() to reinitialize the host timer when network play  |
| is now relevant. Otherwise, a user could play a game in single player,   |
| connect to a network session, and then be considered the host because    |
| his system was running the longest, although he was the last to join the |
| network session. A good time to call ResetHostCalculation() is just      |
| before attempting to join a network room or lobby.                       |
|                                                                          |
| **Reading ID\_FCM2\_NEW\_HOST:**                                         |
|                                                                          |
| ID\_FCM2\_NEW\_HOST has the RakNetGUID of the old host encoded in the    |
| network stream. The new host is written to the systemAddress and guid    |
| members of the Packet.                                                   |
|                                                                          |
|                                                                          |
|     case ID_FCM2_NEW_HOST:                                               |
|     {                                                                    |
|         if (packet->guid==rakPeer->GetMyGUID())                          |
|             printf("Got new host (ourselves)");                          |
|         else                                                             |
|             printf("Got new host %s, GUID=%s", packet->systemAddress.ToS |
| tring(true), packet->guid.ToString());                                   |
|         RakNet::BitStream bs(packet->data,packet->length,false);         |
|         bs.IgnoreBytes(1);                                               |
|         RakNetGUID oldHost;                                              |
|         bs.Read(oldHost);                                                |
|         if (oldHost==UNASSIGNED_RAKNET_GUID)                             |
|         {                                                                |
|             DataStructures::List participantList;                        |
|             fullyConnectedMesh2->GetParticipantList(participantList);    |
|             // First time ID_FCM2_NEW_HOST was returned. Host is now kno |
| wn - can start gameplay, and add all systems that were previously added  |
| with AddParticipant() as players                                         |
|             // ...                                                       |
|         }                                                                |
|         break;                                                           |
|                                                                          |
| See *Samples/FCMHost* for a demonstration of this plugin                 |
+--------------------------------------------------------------------------+
|                                                                          |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [PluginInterface](plugininterface.html)\                                 |
| [NAT-Punchthrough](natpunchthrough.html)\                                |
| [Ready Event](readyevent.html)\                                          |
+--------------------------------------------------------------------------+


