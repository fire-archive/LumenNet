<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ------------------------
   Email Sender Overview
  ------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Simple class to send emails via           |
| C++</span>\                                                              |
| \                                                                        |
| The EmailSender class, found at EmailSender.h, is a simple class with    |
| only one function, Send(...), to send an email using a provided mail     |
| server. It is used internally by the [CrashReporter](crashreporter.html) |
| class to send emails for unmonitored servers. See EmailSender.h for a    |
| full description of each parameter.                                      |
|                                                                          |
| See the project Samples/SendEmail for a sample of this                   |
|                                                                          |
| The class has also been tested to work with Gmail POP servers, so if you |
| have a Gmail account you can send emails without using your own mail     |
| server. The sample has the settings you need by default. You will also   |
| need to uncomment OPEN\_SSL\_CLIENT\_SUPPORT in RakNetDefines.h, as      |
| Gmail requires the TCP connection to be made with SSL.                   |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [Crash Repoter](crashreporter.html)\                                     |
+--------------------------------------------------------------------------+


