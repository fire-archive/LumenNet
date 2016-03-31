<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  --------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Network ID Object
  --------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">The NetworkIDObject and NetworkIDManager  |
| classes allow lookup of pointers using a common ID</span>\               |
| \                                                                        |
| The NetworkIDObject class is an optional class you can derive from that  |
| will automatically assign identification numbers (NetworkID) to objects  |
| that inherit from it. This is useful for multiplayer games, because      |
| otherwise you have no way to refer to dynamically allocated objects on   |
| remote systems.                                                          |
|                                                                          |
| In RakNet 4, NetworkIDs are 8 byte globally unique numbers, chosen at    |
| random. Older versions of RakNet required that a central authority       |
| (server) assign NetworkIDs. This approached was dropped because it       |
| creates difficulties for the programmer when the game is peer to peer,   |
| or there are multiple distributed servers. It also created extra work if |
| a client were to create an object, because the client would have to      |
| assign a temporary ID, request the real NetworkID from the server, and   |
| then assign it sometime later.                                           |
|                                                                          |
| The NetworkIDObject class provides the following major functions:        |
|                                                                          |
| **SetNetworkIDManager( NetworkIDManager \*manager)**\                    |
| The NetworkIDManager holds a list of NetworkIDs for lookup. Therefore,   |
| it is required that you call SetNetworkIDManager before calling          |
| GetNetworkID() or SetNetworkID(). The reason the list isn't just static  |
| is that you might want multiple NetworkIDManagers, for example if you    |
| have multiple gameworlds that do not interact with each other.           |
|                                                                          |
| **NetworkID GetNetworkID( void )**\                                      |
| If SetNetworkID() was previously called, this returns that value.        |
| Otherwise it generates a new, presumably unique NetworkID for the        |
| object, if SetNetwor. Internally, the object is not assigned a NetworkID |
| until GetNetworkID() is actually called. In a client/server application  |
| if all objects were still created by the server, then it would never be  |
| necessary for a client to generate a NetworkID.\                         |
| \                                                                        |
| **SetNetworkID( NetworkID id )**\                                        |
| Assigns a networkID to the object. An example of where this would be     |
| used is a server creating a new game object, and sending that object's   |
| data to the clients. The client would create a class of the same time,   |
| read the NetworkID encoded in the user message, and call SetNetworkID on |
| the same object.                                                         |
|                                                                          |
| The NetworkIDManager class only has one user function:                   |
|                                                                          |
| template &lt;class returnType&gt;\                                       |
| **returnType GET\_OBJECT\_FROM\_ID(NetworkID x);**                       |
|                                                                          |
| This is a templated function, so you write something like:               |
|                                                                          |
| Solder \*soldier =                                                       |
| networkIdManager.GET\_OBJECT\_FROM\_ID&lt;Solider\*&gt;(networkId);      |
|                                                                          |
| Here's an example of storing a pointer to a class, retrieving it back    |
| again, with an assert to make sure the system worked:                    |
|                                                                          |
| class Soldier : public NetworkIDObject {}\                               |
| int main(void)\                                                          |
| {\                                                                       |
| NetworkIDManager networkIDManager;\                                      |
| Soldier \*soldier = new Soldier;\                                        |
| soldier-&gt;SetNetworkIDManager(&networkIDManager);\                     |
| NetworkID soldierNetworkID = soldier-&gt;GetNetworkID();\                |
| assert(networkIDManager.GET\_OBJECT\_FROM\_ID&lt;Soldier\*&gt;(soldierNe |
| tworkID)==soldier);\                                                     |
| }                                                                        |
|                                                                          |
| Here's an example of using the system to create an object on a remote    |
| computer, with the same NetworkID assigned to both:                      |
|                                                                          |
| **Server:**                                                              |
|                                                                          |
| void CreateSoldier(void)\                                                |
| {\                                                                       |
| Soldier \*soldier = new Soldier;\                                        |
| soldier-&gt;SetNetworkIDManager(&networkIDManager);\                     |
| RakNet::BitStream bsOut;\                                                |
| bsOut.Write((MessageID)ID\_CREATE\_SOLDIER);\                            |
| bsOut.Write(soldier-&gt;GetNetworkID();\                                 |
| rakPeerInterface-&gt;Send(&bsOut,HIGH\_PRIORITY,RELIABLE\_ORDERED,0,UNAS |
| SIGNED\_SYSTEM\_ADDRESS,true);\                                          |
| }                                                                        |
|                                                                          |
| **Client:**                                                              |
|                                                                          |
| Packet \*packet = rakPeerInterface-&gt;Receive();\                       |
| if (packet-&gt;data\[0\]==ID\_CREATE\_SOLDIER)\                          |
| {\                                                                       |
| RakNet::BitStream bsIn(packet-&gt;data, packet-&gt;length, false);\      |
| bsIn.IgnoreBytes(sizeof(MessageID));\                                    |
| NetworkID soldierNetworkID;\                                             |
| bsIn.Read(soldierNetworkID);\                                            |
| Soldier \*soldier = new Soldier;\                                        |
| soldier-&gt;SetNetworkIDManager(&networkIDManager);\                     |
| soldier-&gt;SetNetworkID(soldierNetworkID);\                             |
| }                                                                        |
|                                                                          |
| Static objects                                                           |
|                                                                          |
| Sometimes objects are not created dynamically, but instead already exist |
| on all systems and are known ahead of time. For example, if you have a   |
| capture the flag map, with 3 flags, those 3 flags may be hardcoded into  |
| the level design and are thus created by all systems when the level      |
| loads. Thee are static objects, and can still be referred to by          |
| NetworkIDManager. Have those objects derive from NetworkIDObject and     |
| call SetNetworkIDManager as usual. Then simply assign a unique ID of     |
| your choosing. It doesn't matter what the ID is, as long as it is        |
| unique, so you could for example have flag 1 have the ID 0, flag 2 have  |
| the ID 1, and flag 3 have the ID 2.                                      |
|                                                                          |
| // All static network IDs added here.\                                   |
| enum StaticNetworkIDs\                                                   |
| {\                                                                       |
| CTF\_FLAG\_1,\                                                           |
| CTF\_FLAG\_2,\                                                           |
| CTF\_FLAG\_3,\                                                           |
| };\                                                                      |
| \                                                                        |
| class Flag : public NetworkIDObject\                                     |
| {\                                                                       |
| // Level designer named the flag either flag1, flag2, or flag3, and this |
| map will load identically on all systems\                                |
| Flag(std::string flagName, NetworkIDManager \*networkIDManager) {\       |
| \                                                                        |
| SetNetworkIDManager(networkIDManager);\                                  |
| \                                                                        |
| if (flagName=="flag1") SetNetworkID(CTF\_FLAG\_1);\                      |
| else if (flagName=="flag2") SetNetworkID(CTF\_FLAG\_2);\                 |
| else if (flagName=="flag3") SetNetworkID(CTF\_FLAG\_3);\                 |
| };                                                                       |
+--------------------------------------------------------------------------+
|                                                                          |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ----------------------
  [Index](index.html)\
  ----------------------


