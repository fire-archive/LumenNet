<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ---------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Plugin Interface 2
  ---------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Plugin Interface 2 Overview</span>\       |
| \                                                                        |
| *PluginInterface2.h* is a class interface that works with RakNet to      |
| provide automatic functionality. It can intercept, modify, and create    |
| messages before they get to the user. Plugins can be attached to either  |
| RakPeerInterface or PacketizedTCP. Plugins update every time Receive()   |
| is called. To use it, derive from the base class and implement the       |
| virtual functions you want to handle. Then register your class by        |
| calling RakPeerInterface::AttachPlugin()                                 |
|                                                                          |
| These are the virtual functions you'll probably need to handle in most   |
| cases:                                                                   |
|                                                                          |
| /// Update is called every time a packet is checked for .\               |
| virtual void Update(void);\                                              |
| \                                                                        |
| /// OnReceive is called for every packet.\                               |
| /// \\param\[in\] packet the packet that is being returned to the user\  |
| /// \\return True to allow the game and other plugins to get this        |
| message, false to absorb it\                                             |
| virtual PluginReceiveResult OnReceive(Packet \*packet);                  |
|                                                                          |
| /// Called when a connection is dropped because the user called          |
| RakPeer::CloseConnection() for a particular system\                      |
| /// \\param\[in\] systemAddress The system whose connection was closed\  |
| /// \\param\[in\] rakNetGuid The guid of the specified system\           |
| /// \\param\[in\] lostConnectionReason How the connection was closed:    |
| manually, connection lost, or notification of disconnection\             |
| virtual void OnClosedConnection(SystemAddress systemAddress, RakNetGUID  |
| rakNetGUID, PI2\_LostConnectionReason lostConnectionReason );            |
|                                                                          |
| /// Called when we got a new connection\                                 |
| /// \\param\[in\] systemAddress Address of the new connection\           |
| /// \\param\[in\] rakNetGuid The guid of the specified system\           |
| /// \\param\[in\] isIncoming If true, this is                            |
| ID\_NEW\_INCOMING\_CONNECTION, or the equivalent\                        |
| virtual void OnNewConnection(SystemAddress systemAddress, RakNetGUID     |
| rakNetGUID, bool isIncoming);                                            |
|                                                                          |
| \                                                                        |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ----------------------
  [Index](index.html)\
  ----------------------


