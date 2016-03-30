<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -----------------------------------------
   Two Way Authentication Plugin Overview
  -----------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Securely verify a password known in       |
| advance by a pair of systems</span>\                                     |
|                                                                          |
| Normally with RakNet you can transmit data securely using [secure        |
| connections](secureconnections.html). However, sometimes a pair of       |
| systems may not have secure connections active. For example, on mobiles  |
| the security code may take too much memory, be too slow, or not compile. |
| In this case you can still verify a remote system using a password known |
| to two systems in advance. RakNet implements this using [two way         |
| authentication](http://en.wikipedia.org/wiki/Mutual_authentication).     |
| Instead of sending the password itself, a [one way                       |
| hash](http://en.wikipedia.org/wiki/Cryptographic_hash_function) of the   |
| password is sent. The hash is verified as correct or not, and the        |
| results returned to the user.                                            |
|                                                                          |
| Usage:                                                                   |
|                                                                          |
| // Attach the plugin to an instance of RakPeerInterface\                 |
| rakPeer-&gt;AttachPlugin(&twoWayAuthenticationPlugin);\                  |
| // Add a password. The actual password (Password0) is associated with a  |
| identifier (PWD0) for faster hash lookup.\                               |
| twoWayAuthenticationPlugin.AddPassword("PWD0", "Password0");\            |
| // Challenge another system we are connected to.\                        |
| twoWayAuthenticationPlugin.Challenge("PWD0", remoteSystemAddressOrGuid); |
|                                                                          |
| If the other system is also running the two way authentication plugin,   |
| and had also set the same password, you will get <span                   |
| class="RakNetCode">ID\_TWO\_WAY\_AUTHENTICATION\_INCOMING\_CHALLENGE\_SU |
| CCESS</span>                                                             |
| and the other system will get <span                                      |
| class="RakNetCode">ID\_TWO\_WAY\_AUTHENTICATION\_OUTGOING\_CHALLENGE\_SU |
| CCESS</span>.                                                            |
| If the other system is running the plugin but has a different password,  |
| they will get <span                                                      |
| class="RakNetCode">ID\_TWO\_WAY\_AUTHENTICATION\_INCOMING\_CHALLENGE\_FA |
| ILURE</span>                                                             |
| and you will get <span                                                   |
| class="RakNetCode">ID\_TWO\_WAY\_AUTHENTICATION\_OUTGOING\_CHALLENGE\_FA |
| ILURE</span>.                                                            |
| If the other system is not running the plugin you will get <span         |
| class="RakNetCode">ID\_TWO\_WAY\_AUTHENTICATION\_OUTGOING\_CHALLENGE\_TI |
| MEOUT</span>.                                                            |
|                                                                          |
| In the case of                                                           |
|                                                                          |
| -   ID\_TWO\_WAY\_AUTHENTICATION\_INCOMING\_CHALLENGE\_SUCCESS           |
| -   ID\_TWO\_WAY\_AUTHENTICATION\_OUTGOING\_CHALLENGE\_SUCCESS           |
| -   ID\_TWO\_WAY\_AUTHENTICATION\_OUTGOING\_CHALLENGE\_TIMEOUT           |
| -   ID\_TWO\_WAY\_AUTHENTICATION\_OUTGOING\_CHALLENGE\_FAILURE           |
|                                                                          |
| you can read which password challenge the message was associated with    |
| using the following code:                                                |
| RakNet::BitStream bs(packet-&gt;data, packet-&gt;length, false);\        |
| bs.IgnoreBytes(sizeof(RakNet::MessageID));\                              |
| RakNet::RakString password;\                                             |
| bs.Read(password);                                                       |
|                                                                          |
| All this system does is verify a password between two parties. It does   |
| not enable or disable any RakNet features, or prevent any other message  |
| from being sent during the challenge phase. However, you can pair this   |
| plugin with the [MessageFilter](messagefilter.html) plugin so that a new |
| connection cannot send any other messages until validated. To do so,     |
| attach the [MessageFilter](messagefilter.html) plugin to                 |
| RakPeerInterface before this one (actually it should be first). Call     |
| MessageFilter::SetAutoAddNewConnectionsToFilter() so that new            |
| connections are filtered. Make sure that the two way authentication      |
| messages are allowed on that same filter channel by calling              |
| MessageFilter::SetAllowMessageID(). When a connection has been           |
| validated, change the channel for that system using                      |
| MessageFilter::SetSystemFilterSet().                                     |
|                                                                          |
| See *Samples/TwoWayAuthentication* for a complete sample. See            |
| TwoWayAuthentication.h for a complete list of all documented functions   |
| and parameters.                                                          |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

\
[Index](index.html)\
[Message Filter plugin](messagefilter.html)\

