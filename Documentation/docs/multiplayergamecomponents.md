![Oculus VR, Inc.](RakNet_Icon_Final-copy.jpg){width="150"
height="150"}\
\
  -----------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Components of a multiplayer game
  -----------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Major systems that go into the making of  |
| a multiplayer game</span>\                                               |
| \                                                                        |
| In the early days of gaming all you had was an IP address and a          |
| download. These days you have integration into 3rd party systems such as |
| Steam, patching, voice chat, multiple game modes, cross-platform play,   |
| and more. I list some major systems by category below, along with the    |
| options available for solving these problems and pros and cons of each   |
| system. This page applies to any multiplayer game, not just those using  |
| RakNet, although RakNet specific solutions are listed at the end of each |
| section.                                                                 |
+--------------------------------------------------------------------------+

  ---------------------------
  Discovering other systems
  ---------------------------

+--------------------------------------------------------------------------+
| Direct IP entry                                                          |
|                                                                          |
| The oldest and simplest method, this involves typing in the IP address   |
| of the user you want to connect to. The remote user can go to a page     |
| such as <http://www.whatismyip.com/> to get their IP. They can then      |
| communicate this IP to you through other communication channels such as  |
| email or instant messenger. If the remote user is behind a router, they  |
| will have to open the appropriate ports on the firewall to accept        |
| incoming connections. If they are behind a firewall, they will have to   |
| configure the firewall as well.                                          |
|                                                                          |
| DNS entry                                                                |
|                                                                          |
| Applicable to client/server games where you control the servers, you can |
| have a DNS entry point to the server. Connecting clients can then        |
| connect to the DNS entry rather than typing in a fixed IP address. This  |
| is useful if the IP address of the server may change. This service is    |
| available for free through <http://www.dyndns.com/>. RakNet provides a   |
| class to update DynDNS as well, found in Source/DynDNS.h and             |
| Source/DynDNS.cpp. This is usually used for client/server games where    |
| you host your own server.                                                |
|                                                                          |
| <span class="RakNetBlueHeader">LAN Broadcast</span>                      |
|                                                                          |
| If the remote computer is on the same LAN, you can discover this         |
| computer by sending a datagram to the IP address 255.255.255.255         |
| provided that the remote computer is listening on the port you send on,  |
| and will send a datagram in response. RakNet provides this through the   |
| Ping() and AdvertiseSystem() functions.                                  |
|                                                                          |
| Lobby server                                                             |
|                                                                          |
| Consoles such as the XBOX 360 and the PS3, and services such as Steam on |
| the PC offer a lobby system. The lobby system also typically provides    |
| services such as DLC, achievements, friends, and rooms. RakNet provides  |
| the SteamLobby plugin, and rough equivalents on the XBOX and PS3 with    |
| their respective lobby classes. This is usually used for peer-to-peer    |
| games, where players have some significant interaction between each      |
| other before the game starts.                                            |
|                                                                          |
| Master server                                                            |
|                                                                          |
| Similar to the rooms server, a server maintains a list of running games. |
| Typically, when an end-user starts a game, they upload statistics about  |
| the game to a master server, which allows queries on uploaded games. We  |
| offer this service for free at with our [hosted master                   |
| server](masterserver2.html).                                             |
+--------------------------------------------------------------------------+

  ----------------------------------------------------------
  <span class="RakNetWhiteHeader"> Network topology</span>
  ----------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Client/Server where you host the servers  |
