# Cloud Computing Overview

## Client memory / events accessible through a server cloud

Sometimes you want a large number of clients that are not connected and do not necessarily know about each other to share memory or to get notifications of events. For example:

*   A high performance server browser
*   In-game statistics for millions of players
*   Cloud computing

The "Cloud" in CloudServer means that the system supports distributed servers. Any client can Post() to or Get() from any server. Post() operations can be subscribed to or Get() by other clients, regardless of what server that client is subscribed to. Servers can be added or removed at runtime, and the system will continue to work as expected. This allows the system to be scaled according to your player load, using your own servers or virtual servers such as [Rackspace](cloudhosting.html).

The design of the system assumes that all servers are connected in a fully connected mesh. You should authenticate other servers before adding them with CloudServer::AddServer(). The [TwoWayAuthentication](twowayauthentication.html) and [ConnectionGraph2](connectiongraph.html) plugins can help with this. Or just run/modify the CloudServer sample, which does this already.

The servers should be accessible by the internet through a static IP address, either without a router, or with the ports opened.

Note: The design of the system is that client data only persists while that client is connected to the server. The server itself can perform local operations or persist data with a local client.

**Code Usage:**

On the server, you can optionally restrict uploads and downloads to reduce memory and bandwidth usage.

```c++
CloudServer cloudServer;
rakPeer->AttachPlugin(&cloudServer);
// Restrict how many bytes a client can upload to this server.
cloudServer.SetMaxUploadBytesPerClient(MAX_UPLOAD_BYTES);
cloudServer.SetMaxBytesPerDownload(MAX_DOWNLOAD_BYTE</span>S);
```

On the client:

```c++
CloudClient cloudClient;
rakPeer->AttachPlugin(&cloudClient);
// Optional: Provide an overridden allocator to store or deallocate the downloaded rows in your own application
Cloud_Allocator cloudAllocator;
// Optional: You'll want to actually provide an overridden instance to handle downloads
Cloud_ClientCallback clientCallback;
// Set the allocation callbacks
cloudClient.SetCallbacks(&cloudAllocator, &clientCallback);
// Every uploaded is associated with a pair of keys
Cloud_DataKey dataKey;
dataKey.primaryKey="ApplicationName";
dataKey.secondaryKey=ID_PLAYER_COUNT; // Enumeration
unsigned char playerCount=16;
// Upload data to the cloud, to a server we are already connected to
cloudClient.Post(&dataKey, &playerCount, sizeof(playercount), serverAddressOrGuid);
// Download the data we just uploaded. clientCallback will have the OnDownload member called when the query completes.
Cloud_KeyQuery query;
query.keys.Push(dataKey, __FILE__, __LINE__);</span><span class="RakNetCode">
cloudClient.Get(&query, serverAddressOrGuid);</span>
```

## Use cases:

## _Server directory_

Assign a secret unique name for the application, and use that as the the Cloud_DataKey primaryKey. Have each game server maintain a common list of enumerations representing fields to query, such as PLAYER_COUNT, PLAYER_LIST, and LEVEL_NAME. The IP address and RakNetGUID properties of the other game servers are maintained automatically. When a game server becomes available to be listed, use the CloudClient::Post() operation once per field to be uploaded. To query for other servers, use the CloudClient::Get() operation for any system, passing the list of CloudMemory_DataKey keys you care about to Cloud_KeyQuery. If you did not query all keys in the prior call, you can get more detail on a particular server again using the CloudClient::Get() operation, with a larger list of keys, and by using the overloaded version of CloudClient::Get() that has the specificSystems parameter. You can subscribe to updates for a particular system in the CloudClient::Get() call if desired, but this is usually not necessary. The game server is delisted if it disconnects from the CloudServer (for example crashing) and games can be manually delisted with the CloudClient::Release() call.

## In-game statistics

Support you want to track number of kills across all running games ever. Furthermore, the game has millions of players, so it is not viable to have each client individually hit a single database server. You also want to hide the database server from the public. The cloud system can help here, mirroring common statistics in memory. To do so, each game client will Post() kills to the cloud. Each server in the cloud has a local client used to update the database. The local client uses the Get() function to query or subscribe to kill posts by the game clients. The local client will also periodically write to the database server (or it could be every kill if you wanted real-time statistics). Similarly, the local client will read from the central database to get an updated kill count, and Post() this data to the cloud. Lastly, the game clients use the Get() function with the specificSystems parameter set to their own server to subscribe to the updated kill count.

## Cloud computing

Sometimes you want to split a problem across many clients. For example, rendering lighting in your game levels. The cloud system can help by acting as a distributed event coordinator. Each client that wants to process part of the problem will call CloudClient::Post(), potentially with no data, to signal that it is ready to perform processing. CloudMemory_DataKey::primaryKey may be "LevelRenderer" while CloudMemory_DataKey::secondaryKey may be ID_SIGNAL_READY. The client will also call Get() to subscribe to new tasks, such as ID_TASK_SUBSCRIPTION. And to Post() results, such as ID_TASK_COMPLETION. The server will have a local client on 127.0.0.1 that contains the actual problem to solve. This local client will subscribe to ID_SIGNAL_READY. When the notification arrives, part of the problem is split off and Post() is used with ID_TASK_SUBSCRIPTION. The data field can specify the GUID of which client should process this task. If the local client on the server gets the Cloud_ClientCallback::OnDeletion() call, then one of the processing clients lost the connection or crashed. The data being processed can be reassigned to another client.

## Distributed CloudServer Implementation

See Samples/CloudServer for a distributed authenticated implementation of CloudServer with DNS based host migration. See Samples/CloudServer/readme.txt for specific details on how it is implemented, how to implement load balancing among clients, and for a list of supported plugins.

## Server Directory Implementation

See Samples/CloudClient for an implementation of a high-performance server directory using the CloudServer sample as the backend. The distributed topology is allows for new servers can be added at runtime with no restarts, configuration, or code changes.

See CloudServer.h and CloudClient.h for a complete list of all documented functions and parameters. 

## See Also

* [Index](index.html) 
* [Cloud Computing Video](http://www.youtube.com/watch?v=QpwcLQt1E0o) 
* [Cloud Hosting](cloudhosting.html) 
* [ConnectionGraph2 plugin](connectiongraph.html) 
* [TwoWayAuthentication plugin](twowayauthentication.html)
