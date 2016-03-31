![Oculus VR, Inc.](RakNetLogo.jpg)\
\
  -----------------------------------------------------------------
  **![](spacer.gif){width="8" height="1"}Tutorial code sample 1**
  -----------------------------------------------------------------

+--------------------------------------------------------------------------+
| **Instantiation and destruction.**\                                      |
| \                                                                        |
| This is the base code to instantiate and destroy a peer as client or a   |
| server, along with some simple user input.                               |
|     #include <stdio.h>                                                   |
|     #include "RakPeerInterface.h"                                        |
|                                                                          |
|     #define MAX_CLIENTS 10                                               |
|     #define SERVER_PORT 60000                                            |
|                                                                          |
|     int main(void)                                                       |
|     {                                                                    |
|         char str[512];                                                   |
|         RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetIn |
| stance();                                                                |
|         bool isServer;                                                   |
|                                                                          |
|         printf("(C) or (S)erver?\n");                                    |
|         gets(str);                                                       |
|         if ((str[0]=='c')||(str[0]=='C'))                                |
|         {                                                                |
|             RakNet::SocketDescriptor sd;                                 |
|             peer->Startup(1,&sd, 1);                                     |
|             isServer = false;                                            |
|         } else {                                                         |
|             RakNet::SocketDescriptor sd(SERVER_PORT,0);                  |
|             peer->Startup(MAX_CLIENTS, &sd, 1);                          |
|             isServer = true;                                             |
|         }                                                                |
|                                                                          |
|                                                                          |
|         // TODO - Add code body here                                     |
|                                                                          |
|         RakNet::RakPeerInterface::DestroyInstance(peer);                 |
|                                                                          |
|         return 0;                                                        |
|     }                                                                    |
+--------------------------------------------------------------------------+