| </span>\                                                                 |
| \                                                                        |
| Usually used for massively multiplayer games, you will host one or more  |
| servers that contain the game world(s) provided to the players.This is   |
| also the most expensive solution since you have to have dedicated        |
| servers with guaranteed uptime and pay for bandwidth yourself.           |
|                                                                          |
| <span class="RakNetBlueHeader">Client/Server where users host the        |
| servers</span>\                                                          |
| \                                                                        |
| This is used for games where if the server drops, so does the entire     |
| game session. It is nonetheless common because it has the following      |
| advantages:                                                              |
|                                                                          |
| 1.  Easier to program because a single system can resolve contention     |
|     between clients                                                      |
| 2.  Can support a large number of players, because dedicated servers     |
|     with a high bandwidth capacity can host                              |
| 3.  Better for long-term gameplay sessions because a dedicated server is |
|     less likely to drop or cause problems                                |
| 4.  Dedicated servers can be spread throughout the world, resulting in   |
|     low-ping sessions                                                    |
|                                                                          |
| It is also possible to program client/server using an end-user as a      |
| host, but then you get all of the disadvantages of client/server without |
| none of the advantages except ease of programming.                       |
| <span class="RakNetBlueHeader">Peer to peer</span>\                      |
| \                                                                        |
| This is used for more informal game sessions without dedicated servers.  |
| It is the most common topology for console games since consoles do not   |
| allow dedicated servers. The only advantage is a dedicated host is not   |
| necessary. The disadvantages are:                                        |
|                                                                          |
| 1.  Still need a server of some sort to find running game sessions       |
| 2.  Have to punch through routers                                        |
| 3.  Have to deal with host migration                                     |
| 4.  Have to deal with contention. If two peers do the same mutually      |
|     exclusive operation at the same time, how to resolve?                |
|                                                                          |
| RakNet provides plugins to make peer to peer programming easier:         |
| [NATPunchthrough](natpunchthrough.html), [ReadyEvent](readyevent.html),  |
| [ConnectionGraph2](connectiongraph.html),                                |
| [FullyConnectedMesh2](fullyconnectedmesh2.html), and                     |
| [TeamBalancer](teambalancer.html). See the project ComprehensivePCGame   |
| in the RakNet solution for an example where all these plugins are        |
| combined together.\                                                      |
+--------------------------------------------------------------------------+

  -------------------------------------------------------------------------------------
  <span class="RakNetWhiteHeader"> Game and game design changes for networking</span>
  -------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Level loading</span>\                     |
| \                                                                        |
| Rather than loading all objects in the level as done in single player,   |
| objects now need to be categorized according to how they influence       |
| networking\                                                              |
|                                                                          |
| 1.  Objects that still load normally are those that always exist in the  |
|     level and are not referenced by network code.                        |
| 2.  Objects may still load normally with the level, but need to be       |
|     referred to by network code. For example, event triggers. These      |
|     objects can either be loaded with a NetworkID (64 bit GUID), or the  |
|     code at load time can gather these types of objects and assign       |
|     them ids.                                                            |
| 3.  Objects may or may not exist on level load need to be                |
|     dynamically loaded. For example, such as players, spawned weapons,   |
|     and bullets. Some of these objects should be preloaded during level  |
|     load, on the assumption that they will eventually be spawned, to     |
|     avoid runtime harddrive access.                                      |
|                                                                          |
| Generally, after level load the game does not start until all players    |
| have finished loading. Even on consoles, the disk may be scratched so    |
| systems may take a different amount of time to load a level. Before      |
| considering level load complete:\                                        |
| 1.  Transmit selections from other users that affect our load state. For |
|     example, what character models the other users picked                |
| 2.  Load the level as well as whatever models / textures, etc. are       |
|     needed based on the other player's choices                           |
| 3.  Stay on an intermission screen until all other players are also      |
|     done loading. [ReadyEvent](readyevent.html) can be used for this     |
|                                                                          |
| Midgame joins are the same, except that you skip the intermission        |
| screen. However, if the game session ends while you are still loading,   |
| you should be able to cancel the load and enter whatever intermission    |
| state is shown at game end.\                                             |
| <span class="RakNetBlueHeader">Game Objects</span>\                      |
| \                                                                        |
| Objects that are networkable need to implement an interface to support   |
| [ReplicaManager3](replicamanager3.html):                                 |
|                                                                          |
| 1.  Objects must be able to return an identifier for what type of class  |
|     the object is, for example ENUM\_BULLET or "CBullet" for a bullet.   |
| 2.  Object must be instantiable given that identifier and                |
|     initialization data. Sometimes this is done through a class factory. |
| 3.  Objects should implement an interface allowing them to serialize     |
|     data for construction, destruction, and per-tick serialization       |
| 4.  Objects that are deleted when the owning user leaves the game        |
|     session should support deletion. For example, if a remote user's     |
|     avatar is deleted, this should not end the game session locally.     |
|                                                                          |
| Game objects owned by the host or other users may need to support a      |
| partial-interactive ghost state where the object is rendered and         |
| animated but has typically has physics disabled and does not start       |
| triggers. However:\                                                      |
| 1.  Partial-interactive ghost objects may still cause sounds, such as    |
|     footsteps on glass                                                   |
| 2.  Partial-interactive ghost objects may still cause visual effect      |
|     triggers                                                             |
|                                                                          |
| Whether an object is in an fully interactive state depends on whether a  |
| unique host is needed to resolve conflicts. Objects in the game world    |
| need to be categorized correspondingly based on bandwidth and gameplay   |
| considerations:\                                                         |
| 1.  Object is only fully interactive on the host, for example triggers   |
|     that affect gameplay in some way.                                    |
| 2.  Object is fully interactive on all systems, for example a trigger    |
|     that plays a particle effect                                         |
| 3.  Object is only fully interactive on the system that owns it, for     |
|     example your own avatar.                                             |
|                                                                          |
| <span class="RakNetBlueHeader">Host Migration</span>\                    |
| \                                                                        |
| Host migration is needed for peer to peer games, where one system is     |
| host. While some platforms offer a system for host migration, we have a  |
| cross-platform solution [FullyConnectedMesh2](fullyconnectedmesh2.html)  |
|                                                                          |
| <span class="RakNetBlueHeader">Users</span>\                             |
| \                                                                        |
| In-game, a user class needs to be implemented, containing information    |
| such as score, name, user id, achievements, etc. Some games may support  |
| multiple users on the same system, for example split-screen play         |
|                                                                          |
| <span class="RakNetBlueHeader">Remote Systems</span>\                    |
| \                                                                        |
| A Remote system class may need to be implemented, containing information |
| such as level load state or a trust metric for cheat detection. If the   |
| game only supports one user per system, this is sometimes rolled into    |
| the User class.\                                                         |
| \                                                                        |
| <span class="RakNetBlueHeader">Teams</span>\                             |
| \                                                                        |
| If the game supports teams, this needs to be serialized including        |
| players, team score, etc. Team management is supported with the          |
| [TeamManager](teammanager.html) plugin. It supports any network          |
| topology, offline teams, and advanced features such as switching         |
| requested teams.\                                                        |
| \                                                                        |
| <span class="RakNetBlueHeader">World / Game State</span>\                |
| \                                                                        |
| Not all game information is necessarily held by game objects, for        |
| example the match countdown. It can be represented using Replica3 as     |
| usual, or can be updated directly through network messages.\             |
|                                                                          |
| <span class="RakNetBlueHeader">Level End</span>\                         |
| \                                                                        |
| When the host determines level end, the game needs to support the        |
| ability to pause gameplay, despawn all players, and show some kind of    |
| end-game score screen. During this phase score updates should be paused  |
| and other game events should halt. If sesssion statistics are            |
| transmitted to a server, it can be done at this time.\                   |
|                                                                          |
| <span class="RakNetBlueHeader">Spectating / Replay</span>\               |
| \                                                                        |
| Some games allow you to watch gameplay from the point of view of fixed   |
| cameras, other players, or a replay cam after death.\                    |
|                                                                          |
| <span class="RakNetBlueHeader">Post-Game statistics and UI</span>\       |
| \                                                                        |
| After a game session, sometimes a series of UI screens are shown after   |
| the level has unloaded. After that, the game state may either go back to |
| the game browser screen, or stay in a room with the users you just       |
| played with.                                                             |
+--------------------------------------------------------------------------+

  --------------------------------------------------
  <span class="RakNetWhiteHeader"> Patching</span>
  --------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Per-file difference based patching        |
