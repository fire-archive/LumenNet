<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ---------------
   Lobby Server
  ---------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Datbase support friends, rooms, emails,   |
| ranking, and more</span>\                                                |
| \                                                                        |
| The lobby server is a plugin that provides                               |
| [PostgreSQL](http://www.postgresql.org/) database driven functionality   |
| for persistent game data and matchmaking. The lobby server itself does   |
| not require significant user interaction - instead, commands are carried |
| out on via the LobbyClient\_PC class.                                    |
|                                                                          |
| The Lobby Server is split into two classes. **LobbyServer** itself       |
| solely provides networking functionality, calling interfaces to a        |
| generic database via virtual functions.**LobbyServerPostgreSQL**, found  |
| at                                                                       |
| DependentExtensions\\Lobby\\LobbyServer\_PostgreSQL\\LobbyServer\_Postgr |
| eSQL.h                                                                   |
| is an implementation of **LobbyServer** that uses PostgreSQL to power    |
| the database.                                                            |
|                                                                          |
| The basic class has functions to connect to the database, and create and |
| destroy the basic required tables. The sample found at                   |
| Samples/LobbyServerTest/LobbyServerTest.cpp, in the project LobbyServer, |
| demonstrates this fairly clearly.                                        |
|                                                                          |
| One additional requirement is the use of the **Functor** class. A        |
| functor is a class in RakNet that implements a specific unit of          |
| functionality that is run asynchronously in a **FunctionThread**,        |
| another utility class that is part of RakNet. For the most part you      |
| don't have to care about this - however, there is one functor you do     |
| have to care about, which is the one to add new titles                   |
| (games/applications) to the database.                                    |
|                                                                          |
| How to do this is illustrated in the sample                              |
|                                                                          |
| /// This functor asynchronously adds a title to the database. Full       |
| sample in LobbyDB\_PostgreSQLTest\                                       |
| AddTitle\_PostgreSQLImpl \*functor = AddTitle\_PostgreSQLImpl::Alloc();\ |
| printf("Adds a title to the database\\n");\                              |
| printf("Enter title name: ");\                                           |
| gets(inputStr);\                                                         |
| if (inputStr\[0\]==0) strcpy(inputStr, "Hangman EXTREME!");\             |
| functor-&gt;titleName = inputStr;\                                       |
| printf("Enter title password (binary): ");\                              |
| gets(inputStr);\                                                         |
| if (inputStr\[0\]==0) strcpy(inputStr,                                   |
| "SECRET\_PER\_GAME\_LOGIN\_PW\_PREVIOUSLY\_SETUP\_ON\_THE\_DB");\        |
| functor-&gt;titlePassword = AddTitle\_PostgreSQLImpl::AllocBytes((int)   |
| strlen(inputStr));\                                                      |
| functor-&gt;titlePasswordLength = (int) strlen(inputStr);\               |
| memcpy(functor-&gt;titlePassword, inputStr,                              |
| functor-&gt;titlePasswordLength);\                                       |
| functor-&gt;allowClientAccountCreation=true;\                            |
| functor-&gt;lobbyIsGameIndependent=true;\                                |
| functor-&gt;defaultAllowUpdateHandle=true;\                              |
| functor-&gt;defaultAllowUpdateCCInfo=true;\                              |
| functor-&gt;defaultAllowUpdateAccountNumber=true;\                       |
| functor-&gt;defaultAllowUpdateAdminLevel=true;\                          |
| functor-&gt;defaultAllowUpdateAccountBalance=true;\                      |
| functor-&gt;defaultAllowClientsUploadActionHistory=true;\                |
| /// Puts this functor on the processing queue. It will process sometime  |
| later in a thread.\                                                      |
| /// See projects LobbyDB\_PostgreSQLTest,                                |
| TitleValidationDB\_PostgreSQLTest, RankingServerDBTest for a complete    |
| demo of these and other functors\                                        |
| lobbyServer.PushFunctor(functor);                                        |
|                                                                          |
| This adds a title to the database with various properties indicating     |
| what types of operations are allowed for this title. See the class       |
| declaration AddTitle\_Data in                                            |
| DependentExtensions\\Lobby\\TitleValidationDBSpec.h for a complete       |
| explanation of each parameter. Many other functors are available to      |
| perform various database operations. The directories found at            |
| DependentExtensions/\*\_PostgreRepository contain these implementations, |
| while DependentExtensions\\Lobby\\\*DBSpec.h contain the data members    |
| and documentation for this functionality. Test applications and demos    |
| for the various functors can be found in the projects                    |
| TitleValidationDB\_PostgreSQLTest, RankingServerDB\_PostgreSQLTest, and  |
| LobbyDB\_PostgreSQLTest                                                  |
|                                                                          |
| See LobbyServerTest for a console application that will run the          |
| LobbyServer.                                                             |
|                                                                          |
| **Required files (using [PostgreSQL](http://www.postgresql.org/)):**     |
|                                                                          |
| -   All source files in DependentExtensions\\Lobby that do not start     |
|     with LobbyClient                                                     |
| -   All source files in                                                  |
|     DependentExtensions\\Lobby\\LobbyDB\_PostgreRepository               |
| -   All source files in                                                  |
|     DependentExtensions\\Lobby\\LobbyServer\_PostgreSQL                  |
| -   All source files in                                                  |
|     DependentExtensions\\Lobby\\RankingServerDB\_PostgreRepository       |
| -   All source files in                                                  |
|     DependentExtensions\\Lobby\\TitleValidationDB\_PostgreRepository     |
| -   All source files in DependentExtensions\\PostgreSQLInterface         |
| -   All source files in Samples\\LobbyServerTest, should you want to use |
|     the default console application.                                     |
|                                                                          |
| **Dependencies (using [PostgreSQL](http://www.postgresql.org/)):**       |
|                                                                          |
| PostgreSQL 8.2 or newer, installed at C:\\Program                        |
| Files\\PostgreSQL\\8.2. Change the project property paths should your    |
| installation directory be different. Do not forget to check development  |
| tools in the PostgreSQL installer or the headers and libs will not be    |
| installed.                                                               |
|                                                                          |
|                                                                          |
+--------------------------------------------------------------------------+

  --------------------
   Lobby Client (PC)
  --------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">User interface to the database</span>\    |
|                                                                          |
| **Quick start:**                                                         |
|                                                                          |
| 1.  Attach the plugin to an instance of RakPeerInterface, and connect to |
|     the server.                                                          |
| 2.  Call SetCallbackInterface() with a derived implementation            |
|     of LobbyClientInterfaceCB. The general design of the system is that  |
|     all calls are asynchronous, so each call will return its results     |
|     (success or failure) to your registered callback.                    |
| 3.  If you do not already have an account, call RegisterAccount to       |
|     create a user account on the lobby. Wait                             |
|     for LobbyClientInterfaceCB::RegisterAccount\_Result() to see if the  |
|     query was successful. One possible failure is that the name is       |
|     already in use, or disallowed (swear word).                          |
| 4.  Call SetTitleLoginId() with information identifying what title you   |
|     are playing (can be done later if multiple games are allowed         |
|     per lobby). This should have been hardcoded into the application,    |
|     returned when the title was added to the server (as                  |
|     documented above).                                                   |
| 5.  Call Login() with the account you just created (or previously        |
|     had stored). Wait for LobbyClientInterfaceCB::Login\_Result() to     |
|     indicate success. If you have friends, they should                   |
|     get LobbyClientInterfaceCB::FriendStatus\_Notify() calls that you    |
|     are online.                                                          |
| 6.  Use DownloadRooms() to get a list of all rooms, based on search      |
|     filters, followed by JoinRoom(), SetReadyToPlayStatus(),             |
|     and StartGame(). Or use QuickMatch() to automatically start a game   |
|     with a given number of players.                                      |
| 7.  Once the game starts, you will                                       |
|     get LobbyClientInterfaceCB::StartGame\_Notify(). This will give you  |
|     the IP addresses of all players, participants, who the moderator is, |
|     user handles, and other information relevant to playing the game. At |
|     this point you can disconnect from the lobby. If you do not, you are |
|     automatically sent back to the main lobby (outside of any room).     |
|                                                                          |
| For a complete list of functions, with documented parameters, see        |
| DependentExtensions\\Lobby\\LobbyClientPC.h.                             |
|                                                                          |
| **Required files**                                                       |
|                                                                          |
| -   All source files in DependentExtensions\\Lobby, except for           |
|     LobbyServer.h and LobbyServer.cpp                                    |
| -   All source files in Samples\\LobbyClientTest, should you want to use |
|     the default console application as a framework to base your own GUI  |
|     implementation on.                                                   |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [SteamLobby](steamlobby.html)                                            |
|                                                                          |
|                                                                          |
+--------------------------------------------------------------------------+


