---
title: "Frequently Asked Questions"
excerpt: ""
---
I'm having problems sending strings.
[block:api-header]
{
  "type": "basic"
}
[/block]
Use the StringCompressor or RakString class to send strings through Bitstreams.
[block:api-header]
{
  "type": "basic",
  "title": "How do I simulate lag?"
}
[/block]
In a hurry, use RakPeer::ApplyNetworkSimulator. But I recommend [http://www.netlimiter.com/](http://www.netlimiter.com/) instead.  

There is also Network Emulator Toolkit (NEWT) from [http://blog.mrpol.nl/2010/01/14/network-emulator-toolkit/](http://blog.mrpol.nl/2010/01/14/network-emulator-toolkit/) or [http://blogs.msdn.com/b/lkruger/archive/2009/06/08/introducing-true-network-emulation-in-visual-studio-2010.aspx](http://blogs.msdn.com/b/lkruger/archive/2009/06/08/introducing-true-network-emulation-in-visual-studio-2010.aspx)
[block:api-header]
{
  "type": "basic",
  "title": "How do I detect if I have exceeded the available bandwidth of the connection?"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "// Returns true if RakNet's output queue is increasing over time\nbool PushingPastCapacity(RakNet::RakPeerInterface *rakPeer, RakNet::Time currentTime, SystemAddress remoteSystem) {\n  static double bufferedBytesLastTick=0.0;\n  static RakNet::Time whenStartedPushingPastCapacity=currentTime;\n  RakNetStatistics rns;\n  rakPeer->GetStatistics(remoteSystem, &rns);\n  double bufferedBytesThisTick=rns.bytesInSendBuffer[IMMEDIATE_PRIORITY]+rns.bytesInSendBuffer[HIGH_PRIORITY]+rns.bytesInSendBuffer[MEDIUM_PRIORITY]+rns.bytesInSendBuffer[LOW_PRIORITY];\n  if ( bufferedBytesThisTick > bufferedBytesLastTick) {\n    if ( currentTime-whenStartedPushingPastCapacity>500 ) {\n      bufferedBytesLastTick=bufferedBytesThisTick; return true;\n    }\n  }\n  else {\n    whenStartedPushingPastCapacity=currentTime;\n  }\n  bufferedBytesLastTick=bufferedBytesThisTick;\n  return false;\n}",
      "language": "cplusplus"
    }
  ]
}
[/block]

[block:api-header]
{
  "type": "basic",
  "title": "My data that I write using bitstreams is messed up on the other side."
}
[/block]
Make sure if you write one of the ID_* enumerations you cast it to an (unsigned char). Do not use types that may be different on 64 and 32 bit systems, such as int or long (See NativeTypes.h). Other than that, make sure your read and write calls match.  
[block:api-header]
{
  "type": "basic",
  "title": "My data pointed to by a pointer isn't arriving."
}
[/block]
This is the same problem as when trying to use a default copy constructor with allocated memory. You can just send pointers if you want, but it will send the pointer variable rather than the data pointed to. You will need to serialize the contents of pointers yourself.  
[block:api-header]
{
  "type": "basic",
  "title": "How should I deal with firewalls?"
}
[/block]
Be sure to specify that your end-users need to open the appropriate ports, or use a port that is probably already open (such as the http port). One way to reduce tech support calls in this regard is to have your application try connecting a local client to a local server. If you can't connect after a couple of tries then the user probably has a firewall blocking this. You can message the user in-game that they probably have a firewall that needs to be turned off on whichever port your game uses.  
[block:api-header]
{
  "type": "basic",
  "title": "I get errors from winsock.h such as follows"
}
[/block]
C:\Program Files\Microsoft SDKs\Windows\v6.0A\\include\ws2def.h(91) : warning C4005: 'AF_IPX' : macro redefinition  
C:\Program Files\Microsoft SDKs\Windows\v6.0A\\include\winsock.h(460) : see previous definition of 'AF_IPX'  
C:\Program Files\Microsoft SDKs\Windows\v6.0A\\include\ws2def.h(127) : warning C4005: 'AF_MAX' : macro redefinition  
C:\Program Files\Microsoft SDKs\Windows\v6.0A\\include\winsock.h(479) : see previous definition of 'AF_MAX'  
C:\Program Files\Microsoft SDKs\Windows\v6.0A\\include\ws2def.h(163) : warning C4005: 'SO_DONTLINGER' : macro redefinition  
C:\Program Files\Microsoft SDKs\Windows\v6.0A\\include\winsock.h(402) : see previous definition of 'SO_DONTLINGER'  
C:\Program Files\Microsoft SDKs\Windows\v6.0A\\include\ws2def.h(206) : error C2011: 'sockaddr' : 'struct' type redefinition  
C:\Program Files\Microsoft SDKs\Windows\v6.0A\\include\winsock.h(485) : see declaration of 'sockaddr'  
This is a bug in winsock.h. You have to include winsock2.h before including winsock.h. You can fix this by including "WindowsIncludes.h" before including winsock.h.  
[block:api-header]
{
  "type": "basic",
  "title": "I get conflicting lib errors such as follows"
}
[/block]
LIBCMT.lib(dosmap.obj) : error LNK2005: __dosmaperr already defined in LIBCD.lib(dosmap.obj)  
LIBCMT.lib(mbctype.obj) : error LNK2005: __getmbcp already defined in LIBCD.lib(mbctype.obj)  
LIBCMT.lib(mbctype.obj) : error LNK2005: __setmbcp already defined in LIBCD.lib(mbctype.obj)  
LIBCMT.lib(mbctype.obj) : error LNK2005: ___initmbctable already defined in LIBCD.lib(mbctype.obj)  
LIBCMT.lib(tolower.obj) : error LNK2005: __tolower already defined in LIBCD.lib(tolower.obj)  
LIBCMT.lib(tolower.obj) : error LNK2005: _tolower already defined in LIBCD.lib(tolower.obj)  
LIBCMT.lib(isctype.obj) : error LNK2005: __isctype already defined in LIBCD.lib(isctype.obj)  
LINK : warning LNK4098: defaultlib 'LIBCMT' conflicts with use of other libs; use /NODEFAULTLIB:library  