| </span>\                                                                 |
| \                                                                        |
| The most advanced but time consuming way to patch users is to find the   |
| difference between a file the user has and the current version of that   |
| file. Under those circumstances the smallest delta can be sent and       |
| applied to the file. If the patch fails (for example, an unknown version |
| of the file) the entire file will need to be transmitted. A database of  |
| patches will need to be maintained for this solution, as generating the  |
| patch at runtime is too time consuming.                                  |
|                                                                          |
| RakNet provides the [AutopatcherServer and AutopatcherClient             |
| plugins](autopatcher.html) as a diff based patching system.              |
|                                                                          |
| <span class="RakNetBlueHeader">Per-file patching</span>\                 |
| \                                                                        |
| A simpler way to patch is to find a list of changed or missing files for |
| a client and to send only those files. One advantage of this system is   |
| that it can be used by end-user hosted game servers. For example, if a   |
| game server has a map or skins that a connecting client does not, those  |
| files can be downloaded before the game starts.                          |
|                                                                          |
| RakNet provides the [FileListTransfer](filelisttransfer.html) plugin to  |
| transfer lists of files, and the                                         |
| [DirectoryDeltaTransfer](directorydeltatransfer.html) plugin to transfer |
| lists of changed or missing files.                                       |
|                                                                          |
| \                                                                        |
+--------------------------------------------------------------------------+

  ---------------------------------------------------
  <span class="RakNetWhiteHeader"> Debugging</span>
  ---------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Logging</span>\                           |
