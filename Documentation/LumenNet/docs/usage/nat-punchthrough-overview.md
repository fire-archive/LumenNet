---
title: "NAT Punchthrough overview"
excerpt: ""
---
[Serbo-Croatian translation](http://science.webhostinggeeks.com/raknet-nat-punchthrough)
[block:api-header]
{
  "type": "basic",
  "title": "What is NAT?"
}
[/block]
NAT is short for network address translation. It is used by routers to map addresses behind the router to a single destination address, using different ports. For example, if you have two computers behind a router, but only one ISP, then both computers will use the same IP address, but with different source ports than what the application actually assigned. The router keeps a lookup table of what mappings it provides, so when a remote computer replies it is routed to the correct local computer behind the NAT.

The problem with NAT is that remote computers cannot initiate sends to local computers because no mapping yet exists. Therefore, if two computers both behind NAT try to connect, neither will be able to do so. This is a problem with voice communication, peer to peer games, or games where your users host and the host is behind a NAT. In the old days your users would have to go to their router configuration screen and setup a mapping. However, in modern applications users are not usually required to do this, thanks to NatPunchthrough.

<span class="RakNetBlueHeader">NAT Punchthrough Overview</span>

The NatPunchthroughClient.cpp plugin requires a user hosted server, not behind NAT, running NatPunchthroughServer.cpp that both clients can connect to. The server will find the external IP address of each client, and tell both clients to connect to that address at the same time. If that fails, each client will attempt to estimate the ports used by the other. If that fails, the process repeats once again, in case later port estimation opened a prior port. If that also fails, the plugin returns ID_NAT_PUNCHTHROUGH_FAILED.

Note 1: If you publish through Steam, we also provide [SteamLobby](steamlobby.html), which uses servers hosted by Valve, in which case NATPunchthrough is not necessary.  
Note 2: NAT Punchthrough is not necessary if exclusively using [IPV6](ipv6support.html).  
Note 3: If your game is client/server only, you may simply enforce that servers must support UPNP. See _DependentExtensions\miniupnpc-1.6.20120410_. Most routers support this these days, and assuming UPNP passes, anyone can connect to you.

<span class="RakNetBlueHeader">NAT Punchthrough Algorithm</span>

1.  Peer P1 wants to connect to peer P2, both of whom are connected to a third Non-NAT system, F
2.  Peer P1 calls OpenNAT() with the RakNetGUID (unique identifier) of P2 to F.
3.  F returns failure if P2 is not connected, or already attempting punchthrough to P1.
4.  F remembers busy state of P1 and P2\. If either P1 or P2 is busy, the request is pushed to a queue. Otherwise F requests most recently used external port from P1 and P2\. P1 and P2 are flagged as busy.
5.  If either P1 or P2 do not respond punchthrough fails with ID_NAT_TARGET_UNRESPONSIVE and the busy flag is unset. Otherwise, F sends timestamped connection message to P1 and P2 simultaneously.
6.  P1 and P2 act identically at this point. First, they send multiple UDP datagrams to each other's internal LAN addresses. They then try each other's external IP/port as seen by F. Ports are attempted sequentially, up to MAX_PREDICTIVE_PORT_RANGE.
7.  If at any point a datagram arrives from the remote peer, we enter state PUNCHING_FIXED_PORT. Datagrams are only sent to that IP/port combination the remainder of the algorithm. If our reply arrives on the remote system, the NAT is considered bidirectional and ID_NAT_PUNCHTHROUGH_SUCCEEDED is returned to the user.
8.  When NAT is open, or if we exhaust all ports, P1 and P2 send to F that they are ready for a new punchthrough attempt.

Algorithm effectivness depends on the NAT types involved. It will work with whichever NAT is the most permissive.

**Full cone NAT**: Accepts any datagrams to a port that has been previously used. Will accept the first datagram from the remote peer.

**Address-Restricted cone NAT**: Accepts datagrams to a port as long as the datagram source IP address is a system we have already sent to. Will accept the first datagram if both systems send simultaneously. Otherwise, will accept the first datagram after we have sent one datagram.

**Port-Restricted cone NAT**: Same as address-restricted cone NAT, but we had to send to both the correct remote IP address and correct remote port. The same source address and port to a different destination uses the same mapping.

**Symmetric NAT**: A different port is chosen for every remote destination. The same source address and port to a different destination uses a different mapping. Since the port will be different, the first external punchthrough attempt will fail. For this to work it requires port-prediction (MAX_PREDICTIVE_PORT_RANGE>1) and that the router chooses ports sequentially.

**Success Graph**
[block:parameters]
{
  "data": {
    "h-0": "Router Type",
    "0-0": "_Full cone NAT_",
    "1-0": "_Address-Restricted cone NAT_",
    "2-0": "_Port-Restricted cone NAT_",
    "3-0": "_Symmetric NAT_",
    "h-1": "Full cone NAT",
    "0-1": "YES",
    "1-1": "YES",
    "2-1": "YES",
    "3-1": "YES",
    "0-2": "YES",
    "h-2": "Address-Restricted cone NAT",
    "1-2": "YES",
    "2-2": "YES",
    "3-2": "YES",
    "h-3": "Port-Restricted cone NAT",
    "0-3": "YES",
    "1-3": "YES",
    "2-3": "YES",
    "3-3": "NO",
    "h-4": "Symmetric NAT",
    "0-4": "YES",
    "1-4": "YES",
    "2-4": "NO",
    "3-4": "NO"
  },
  "cols": 5,
  "rows": 4
}
[/block]
* NO may still connect if port estimation works, but can't be relied upon.
[block:api-header]
{
  "type": "basic",
  "title": "Client Implementation"
}
[/block]
1.  Create an instance of the plugin: <span class="RakNetCode">NatPunchthroughClient natPunchthroughClient;</span>
2.  Attach the plugin to an instance of RakPeerInterface: <span class="RakNetCode">rakPeer->AttachPlugin(&natPunchthroughClient);</span>
3.  Connect to the server, and wait for ID_CONNECTION_REQUEST_ACCEPTED. Use the following line to use the free server provided by RakNet: <span class="RakNetCode">rakPeer->Connect("natpunch.jenkinssoftware.com", 61111, 0, 0);</span>
4.  Call OpenNAT with the RakNetGUID (globally unique identifier) of the remote system that you want to connect to. In order to get the RakNetGUID, you would either have to transmit it with your own code on the server, upload it to the [PHPDirectoryServer](phpdirectoryserver.html), or use a plugin that stores it, such as [LightweightDatabase](lightweightdatabase.html): <span class="RakNetCode">natPunchthroughClient.OpenNAT(remoteGuid, serverSystemAddress);</span>. In order to read your own RakNetGUID, use <span class="RakNetCode">RakPeerInterface::GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS);</span>
5.  Wait a while. It may take over 10 seconds to try every possible port twice, although it often works within a couple of seconds. If you want to get text messages on what is happening, you can use <span class="RakNetCode">NatPunchthroughClient::SetDebugInterface()</span>
6.  ID_NAT_PUNCHTHROUGH_SUCCEEDED means the punchthrough succeeded, and you should be able to connect or send other messages to the remote system. Packet::SystemAddress is the address of the system you can now connect to. Any other ID_NAT_* means the punchthrough failed. See MessageIdentifiers.h for the list of codes and comments on each.
[block:api-header]
{
  "type": "basic",
  "title": "Server Implementation"
}
[/block]
1.  Host a server somewhere, not using NAT / e.g. behind a firewall. (RakNet provides a free one at 8.17.250.34:60481, however you may wish to host your own for consistent uptime).
2.  Create an instance of the plugin: <span class="RakNetCode">NatPunchthroughServer natPunchthroughServer;</span>
3.  Attach the plugin: <span class="RakNetCode">rakPeer->AttachPlugin(&natPunchthroughServer);</span>
4.  Don't forget to call <span class="RakNetCode">RakPeerInterface::Startup()</span> and <span class="RakNetCode">RakPeerInterface::SetMaximumIncomingConnections(MAX_CONNECTIONS);</span>
[block:api-header]
{
  "type": "basic",
  "title": "Using the NatPunchthrough class"
}
[/block]
See the sample _\Samples\NATCompleteClient_ and _\Samples\NATCompleteServer_
[block:api-header]
{
  "type": "basic",
  "title": "UDP Proxy"
}
[/block]
With some poor quality or homemade routers, it is possible that NAT punchthrough will not work. For example, a router that picks a new random port for each outgoing connection, and will only allow incoming connections to this port, will never work. This happens about 5% of the time. To handle this case, RakNet provides the UDPProxy system. Essentially, it uses a server that you run to route messages between the source and destination client transparently. This even works to route datagrams from games not using RakNet (though you need RakNet to setup the forwarding). The combination of NATPunchthrough and UDPProxy should enable any system to connect to any other system with a 100% success rate, provided you are willing to host enough proxy servers to forward all the traffic.

