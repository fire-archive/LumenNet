<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  --------------------------
   Message Filter Overview
  --------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Limit incoming messages by                |
| category</span>\                                                         |
|                                                                          |
| With client/server topologies, you do not usually want any system to     |
| send any message. For example, perhaps only the server can send kill     |
| messages. Or perhaps you want to segment players into stages, where      |
| players who have logged on but not yet provided their password cannot    |
| yet send game messages. The message filter is designed to deal with      |
| these situations automatically.                                          |
|                                                                          |
| The MessageFilter plugin defines categories of users by 'filterSet'      |
| which is just a numerical identifier supplied by the user. For example,  |
| you may have one filter set for newly connected systems, and another for |
| authenticated systems. For each filter set you can                       |
|                                                                          |
| 1.  Automatically add new connections                                    |
| 2.  Allow RPC calls                                                      |
| 3.  Limit what messages, or ranges of messages, can be received, and     |
|     what actions to take if this condition is violated (kick/ban/notify) |
| 4.  Delete them                                                          |
|                                                                          |
| **Example:**                                                             |
|                                                                          |
| messageFilter.SetAutoAddNewConnectionsToFilter(0);\                      |
| messageFilter.SetAllowMessageID(true, ID\_USER\_PACKET\_ENUM,            |
| ID\_USER\_PACKET\_ENUM, 0);\                                             |
| messageFilter.SetAllowMessageID(true, ID\_USER\_PACKET\_ENUM+1,          |
| ID\_USER\_PACKET\_ENUM+1, 1);                                            |
|                                                                          |
| This setup would automatically add all new connections to filter set 0,  |
| and only allow the message ID\_USER\_PACKET\_ENUM to arrive. It would    |
| also create a new filter set, with the filterSet id 1, that only allowed |
| ID\_USER\_PACKET\_ENUM+1 to arrive.                                      |
|                                                                          |
| **Messages that are always allowed (filtering them has no effect):**     |
|                                                                          |
| ID\_CONNECTION\_LOST\                                                    |
| ID\_DISCONNECTION\_NOTIFICATION\                                         |
| ID\_NEW\_INCOMING\_CONNECTION\                                           |
| ID\_CONNECTION\_REQUEST\_ACCEPTED\                                       |
| ID\_CONNECTION\_ATTEMPT\_FAILED\                                         |
| ID\_NO\_FREE\_INCOMING\_CONNECTIONS\                                     |
| ID\_RSA\_PUBLIC\_KEY\_MISMATCH\                                          |
| ID\_CONNECTION\_BANNED\                                                  |
| ID\_INVALID\_PASSWORD\                                                   |
| ID\_MODIFIED\_PACKET\                                                    |
| ID\_PONG\                                                                |
| ID\_ALREADY\_CONNECTED\                                                  |
| ID\_ADVERTISE\_SYSTEM\                                                   |
| ID\_REMOTE\_DISCONNECTION\_NOTIFICATION\                                 |
| ID\_REMOTE\_CONNECTION\_LOST\                                            |
| ID\_REMOTE\_NEW\_INCOMING\_CONNECTION\                                   |
| ID\_DOWNLOAD\_PROGRESS                                                   |
|                                                                          |
| See *Samples/MessageFilter* for a complete sample. See MessageFilter.h   |
| for a complete list of all documented functions and parameters.          |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ----------------------
  [Index](index.html)\
  ----------------------