| \                                                                        |
| Multiplayer games are hard to debug because a bug can be spread between  |
| two systems. For example, system A performs an action but system B does  |
| not see it, or sees it differently. The bug may be caused by latency,    |
| showing up only at certain loads. Performance or other issues may come   |
| up as the application scales with more users. While logging can help     |
| with all these problems, they are hard to correlate because the system   |
| times are different.                                                     |
|                                                                          |
| RakNet provides two logging solutions. The first is called               |
| [SQLite3LoggerPlugin](sqlite3loggerplugin.html), and is based on SQLite3 |
| on a hosted server. All logs go to the same server, and are              |
| automatically correlated. The logs can be viewed in viewer that supports |
| SQLite although RakNet also provides a free and open source custom       |
| viewer called [EchoChamber](http://www.raknet.net/echochamber).          |
| Individual game and connectivity messages can be logged per system using |
| the [PacketLogger](packetlogger.html) plugin.                            |
|                                                                          |
| <span class="RakNetBlueHeader">Minidump</span>\                          |
| \                                                                        |
| Because crashes can be hard to reproduce, Windows applications can       |
| produce                                                                  |
| [minidump](http://msdn.microsoft.com/en-us/library/ms680369%28v=vs.85%29 |
| .aspx)                                                                   |
| files. If you know what version of the code produced the crash, you can  |
| debug the crash as if you had a debugger connected at the time.          |
|                                                                          |
| RakNet provides the [CrashReporter](crashreporter.html) system to make   |
| this easier. It provides additional functionality such as sending emails |
| to the developer in the case of unattended servers.                      |
|                                                                          |
| \                                                                        |
+--------------------------------------------------------------------------+

  ---------------------------------------------------------
  <span class="RakNetWhiteHeader"> Persistent data</span>
  ---------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Persistent user data </span>\             |
| \                                                                        |
| Games that persist data beyond a single session require a system to      |
| create user accounts. User accounts can store data such as game          |
| statistics, name, and logo. Users can also have friends, form clans, and |
| perform other social tasks. In order to write such a system, a database  |
| backend is needed with a persistent sever to store this data. The users  |
| should not be able to send arbitrary queries to the database, so the     |
| server will need code to form queries based on user inputs.              |
|                                                                          |
| RakNet provides a system called [LobbyServer and                         |
| LobbyClient](lobby.html) to provide this kind of functionality for the   |
| PC. Steam, the PS3, and the XBOX already store this on their own         |
| backend. For those cases, RakNet uses the same [LobbyClient](lobby.html) |
| interface so as to provide a unified interface to all systems.           |
|                                                                          |
| \                                                                        |
+--------------------------------------------------------------------------+

  --------------------------------------------------
  <span class="RakNetWhiteHeader"> Security</span>
  --------------------------------------------------

+--------------------------------------------------------------------------+
| \                                                                        |
| Popular competitive games will draw cheaters. Cheaters can attack the    |
| application by                                                           |
|                                                                          |
| 1.  Modifying the EXE to send unauthorized data (sending kill messages)  |
| 2.  Modifying the EXE to view extra data (seeing through walls)          |
| 3.  Modifying datagrams in transmit to change data sent                  |
| 4.  Replaying datagrams to simulate login or game events (running bots)  |
| 5.  Introducing latency to get a competitive advantage                   |
|                                                                          |
| The game should verify all inputs for sanity when possible. This will    |
| need to be done even if cheating is not a concern, since latency will    |
| also cause unusual inputs.                                               |
|                                                                          |
| RakNet can automatically protect against attacks \#3 and \#4 with        |
| [secure connection](secureconnections.html) support. Solutions already   |
| exist for protecting the EXE from modification on the PC. Protecting     |
| against latency based cheating just takes smart design decisions, such   |
| as not trusting client/peer inputs.                                      |
|                                                                          |
| \                                                                        |
+--------------------------------------------------------------------------+

  -----------
   See Also
  -----------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [Autopatcher](autopatcher.html)\                                         |
| [CrashReporter](crashreporter.html)\                                     |
| [ReplicaManager3](replicamanager3.html)\                                 |
| [FullyConnectedMesh2](fullyconnectedmesh2.html)\                         |
| [Master Server 2](http://masterserver2.raknet.com/)\                     |
| [NATPunchthrough](natpunchthrough.html)\                                 |
| [PacketLogger](packetlogger.html)\                                       |
| [RPC3](RPC3Video.htm)\                                                   |
| [TeamManager](teammanager.html)\                                         |
| [SQLite3LoggerPlugin](sqlite3loggerplugin.html)                          |
| [](packetlogger.html)\                                                   |
+--------------------------------------------------------------------------+


