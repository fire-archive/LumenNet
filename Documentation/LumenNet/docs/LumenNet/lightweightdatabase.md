<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -----------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Lightweight Database
  -----------------------------------------------------------

+--------------------------------------------------------------------------+
| **--- Depreciated, use [SQLite3Plugin](sqlite3plugin.html) instead       |
| ---**\                                                                   |
| \                                                                        |
| LightweightDatabaseServer/LightweightDatabaseClient provides a simple    |
| way to implement a master game server.\                                  |
| A master game server is a server that maintains a list of running game   |
| servers. It provides the same functionality as similar commercial        |
| utilities, at no extra charge.                                           |
|                                                                          |
| ![Directory Server Listing](DirectoryServerListing.jpg){width="512"      |
| height="128"}\                                                           |
| \                                                                        |
| There are just two classes you can use. One for the master game server   |
| (LightweightDatabaseServer), and one for the client                      |
| (LightweightDatabaseClient), which your game should use to talk to the   |
| master game server. To include this functionality, just make one         |
| instantiation of LightweightDatabaseServer or LightweightDatabaseClient  |
| as appropriate.\                                                         |
| \                                                                        |
| Your master game server, (which uses LightweightDatabaseServer) will     |
| generally be a console application or a simple windowed application,     |
| whose only purpose is to wait for game servers to inform they are        |
| available , or to reply to players systems who want to know what game    |
| servers are available.\                                                  |
| LightweightDatabaseServer uses in-memory tables to manage the game       |
| servers. Just like in a real database, you can define what fields you    |
| want in a table.\                                                        |
| Check the documentation for LightweightDatabaseServer::AddTable and      |
| LightweightDatabaseServer::GetTable\                                     |
| Those functions return a table to which you can add columns (fields).\   |
| \                                                                        |
| It's a good idea to host your master game server on a domain name rather |
| than a specific IP so you can change servers without forcing your        |
| players to update. For example, if your game's website is                |
| mutantkillerfrogs.com you can code the MasterClient to connect to this   |
| domain, which will be resolved to an IP.\                                |
| \                                                                        |
| LightweightDatabaseClient is a client that game servers should use to    |
| inform the master game server they are available for use. That is done   |
| by connecting to the master game server, and adding a new row in master  |
| game server's table. Use LightweightDatabaseClient::UpdateRow for that.\ |
| \                                                                        |
| Note you'll also use LightweightDatabaseClient for the player system to  |
| connect to the master game server, but just for queries to find          |
| available game servers.\                                                 |
| \                                                                        |
| See *\\Samples\\LightweightDatabase* for full details on how to use      |
| those classes.\                                                          |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [NAT Punch-through](natpunchthrough.html)\                               |
| [SQLite3Plugin](sqlite3plugin.html)\                                     |
+--------------------------------------------------------------------------+


