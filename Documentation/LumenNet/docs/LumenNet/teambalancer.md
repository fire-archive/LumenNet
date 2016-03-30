<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}TeamBalancer Overview
  ------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Request and balance teams client/server   |
| or peer to peer</span>                                                   |
|                                                                          |
| **DEPRECATED: See [TeamManager](teammanager.html)**                      |
|                                                                          |
| The TeamBalancer plugin is used to assign each player in a game session  |
| a team number. Players by default have no team, and join teams by        |
| calling *RequestSpecificTeam()* or *RequestAnyTeam()*                    |
|                                                                          |
| Operations include:                                                      |
|                                                                          |
| -   **SetTeamSizeLimits()** - Define the maximum number of players that  |
|     can join a given team number                                         |
| -   **SetDefaultAssignmentAlgorithm()** - Define how to automatically    |
|     add new players to team - either filling teams in order, or joining  |
|     the smallest team. This is triggered by a call to *RequestAnyTeam()* |
| -   **SetForceEvenTeams()** - Cause all teams to be evenly balanced.     |
|     Teams with too many players will have players randomly moved to      |
|     teams with too few players.                                          |
| -   **RequestSpecificTeam()** - Change to a requested team. If this team |
|     is full, your join will be pending, until either that team is not    |
|     full, or a player on the desired team wants to switch with           |
|     your team.                                                           |
| -   **CancelRequestSpecificTeam()** - If *RequestSpecificTeam()* has not |
|     yet completed, this will remove that request.                        |
| -   **RequestAnyTeam()** - Join a team randomly, based on the default    |
|     team assignment algorithm.                                           |
| -   **GetMyTeam()** - Return which team I am on, if any.                 |
| -   **SetAllowHostMigration()** - Call with true for peer to peer,       |
|     otherwise call with false.                                           |
|                                                                          |
| See the header file TeamBalancer.h for more information and complete     |
| documentation of each parameter and function, as well as messages        |
| returned to the user.                                                    |
|                                                                          |
| *See the sample project Samples\\TeamBalancer for an implementation of   |
| this system.*                                                            |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  -----------------------------------------
  [Index](index.html)\
  [PluginInterface](plugininterface.html)
  -----------------------------------------

[TeamManager](teammanager.html)