The UDP Proxy system uses 3 main classes:

*   **UDPProxyClient**: Makes requests of UDPProxyCoordinator to setup forwarding. This is the class the client runs.
*   **UDPProxyCoordinator**: Runs on the server that will get all requests from UDPProxyClient. Also, gets all logins from UDPProxyServer
*   **UDPProxyServer**: Actually does the UDP datagram forwarding, via a composite instance of UDPForwarder.cpp  

<span class="RakNetBlueHeader">Client Implementation</span>:

1.  Create an instance of the plugin: <span class="RakNetCode">UDPProxyClient udpProxyClient;</span>
2.  Derive a class from <span class="RakNetCode">RakNet::UDPProxyClientResultHandler</span> to get event notifications for the system.
3.  Attach the plugin to an instance of RakPeerInterface: <span class="RakNetCode">rakPeer->AttachPlugin(&udpProxyClient);</span>
4.  Call UDPProxyClient::SetResultHandler() on the class created in step 2.
5.  Try NATPunchthrough first. If you get ID_NAT_PUNCHTHROUGH_FAILED for the system that initiated NATPunchthrough, go to step 6\. Both systems will return ID_NAT_PUNCHTHROUGH_FAILED, however, only one system needs to start the proxy system.
6.  Call UDPProxyClient::RequestForwarding with the address of the coordinator, the address you want to forward from (UNASSIGNED_SYSTEM_ADDRESS for your own), the address you want to forward to, and how long to keep the forwarding active on no data. For example:  
    <span class="RakNetCode">SystemAddress coordinatorAddress;  
    coordinatorAddress.SetBinaryAddress("8.17.250.34");  
    coordinatorAddress.port=60481;  
    udpProxyClient.RequestForwarding(coordinatorAddress, UNASSIGNED_SYSTEM_ADDRESS, p->systemAddress, 7000);</span>
