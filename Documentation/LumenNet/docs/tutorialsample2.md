![Oculus VR, Inc.](RakNetLogo.jpg)\
\
  -----------------------------------------------------------------
  **![](spacer.gif){width="8" height="1"}Tutorial code sample 2**
  -----------------------------------------------------------------

+--------------------------------------------------------------------------+
| **Connecting, reading, and parsing network messages.**\                  |
| \                                                                        |
| The target of this exercise was to add the following features to sample  |
| 1:                                                                       |
| 1.  Create a main loop for the program.                                  |
| 2.  Call Receive and store the pointer returned in a pointer variable of |
|     type Packet. Note that we continually call Receive() until no        |
|     further packets are returned. A common mistake is to only call       |
|     it once.                                                             |
| 3.  Include the header file to use struct Packet                         |
| 4.  If a packet arrived, check the first byte of Packet::data, and       |
|     process accordingly. The list of enumerations is                     |
|     in MessageIdentifiers.h.                                             |
| 5.  Print out the comment that goes along with the enumeration.          |
| 6.  Deallocate the packet pointer when done with it.                     |
|                                                                          |
| New code over sample 1 is in bold.                                       |
|                                                                          |
|                                                                          |
|                                                                          |
|     #include <stdio.h>                                                   |
|     #include <string.h>                                                  |
|     #include "RakPeerInterface.h"                                        |
|     #include "MessageIdentifiers.h"                                      |
|                                                                          |
|     #define MAX_CLIENTS 10                                               |
|     #define SERVER_PORT 60000                                            |
|                                                                          |
|     int main(void)                                                       |
|     {                                                                    |
|         char str[512];                                                   |
|                                                                          |
|         RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetIn |
| stance();                                                                |
|         bool isServer;                                                   |
|         RakNet::Packet *packet;                                          |
|                                                                          |
|         printf("(C) or (S)erver?\n");                                    |
|         gets(str);                                                       |
|                                                                          |
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
|         if (isServer)                                                    |
|         {                                                                |
|             printf("Starting the server.\n");                            |
|             // We need to let the server accept incoming connections fro |
| m the clients                                                            |
|             peer->SetMaximumIncomingConnections(MAX_CLIENTS);            |
|         } else {                                                         |
|             printf("Enter server IP or hit enter for 127.0.0.1\n");      |
|             gets(str);                                                   |
|             if (str[0]==0){                                              |
|                 strcpy(str, "127.0.0.1");                                |
|             }                                                            |
|             printf("Starting the client.\n");                            |
|             peer->Connect(str, SERVER_PORT, 0,0);                        |
|                                                                          |
|         }                                                                |
|                                                                          |
|         while (1)                                                        |
|         {                                                                |
|             for (packet=peer->Receive(); packet; peer->DeallocatePacket( |
| packet), packet=peer->Receive())                                         |
|             {                                                            |
|                 switch (packet->data[0])                                 |
|                     {                                                    |
|                     case ID_REMOTE_DISCONNECTION_NOTIFICATION:           |
|                         printf("Another client has disconnected.\n");    |
|                         break;                                           |
|                     case ID_REMOTE_CONNECTION_LOST:                      |
|                         printf("Another client has lost the connection.\ |
| n");                                                                     |
|                         break;                                           |
|                     case ID_REMOTE_NEW_INCOMING_CONNECTION:              |
|                         printf("Another client has connected.\n");       |
|                         break;                                           |
|                     case ID_CONNECTION_REQUEST_ACCEPTED:                 |
|                         printf("Our connection request has been accepted |
| .\n");                                                                   |
|                         break;                                           |
|                     case ID_NEW_INCOMING_CONNECTION:                     |
|                         printf("A connection is incoming.\n");           |
|                         break;                                           |
|                     case ID_NO_FREE_INCOMING_CONNECTIONS:                |
|                         printf("The server is full.\n");                 |
|                         break;                                           |
|                     case ID_DISCONNECTION_NOTIFICATION:                  |
|                         if (isServer){                                   |
|                             printf("A client has disconnected.\n");      |
|                         } else {                                         |
|                             printf("We have been disconnected.\n");      |
|                         }                                                |
|                         break;                                           |
|                     case ID_CONNECTION_LOST:                             |
|                         if (isServer){                                   |
|                             printf("A client lost the connection.\n");   |
|                         } else {                                         |
|                             printf("Connection lost.\n");                |
|                         }                                                |
|                         break;                                           |
|                     default:                                             |
|                         printf("Message with identifier %i has arrived.\ |
| n", packet->data[0]);                                                    |
|                         break;                                           |
|                     }                                                    |
|             }                                                            |
|         }                                                                |
|                                                                          |
|                                                                          |
|         RakNet::RakPeerInterface::DestroyInstance(peer);                 |
|                                                                          |
|         return 0;                                                        |
|     }                                                                    |
+--------------------------------------------------------------------------+


