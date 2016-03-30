<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -----------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}TeamManager Overview
  -----------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Manages lists of teams and team members.  |
| Supports client/server and peer to peer</span>                           |
|                                                                          |
| TeamManager reduces the work involved with managing teams and team       |
| members. Functionality includes:                                         |
|                                                                          |
| -   Support for any number of teams with join conditions on each.        |
| -   Support for team members being on multiple teams at the same time,   |
|     or no team at all.                                                   |
| -   Support for independent worlds, enabling you to host multiple game   |
|     sessions simultaneously.                                             |
| -   The ability to lock, unlock, and resize teams.                       |
| -   Team requests for locked or full teams are buffered and filled in    |
|     first-come first-server order, including the ability to swap teams.  |
| -   The state of all teams and all team members are fully replicated to  |
|     all systems.                                                         |
| -   Flexible architecture, with support client/server,                   |
|     [ReplicaManager3](replicamanager3.html) and the use of either        |
|     composition or inheritance.                                          |
|                                                                          |
| Usage                                                                    |
|                                                                          |
| 1.  Define your game classes to represent teams and team members. Your   |
|     game classes should hold game-specific information such as team name |
|     and color.                                                           |
| 2.  Have those game classes contain a corresponding TM\_Team or          |
|     TM\_TeamMember instance. Operations on teams will be performed by    |
|     those instances. Use SetOwner() to refer to the parent object when   |
|     using composition.                                                   |
| 3.  Call TeamManager::SetTopology() for client/server or peer to peer.   |
| 4.  Call AddWorld() to instantiate a TM\_World object which will contain |
|     references to your TM\_TeamMember and TM\_Team instances.            |
| 5.  When you instantiate a TM\_TeamMember or TM\_Team object,            |
|     call ReferenceTeam() and ReferenceTeamMember() for each              |
|     corresponding object. If using ReplicaManager3, the Reference calls  |
|     should be at the top of DeserializeConstruction(), as well as when   |
|     creating the object locally.                                         |
| 6.  When sending world state to a new connection, for example in         |
|     ReplicaManager3::SerializeConstruction(),                            |
|     call TM\_SerializeConstruction() on the corresponding TM\_TeamMember |
|     and TM\_Team objects. TM\_Team instances on the new connection must  |
|     be created before TM\_TeamMember instances.                          |
| 7.  Call TM\_DeserializeConstruction() on your new corresponding         |
|     TM\_TeamMember and TM\_Team instances.                               |
| 8.  Execute team operations. ID\_TEAM\_BALANCER\_REQUESTED\_TEAM\_FULL,  |
|     ID\_TEAM\_BALANCER\_REQUESTED\_TEAM\_LOCKED,                         |
|     ID\_TEAM\_BALANCER\_TEAM\_REQUESTED\_CANCELLED, and                  |
|     ID\_TEAM\_BALANCER\_TEAM\_ASSIGNED are returned to all systems when  |
|     the corresponding event occurs for a team member.                    |
| 9.  As the peer to peer session host changes, call SetHost() (Not        |
|     necessary if using FullyConnectedMesh2). If using client/server, you |
|     must set the host                                                    |
| 10. DeserializeConstruction must be called on TM\_Team before            |
|     DeserializeConstruction is called on TM\_TeamMember that is a member |
|     of that team. If using ReplicaManager3, you can simply               |
|     call ReplicaManager3::Reference() on TM\_TeamMember later than       |
|     any ReplicaManager3::Reference() calls to TM\_Team                   |
|                                                                          |
| See the header file TeamManager.h for more information and complete      |
| documentation of each parameter and function, as well as messages        |
| returned to the user.                                                    |
|                                                                          |
| *See the sample project Samples\\TeamManager for an implementation of    |
| this system.*                                                            |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ------------------------------------------
  [Index](index.html)\
  [PluginInterface](plugininterface.html)\
  [ReplicaManager3](replicamanager3.html)\
  [TeamManager](teammanager.html)
  ------------------------------------------