7.  Assuming you are connected to the coordinator, and the coordinator is running the plugin, your event handler class created in step 2 should get a callback within a second or two. <span class="RakNetCode">UDPProxyClientResultHandler::OnForwardingSuccess</span> will be returned if a UDPProxyServer has been assigned to forward datagrams from the source system specified in step 6, to the target system specified in step 6\. For example, to connect to the remote system use: <span class="RakNetCode">rakPeer->Connect(proxyIPAddress, proxyPort, 0, 0);</span>

If more than one server is available, and both source and target relay systems are running RakNet, then source and target will automatically ping all available servers. The servers will be attempted in order of lowest ping sum to highest. This is based on the assumption that the lowest ping sum gives you the server that has the shortest path between the two systems, and therefore the least lag.

<span class="RakNetBlueHeader">Coordinator Implementation</span>:

1.  Create an instance of the plugin: <span class="RakNetCode">UDPProxyCoordinator udpProxyCoordinator;</span>
2.  Attach the plugin to an instance of RakPeerInterface: <span class="RakNetCode">rakPeer->AttachPlugin(&udpProxyCoordinator);</span>
3.  Set the password on the coordinator for the servers to use <span class="RakNetCode">udpProxyCoordinator.SetRemoteLoginPassword(COORDINATOR_PASSWORD);</span>
4.  Don't forget to call <span class="RakNetCode">RakPeerInterface::Startup()</span> and <span class="RakNetCode">RakPeerInterface::SetMaximumIncomingConnections(MAX_CONNECTIONS);</span>

