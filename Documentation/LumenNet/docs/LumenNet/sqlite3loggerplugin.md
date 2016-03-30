<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ----------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}SQLite3LoggerPlugin Setup
  ----------------------------------------------------------------

+--------------------------------------------------------------------------+
| Overview                                                                 |
|                                                                          |
| RakNet's SQLLite3 logging system allows any system that supports TCP to  |
| send logs to a remote server. Logs automatically include the source file |
| and line, as well as the time the log was sent, and the IP address of    |
| the sender. The logging system supports real-time DXT1 compression of    |
| screenshots, allowing for video replay of game sessions. SQL knowledge   |
| is not required to write logs, in fact logging is just as easy through   |
| RakNet as traditionally sent through printf. Variable types are          |
| automatically determined at compile time.                                |
|                                                                          |
| Especially valuable is the ability to log multiplayer game sessions into |
| a single log file. This allows the developer to view multiplayer         |
| sessions across a LAN, all on a single PC after the fact. Combined with  |
| automatic packet logging and network statistics, this allows analysis of |
| multiplayer sessions with a high degree of precision.                    |
|                                                                          |
| <span class="RakNetBlueHeader">SQLiteServerLoggerPlugin</span>           |
|                                                                          |
| SQLiteServerLoggerPlugin derives from                                    |
| [SQLiteLogger](sqlite3plugin.html), adding the capability to write log   |
| files sent from SQLiteClientLogger.To start, simply run the project      |
| found at                                                                 |
| DependentExtensions\\SQLite3Plugin\\ServerOnly\\SQLiteServerLoggerSample |
| .cpp                                                                     |
| . In the Visual Studio 2005 solution, this is found under Samples /      |
| SQLite3Plugin / SQLiteServerLogger                                       |
|                                                                          |
| New SQL log files can be manually specified, or created automatically.   |
| To manually specify log files, create and register them the same way you |
| do with [SQLiteLogger](sqlite3plugin.html). For example, this creates an |
| in-memory database                                                       |
|                                                                          |
| if (sqlite3\_open\_v2(":memory:", &database, SQLITE\_OPEN\_READWRITE |   |
| SQLITE\_OPEN\_CREATE, 0)!=SQLITE\_OK)\                                   |
| return 1;                                                                |
|                                                                          |
| static const char\* DATABASE\_IDENTIFIER="ConnectionStateDBInMemory";\   |
| sqlite3ServerPlugin.AddDBHandle(DATABASE\_IDENTIFIER, database);         |
|                                                                          |
| To automatically create log files based on new client sessions, use      |
| SQLiteServerLoggerPlugin::SetSessionManagementMode with either           |
| CREATE\_EACH\_NAMED\_DB\_HANDLE or CREATE\_SHARED\_NAMED\_DB\_HANDLE.    |
| CREATE\_EACH\_NAMED\_DB\_HANDLE will create one log file for each new    |
| connection that sends a log. CREATE\_SHARED\_NAMED\_DB\_HANDLE will      |
| create a new log file under the working directory every time a new       |
| connection sends a log, and closes that file when all connections have   |
| been lost. See SQLiteServerLoggerPlugin.h for more details on these      |
| settings.                                                                |
|                                                                          |
| **Minimal server setup using TCP:**                                      |
|                                                                          |
| PacketizedTCP packetizedTCP;\                                            |
| RakNet::SQLiteServerLoggerPlugin loggerPlugin;\                          |
| loggerPlugin.SetSessionManagementMode(RakNet::SQLiteServerLoggerPlugin:: |
| CREATE\_SHARED\_NAMED\_DB\_HANDLE,                                       |
| true, "");\                                                              |
| packetizedTCP.AttachPlugin(&loggerPlugin);\                              |
| packetizedTCP.Start(38123,8);                                            |
|                                                                          |
| When raw image data is sent to the server, the server will compress it   |
| automatically if specified by the client (more on this in the client     |
| section below). The server can enable hardware based DXT compression if  |
| the number or size of images sent is too frequent for the CPU to keep    |
| up. Enable this setting with                                             |
| SQLiteServerLoggerPlugin::SetEnableDXTCompression(true). It requires     |
| that the server have a hardware accelerated 3D card. If the setting      |
| fails, the server will automatically use JPEG compression isntead. JPEG  |
| compression produces smaller files, so is the better choice if the CPU   |
| can keep up.                                                             |
|                                                                          |
| <span class="RakNetBlueHeader">SQLiteClientLoggerPlugin</span>           |
|                                                                          |
| The client sources integrates with your application. You should add all  |
| files under DependentExtensions\\SQLite3Plugin\\ClientOnly to your       |
| application, except possibly SQLiteClientLogger\_PacketLogger.h/.cpp and |
| SQLiteClientLogger\_RNSLogger.h/cpp as these are optional. They are      |
| [plugins](plugininterface.html) used to log all packet logs, and         |
| RakNetStatistics respectively. You also have to add                      |
| DependentExtensions\\SQLite3Plugin\\SQLiteLoggerCommon.h/.cpp            |
|                                                                          |
| If your application does not already use RakNet, you will need to add    |
| RakNet source files under /Source as well. See the section on [compiler  |
| setup](compilersetup.html) if needed.                                    |
|                                                                          |
| There is also a [video covering this                                     |
| plugin](http://www.jenkinssoftware.com/raknet/manual/SQLite3LoggerPlugin |
| Video.html).                                                             |
|                                                                          |
| **Minimal client setup using TCP:**                                      |
|                                                                          |
| PacketizedTCP packetizedTCP;\                                            |
| RakNet::SQLiteClientLoggerPlugin loggerPlugin;\                          |
| packetizedTCP.AttachPlugin(&loggerPlugin);\                              |
| packetizedTCP.Start(0,0);\                                               |
| SystemAddress serverAddress = packetizedTCP.Connect("127.0.0.1", 38123,  |
| true);\                                                                  |
| // Assuming connection completed. See                                    |
| TCPInterface::HasNewIncomingConnection()\                                |
| loggerPlugin.SetServerParameters(serverAddress, "functionLog.sqlite");   |
|                                                                          |
| In this case, we are assuming the server is located at localhost         |
| (127.0.0.1) on port 38123. The port is arbitrary, and is whatever you    |
| used on the server.                                                      |
|                                                                          |
| "functionLog.sqlite" is the name of the first parameter passed to <span  |
| class="RakNetCode">SQLite3ServerPlugin::AddDBHandle</span>. However, if  |
| you are using CREATE\_SHARED\_NAMED\_DB\_HANDLE or                       |
| CREATE\_EACH\_NAMED\_DB\_HANDLE on the server, then this file will be    |
| created instead. It is OK for the application to use the same name, as   |
| the files are stored in separate directories. In fact, for multiplayer,  |
| you want all systems to use the same name so all logs are put into the   |
| same file and can be compared time-relative to each other.               |
|                                                                          |
| To constrain the amount of memory used by the system, use                |
| SQLiteClientLoggerPlugin::SetMemoryConstraint(unsigned int constraint).  |
| This is important if sending a lot of data. Otherwise if the server      |
| crashes, the application may consume a lot of memory until the crash is  |
| detected.                                                                |
|                                                                          |
|                                                                          |
+--------------------------------------------------------------------------+

  ----------------------------------------------
  ![](spacer.gif){width="8" height="1"}Logging
  ----------------------------------------------

