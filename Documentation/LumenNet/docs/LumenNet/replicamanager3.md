<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ----------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Replica Manager 3 Plugin Interface Implementation
  ----------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Replica Manager 3 Implementation          |
| Overview</span>\                                                         |
|                                                                          |
| Any game that has objects that are created and destroyed while the game  |
| is in progress, almost all non-trivial games, faces a minimum of 3       |
| problems:                                                                |
|                                                                          |
| -   How to broadcast existing game objects to new players                |
| -   How to broadcast new game objects to existing players                |
| -   How to broadcast deleted game objects to existing players            |
|                                                                          |
| Additional potential problems, depending on complexity and optimization  |
|                                                                          |
| -   How to create and destroy objects dynamically as the player moves    |
|     around the world                                                     |
| -   How to allow the client to create objects locally when this is       |
|     necessary right away for programming or graphical reasons (such as   |
|     shooting a bullet).                                                  |
| -   How to update objects as they change over time                       |
|                                                                          |
| The solution to most of these problems is usually straightforward, yet   |
| still requires a significant amount of work and debugging, with several  |
| dozen lines of code per object.                                          |
|                                                                          |
| ReplicaManager3 is designed to be a generic, overridable plugin that     |
| handles as many of these details as possible automatically.              |
| ReplicaManager3 automatically creates and destroys objects, downloads    |
| the world to new players, manages players, and automatically serializes  |
| as needed. It also includes the advanced ability to automatically relay  |
| messages, and to automatically serialize your objects when the           |
| serialized member data changes.                                          |
|                                                                          |
| **Order of operations:**                                                 |
|                                                                          |
| Objects are remotely created in the order they are registered using      |
| ReplicaManager3::Reference(). All objects created or destroyed in a tick |
| are created or destroyed in the same packet, meaning all calls to        |
| construct or destroy objects are triggered by the same                   |
| RakPeerInterface::Receive() call.                                        |
|                                                                          |
| Serialize() happens after construction. Therefore, all objects will be   |
| created and will have DeserializeConstruction() called before any        |
| Serialize() call happens for any of the objects created that update      |
| tick. Unlike construction, Serialize() calls may be spread out over      |
| multiple calls to RakPeerInterface::Receive() call depending on          |
| bandwidth availability. Therefore, be sure that you send all data        |
| necessary for the object to be properly setup in the initial             |
| SerializeConstruction() call, since it is not guaranteed you will        |
| receive Deserialize() on the same tick.                                  |
|                                                                          |
| The first time objects are sent to a remote system, you will get the     |
| Connection\_RM3::DeserializeOnDownloadComplete() once all objects have   |
| been constructed and Deserialized().                                     |
|                                                                          |
| **Dependency resolution:**                                               |
|                                                                          |
| If one object refers to another (for example, a gun has a pointer to its |
| owner) then the dependent objects need to be created first. In the case  |
| of a gun with a pointer to its owner, the owner would be created first.  |
| The gun would serialize the NetworkID of the owner, and lookup the owner |
| in its DeserializeConstruction call. This can be achieved by registering |
| the objects in that order using ReplicaManager3::Reference().            |
|                                                                          |
| Sometimes you have dependency chains that cannot be resolved through     |
| reordering. For example, a player has an inventory list, and each item   |
| in the inventory has a pointer to its owner. Or you may have a circular  |
| chain, where A depends on B, B depends on C, and C depends on A. Or it   |
| may not be feasable to reorder the objects. For these cases, you can     |
| resolve dependencies in the Replica3::PostDeserializeConstruction()      |
| callback. PostDeserializeConstruction() is called after                  |
| DeserializeConstruction() completes for all objects in a given update    |
| tick, so all objects that are going to be created will have been created |
| by then.                                                                 |
|                                                                          |
| **Static Objects:**                                                      |
|                                                                          |
| Sometimes you have an object that already exists in the world and is     |
| known to all systems. For example, a door on level load. In those        |
| situations you usually do not want the server to transmit the object     |
| creation message, since it would result in the same door twice. Yet you  |
| still want to reference and serialize the object, such as the door       |
| opening and closing, or the remaining health for the door.               |
|                                                                          |
| 1.  Derive your object from Replica3                                     |
| 2.  BEFORE calling replicaManager3-&gt;Reference() on the object, call   |
|     replica3Object-&gt;SetNetworkIDManager(replicaManager3-&gt;GetNetwor |
| kIDManager());                                                           |
| 3.  BEFORE calling replicaManager3-&gt;Reference() on the object, call   |
|     replica3Object-&gt;SetNetworkID(unique64BitIDLoadedWithLevel);       |
| 4.  return RM3CS\_ALREADY\_EXISTS\_REMOTELY from QueryConstruction()     |
|     from the host/server. Otherwise                                      |
|     return RM3CS\_ALREADY\_EXISTS\_REMOTELY\_DO\_NOT\_CONSTRUCT.         |
|     Alternatively, use QueryConstruction\_PeerToPeer() with              |
|     R3P2PM\_STATIC\_OBJECT\_CURRENTLY\_AUTHORITATIVE                     |
|     or R3P2PM\_STATIC\_OBJECT\_NOT\_CURRENTLY\_AUTHORITATIVE.            |
| 5.  WriteAllocationID(),                                                 |
|     SerializeConstruction(), DeserializeConstruction() are not used for  |
|     static objects, and can have empty implementations.                  |
| 6.  If the object should also never be destroyed over the network,       |
|     Implement QueryActionOnPopConnection(), to                           |
|     return RM3AOPC\_DO\_NOTHING. SerializeDestruction(),                 |
|     DeserializeDestruction(), DeallocReplica() can have                  |
|     empty implementations.                                               |
| 7.  Return whatever you want from QueryRemoteConstruction(), as it will  |
|     not be called                                                        |
| 8.  Implement QuerySerialization() to return RM3QSR\_CALL\_SERIALIZE     |
|     from the system that serializes the object, typically the peer to    |
|     peer host or the server. If a system is not currently but can later  |
|     become a host, such as for peer to peer with host migration,         |
|     return RM3QSR\_DO\_NOT\_CALL\_SERIALIZE. Otherwise                   |
|     return RM3QSR\_NEVER\_CALL\_SERIALIZE. Alternatively,                |
|     use QuerySerialization\_PeerToPeer() with                            |
|     R3P2PM\_STATIC\_OBJECT\_CURRENTLY\_AUTHORITATIVE                     |
|     or R3P2PM\_STATIC\_OBJECT\_NOT\_CURRENTLY\_AUTHORITATIVE.            |
| 9.  Write to the BitStream in SerializeConstructionExisting() your       |
|     one-time initialization data, and read it                            |
|     in DeserializeConstructionExisting(). This function is called if and |
|     only if QueryConstruction returns RM3CS\_ALREADY\_EXISTS\_REMOTELY.  |
| 10. Write per-tick serialization data in Serialize(), and read it        |
|     in Deserialize().                                                    |
|                                                                          |
| RM3CS\_ALREADY\_EXISTS\_REMOTELY causes ReplicaManager3 to consider the  |
| door to exist on the other system, so when Serialize() is called updates |
| will still be sent to that system. But the SerializeConstruction() call  |
| and object creation is skpped.                                           |
|                                                                          |
| <span class="RakNetBlueHeader">Combining with                            |
| FullyConnectedMesh2</span>\                                              |
|                                                                          |
| If you are using [FullyConnectedMesh2](fullyconnectedmesh2.html) for     |
| host determination and ReplicaManager3 relies on a host, then you have   |
| to delay calling AddParticipant() until a host has been determined. Here |
| is how to do so:                                                         |
|                                                                          |
| 1.  <span                                                                |
|     class="RakNetCode">replicaManager3-&gt;SetAutoManageConnections(fals |
| e,                                                                       |
|     \[false or true, depends on your preference\]);</span>               |
| 2.  <span                                                                |
|     class="RakNetCode">fullyConnectedMesh2-&gt;SetAutoparticipateConnect |
| ions(false);</span> (optional)                                           |
| 3.  Start connections to all remote systems                              |
| 4.  On ID\_CONNECTION\_REQUEST\_ACCEPTED or                              |
|     ID\_NEW\_INCOMING\_CONNECTION, execute:\                             |
|     <span class="RakNetCode"> // Add mid-game joins to ReplicaManager3   |
|     as long as we know who the host is\                                  |
|     if                                                                   |
|     (fullyConnectedMesh2-&gt;GetConnectedHost()!=UNASSIGNED\_RAKNET\_GUI |
| D)\                                                                      |
|     {\                                                                   |
|     bool success =                                                       |
|     replicaManager3-&gt;PushConnection(replicaManager3-&gt;AllocConnecti |
| on(packet-&gt;systemAddress,                                             |
|     packet-&gt;guid));\                                                  |
|     RakAssert(success);\                                                 |
|     }\                                                                   |
|     </span>                                                              |
| 5.  On ID\_FCM2\_NEW\_HOST execute:\                                     |
|     <span class="RakNetCode">BitStream bsIn(packet-&gt;data,             |
|     packet-&gt;length, false);\                                          |
|     bsIn.IgnoreBytes(sizeof(MessageID));\                                |
|     RakNetGUID oldHost;\                                                 |
|     bsIn.Read(oldHost);\                                                 |
|     if (oldHost==UNASSIGNED\_RAKNET\_GUID)\                              |
|     {\                                                                   |
|     // First time calculated host. Add existing connections to           |
|     ReplicaManager3\                                                     |
|     AddFullyConnectedMesh2ParticipantsToReplicaManager3();\              |
|     }</span>                                                             |
| 6.  <span class="RakNetCode"> void                                       |
|     AddFullyConnectedMesh2ParticipantsToReplicaManager3(void)\           |
|     {\                                                                   |
|     {\                                                                   |
|     DataStructures::List participantList;\                               |
|     fullyConnectedMesh2-&gt;GetParticipantList(participantList);\        |
|     for (unsigned int i=0; i &lt; participantList.Size(); i++)\          |
|     {\                                                                   |
|     Connection\_RM3 \*connection =                                       |
|     replicaManager3-&gt;AllocConnection(rakPeer-&gt;GetSystemAddressFrom |
| Guid(participantList\[i\]),                                              |
|     participantList\[i\]);\                                              |
|     if (replicaManager3-&gt;PushConnection(connection)==false)\          |
|     replicaManager3-&gt;DeallocConnection(connection);\                  |
|     }\                                                                   |
|     };\                                                                  |
|     </span>                                                              |
|                                                                          |
| *Explanation:*                                                           |
|                                                                          |
| Line 1, the first parameter to                                           |
| Replicamanager3::SetAutoManageConnections() is set to false in order to  |
| disable ReplicaManager3 from automatically calling PushConnection(),     |
| because you want to delay systems from participating in Replicamanager3  |
| until a host has been determined. The second parameter is up to you.     |
|                                                                          |
| Line 2: If every system that connects to you is another game instance,   |
| you can leave SetAutoparticipantConnections() as the default to true,    |
| and do not need to call                                                  |
| fullyConnectedMesh2-&gt;AddParticipant(packet-&gt;guid); later either.   |
| The reason this is here is in case you want to connect to a profiling    |
| tool or other non-game program.                                          |
|                                                                          |
| Line 3: FullyConnectedMesh2 requires a fully connected mesh topology, so |
| you need to connect to everyone else in the game instance. This can be   |
| done with a simple rakPeer-&gt;Connect() call, or you could have other   |
| systems such as [NAT punchthrough](natpunchthrough.html) involved        |
| depending on your needs. The code here works with both everyone starting |
| at the same time from a lobby, and with mid-game joins. See the manual   |
| page on [connecting](connecting.html) for more information about this.   |
|                                                                          |
| Line 4: Until a host has been determined,                                |
| fullyConnectedMesh2-&gt;GetConnectedHost() will return                   |
| UNASSIGNED\_RAKNET\_GUID. In that case, we delay                         |
| replicaManager3-&gt;PushConnection() until ID\_FCM2\_NEW\_HOST is        |
| returned. However, if a host is already known (for example, the game is  |
| already in progress), then the remote system is added immediately.       |
|                                                                          |
| Line 5: Once the host is known for the first time, all connected systems |
| can be added to ReplicaManager3. oldHost==UNASSIGNED\_RAKNET\_GUID means |
| there was no prior host.                                                 |
|                                                                          |
| Line 6: A function to uniquely add connections to ReplicaManager3 given  |
| a list of remote RakNetGUIDs.                                            |
|                                                                          |
| <span class="RakNetBlueHeader">Integration with component based          |
| systems</span>\                                                          |
|                                                                          |
| By component-based system I mean one where a game actor has a list of    |
| classes attached, each of which contain an attribute of the actor        |
| itself. For example, a player may have position, health, animation,      |
| physics components for example.                                          |
|                                                                          |
| 1\. Instances of the same actor either have the same type, order, and an |
| d                                                                        |
| number of components or else when you serialize you will have to provide |
| a way to identify components. To Serialize(), first Serialize() your     |
| actor. Then Serialize() your components in order.\                       |
| \                                                                        |
| 2. Here is an example of QuerySerialization() in a peer to peer game     |
| where the host controls objects loaded with the level (static objects).  |
| Otherwise, the peer that created the object serializes it. However, a    |
| component can override this and allow the host to serialize the object   |
| regardless. For example, if a player puts a weapon on the ground, the    |
| weapon could return RM3QSR\_CALL\_SERIALIZE if our own system is the     |
| host system, and RM3QSR\_DO\_NOT\_CALL\_SERIALIZE otherwise.\            |
|     if (IsAStaticObject())                                               |
|     {                                                                    |
|         // Objects loaded with the level are serialized by the host      |
|         if (fullyConnectedMesh2->IsHostSystem())                         |
|             return RM3QSR_CALL_SERIALIZE;                                |
|         else                                                             |
|             return RM3QSR_DO_NOT_CALL_SERIALIZE;                         |
|     }                                                                    |
|     else                                                                 |
|     {                                                                    |
|         // Allow components opportunity to overwrite method of serializa |
| tion                                                                     |
|         for (int i=0; i < components.Size(); i++)                        |
|         {                                                                |
|             RM3QuerySerializationResult res = components[i]->QuerySerial |
| ization(destinationconnection);                                          |
|             if(res != RM3QSR_MAX)                                        |
|                 return res;                                              |
|         }                                                                |
|         return QuerySerialization_PeerToPeer(destinationconnection);     |
|     }                                                                    |
|                                                                          |
| 3\. This variation, for QueryConstruction(), has components return       |
| Replica3P2PMode instead. Using the gun example, a gun may controlled by  |
| the host when on the ground, or by another player when picked up. If     |
| R3P2PM\_MULTI\_OWNER\_CURRENTLY\_AUTHORITATIVE or                        |
| R3P2PM\_MULTI\_OWNER\_NOT\_CURRENTLY\_AUTHORITATIVE is returned by a     |
| component, then QueryConstruction\_PeerToPeer() will use that value to   |
| return an appropriate value for RM3ConstructionState. Internally,        |
| QueryConstruction\_PeerToPeer() will return RM3CS\_SEND\_CONSTRUCTION if |
| we control the object, RM3CS\_NEVER\_CONSTRUCT if we do not control the  |
| object and nobody else ever can, and RM3CS\_ALREADY\_EXISTS\_REMOTELY if |
| someone else controls the object but the owner can change.\              |
|     if (destinationConnection->HasLoadedLevel() == false)                |
|         return RM3CS_NO_ACTION;                                          |
|     if (IsAStaticObject())                                               |
|     {                                                                    |
|         if(fullyConnectedMesh2->IsHostSystem())                          |
|                 return RM3CS_ALREADY_EXISTS_REMOTELY;                    |
|         else                                                             |
|                 return RM3CS_ALREADY_EXISTS_REMOTELY_DO_NOT_CONSTRUCT;   |
|     }                                                                    |
|     else                                                                 |
|     {                                                                    |
|         Replica3P2PMode p2pMode = R3P2PM_SINGLE_OWNER;                   |
|         for (int i=0; i < components.Size(); i++)                        |
|         {                                                                |
|             p2pMode = components[i]->QueryP2PMode();                     |
|             if(p2pMode != R3P2PM_SINGLE_OWNER)                           |
|                 break;                                                   |
|         }                                                                |
|         return QueryConstruction_PeerToPeer(destinationconnection, p2pMo |
| de);                                                                     |
|     }                                                                    |
|                                                                          |
|     virtual Replica3P2PMode BaseClassComponent::QueryP2PMode() {return R |
| 3P2PM_SINGLE_OWNER;}                                                     |
|                                                                          |
|     virtual Replica3P2PMode GunComponent::QueryP2PMode()                 |
|     {                                                                    |
|         if (IsOnTheGround())                                             |
|             if(fullyConnectedMesh2->IsHostSystem())                      |
|                 return R3P2PM_MULTI_OWNER_CURRENTLY_AUTHORITATIVE;       |
|             else                                                         |
|                 return R3P2PM_MULTI_OWNER_NOT_CURRENTLY_AUTHORITATIVE;   |
|         else                                                             |
|             if (WeOwnTheGun())                                           |
|                 return R3P2PM_MULTI_OWNER_CURRENTLY_AUTHORITATIVE;       |
|             else                                                         |
|                 return R3P2PM_MULTI_OWNER_NOT_CURRENTLY_AUTHORITATIVE;   |
|                                                                          |
|     }                                                                    |
|                                                                          |
| 4\. If you need to use composition instead of derivation see             |
| Replica3Composite in ReplicaManager3.h. It is a templated class with     |
| only one member, r3CompositeOwner. All Replica3 interfaces are queried   |
| on r3CompositeOwner.                                                     |
| **Methods of object serialization:**                                     |
|                                                                          |
| **Manual sends on dirty flags**\                                         |
| *Description*: When a variable changes, it's up to you to set some flag  |
| that the variable has changed. The next Serialize() tick, you send all   |
| variables with dirty flags set\                                          |
| *Pros*: fast, memory efficient\                                          |
| *Cons*: All replicated variables must change through accessors so the    |
| flags can be set. So it's labor intensive on the programmer as you have  |
| to program it to set the dirty flags, and bugs will likely be made       |
| during the process                                                       |
|                                                                          |
| *Example*\                                                               |
| \                                                                        |
| <span class="RakNetCode">void SetHealth(float newHealth) {if             |
| (health==newHealth) return; health=newHealth; serializeHealth=true;}\    |
| void SetScore(float newScore) {if (score==newScore) return;              |
| score=newScore; serializeScore=true;}\                                   |
| virtual RM3SerializationResult Serialize(SerializeParameters             |
| \*serializeParameters)\                                                  |
| {\                                                                       |
| bool anyVariablesNeedToBeSent=false;\                                    |
| if (serializeHealth==true)\                                              |
| {\                                                                       |
| serializeParameters-&gt;outputBitstream\[0\]-&gt;Write(true);\           |
| serializeParameters-&gt;outputBitstream\[0\]-&gt;Write(health);\         |
| anyVariablesNeedToBeSent=true;\                                          |
| }\                                                                       |
| else\                                                                    |
| {\                                                                       |
| serializeParameters-&gt;outputBitstream\[0\]-&gt;Write(false);\          |
| }\                                                                       |
| if (serializeScore==true)\                                               |
| {\                                                                       |
| serializeParameters-&gt;outputBitstream\[0\]-&gt;Write(true);\           |
| serializeParameters-&gt;outputBitstream\[0\]-&gt;Write(score);\          |
| anyVariablesNeedToBeSent=true;\                                          |
| }\                                                                       |
| else\                                                                    |
| {\                                                                       |
| serializeParameters-&gt;outputBitstream\[0\]-&gt;Write(false);\          |
| }\                                                                       |
| if (anyVariablesNeedToBeSent==false)\                                    |
| serializeParameters-&gt;outputBitstream\[0\]-&gt;Reset();\               |
| // Won't send anything if the bitStream is empty (was Reset()).          |
| RM3SR\_SERIALIZED\_ALWAYS skips default memory compare\                  |
| return RM3SR\_SERIALIZED\_ALWAYS;\                                       |
| }</span>                                                                 |
|                                                                          |
| virtual void Deserialize(RakNet::DeserializeParameters                   |
| \*deserializeParameters)\                                                |
| {\                                                                       |
| bool healthWasChanged, scoreWasChanged;\                                 |
| deserializeParameters-&gt;serializationBitstream\[0\]-&gt;Read(healthWas |
| Changed);\                                                               |
| if (healthWasChanged)\                                                   |
| deserializeParameters-&gt;serializationBitstream\[0\]-&gt;Read(health);\ |
| deserializeParameters-&gt;serializationBitstream\[0\]-&gt;Read(scoreWasC |
| hanged);\                                                                |
| if (scoreWasChanged)\                                                    |
| deserializeParameters-&gt;serializationBitstream\[0\]-&gt;Read(score);\  |
| }                                                                        |
|                                                                          |
| **Serializing based on the object changing**\                            |
| *Description*: This is what ReplicaManager3 comes with. If the object's  |
| state for a bitStream channel change at all, the entire channel is       |
| resent\                                                                  |
| *Pros:* Easy to use for the programmer\                                  |
| *Cons:* Some variables will be sent unneeded, using more bandwidth than  |
| necessary. Moderate CPU and memory usage                                 |
|                                                                          |
| *Example*                                                                |
|                                                                          |
| <span class="RakNetCode">void SetHealth(float newHealth)                 |
| {health=newHealth;}\                                                     |
| virtual RM3SerializationResult Serialize(SerializeParameters             |
| \*serializeParameters)\                                                  |
| {\                                                                       |
| serializeParameters-&gt;outputBitstream\[0\]-&gt;Write(health);\         |
| serializeParameters-&gt;outputBitstream\[0\]-&gt;Write(score);\          |
| // Memory compares against last outputBitstream write. If changed,       |
| writes everything on the changed channel(s), which can be wasteful in    |
| this case if only health or score changed, and not both </span><span     |
| class="RakNetCode">\                                                     |
| ieturn RM3SR\_BROADCAST\_IDENTICALLY;\                                   |
| }</span>\                                                                |
| <span class="RakNetCode">virtual void                                    |
| Deserialize(RakNet::DeserializeParameters \*deserializeParameters)\      |
| {\                                                                       |
| deserializeParameters-&gt;serializationBitstream\[0\]-&gt;Read(health);\ |
| deserializeParameters- &gt;serializationBitstream\[0\]-&gt;Read(score);  |
| </span><span class="RakNetCode">\                                        |
| }</span>                                                                 |
|                                                                          |
| \                                                                        |
| **Serializing per-variable**\                                            |
| *Description*: The optional module I was talking about. Every variable   |
| is copied internally and compared to the last state\                     |
| *Pros:* Maximum bandwidth savings\                                       |
| *Cons:* Heavy CPU and memory usage                                       |
|                                                                          |
| *Example (also see ReplicaManager3 sample project)*                      |
|                                                                          |
| virtual RM3SerializationResult Serialize(SerializeParameters             |
| \*serializeParameters) {\                                                |
| VariableDeltaSerializer::SerializationContext serializationContext;\     |
| // All variables to be sent using a different mode go on different       |
| channels\                                                                |
| serializeParameters-&gt;pro\[0\].reliability=RELIABLE\_ORDERED;\         |
| variableDeltaSerializer.BeginIdenticalSerialize(\                        |
| &serializationContext,\                                                  |
| serializeParameters-&gt;whenLastSerialized==0,\                          |
| &serializeParameters-&gt;outputBitstream\[0\]\                           |
| );\                                                                      |
| variableDeltaSerializer.SerializeVariable(&serializationContext,         |
| var3Reliable);\                                                          |
| variableDeltaSerializer.SerializeVariable(&serializationContext,         |
| var4Reliable);\                                                          |
| variableDeltaSerializer.EndSerialize(&serializationContext);\            |
| return RM3SR\_SERIALIZED\_ALWAYS\_IDENTICALLY;\                          |
| }\                                                                       |
| \                                                                        |
| virtual void Deserialize(RakNet::DeserializeParameters                   |
| \*deserializeParameters) {\                                              |
| VariableDeltaSerializer::DeserializationContext deserializationContext;\ |
| variableDeltaSerializer.BeginDeserialize(&deserializationContext,        |
| &deserializeParameters-&gt;serializationBitstream\[0\]);\                |
| if (variableDeltaSerializer.DeserializeVariable(&deserializationContext, |
| var3Reliable))\                                                          |
| printf("var3Reliable changed to %i\\n", var3Reliable);\                  |
| if (variableDeltaSerializer.DeserializeVariable(&deserializationContext, |
| var4Reliable))\                                                          |
| printf("var4Reliable changed to %i\\n", var4Reliable);\                  |
| variableDeltaSerializer.EndDeserialize(&deserializationContext);\        |
| }                                                                        |
|                                                                          |
| **Quick start:**\                                                        |
|                                                                          |
| 1.  Derive from Connection\_RM3 and                                      |
|     implement Connection\_RM3::AllocReplica(). This is a factory         |
|     function where given an identifier for a class (such as name) return |
|     an instance of that class. Should be able to return any networked    |
|     object in your game.                                                 |
| 2.  Derive from ReplicaManager3 and implement AllocConnection()          |
|     and DeallocConnection() to return the class you created in step 1.   |
| 3.  Derive your networked game objects from Replica3. All pure virtuals  |
|     have to be implemented, however defaults are provided                |
|     for Replica3::QueryConstruction()                                    |
|     and Replica3::QueryRemoteConstruction() depending on your            |
|     network architecture.                                                |
| 4.  When a new game object is created on the local system, pass it       |
|     to ReplicaManager3::Reference().                                     |
| 5.  When a game object is destroyed on the local system, and you want    |
|     other systems to know about it,                                      |
|     call Replica3::BroadcastDestruction()                                |
| 6.  Attach ReplicaManager3 as a plugin                                   |
|                                                                          |
| For a full list of functions with detailed documentation on each         |
| parameter, see ReplicaManager3.h.                                        |
|                                                                          |
| The primary sample is located at *Samples\\ReplicaManager3*.\            |
+--------------------------------------------------------------------------+
|                                                                          |
+--------------------------------------------------------------------------+

  ----------------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Differences between ReplicaManager3 and ReplicaManager2
  ----------------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">ReplicaManager3 should be simpler and     |
| more transparent</span>                                                  |
| 1.  Connection\_RM2::Construct is now two functions:                     |
|     Connection\_RM3::AllocReplica                                        |
|     and Connection\_RM3::DeserializeConstruction. Previously, you were   |
|     given raw data in Connection\_RM2::Construct and expected to both    |
|     create and deserialize construction yourself. Now, AllocReplica will |
|     create the object. DeserializeConstruction will fill out the data    |
|     for the object.                                                      |
| 2.  Because of the change above, NetworkID, creatingSystemGUID, and      |
|     replicaManager are already set as member variables before you get    |
|     the DeserializeConstruction callback. This simplies usage because    |
|     the object is already ready to use.                                  |
| 3.  Objects created the same tick were previously sent in                |
|     individual messages. This means it was possible for the two objects  |
|     to arrive on different remote game ticks for recipients              |
|     already connected. This is a problem if two objects depend on each   |
|     other before either will work. Now, all objects created the same     |
|     tick (defined by calls to RakPeerInterface::Receive(), which         |
|     calls PluginInterface2::Update() are sent in the same message.       |
| 4.  Previously, you would call ReplicaManager2::SetConnectionFactory     |
|     with a special connection factory class to create instances          |
|     of Connection\_RM2. Now, ReplicaManager3 itself has pure virtual     |
|     functions AllocConnection() and DeallocConnection()                  |
| 5.  Previously, object references were implicit. A call to               |
|     ReplicaManager2::SendConstruction, ReplicaManager2::SendSerialize,   |
|     or ReplicaManager2::SendVisibility would register the instance if it |
|     didn't already exist. Now, references are explicit, with             |
|     ReplicaManager3::Reference replacing all three of those              |
|     ReplicaManager2 calls. This was a previous source of confusion,      |
|     where those Send functions (or the Broadcast equivalents) did not    |
|     check the corresponding Replica2::Query\* functions. The             |
|     Construction and Serialization functions are now gone, and happen    |
|     soley through the automatic update tick.                             |
| 6.  ReplicaManager2 did not support different                            |
|     serializations per-connection. ReplicaManager3 does, by returning    |
|     RM3SR\_SERIALIZED\_UNIQUELY from ReplicaManager3::Serialize. It is   |
|     still more efficient to return RM3SR\_SERIALIZED\_IDENTICALLY if     |
|     serializations are the same for all connections.                     |
| 7.  ReplicaManager3 does not support the visiblity commands, such as     |
|     ReplicaManager2::SendVisibility, to keep the system simpler and      |
|     more transparent. To support this, add a boolean visiblity flag.     |
|     Transmit it once in Serialize, using RM3SR\_SERIALIZED\_UNIQUELY. On |
|     the remote system, if the visibility flag is false, hide the object. |
|     On the sending system, if the visibility flag is false, return       |
|     RM3SR\_DO\_NOT\_SERIALIZE from ReplicaManager3::Serialize. You can   |
|     check if the visibility flag for this replica / connection pair has  |
|     changed by reading SerializeParameters::lastSerializationSent, which |
|     will contain the last transmitted value of                           |
|     SerializeParameters::outputBitstream                                 |
| 8.  ReplicaManager3 does not support                                     |
|     Connection\_RM2::SerializeDownloadStarted to keep the system simpler |
|     and more transparent. You can check the equivalent in the function   |
|     ReplicaManager3::SerializeConstruction withthe value                 |
|     of destinationConnection-&gt;IsInitialDownload(). For more complex   |
|     behavior, you can also send data before registering the              |
|     remote system. Call ReplicaManager3::SetAutoManageConnections with   |
|     the autoCreate parameter as false. Send your data. Then              |
|     call ReplicaManager3::PushConnection.                                |
| 9.  QueryDestruction no longer exists. QueryConstruction now has a       |
|     return value that indicates destruction.                             |
| 10. QueryIs\*Authority no longer exists. Return values from the existing |
|     functions in ReplicaManager3 achieve the same results.               |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [Connecting](connecting.html)\                                           |
| [NAT punchthrough](natpunchthrough.html)\                                |
| [PluginInterface](plugininterface.html)\                                 |
| [ReplicaManager3                                                         |
| Video](http://www.jenkinssoftware.com/raknet/manual/ReplicaManager3Video |
| .htm)\                                                                   |
| \                                                                        |
+--------------------------------------------------------------------------+


