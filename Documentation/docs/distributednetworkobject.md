![Oculus VR, Inc.](RakNetLogo.jpg)\
\
  ----------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Distributed Objects
  ----------------------------------------------------------

+--------------------------------------------------------------------------+
| Overview of the distributed network object system\                       |
| \                                                                        |
| The distributed network object system is the highest level layer over    |
| RakNet. The concept is simple: objects that are instantiated on one      |
| system are instantiated on all systems. Objects that are destroyed on    |
| one system are destroyed on all systems. Tagged memory is matched        |
| between systems. When a new player connects, these objects are also      |
| created on his system.\                                                  |
| \                                                                        |
| This is very useful conceptually because it has a direct analogy to game |
| objects. For example, a one tank in a multiplayer game with twenty       |
| players actually has been instantiated twenty times. However, as far as  |
| the player is concerned there is only one tank. The player expects that  |
| the position, orientation, number of shells left, and amount of armor is |
| the same on all systems.\                                                |
| \                                                                        |
| Traditionally, to maintain a tank you would have to craft a series of    |
| custom packets for the tank. One packet to describe position, another    |
| packet for the tank to shoot, and another to have the tank take damage.  |
| Using the distributed network object system, you can synchronize the     |
| tank, those 3 member variables, and everything matches automatically.\   |
| \                                                                        |
| The distributed object system has both strengths and weaknesses.\        |
| \                                                                        |
| **Strengths**                                                            |
| -   Implementation only takes a minute and once it works it              |
|     is foolproof.                                                        |
| -   You don't have to worry about sending game data to new players.      |
| -   You don't have to worry about game objects getting out of synch.     |
| -   You don't care about the complexity of interactions between objects  |
|     because you always get the correct final result.                     |
| -   It is easy to network existing single player games.                  |
| -   Interpolation is built-in.                                           |
|                                                                          |
| \                                                                        |
| **Weaknesses**                                                           |
| -   Timestamping is not supported so you can't extrapolate position.     |
| -   Tracking the results of actions is less accurate than sending        |
|     triggers that cause actions.                                         |
| -   Wasteful of bandwidth for predictable actions. For example, if a     |
|     rocket shoots 20 cans this system requires 20 objects to receive     |
|     data over time as the cans fall. With a packet you could describe    |
|     only the rocket when it was launched and hence only one do one send. |
|     The cans would also fall precisely assuming the physics              |
|     is repeatable.                                                       |
| -   Doesn't currently support arrays or pointers, although with arrays   |
|     you can get around this by synchronizing each element or enclosing   |
|     it in a structure.                                                   |
|                                                                          |
| Despite these weaknesses, this is the primary system in use by many      |
| games.\                                                                  |
| \                                                                        |
| How to implement the distributed object system\                          |
| \                                                                        |
| Before you can use the distributed object system, you have to register   |
| your instance of RakClient and/or RakServer with the Distributed Network |
| Object Manager.\                                                         |
| \                                                                        |
| DistributedNetworkObjectManager::Instance()-&gt;RegisterRakClientInterfa |
| ce(rakClient);\                                                          |
| DistributedNetworkObjectManager::Instance()-&gt;RegisterRakServerInterfa |
| ce(rakServer);\                                                          |
| \                                                                        |
| The multiplayer class will automatically handle distributed object       |
| network messages. If you don't use the multiplayer class, you must       |
| handle these packet types yourself:\                                     |
| \                                                                        |
| ID\_UPDATE\_DISTRIBUTED\_NETWORK\_OBJECT\                                |
| ID\_DISTRIBUTED\_NETWORK\_OBJECT\_CREATION\_ACCEPTED\                    |
| ID\_DISTRIBUTED\_NETWORK\_OBJECT\_CREATION\_REJECTED\                    |
| \                                                                        |
| You would pass them to the DistributedNetworkObjectManager in exactly    |
| the same fashion as is done in Multiplayer.h.\                           |
| \                                                                        |
| Once that is done, then you have several steps per class.                |
| 1.  Add *\#include "DistributedNetworkObjectHeader.h"* to the header     |
|     file for your class.                                                 |
| 2.  The basemost class should derive from *DistributedNetworkObject*     |
| 3.  If you plan to instantiate this class, then add                      |
|     *REGISTER\_DISTRIBUTED\_CLASS(ClassName)* in main() or Winmain(),    |
|     with the name of your class or a unique identifier                   |
|     replacing ClassName.                                                 |
| 4.  Once per game cycle call                                             |
|     *objectInstance-&gt;UpdateDistributedObject(ClassName)* where        |
|     objectInstance is the instance of your class and ClassName is the    |
|     name of the class or a unique identifier replacing ClassName that    |
|     matches the unique identifier passed                                 |
|     to REGISTER\_DISTRIBUTED\_CLASS.                                     |
|                                                                          |
| For example, if you want every instance of Tank to match among all       |
| systems then you would do the following:\                                |
| \                                                                        |
| \#include "DistributedNetworkObjectHeader.h"\                            |
| \                                                                        |
| class Tank : public DistributedNetworkObject\                            |
| {\                                                                       |
| // Your data and functions here\                                         |
| // ...\                                                                  |
| \                                                                        |
| // The update function for the class is a good place to put              |
| UpdateDistributedObject\                                                 |
| void Update(void) {UpdateDistributedObject("Tank");}\                    |
| };\                                                                      |
| \                                                                        |
| REGISTER\_DISTRIBUTED\_CLASS(Tank);\                                     |
| \                                                                        |
| \                                                                        |
| How to implement synchronized member variables within the distributed    |
| object system\                                                           |
| \                                                                        |
| That tank is nice but would be a lot more useful if we had the data      |
| members synchronized automatically as well. There are two ways to do     |
| that:                                                                    |
| 1.  REGISTER\_X\_DISTRIBUTED\_OBJECT\_MEMBERS preprocessor macro.        |
| 2.  SynchronizeMemory function                                           |
|                                                                          |
| The advantage of the REGISTER\_X\_DISTRIBUTED\_OBJECT\_MEMBERS macro is  |
| that you can perform automatic interpolation on data elements and it     |
| requires only one line of code in your header file for all members. The  |
| disadvantages are that the declaration must match on all systems,        |
| variables cannot be added at runtime, and it doesn't support pointers or |
| arrays.\                                                                 |
| \                                                                        |
| The advantage of the SynchronizeMemory function is that you can add      |
| elements at runtime, members do not have to match, and it can support    |
| anything. The disadvantages are that it cannot perform interpolation, is |
| more susceptible to user error, and requires one line of code in your    |
| cpp file per variable.\                                                  |
| \                                                                        |
| The REGISTER\_X\_DISTRIBUTED\_OBJECT\_MEMBERS macro\                     |
| \                                                                        |
| To use REGISTER\_X\_DISTRIBUTED\_OBJECT\_MEMBERS, in the public section  |
| of the class definition add a macro that takes the following form:\      |
| \                                                                        |
| REGISTER\_X\_DISTRIBUTED\_OBJECT\_MEMBERS(BaseClass,\                    |
| SynchronizationMethod, AuthoritativeNetwork, VariableType,               |
| VariableName,\                                                           |
| ...\                                                                     |
| )\                                                                       |
| \                                                                        |
| The first parameter is in *REGISTER\_X\_DISTRIBUTED\_OBJECT\_MEMBERS*.   |
| Replace that X with however many member variables you are                |
| synchronizing.\                                                          |
| For example, if you want to synch 3 member variables then you would      |
| instead write *REGISTER\_3\_DISTRIBUTED\_OBJECT\_MEMBERS*.\              |
| \                                                                        |
| The second parameter, *BaseClass* is the name of the class your class    |
| derives from. As we specified earlier, you must derive from              |
| DistributedNetworkObject in the basemost class so this always has a      |
| value. If you had Apple derive from Fruit derive from                    |
| DistributedNetworkObject then the first parameter for                    |
| REGISTER\_X\_DISTRIBUTED\_OBJECT\_MEMBERS for Apple would be Fruit, and  |
| for Fruit it would be DistributedNetworkObject.\                         |
| \                                                                        |
| The third parameter is a set of parameters - SynchronizationMethod,      |
| AuthoritativeNetwork, VariableType, and VariableName.\                   |
| \                                                                        |
| *SynchronizationMethod* takes one of the following values:               |
| -   *DOM\_COPY\_UNCOMPRESSED*\                                           |
|     This means send the data without [bitstream                          |
|     compression](bitstreams.html) and when a new value arrives on a      |
|     system, just copy over the old value. This is useful for data such   |
|     as player health, stored in a unsigned char and going from 0 to 200. |
| -   *DOM\_COPY\_COMPRESSED*\                                             |
|     Same as DOM\_COPY\_UNCOMPRESSED except use [bitstream                |
|     compression](bitstreams.html). Useful for values that stay near 0,   |
|     such as sending the score in a soccer game. As per the restrictions  |
|     with bitstream compression, this can only be used with native types  |
|     (char, int, short, long, float, bool).                               |
| -   *DOM\_INTERPOLATE\_UNCOMPRESSED*\                                    |
|     No compression and when the data arrives on the new system,          |
|     interpolate from the old value to the new value. Interpolation is    |
|     linear and and lasts for whatever value was passed to                |
|     DistributedNetworkObject::SetMaximumUpdateFrequency (default is      |
|     50 ms). If you overwrite the value while it is interpolating, the    |
|     interpolation will stop. Interpolation requires the +, -, \*, and =  |
|     operators to be defined.                                             |
| -   *DOM\_INTERPOLATE\_COMPRESSED*\                                      |
|     Same as DOM\_INTERPOLATE\_UNCOMPRESSED except that data is sent      |
|     using [bitstream compression](bitstreams.html). As per the           |
|     restrictions with bitstream compression, this can only be used with  |
|     native types (char, int, short, long, float, bool). Interpolation    |
|     requires the +, -, \*, and = operators to be defined.                |
|                                                                          |
| The rules on type bear repeating, because if you make a mistake you will |
| get a seemingly unrelated compile error:\                                |
| **My type is a**                                                         |
| -   *Mathematical native data type - bool, float, double, char, int,     |
|     long, short.* You can use DOM\_COPY\_UNCOMPRESSED,                   |
|     DOM\_COPY\_COMPRESSED, DOM\_INTERPOLATE\_UNCOMPRESSED,               |
|     or DOM\_INTERPOLATE\_COMPRESSED.                                     |
| -   *Nonnative data type but is mathematical, i.e. has +, -, \*, and =   |
|     overloaded, such as many vector classes.* You can use                |
|     DOM\_COPY\_UNCOMPRESSED or DOM\_INTERPOLATE\_UNCOMPRESSED.           |
| -   *Any regular data block (i.e. struct) as long as the data block does |
|     not contain pointers.* You can use DOM\_COPY\_UNCOMPRESSED.          |
| -   *Array.* You can either synchronize each element normally or can     |
|     enclose the array in a struct and send the struct. We'll try to find |
|     a better solution for this in a later release.                       |
| -   *Pointer.* Unsupported.                                              |
|                                                                          |
| *AuthoritativeNetwork* takes one of the following values:                |
| -   *DOM\_SERVER\_AUTHORITATIVE*\                                        |
|     The server is in charge of the variable. While a client can change   |
|     it, any changes will be overwritten the next time the server         |
|     changes it. This is what you would normally use for data such        |
|     as health.                                                           |
| -   *DOM\_CLIENT\_AUTHORITATIVE*\                                        |
|     The client(s) are in charge of the variable. While the server can    |
|     change it, any changes will be overwritten the next time an          |
|     authorized client changes it. By default, the client that created    |
|     the object is the only system authorized to change the client        |
|     authoritative members of that object. You can change the owner to    |
|     another client, or remove the owner by calling SetClientOwnerID. You |
|     will also want to call that function when the server creates an      |
|     object with client authoritative members and you want to assign an   |
|     owner to your new object. When there is no owner, multiple clients   |
|     can fight over the same data if you wish - although it doesn't make  |
|     much sense to do so.                                                 |
|                                                                          |
| *VariableType* is the type of the variable being synchronized. This must |
| match the type of the variable declaration and cannot be an array or a   |
| pointer.\                                                                |
| \                                                                        |
| *VariableName* must match the name of the variable being synchronized.\  |
| \                                                                        |
| These four parameters that compose the third set of parameters can be    |
| repeated as many times as you wish, up to the number of types the define |
| pattern was cut and paste in DistributedObjectNetworkHeader.h\           |
| \                                                                        |
| Here is our tank with two member variables synchronized:\                |
| \                                                                        |
| \#include "DistributedNetworkObjectHeader.h"\                            |
| \                                                                        |
| class Tank : public DistributedNetworkObject\                            |
| {\                                                                       |
| // Your data and functions here\                                         |
| // ...\                                                                  |
| \                                                                        |
| // The update function for the class is a good place to put              |
| UpdateDistributedObject\                                                 |
| void Update(void) {UpdateDistributedObject("Tank");}\                    |
| public:\                                                                 |
| float turrentAngle;\                                                     |
| Vector position;\                                                        |
| \                                                                        |
| REGISTER\_2\_DISTRIBUTED\_OBJECT\_MEMBERS(DistributedNetworkObject,\     |
| DOM\_INTERPOLATE\_COMPRESSED, DOM\_CLIENT\_AUTHORITATIVE, float,         |
| turrentAngle,\                                                           |
| DOM\_COPY\_UNCOMPRESSED, DOM\_SERVER\_AUTHORITATIVE, Vector, position)\  |
| };\                                                                      |
| \                                                                        |
| REGISTER\_DISTRIBUTED\_CLASS(Tank);\                                     |
| \                                                                        |
| **Additional notes**\                                                    |
| 1.  This is all done by the preprocessor so if you make a mistake you    |
|     will get a compile error rather than a run-time error.               |
| 2.  REGISTER\_X\_DISTRIBUTED\_OBJECT\_MEMBERS may not be written out as  |
|     many times as you have data members. If you have more members than I |
|     wrote out, you can add elements yourself. It follows a very          |
|     obvious pattern. Refer to the bottom                                 |
|     of DistributedNetworkObjectHeader.h. If anyone knows of a way to     |
|     automate this please let me know.                                    |
| 3.  If a data member is client authoritative, then you will get a        |
|     different value on creation depending on whether the client created  |
|     the object or the server did. If the client created the object, then |
|     the value propigated over the network will be whatever the client    |
|     set before the first call to UpdateDistributedObject. If the server  |
|     created the object, then the value propigated over the network will  |
|     be whatever the server set before the first call                     |
|     to UpdateDistributedObject. In this way, the server can force the    |
|     client to start with particular values, or the client can specify    |
|     which values to start with.                                          |
|                                                                          |
| The SynchronizeMemory function\                                          |
| \                                                                        |
| Synchronizing memory at runtime is possible with the SynchronizeMemory   |
| and related functions. The outcome is the same as with                   |
| REGISTER\_X\_DISTRIBUTED\_OBJECT\_MEMBERS. Here is how to use it with    |
| our tank example:\                                                       |
| \                                                                        |
| \#include "DistributedNetworkObjectHeader.h"\                            |
| \                                                                        |
| class Tank : public DistributedNetworkObject\                            |
| {\                                                                       |
| Tank() {SynchronizeMemory(0, &turrentAngle, sizeof(turrentAngle),        |
| false); SynchronizeMemory(1, &position, sizeof(position), true); }\      |
| \                                                                        |
| // Your data and functions here\                                         |
| // ...\                                                                  |
| \                                                                        |
| // The update function for the class is a good place to put              |
| UpdateDistributedObject\                                                 |
| void Update(void) {UpdateDistributedObject("Tank");}\                    |
| public:\                                                                 |
| float turrentAngle;\                                                     |
| Vector position;\                                                        |
| \                                                                        |
| };\                                                                      |
| \                                                                        |
| REGISTER\_DISTRIBUTED\_CLASS(Tank);\                                     |
| \                                                                        |
| This does the same as the code above. The first parameter is a unique    |
| unsigned char to identify the variable. The system will then expect all  |
| objects with synchronized memory that use that same value to match in    |
| size and type. The second parameter is the memory address of the         |
| variable. The third parameter is the size of the block to synchronize.   |
| The last parameter is true if you want the server to be the authority on |
| the object, false for the client to be the authority.\                   |
| \                                                                        |
| **Refer to                                                               |
| Samples\\CodeSamples\\DistributedNetworkObject\\DistributedNetworkObject |
| Sample.cpp                                                               |
| for an implementation example.**\                                        |
| \                                                                        |
| User functions of the DistributedNetworkObject\                          |
| \                                                                        |
| Call this every update cycle for every distributed object that you want  |
| updated over the network and to interpolate.\                            |
| classID should be a unique identifier for the class that matches the     |
| parameter to REGISTER\_DISTRIBUTED\_CLASS. The obvious choice is the     |
| name of the class - however you can use something shorter if you wish to |
| save a bit of bandwidth\                                                 |
| **virtual void UpdateDistributedObject(char \*classID, bool              |
| isClassIDEncoded=false);\                                                |
| **\                                                                      |
| Sets the maximum frequency with which memory synchronization packets can |
| be sent.\                                                                |
| Lower values increase granularity but require more bandwidth\            |
| **virtual void SetMaximumUpdateFrequency(unsigned long frequency);**\    |
| \                                                                        |
| Broadcasts a request to destroy an object on the network.                |
| OnDistrubtedObjectDestruction will be called.\                           |
| If you wish to block deletion, override OnDistributedObjectDestruction   |
| to not delete itself\                                                    |
| **virtual void DestroyObjectOnNetwork(void);**\                          |
| \                                                                        |
| Server only function -\                                                  |
| By default, when a client creates an object only it can update the       |
| client authoritative members of the class it creates. You can also set   |
| this manually with SetClientOwnerID\                                     |
| This function is called when a client that does not own an object tries  |
| to change any fields in that object\                                     |
| Return true to allow the update.\                                        |
| Return false (default) to not allow the update.\                         |
| **virtual bool AllowSpectatorUpdate(PlayerID sender);**\                 |
| \                                                                        |
| Tags memory to be synchronized. You can set the server or the client as  |
| the authority for this block.\                                           |
| Only the authority will write this memory to the network when it is      |
| changed.\                                                                |
| **void SynchronizeMemory(unsigned char memoryBlockIndex, void\*          |
| memoryBlock, int memoryBlockSize, bool serverAuthority);**\              |
| \                                                                        |
| Untags memory that was formerly synchronized.\                           |
| **void DesynchronizeMemory(unsigned char memoryBlockIndex);**\           |
| \                                                                        |
| Changes the authority for memory. You probably will never need this.\    |
| **void SetAuthority(unsigned char memoryBlockIndex, bool                 |
| serverAuthority);**\                                                     |
| \                                                                        |
| Tells you if a block of memory was formerly used. You probably will      |
| never need this.\                                                        |
| **bool IsMemoryBlockIndexUsed(unsigned char memoryBlockIndex);**\        |
| \                                                                        |
| Use this to set a maximum update frequency higher than what was          |
| specified to SetMaximumUpdateFrequency\                                  |
| Lower values have no effect.\                                            |
| **void SetMaxMemoryBlockUpdateFrequency(unsigned char memoryBlockIndex,  |
| int max);**\                                                             |
| \                                                                        |
| When object creation data is needed, WriteCreationData is called.\       |
| This function is for you to write any data that is needed to create or   |
| initialize the object on remote systems\                                 |
| **virtual void WriteCreationData(BitStream \*initialData);**\            |
| \                                                                        |
| When an object is created, ReadCreationData is called immediately after  |
| a successful call to OnDistributedObjectCreation\                        |
| This function is for you to read any data written from WriteCreationData |
| on remote systems. If the object is created by the client, this function |
| is also called by the creator of the object when sent back from the      |
| server in case the server overrode any settings\                         |
| **virtual void ReadCreationData(BitStream \*initialData);**\             |
| \                                                                        |
| When distributed data changes for an object, this function gets called.  |
| Default behavior is to do nothing. Override it if you want to perform    |
| updates when data is changed.\                                           |
| On the server it is also important to override this to make sure the     |
| data the client just sent you is reasonable.\                            |
| **virtual void OnNetworkUpdate(PlayerID sender);**\                      |
| \                                                                        |
| This is called when the object is created by the network. Return true to |
| accept the new object, false to reject it.\                              |
| The return value is primarily useful for the server to reject objects    |
| created by the client. On the client you would normally return true\     |
| senderID is the playerID of the player that created the object (or the   |
| server, which you can get from RakClientInterface::GetServerID)\         |
| *You must call the base class version of this function when              |
| overriding!*.\                                                           |
| **virtual bool OnDistributedObjectCreation(PlayerID senderID);**\        |
| \                                                                        |
| This is called when the object is destroyed by the network.\             |
| Default behavior is to delete itself. You can override this if you want  |
| to delete it elsewhere, or at a later time.\                             |
| If you don't delete the object, you should call DestroyObjectOnNetwork   |
| manually to remove it from the network.\                                 |
| Note it is important to override this on the server for objects you      |
| don't want clients to delete.\                                           |
| senderID is the playerID of the player that created the object (or the   |
| server, which you can get from RakClientInterface::GetServerID)\         |
| **virtual void OnDistributedObjectDestruction(PlayerID senderID);**\     |
| \                                                                        |
| This is called when the server rejects an object the client created.     |
| Default behavior is to destroy the object.\                              |
| You can override this to destroy the object yourself.\                   |
| **virtual void OnDistributedObjectRejection(void);**\                    |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ------------------------------------
  [Index](index.html)\
  [Bitstreams](bitstreams.html)\
  [Timestamping](timestamping.html)\
  ------------------------------------