+--------------------------------------------------------------------------+
| **Function call logs:**                                                  |
|                                                                          |
| All function call logs to to a single table, while the parameter list to |
| the function calls go to another table. The names of the tables are      |
| defined at the top of SQLiteServerLoggerPlugin.cpp.                      |
|                                                                          |
| \#define FUNCTION\_CALL\_TABLE 'functionCalls'\                          |
| \#define FUNCTION\_CALL\_PARAMETERS\_TABLE 'functionCallParameters'      |
|                                                                          |
| All parameters are saved as strings.                                     |
|                                                                          |
| To log a function call, use the define rakFnLog("function name",         |
| (parameterList));                                                        |
|                                                                          |
| For example:                                                             |
|                                                                          |
| RakNet::SQLLogResult res;\                                               |
| int x=1;\                                                                |
| unsigned short y=2;\                                                     |
| float c=3;\                                                              |
| double d=4;\                                                             |
| char \*e="HI";\                                                          |
| res = rakFnLog("My func", (x,y,c,d,e));\                                 |
| RakAssert(res==RakNet::SQLLR\_OK);                                       |
|                                                                          |
| Note the parenthesis around the parameter list. This is necessary for    |
| the macro to automatically log the \_\_FILE\_\_ and \_\_LINE\_\_ files   |
| that it uses does in C++.                                                |
|                                                                          |
| The return value is not necessary to usually check, but is good the      |
| first time you use the system. The call will fail if you did not setup   |
| the system properly.                                                     |
|                                                                          |
| **All other types of logs:**                                             |
|                                                                          |
| Log using the macro rakSqlLog("table name",                              |
| "column1,column2,column3...", (parameterList));                          |
|                                                                          |
| For example:                                                             |
|                                                                          |
| rakSqlLog("sqlLog", "handle, mapName, positionX, positionY, positionZ,   |
| gameMode, connectedPlayers", ("handle1", "mapname1", 1,2,3,"",4));\      |
| rakSqlLog("sqlLog", "handle, mapName, positionX, positionY, positionZ,   |
| gameMode, connectedPlayers", ("handle2", "mapname2",                     |
| 5,6,7,"gameMode2",8));\                                                  |
| rakSqlLog("sqlLog", "x", (999));                                         |
|                                                                          |
| The first line would create a new table in the database named "sqlLog".  |
| The table would have 7 columns: <span class="RakNetCode">handle,         |
| mapName, positionX, positionY, positionZ, gameMode,                      |
| connectedPlayers</span>. The types of the columns are based on the types |
| of the parameter list - in this case, two strings, followed by 3         |
| numbers, followed by another string, followed by another number.         |
|                                                                          |
| The second line would add a row to the table created by the first line.  |
| Note - if the types in the parameter lists didn't match at this point,   |
| for example if we sent a number instead of a string for the first        |
| parameter, then the call would fail on the server.                       |
|                                                                          |
| The third line would add a new column 'x' to the table, of type integer, |
| and the value 999.                                                       |
|                                                                          |
| Via macros, the values for \_\_FILE\_\_ and \_\_LINE\_\_ are also        |
| automatically sent to the server.                                        |
|                                                                          |
| *Tick Count*                                                             |
|                                                                          |
| Most games update the simulation through discrete ticks. The tick count  |
| on the client is automatically sent to the server with logs. Update the  |
| tick count by calling                                                    |
| SQLiteClientLoggerPlugin::IncrementAutoTickCount(). Ticks are supported  |
| in [Echo Chamber](http://www.jenkinssoftware.com/echochamber) for single |
| stepping animations.                                                     |
|                                                                          |
| *Binary Data*:                                                           |
|                                                                          |
| Enclose two parameters into one value in the parameter list using the    |
| **BlobDescriptor** structure.                                            |
|                                                                          |
| rakSqlLog("blobTable", "blobColumn", (                                   |
| &RakNet::BlobDescriptor(bytes,byteLength) ));                            |
|                                                                          |
| *Image Data*:                                                            |
|                                                                          |
| Enclose relevent parameters into one value in the parameter list using   |
| the **RGBImageBlob** structure.                                          |
|                                                                          |
| RGBImageBlob(void \*\_data, uint16\_t \_imageWidth, uint16\_t            |
| \_imageHeight, uint16\_t \_linePitch, unsigned char \_input\_components, |
| ImageBlobCompressionMode mode=DXT)                                       |
|                                                                          |
| The first parameter is the data to send. The 2nd and 3rd paramters are   |
| the image dimenstions. The \_linePitch parameter is the number of        |
| *bytes* per row of the \_data. <span                                     |
| class="RakNetCode">\_input\_components</span> should be 3 for RGB, and 4 |
| for RGBA. <span class="RakNetCode">mode</span>, of <span                 |
| class="RakNetCode">ImageBlobCompressionMode</span>, should be the        |
| preferred encoding mode. If DXT is specified, but not supported or fails |
| on the server, JPEG will be used instead.                                |
|                                                                          |
| Here's an example from SQLiteClientLoggerSample.cpp                      |
|                                                                          |
| rakSqlLog("gradient", "gradientImage", (                                 |
| &RakNet::RGBImageBlob(bytes,4096,4096,4096\*4,4) ));                     |
|                                                                          |
|                                                                          |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| \                                                                        |
| [Index](index.html)\                                                     |
| [Compiler setup](compilersetup.html)\                                    |
| [LightweightDatabase plugin](lightweightdatabase.html)\                  |
| [PluginInterface](plugininterface.html)\                                 |
| [SQLiteLogger](sqlite3plugin.html)\                                      |
| [SQLiteClientLoggerPlugin                                                |
| Video.](http://www.jenkinssoftware.com/raknet/manual/SQLite3LoggerPlugin |
| Video.html)                                                              |
+--------------------------------------------------------------------------+


