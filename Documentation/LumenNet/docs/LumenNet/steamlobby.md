<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Lobby2Client\_Steam Overview
  -------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Use Steamworks to join Lobbies, Rooms,    |
| and do NAT traversal</span>                                              |
|                                                                          |
| The Lobby2Client\_Steam plugin provides an interface to Steamworks       |
| services that cooperate with RakNet. This avoids the need to host your   |
| owns sever, which is otherwise required by RakNet's                      |
| [NATPunchthrough](natpunchthrough.html) and [Lobby](lobby.html) systems. |
|                                                                          |
| Dependencies:                                                            |
|                                                                          |
| 1.  Assumes the Steam SDK is located at C:\\Steamworks . If not, modify  |
|     the post-build step paths and linker paths accordingly.              |
| 2.  You can get the Steamworks API from https://partner.steamgames.com/  |
|     , which requires a signup and legal agreement.                       |
| 3.  You need your own steam\_appid.txt file. This sample just copies the |
|     one that comes with steam.                                           |
|                                                                          |
| Operations include:                                                      |
|                                                                          |
| -   **Get the list of rooms** - L2MID\_Console\_SearchRooms              |
| -   **Leave a room** - L2MID\_Console\_LeaveRoom                         |
| -   **Create a room** - L2MID\_Console\_CreateRoom                       |
| -   **Join a room** - L2MID\_Console\_JoinRoom                           |
| -   **Get details about a specific room** -                              |
|     L2MID\_Console\_GetRoomDetails                                       |
| -   **Send a chat message to a room** -                                  |
|     L2MID\_Console\_SendRoomChatMessage                                  |
| -   **Get the members in a room**- Lobby2Client\_Steam::GetRoomMembers   |
| -   **Get notification of NAT Traversal success** -                      |
|     SteamResults::Notification\_Console\_RoomMemberConnectivityUpdate    |
|                                                                          |
| *See the sample project Samples\\SteamLobby for an implementation of     |
| this system.*                                                            |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [Lobby](lobby.html)\                                                     |
| [NATPunchthrough](natpunchthrough.html)\                                 |
| [PluginInterface](plugininterface.html)                                  |
+--------------------------------------------------------------------------+