<span class="RakNetBlueHeader">Server Implementation</span>:

1.  Create an instance of the plugin: <span class="RakNetCode">UDPProxyServer udpProxyServer;</span>
2.  Attach the plugin to an instance of RakPeerInterface: <span class="RakNetCode">rakPeer->AttachPlugin(&udpProxyServer);</span>
3.  Connect to the coordinator
4.  Login to the coordinator. This can be done at runtime, so you can dynamically add more forwarding servers as your game is more popular.  
    <span class="RakNetCode">udpProxyServer.LoginToCoordinator(COORDINATOR_PASSWORD, coordinatorSystemAddress);</span>  
    If the coordinator plugin is on the same system as the server plugin, use:  
    <span class="RakNetCode">udpProxyServer.LoginToCoordinator(COORDINATOR_PASSWORD, rakPeer->GetInternalID(UNASSIGNED_SYSTEM_ADDRESS));</span>
5.  If you want to get callbacks as events occur (especially login failure) derive from <span class="RakNetCode">RakNet::UDPProxyServerResultHandler</span> and register your derived class with <span class="RakNetCode">UDPProxyServer::SetResultHandler()</span>

**State diagram with UDP Proxy**


[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/A5PZVmXQgajs6GXclxDQ",
        "natpunchpanel1.jpg",
        "600",
        "600",
        "#ad554b",
        ""
      ]
    }
  ]
}
[/block]

[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/6hQYw28RZullkEMZ2Wfq",
        "natpunchpanel2.jpg",
        "600",
        "600",
        "#b35845",
        ""
      ]
    }
  ]
}
[/block]

[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/ugV8tuhNTXmtewqdcjvy",
        "natpunchpanel3.jpg",
        "600",
        "600",
        "#94785d",
        ""
      ]
    }
  ]
}
[/block]

[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/3tbxRlCTzSeCFxv2OdJA",
        "natpunchpanel4.jpg",
        "600",
        "600",
        "#a45d56",
        ""
      ]
    }
  ]
}
[/block]

[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/IBJyzN30Qy4kO0UxWsUA",
        "natpunchpanel5.jpg",
        600,
        600,
        "",
        ""
      ]
    }
  ]
}
[/block]

[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/XJ6GOkyuTmapCRrV2Xzk",
        "natpunchpanel7.jpg",
        "600",
        "600",
        "#7baa63",
        ""
      ]
    }
  ]
}
[/block]
Server hosting

[block:api-header]
{
  "type": "basic",
  "title": "Server requirements"
}
[/block]
1.  No network address translation.
2.  No firewall, or firewall opened on the appropriate ports.
3.  Static IP address. [Dynamic DNS](http://www.dyndns.com/) is one way to get around this requirement.
4.  Compile with __GET_TIME_64BIT if you want to run the server longer than a month without rebooting
5.  Enough bandwidth to handle all connections

<span class="RakNetBlueHeader">Commercial hosting solutions</span>

1.  [Hypernia](http://www.hypernia.com/)  
    Worldwide locations. Servers are individual machines. Starting at $150 a month

If you find more hosting solutions, 

<noscript>contact us (rakkar at jenkinssoftware dot com)</noscript>

and it'll be added to this list.  
[block:api-header]
{
  "type": "basic",
  "title": "See Also"
}
[/block]
[Index](index.html)  
[Cloud Hosting](cloudhosting.html)  
[IPV6 support](ipv6support.html)  
[NAT Traversal architecture](nattraversalarchitecture.html)  
[NAT type detection](nattypedetection.html)  
[SteamLobby](steamlobby.html)