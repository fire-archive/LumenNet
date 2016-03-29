---
title: "Tutorial code sample 1"
excerpt: ""
---
[block:api-header]
{
  "type": "basic",
  "title": "Instantiation and destruction"
}
[/block]
This is the base code to instantiate and destroy a peer as client or a server, along with some simple user input.
[block:code]
{
  "codes": [
    {
      "code": "#include <stdio.h>\n#include <rakpeerinterface.h>\n#define MAX_CLIENTS 10 \n#define SERVER_PORT 60000 \nint main(void) \n{ \n  char str[512]; \n  RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance(); \n  bool isServer; \n  printf(\"(C) or (S)erver?\\n\"); \n  gets(str); \n  if ((str[0]=='c')||(str[0]=='C'))\n  { \n    RakNet::SocketDescriptor sd; peer->Startup(1,&sd, 1); isServer = false;\n  } \n  else\n  { \n    RakNet::SocketDescriptor sd(SERVER_PORT,0);\n    peer->Startup(MAX_CLIENTS, &sd, 1); \n    isServer = true; \n  } \n  // TODO - Add code body here \n  RakNet::RakPeerInterface::DestroyInstance(peer); \n  return 0; \n}",
      "language": "cplusplus"
    }
  ]
}
[/block]