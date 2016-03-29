---
title: "Connecting to other systems"
excerpt: ""
---
## Find who to connect to

There are 5 ways to find other systems to connect to:

1.  Direct IP entry (you already know it)
2.  LAN Broadcast
3.  Using the CloudServer/CloudClient plugins
4.  Using the Lobby server or RoomsPlugin
5.  Using MasterServer2

<span class="RakNetBlueHeader">Option 1: Direct IP Entry</span>

The simplest and easiest way from a coding perspective is to either hardcode an IP address or domain name, or present a GUI to the user asking them to enter the IP address of the other system they would like to connect to. Most of the samples use this method. Back when networked games first came out, this was the only option available.

<span style="font-style: italic;">Advantages:</span>

*   Little to no GUI work required of programmers and artists
*   If the IP address or domain name is fixed, such as if you are running a dedicated server, this is the correct solution

<span style="font-style: italic;">Disadvantages:</span>

*   Inflexible
*   Users will only be able to play with people they already know.

Note: Use 127.0.0.1, or localhost, to connect to another instance of RakPeer on the same computer, or the same application.

<span class="RakNetBlueHeader">Option 2: Lan Broadcast</span>

RakNet supports the ability to broadcast a packet to find other systems on a local LAN, with optional data to send and retrieve identifying the application. The sample <span style="font-weight: bold;">LANServerDiscovery</span> demonstrates this technique.

In RakPeerInterface.h, the Ping function will can do this, as follows

<span style="font-style: italic;"></span>rakPeer->Ping("255.255.255.255", REMOTE_GAME_PORT, onlyReplyOnAcceptingConnections);
<span style="font-weight: bold;"></span>
REMOTE_GAME_PORT should be whatever port the other system is running the application you care about on. onlyReplyOnAcceptingConnections is a boolean indicating if the other system should reply, even if they have no connections available for you to connect to.

Open systems will reply with ID_UNCONNECTED_PONG. From the sample:

```c++
if (p->data[0]==ID_UNCONNECTED_PONG)
{
    RakNet::TimeMS time;
    RakNet::BitStream bsIn(packet->data,packet->length,false);
    bsIn.IgnoreBytes(1);
    bsIn.Read(time);
    printf("Got pong from %s with time %i\n", p->systemAddress.ToString(), RakNet::GetTime() - time);</span>
}
```

<span style="font-weight: bold;"></span>
In order to send custom user data, call RakPeer::SetOfflinePingResponse(customUserData, lengthInBytes); RakNet will copy the data passed to it and return this data appended to ID_UNCONNECTED_PONG.
<span style="font-style: italic;">
Note: there is a hardcoded define MAX_OFFLINE_DATA_LENGTH in RakPeer.cpp limiting the length of your custom user data. Change this value and recompile if your data is larger than this define.
</span>
<span style="font-style: italic;">Advantages:</span>

*   You can join games automatically on program startup, no GUI or user interaction required
*   Best way to find games on the LAN

<span style="font-style: italic;">Disadvantages:</span>

*   Won't work for the general internet
*   Not as flexible as the [lightweight database plugin](lightweightdatabase.html)

<span class="RakNetBlueHeader">Option 3: Using the CloudServer/CloudClient plugins</span>

The [CloudServer/CloudClient](cloudcomputing.html) plugin can act as a directory server without modification.

<span style="font-style: italic;">Advantages:</span>

*   Customizable
*   You can subscribe to update notifications when memory has been updated from another system

<span style="font-style: italic;">Disadvantages:</span>

*   Only scales to a few hundred users
*   You have to host your own server

<span class="RakNetBlueHeader">Option 4: Using the Lobby server or RoomsPlugin</span>

If you are not using a service that already provides a lobby, on the PC we provide database code that has similar functionality. The lobby server provides a database driven service for players to interact and start games. It provides features such as friends, matchmaking, emails, ranking, instant messenging, quick match, rooms, and room moderation.

See the samples <span style="font-weight: bold;">Lobby2Server_PGSQL</span> and <span style="font-weight: bold;">Lobby2Client</span> for a demonstration of how to use this feature.

<span style="font-style: italic;">Advantages:</span>

*   The most flexible solution for players to join games
*   Allows users to interact before starting games
*   Builds community
*   Supports multiple titles

<span style="font-style: italic;"><span style="font-style: italic;">Disadvantages:
</span></span>

*   Requires a separate, dedicated server to host the plugin, and the server must have database support
*   Feature is relatively large and complex compared to a simple game listing, requiring a good investment in time and programming

<span class="RakNetBlueHeader">Option 5: MasterServer2</span>