You need to select Multithreaded Debug and Multithreaded libraries in the project options.  
[block:api-header]
{
  "type": "basic",
  "title": "I get linker errors such as follows"
}
[/block]
LIBCMTD.lib(invarg.obj) : error LNK2005: __invoke_watson already defined in MSVCRTD.lib(MSVCR80D.dll)  
LIBCMTD.lib(setlocal.obj) : error LNK2005: __configthreadlocale already defined in MSVCRTD.lib(MSVCR80D.dll)  
LIBCMTD.lib(tidtable.obj) : error LNK2005: __encode_pointer already defined in MSVCRTD.lib(MSVCR80D.dll)  
LIBCMTD.lib(tidtable.obj) : error LNK2005: __decode_pointer already defined in MSVCRTD.lib(MSVCR80D.dll)  
LIBCMTD.lib(dbgheap.obj) : error LNK2005: _malloc already defined in MSVCRTD.lib(MSVCR80D.dll)  
LIBCMTD.lib(dbgheap.obj) : error LNK2005: _realloc already defined in MSVCRTD.lib(MSVCR80D.dll)  
LIBCMTD.lib(dbgheap.obj) : error LNK2005: _free already defined in MSVCRTD.lib(MSVCR80D.dll)  
LINK : warning LNK4098: defaultlib 'MSVCRTD' conflicts with use of other libs; use /NODEFAULTLIB:library  
LINK : warning LNK4098: defaultlib 'LIBCMTD' conflicts with use of other libs; use /NODEFAULTLIB:library  

Right click on the project name, click properties, go to Configuration Properties / C/C++ / Code Generation and change from Multithreaded Debug DLL to Multithreaded Debug (same for release).  
[block:api-header]
{
  "type": "basic",
  "title": "Dropped connections are not detected and/or I can't reconnect after losing the connection."
}
[/block]
By default, the timeout in debug build is set to 30 seconds, and in release to 10 senconds. A detect lost connections message is sent every 5 seconds. So you may have to wait 35 seconds before you can reconnect. You can change the timeout using RakPeerInterface::SetTimeoutTime.  
[block:api-header]
{
  "type": "basic",
  "title": "I want event callbacks on packet arrival."
}
[/block]
There are no event callbacks on packet arrival. If you want an event, poll Receive and make your own event if non-zero is returned.  
[block:api-header]
{
  "type": "basic",
  "title": "I can't connect to the other system or other systems can't connect to me. What are some possible reasons?"
}
[/block]
*   The other system isn't running RakNet.
*   The other system didn't start the connection, or tried to start it and it failed (the startup function returned false).
*   The server has a firewall blocking incoming connections.
*   The server has a firewall blocking UDP data on the specified server port or the server port + 1 (for winsock 2.0+).
*   The client has a firewall blocking UDP data on the specified client port or the server port + 1 (for winsock 2.0+).
*   The server already has the maximum number of connected clients.
*   The server has a lot of network traffic and is too busy to respond to your connection request.
*   You used a different value for connectionValidationInteger than the other system.
*   You are connecting to the wrong port on the server.
*   You entered the wrong IP address of the server. This could be by mistyping or confusing the LAN address with the internet address.
*   One or both systems are not using high priority threads and are at the same time using a lot of CPU power for other threads. This could cause the network threads to not respond to the handshaking sequence fast enough.
*   The handshaking packets were lost due to normal packetloss
*   You did connect, but never handled the network messaging packets that indicated you you did either because you aren't handling any messages or because you didn't handle those in particular.
*   The recipient is behind a NAT and didn't use NAT punch-through.
[block:api-header]
{
  "type": "basic",
  "title": "I get linker errors about winsock function redefinitions   i.e. - error C2011: 'WSAData' : 'struct' type redefinition   i.e. - warning C4005: 'SO_DONTLINGER' : macro redefinition"
}
[/block]
Add this to your preprocessor definitions  
_WINSOCKAPI_  
In .Net this would be project / configuration properties / C/C++ / Preprocessor / Preprocessor defintions.  
You will get this or a similar warning:  
warning C4005: '_WINSOCKAPI_' : macro redefinition unknown(0) : see previous definition of '_WINSOCKAPI_'  
You can ignore it.  

