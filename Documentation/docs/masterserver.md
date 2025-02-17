![Oculus VR, Inc.](RakNetLogo.jpg)\
\
  ----------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Master Server
  ----------------------------------------------------

  -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  **Deprecated, see [Master Server 2](http://masterserver2.raknet.com/)** Description of the provided master server\
  \
  A master game server is a server that maintains a list of running game servers. It provides the same functionality as Gamespy minus the limited sorting features they provide but for thousands of \$\$\$ less. It's almost required these days because otherwise your players have no way to find other active games to connect to.\
  \
  This is the sample implementation of a master game server using RakNet. There are many features you may wish to add on your own as this is just a shell.\
  \
  The code is class-based, one class for the master server and another for the master client, which your game should use to talk to the master server. To include this functionality, just make one instantiation of MasterServer or MasterClient as appropriate.\
  \
  MasterServer will generally be a console application or a simple windowed application. To run it, just call Initialize once, then Update once per frame. You can also derive and implement OnModifiedPacket if you want. MasterServerMain contains test code which is an excellent overview of the master server's capabilities. It's a good idea to host this on a domain name rather than a specific IP so you can change servers without forcing your players to update. For example, if your game's website is mutantkillerfrogs.com you can code the MasterClient to connect to this domain, which will be resolved to an IP.\
  \
  MasterClient is a client that game servers should include and manage. It would be a good idea to connect to a domain name rather than a specific IP (see above)\
  \
  See **MasterClient.h**, **MasterServer.h**, and **MasterCommon.h** for full details on what the master server and master client can do.\
  -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  --------------------------------------------
  [Index](index.html)\
  [NAT Punch-through](natpunchthrough.html)\
  --------------------------------------------


