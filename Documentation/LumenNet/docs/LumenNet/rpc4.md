<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  --------------------------------------------------
  ![](spacer.gif){width="8" height="1"}RPC4 Plugin
  --------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Call C functions on local and remote      |
| systems.</span>                                                          |
|                                                                          |
| RPC4 contains mappings between string identifiers for functions, and a   |
| pointer to those functions.                                              |
|                                                                          |
| **Registering functions:**                                               |
|                                                                          |
| To Register a function, use the RegisterSlot() or                        |
| RegisterBlockingFunction() members.                                      |
|                                                                          |
| void RegisterSlot(const char \*sharedIdentifier, void (                  |
| \*functionPointer ) ( RakNet::BitStream \*userData, Packet \*packet ),   |
| int callPriority);\                                                      |
| bool RegisterBlockingFunction(const char\* uniqueID, void (              |
| \*functionPointer ) ( RakNet::BitStream \*userData, RakNet::BitStream    |
| \*returnData, Packet \*packet ));                                        |
|                                                                          |
| The first parameter is a string representing that function. It can be    |
| the same as the name of the function. The second parameter is a pointer  |
| to the function to be called. If it is a blocking function, the          |
| parameter list also contains a BitStream to return data to the caller.   |
|                                                                          |
| The class RPC4GlobalRegistration can be used to register functions where |
| they are declared. For example:                                          |
|                                                                          |
| void CFunc1( RakNet::BitStream \*bitStream, Packet \*packet ) {}\        |
| RPC4GlobalRegistration cfunc1reg("CFunc1", CFunc1);                      |
|                                                                          |
| If you use RPC4GlobalRegistration extensively, you may need to change    |
| RPC4\_GLOBAL\_REGISTRATION\_MAX\_FUNCTIONS to a higher number in         |
| RakNetDefines.h                                                          |
|                                                                          |
| **Calling functions:**                                                   |
|                                                                          |
| Use the Signal() function to call a non-blocking function. Use the       |
| CallBlocking() function otherwise.                                       |
|                                                                          |
| void Signal(const char \*sharedIdentifier, RakNet::BitStream \*          |
| bitStream, PacketPriority priority, PacketReliability reliability, char  |
| orderingChannel, const AddressOrGUID systemIdentifier, bool broadcast,   |
| bool invokeLocal);\                                                      |
| bool CallBlocking( const char\* uniqueID, RakNet::BitStream \*           |
| bitStream, PacketPriority priority, PacketReliability reliability, char  |
| orderingChannel, const AddressOrGUID systemIdentifier, RakNet::BitStream |
| \*returnData );                                                          |
|                                                                          |
| Signal will call all functions registered with that identifier using     |
| RegisterSlot(), including potentially on the same system. CallBlocking() |
| will call a single function on a single system, registered with          |
| RegisterBlockingFunction(). CallBlocking() does not return until the     |
| remote system replies or the connection to that system is lost.          |
|                                                                          |
| See *Samples/RPC4* for a demonstration of this plugin                    |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [RPC3](RPC3Video.htm)[](readyevent.html)\                                |
+--------------------------------------------------------------------------+


