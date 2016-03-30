<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -------------------------
   TCP Interface Overview
  -------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Connect to Telnet, HTTP servers, mail     |
| servers, or other</span>\                                                |
| \                                                                        |
| TCPInterface, found at TCPInterface.h, is a utility class designed to    |
| connect using the TCP protocol in cases where this is necessary. The     |
| connection process is similar to RakPeerInterface.h, with the exception  |
| that Receive() returns the actual data received, the first byte does not |
| contain any specific identifiers.                                        |
|                                                                          |
| To get connection status updates, use HasNewConnection() and             |
| HasLostConnection()                                                      |
|                                                                          |
| There is no sample that uses the TCPInterface class specifically, but    |
| TelnetTransport.cpp is a good place to look for a reference.             |
|                                                                          |
| **Functions:**                                                           |
|                                                                          |
| // Starts the TCP server on the indicated port\                          |
| <span class="RakNetCode">bool Start(unsigned short port, unsigned short  |
| maxIncomingConnections);</span>                                          |
|                                                                          |
| // Stops the TCP server\                                                 |
| <span class="RakNetCode">void Stop(void);</span>                         |
|                                                                          |
| // Connect to the specified host on the specified port\                  |
| <span class="RakNetCode">SystemAddress Connect(const char\* host,        |
| unsigned short remotePort);</span>                                       |
|                                                                          |
| // Sends a byte stream\                                                  |
| <span class="RakNetCode">void Send( const char \*data, unsigned length,  |
| SystemAddress systemAddress );</span>                                    |
|                                                                          |
| // Returns data received\                                                |
| <span class="RakNetCode">Packet\* Receive( void );</span>                |
|                                                                          |
| // Disconnects a player/address\                                         |
| <span class="RakNetCode">void CloseConnection( SystemAddress             |
| systemAddress );</span>                                                  |
|                                                                          |
| // Deallocates a packet returned by Receive\                             |
| <span class="RakNetCode">void DeallocatePacket( Packet \*packet          |
| );</span>                                                                |
|                                                                          |
| // Queued events of new connections\                                     |
| <span class="RakNetCode">SystemAddress HasNewConnection(void);</span>    |
|                                                                          |
| // Queued events of lost connections\                                    |
| <span class="RakNetCode">SystemAddress HasLostConnection(void);</span>   |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [TCP                                                                     |
| (Wikipedia)](http://en.wikipedia.org/wiki/Transmission_Control_Protocol) |
| \                                                                        |
| [Email Sender](emailsender.html)\                                        |
+--------------------------------------------------------------------------+


