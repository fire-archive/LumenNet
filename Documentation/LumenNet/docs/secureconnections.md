<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ---------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Secure Connections
  ---------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Secure your network traffic</span>\       |
| \                                                                        |
| Once your online game reaches a certain popularity people will try to    |
| cheat. You will need to account for this both at the game layer and at   |
| the network layer. RakNet handles the network layer by providing secure  |
| connections if you wish to use them.                                     |
|                                                                          |
| RakNet provides data security on par with 256-bit TLS. An efficient      |
| 256-bit Elliptic Curve key agreement with forward secrecy protects each  |
| connection with the server.                                              |
| -   Cookies: Uses stateless cookie in the handshake, analogous to SYN    |
|     cookies, that ensures the remote IP address is not spoofed           |
| -   Efficient: Modern techniques published and improved in the last 2    |
|     years are employed to offer security without a performance penalty.  |
| -   Forward secrecy: Uses Tunnel Key Agreement "Tabby" protocol. If the  |
|     server is compromised at some point in the future, previously        |
|     exchanged data cannot be decrypted.                                  |
| -   Protection: Each message is encrypted and stamped with a message     |
|     authentication code (MAC) and unique identifier to protect sensitive |
|     data and prevent replays.                                            |
| -   Immune to active attacks (man-in-the-middle) if server key is known  |
|     ahead of time                                                        |
| -   Uses 256-bit Elliptic Curve Cryptography                             |
| -   Elliptic Curve: Over finite field Fp, p = 2\^n - c, c small\         |
|          Shape of curve: a' \* x\^2 + y\^2 = 1 + d' \* x\^2 \* y\^2, a'  |
|     = -1 (square in Fp)\                                                 |
|          d' (non square in Fp) -&gt; order of curve = q \* cofactor h,   |
|     order of generator point = q\                                        |
|          Curves satisfy MOV conditions and are not anomalous\            |
|          Point operations performed with Extended Twisted Edwards group  |
|     laws                                                                 |
|                                                                          |
| Secure connections add up to 11 bytes per packet and take time to        |
| compute so you may wish to limit usage to release mode.                  |
|                                                                          |
| <span class="RakNetBlueHeader">Usage:</span>                             |
|                                                                          |
| 1\. Add \#define LIBCAT\_SECURITY 1 to                                   |
| "NativeFeatureIncludesOverrides.h". Rebuild all.                         |
|                                                                          |
| 2\. Include "Source/SecureHandshake.h". **DO NOT INCLUDE ANY FILES FROM  |
| Source/cat**                                                             |
|                                                                          |
| 3\. Create the public and private keys in advance                        |
|                                                                          |
| <span class="RakNetCode">cat::EasyHandshake::Initialize()\               |
| cat::EasyHandshake handshake;\                                           |
| char public\_key\[cat::EasyHandshake::PUBLIC\_KEY\_BYTES\];\             |
| char private\_key\[cat::EasyHandshake::PRIVATE\_KEY\_BYTES\];\           |
| handshake.GenerateServerKey(public\_key, private\_key);</span>\          |
| \                                                                        |
| 4. Save the public and private keys to disk                              |
|                                                                          |
| fwrite(private\_key, sizeof(private\_key), 1, fp);\                      |
| fwrite(public\_key, sizeof(public\_key), 1, fp);                         |
|                                                                          |
| 5\. The server should load the public and private keys, and pass it to   |
| RakPeerInterface::InitializeSecurity(); Do not distribute the private    |
| key, this should remain secret.                                          |
|                                                                          |
| 6\. The client should load the public key. The public key should be      |
| distributed with the client application, or downloaded from a secure     |
| location. Pass the public key to RakPeerInterface::Connect()             |
|                                                                          |
| 7\. Connect the server to the client as usual.                           |
|                                                                          |
| Possible errors, returned in packet-&gt;data\[0\]:                       |
|                                                                          |
| **ID\_REMOTE\_SYSTEM\_REQUIRES\_PUBLIC\_KEY**: You didn't pass a public  |
| key to RakPeerInterface::Connect().\                                     |
| **ID\_OUR\_SYSTEM\_REQUIRES\_SECURITY**: You did pass a public key to    |
| RakPeerInterface::Connect(), but InitializeSecurity() was not called on  |
| the server.\                                                             |
| **ID\_PUBLIC\_KEY\_MISMATCH**: The public key on the client does not     |
| match the public key on the server.                                      |
|                                                                          |
| <span class="RakNetBlueHeader">Public key transmission:</span>           |
|                                                                          |
| You should generate the public key on a remote system in advance of      |
| trying to connect to that system. The reason is that the public key is   |
| used to identify the remote system, so you know the system that replied  |
| is the one you are actually trying to connect to. An attacker might know |
| the public key, but they wouldn't know the private key (which you keep   |
| secret) so they would not be able to establish a connection with you.\   |
| \                                                                        |
| For peer to peer, you should run a dedicated server, which itself is     |
| secure. Distribute the client with the public key to that server known   |
| in advance. Connect to that server, upload the peer's public key into a  |
| database, and then wait for incoming connections. Correspondingly, when  |
| a peer wants to connect, connect to that server, download the public key |
| for that peer, and use that public key for connections.                  |
|                                                                          |
| You can rent a discounted dedicated server from dx.net at                |
| <http://www.dx.net/raknet_dx.php>                                        |
|                                                                          |
| Alternate solutions:                                                     |
|                                                                          |
| 1.  You can use PHPDirectoryServer to pass the public keys. While not    |
|     secure, it will work with a PHP enabled webhost (typically \$5 to    |
|     \$10 a month) and it's more secure than option 2 which is            |
| 2.  In RakPeer::Connect, pass true for acceptAnyPublicKey for the        |
|     publicKey parameter. This is similar to RakNet version 3 where you   |
|     just pass 0 for each parameter for InitializeSecurity. In this case  |
|     it is not necessary to transmit the public key in advance.           |
|                                                                          |
| See the sample at *Samples\\Encryption* for a working example.           |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ----------------------
  [Index](index.html)\
  ----------------------


