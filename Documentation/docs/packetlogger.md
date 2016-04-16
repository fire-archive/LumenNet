<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -------------------------
   Packet Logger Overview
  -------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Log incoming and outgoing messages for    |
| debugging</span>\                                                        |
| \                                                                        |
| The PacketLogger is a plugin that will print all incoming and outgoing   |
| messages for debugging. It parses the message where necessary,           |
| indicating if a message is an RPC, or a timestamp. It also converts the  |
| numerical MessageID into the corresponding string. The output by default |
| is comma delineated, readable as a [CSV                                  |
| file](http://en.wikipedia.org/wiki/Comma-separated_values), and goes to  |
| the console with printf().                                               |
|                                                                          |
| To change the output destination, derive from PacketLogger and override  |
| WriteLog();                                                              |
|                                                                          |
| Aside from PacketLogger itself, the following implementations are        |
| already included:                                                        |
|                                                                          |
| -   PacketConsoleLogger - For use with the ConsoleServer.                |
| -   PacketFileLogger - Logs to a file. Call StartLog() to open the file. |
| -   ThreadsafePacketLogger - Same as PacketLogger, but delays WriteLog() |
|     until out of the RakNet thread. Use this if you do anything          |
|     significant with the logs (anything other than printf).              |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ----------------------
  [Index](index.html)\
  ----------------------