**I can connect but don't get any data from the other system. What are some possible reasons?**  

You aren't calling Receive.  
The other system didn't send any data, or didn't send any to you.  
The other system immediately kicked you after you connected, such as due to you being banned or using a wrong password.  
The network disconnected you because of cheating or because it couldn't deliver a reliable packet.  

**Some kind of networked action happens twice, such as when I press the trigger to fire a bullet two bullets come out.**  

The server is broadcasting to everyone, including the client that just initiated the action. To fix this, pass the systemAddress parameter of the packet to the systemAddress field of RakPeerInterface::Send when broadcasting. This will relay the message to all players BUT the sender.  

**When I send some particular kind of packet, I immediately get flooded with hundreds of copies the same packet.**  
This is a feedback loop, caused by the following sort of coding:  

// Client  
void DoMyFunctionA(void)  
{  
SendPacketToDoFunctionA();  
}  

// Server  
void HandlePacketToDoFunctionA(void)  
{  
// Broadcast to all connected players  
SendToAllPacketToDoFunctionA();  
}  

// Client  
void ReceivePacketToDoFunctionA(void)  
{  
DoMyFunctionA();  
}  

To fix this, either don't have the function that does the action also send the packet, or use a parameter specifying whether to send a packet or not and set that parameter to false if the function is called from the network code. See Programming Tips for help on how to handle this.  

**How do I create a master game browser?**  
We offer this at http://masterserver2.raknet.com/. You could also use CloudServer, PHPDirectoryServer2, RoomsPlugin, SteamLobby, or SQLite3Plugin  

**Which version of the multithreaded library does RakNet use?**  
Multithreaded (/MT)  

**Since RakNet uses threads does my program need to use the multithreaded library?**  
If you use the DLL then no. The threads are confined to the dll. If you use the static lib or source then yes.  

**Can I run more than one instance of the client or server on the same system?  
**Yes, but each instance will have its own thread and require its own memory. You'll need to remember to give different port assigments to each instance as well. There isn't really any reason to do this since you can use RakPeer to handle multiple outgoing connections.  

**How do I send files?**  
Just send it as a data stream using RELIABLE.  

**If I purchase one license, can I use it in more than one game?**  
A site license will allow you to do this. A normal license requires one copy of the license per game. Refer to the License Agreement for full details.  

**Can I use RakNet in non-games?**  
Yes  

**My game is too laggy. How can I decrease lag?**  
- Use bandwidth more efficiently (see the optimization section in Programming Tips )  
- Design your game so it doesn't require as much bandwidth (see the optimization section in Programming Tips )  
- Use high priority threads  
- Get a faster computer. This will make threads more responsive.  
- Get a better internet connection.  
- Decrease the number of clients allowed.  

**Does RakNet use TCP at all?**  
RakPeer does not. However, some plugins support it - EmailSender, Autopatcher, FileListTransfer, DeltaDirectoryTransfer.  

**Will RakNet work with my game written in C?**  
No.

**On Windows 7 why can I not open more than one outgoing connection at a time, unless I run as administrator?**  
This was a design flaw in Windows 7 when it shipped. However, once you run the updater, this design flaw was fixed. See [http://www.jenkinssoftware.com/forum/index.php?topic=3721.0](http://www.jenkinssoftware.com/forum/index.php?topic=3721.0)

**Does RakNet support cloud hosting services?  
**[Yes](cloudhosting.html), RakNet works with [Rackspace Cloud](http://www.rackspace.com/cloud/).