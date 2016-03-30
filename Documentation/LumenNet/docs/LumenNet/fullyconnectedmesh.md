<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -------------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Fully Connected Mesh Plugin Interface Implementation
  -------------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Automatically connect all peers in a peer |
| to peer game</span>\                                                     |
| \                                                                        |
| The fully connected mesh implementation reads connection messages from   |
| RakNet and tries to connect to all systems on the network. On a new      |
| connection, it will tell the remote system of all systems it knows       |
| about. When that packet arrives, that system will then try to connect to |
| all those systems in turn. You can optionally specify a password which   |
| you can use to allow certain systems to join the mesh and other systems  |
| to not do so.                                                            |
|                                                                          |
| NOTE : The implementation requires that a ConnectionGraph plugin is also |
| attached to the RakPeer.\                                                |
|                                                                          |
| /// Set the password to use to connect to the other systems\             |
| void Startup(const char \*password, int \_passwordLength);               |
|                                                                          |
| /// Use the NAT punchthrough system to connect rather than calling       |
| directly\                                                                |
| void ConnectWithNatPunchthrough(NatPunchthrough \*np, SystemAddress      |
| \_facilitator);                                                          |
|                                                                          |
| See *Samples/FullyConnectedMesh* for a demonstration of this plugin      |
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


