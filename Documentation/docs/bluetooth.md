![Oculus VR, Inc.](RakNet_Icon_Final-copy.jpg){width="150"
height="150"}\
\
  --------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Windows bluetooth integration
  --------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Can be supported in C using sockets and   |
| native libraries</span>\                                                 |
| \                                                                        |
| Bluetooth support is relatively easy to add.                             |
|                                                                          |
| 1.  Include "Ws2bth.h"                                                   |
| 2.  Modify socket calls in SocketLayer.cpp, refer to                     |
|     <http://msdn.microsoft.com/en-us/library/aa362928%28v=vs.85%29.aspx> |
| 3.  [Source                                                              |
|     example](http://www.winsocketdotnetworkprogramming.com/winsock2progr |
| amming/winsock2advancedotherprotocol4j.html)                             |
| 4.  There is also an [API from                                           |
|     Broadcom](http://www.broadcom.com/support/bluetooth/sdk.php) for     |
|     Windows although I'm not sure what the difference is between that    |
|     and the native Windows system calls.                                 |
+--------------------------------------------------------------------------+

  ------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Linux bluetooth integration
  ------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Can be supported in C using the BlueZ     |
| library</span>\                                                          |
| \                                                                        |
| Linux uses the [BlueZ](http://www.bluez.org) library to interface with   |
| Bluetooth devices. There is a great resource on BlueZ here:              |
| <http://people.csail.mit.edu/albert/bluez-intro/>.                       |
+--------------------------------------------------------------------------+

  ----------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Mac bluetooth integration
  ----------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Indirectly send through                   |
| IOBluetoothL2CAPChannelRef?</span>\                                      |
| \                                                                        |
| [Mac Bluetooth                                                           |
| support](http://developer.apple.com/library/mac/documentation/DeviceDriv |
| ers/Conceptual/Bluetooth/Bluetooth.pdf)                                  |
| is supported through the IOBluetooth library, written in Objective-C. C  |
| equivalents are available by suffixing Ref to the name, for example      |
| IOBluetoothObjectRef contains the interface in C. You are expected to    |
| create instances of                                                      |
| [IOBluetoothL2CAPChannel](http://developer.apple.com/library/mac/#docume |
| ntation/DeviceDrivers/Reference/IOBluetooth/IOBluetoothL2CAPChannel_h/Cl |
| asses/IOBluetoothL2CAPChannel/)                                          |
| which represent a communication channel. L2CAP is an unreliable          |
| communications channel. The equivalent reliable communications channel   |
| uses                                                                     |
| [RFCOMM](http://developer.apple.com/library/mac/#documentation/DeviceDri |
| vers/Reference/IOBluetooth/IOBluetoothRFCOMMChannel_h/Classes/IOBluetoot |
| hRFCOMMChannel/index.html)                                               |
| [The full framework of                                                   |
| methods](http://developer.apple.com/library/mac/#documentation/DeviceDri |
| vers/Reference/IOBluetooth/)                                             |
| It doesn't appear to be possible to get direct socket access to          |
| Bluetooth on the Mac. However, it may be possible to use RakNet and      |
| IOBluetoothL2CAPChannel together by using RakNet's                       |
| SocketLayer::SetSocketLayerOverride(), and thereby changing RakNet's     |
| sendto and recvfrom calls to use IOBluetoothL2CAPChannel instead.        |
+--------------------------------------------------------------------------+

  -------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}iPhone bluetooth integration
  -------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Bluetooth exposed through Gamekit</span>\ |
| \                                                                        |
| The only interface for Bluetooth communications is through the higher    |
| level framework                                                          |
| [GameKit](http://developer.apple.com/library/ios/#documentation/Networki |
| ngInternet/Conceptual/GameKit_Guide/Introduction/Introduction.html).     |
| Gamekit uses Objective-C.                                                |
|                                                                          |
| Similar to the Mac, it may be possible to indirectly send through RakNet |
| using SocketLayer::SetSocketLayerOverride() through the                  |
| [sendData:toPeers](http://developer.apple.com/library/ios/#documentation |
| /GameKit/Reference/GKSession_Class/Reference/Reference.html#//apple_ref/ |
| occ/instm/GKSession/sendData:toPeers:withDataMode:error:)                |
| method exposed by GKSession, and sending that data unreliabily.          |
+--------------------------------------------------------------------------+

  --------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Android bluetooth integration
  --------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">BlueZ used for underlying support,        |
| however not accessible to implementation</span>\                         |
|                                                                          |
| -   Android uses BlueZ (w/ l2cap, etc.) as the underlying Bluetooth API  |
|     (at the Linux OS level, underneath the Android Dalvik VM). All of    |
|     the Android SDK (Java) Bluetooth classes end up using this API. The  |
|     Android NDK cross-compiler provides access to many of the Android    |
|     system's underlying libraries. However, Bluetooth does NOT appear to |
|     be exposed by the NDK. I.e.: The NDK's headers do not include        |
|     Bluetooth-specific headers, tokens, etc. (I performed a              |
|     find-in-files on the NDK headers and other files for various         |
|     Bluetooth related/specific tokens like: BTPROTO\_RFCOMM,             |
|     l2cap, etc.)                                                         |
| -   For a list of supported native libraries, see:                       |
|     <http://developer.android.com/sdk/ndk/overview.html>                 |
| -   There is indication in the forums and stackoverflow that Bluetooth   |
|     cannot be accessed directly via the NDK (see:                        |
|     <http://groups.google.com/group/android-ndk/browse_thread/thread/bd0 |
| 834426b4264b9>                                                           |
|     and                                                                  |
|     <http://groups.google.com/group/android-ndk/browse_thread/thread/a2e |
| 3b5133f4a7a4b>                                                           |
|     and                                                                  |
|     <http://groups.google.com/group/android-ndk/msg/fe9b846a7ee37ba5>    |
|     and accepted answer at                                               |
|     <http://stackoverflow.com/questions/4205468/create-an-android-rfcomm |
| -socket-without-any-input-from-the-user-how>)                            |
| -   It looks like Bluetooth support via the NDK was possible at one      |
|     point via a hack involving the HTC released BlueZ sources:           |
|     <http://blog.blackwhale.at/2009/08/android-bluetooth-on-steroids-wit |
| h-the-ndk-and-bluez/>                                                    |
| -   A possible work around is to use the Android SDK's Java Bluetooth    |
|     libraries for discovery, establishing connections, etc. and          |
|     delegating the actual communications streams to RakNet by passing    |
|     the in/out streams to RakNet via a JNI bridge.                       |
+--------------------------------------------------------------------------+

  -----------
   See Also
  -----------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [Autopatcher](autopatcher.html)\                                         |
| [CloudComputing](cloudcomputing.html)\                                   |
| [ConnectionGraph2](connectiongraph.html)\                                |
| [CrashReporter](crashreporter.html)\                                     |
| [ReplicaManager3](replicamanager3.html)\                                 |
| [FullyConnectedMesh2](fullyconnectedmesh2.html)\                         |
| [NATPunchthrough](natpunchthrough.html)\                                 |
| [PacketLogger](packetlogger.html)\                                       |
| [ReadyEvent](readyevent.html)\                                           |
| [RPC3](RPC3Video.htm)\                                                   |
| [TeamBalancer](teambalancer.html)\                                       |
| [SQLite3LoggerPlugin](sqlite3loggerplugin.html)                          |
| [](packetlogger.html)\                                                   |
+--------------------------------------------------------------------------+


