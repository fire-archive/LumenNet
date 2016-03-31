<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ----------------------------
  Network Simulator Overview
  ----------------------------

  -----------------------------------------------------------------------------------------------------------------------------
  <span class="RakNetBlueHeader">Description</span>\
  \
  If you are using RakNet locally, chances are you will not have real-world problems like packet loss and ping fluctuations.\
  RakNet provides some functions to simulate those problems.
  -----------------------------------------------------------------------------------------------------------------------------

  -----------------------------
  Network Simulator Functions
  -----------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetCode">ApplyNetworkSimulator( double maxSendBPS,       |
| unsigned short minExtraPing, unsigned short extraPingVariance)</span>\   |
| \                                                                        |
| Enables simulated ping and packet loss to the outgoing data flow. To     |
| simulate bi-directional ping and packet loss, you should call this on    |
| both the sender and the recipient, with half the total ping and          |
| maxSendBPS value on each.                                                |
| *maxSendBPS* - Maximum bits per second to send. Packetloss grows         |
| linearly. 0 to disable.\                                                 |
| *minExtraPing* - The minimum time to delay sends.\                       |
| *extraPingVariance* The additional random time to delay sends.\          |
| \                                                                        |
| <span class="RakNetCode">bool IsNetworkSimulatorActive( void )</span>\   |
| \                                                                        |
| Returns if you previously called ApplyNetworkSimulator\                  |
| \                                                                        |
| \                                                                        |
| For a better solution, see                                               |
|                                                                          |
| <http://www.jenkinssoftware.com/raknet/forum/index.php?topic=1671.0>     |
|                                                                          |
|   -----------------------------------------------                        |
|   ![](spacer.gif){width="8" height="1"}See Also                          |
|   -----------------------------------------------                        |
|                                                                          |
|   ----------------------                                                 |
|   [Index](index.html)\                                                   |
|   ----------------------                                                 |
+--------------------------------------------------------------------------+