We host a master server for our customers. See [this page](http://masterserver2.raknet.com/) for more details.

<span style="font-style: italic;">Advantages:</span>

*   Fast
*   Easy to use
*   You do not have to host a server

<span style="font-style: italic;">Disadvantages:
</span>

*   Special licensing if you need the server sources

<span class="RakNetBlueHeader">Initiate connection attempt<span style="font-weight: normal;">

</span></span>Once you know the IP address of the remote system(s) to connect to, use RakPeerInterface::Connect() to initiate an <span style="font-style: italic;">asynchronous</span> connection attempt. The parameters to connect are:

<span class="RakNetCode">ConnectionAttemptResult Connect( const char* host, unsigned short remotePort, const char *passwordData, int passwordDataLength, PublicKey *publicKey=0, unsigned connectionSocketIndex=0, unsigned sendConnectionAttemptCount=6, unsigned timeBetweenSendConnectionAttemptsMS=1000, RakNet::TimeMS timeoutTime=0 )</span>

*   host is an IP address, or domain name.
*   remotePort is the port that the remote system is listening on, which you passed to the Startup() function
*   passwordData is optional binary data to send with the connection request. If this data does not match what was passed to RakPeerInterface::SetPassword(), the remote system will reply with ID_INVALID_PASSWORD.
*   passwordDataLength is the length, in bytes, of passwordData
*   publicKey is the public key parameter that was passed to InitializeSecurity() on the remote system. If you don't use security, pass 0.
*   connectionSocketIndex is the index into the array of socket descriptors passed to socketDescriptors in RakPeer::Startup() to determine the one to send on.
*   sendConnectionAttemptCount is how many datagrams to send before giving up as unable to connect. This is also used for MTU detection, with 3 different MTU sizes. So the default of 12 means send each MTU size 4 times, which should be sufficient to tolerate any reasonable packetloss. Lower values mean that ID_CONNECTION_ATTEMPT_FAILED would be returned to you faster.
*   timeBetweenSendConnectionAttemptsMS is how many milliseconds to wait before sending another connection attempt. A good value is 4 times the expected ping.
*   timeoutTime is how many milliseconds to wait, for this particular connection, before dropping the remote system if a message cannot be delivered. The default value of 0 means use the global value from SetTimeoutTime().

Connect() will return CONNECTION_ATTEMPT_STARTED for a successful attempt, something else on failure.

<span style="font-style: italic;">Note: Connect() returning true does NOT mean you are connected. If successful the message ID_CONNECTION_REQUEST_ACCEPTED should be received. If not you will recieve one of the error messages.</span>

Connectivity messages returned as the first byte of the Packet::data structure

* **Connection closed**: ID_DISCONNECTION_NOTIFICATION, ID_CONNECTION_LOST
* **New connection**: ID_NEW_INCOMING_CONNECTION, ID_CONNECTION_REQUEST_ACCEPTED
* **Connection attempt failed**: ID_CONNECTION_ATTEMPT_FAILED, ID_REMOTE_SYSTEM_REQUIRES_PUBLIC_KEY, ID_OUR_SYSTEM_REQUIRES_SECURITY,  ID_PUBLIC_KEY_MISMATCH, ID_ALREADY_CONNECTED, ID_NO_FREE_INCOMING_CONNECTIONS, ID_CONNECTION_BANNED, ID_INVALID_PASSWORD, ID_INCOMPATIBLE_PROTOCOL_VERSION, ID_IP_RECENTLY_CONNECTED

## Troubleshooting ID_CONNECTION_ATTEMPT_FAILED

ID_CONNECTION_ATTEMPT_FAILED is the generic message meaning no communication was established with the remote system. Possible reasons include:

*   The IP address is wrong
*   That system is not running RakNet, or RakPeerInterface::Startup() was not called on that system
*   The remote system has started RakNet, but RakPeerInterface::SetMaximumIncomingConnections() was not called
*   A firewall on either system is blocking UDP packets on the port you have chosen
*   A router on the remote system is blocking incoming UDP packets on the port you have chosen. See the [NAT Punchthrough](natpunchthrough.html) plugin to resolve this.
*   On Windows Vista, the network driver security service pack sometimes breaks UDP, not just for RakNet, but in general, even for DirectPlay. This service pack should be rolled back, and not installed.
*   [Secure connections](secureconnections.html) are enabled, and your system failed the security check.
*   Your IP address was banned with RakPeerInterface::AddToBanList(). Note that some plugins, such as the [connection filter](connectionFilter.html), have the option to ban IP addresses automatically.

Assuming you are able to connect, it is time to go onto the section: [Creating Packets](creatingpackets.html)

## See Also

* [Index](index.html) [Connection Filter](connectionFilter.html) 
* [Creating Packets](creatingpackets.html) 
* [Lightweight Database plugin](lightweightdatabase.html) 
* [<span style="text-decoration: underline;">NAT Punchthrough plugin</span>](natpunchthrough.html) [Secure connections](secureconnections.html) 
* [FAQ](faq.html)