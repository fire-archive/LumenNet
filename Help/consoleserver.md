# Command Console Server Overview - Use the console to remotely control a game server

Sometimes it is useful to control a server when you are not in front of that particular computer. This can arise due to server hosting, where the host is located offsite. Or perhaps you have many servers, and you want to control them via a script. The ConsoleServer, CommandParserInterface, and TransportInterface are three classes that work together to meet these needs.

**ConsoleServer**

The ConsoleServer class, located at ConsoleServer.h, contains a list of CommandParserInterface classes, added with ConsoleServer::AddCommandParser(). By calling ConsoleServer::Update() once per game tick, all CommandParserInterface classes are processed for incoming input

**CommandParserInterface**

A command parser is a class which operates on a named set of registered commands. CommandParserInterface is a base class from which you should derive functionality for each command parser. For example, RakNetCommandParser.h exposes most functions that are available to call in RakPeerInterface. RakNetTransportCommandParser exposes functions that deal with the RakNetTransport class, used to actually send data used by the ConsoleServer.

**TransportInterface**

The TransportInterface class provides functionality to the ConsoleServer to send strings. There are currently two implementations of TransportInterface: TelnetTransport, and RakNetTransport. TelnetTransport uses [TCPInterface.h](tcpinterface.html) to reply to a remote telnet terminal. RakNetTransport sends strings through an instance of RakPeer, with [secure connections](secureconnections.html) enabled.

**Putting it all together**

Excerpts from the sample CommandConsoleServer

```cpp
ConsoleServer consoleServer;  
TelnetTransport tt;  
RakNetCommandParser rcp;  
LogCommandParser lcp;

consoleServer.AddCommandParser(&rcp);  
consoleServer.AddCommandParser(&lcp);  
consoleServer.SetTransportProvider(ti, port);  
lcp.AddChannel("TestChannel");  

while (1)  
{  
lcp.WriteLog("TestChannel", "Test of logger");  
consoleServer.Update();  
// Game loop here  
}
```

It's quite simple in practice. You have one instance of a console server, one instance of a transport interface (EIther TelnetTransport or RakNetTransport), and your command parsers. Call ConsoleServer::AddCommandParser for each parser, ConsoleServer::SetTransportProvider() for telnet or RakNet, and ConsoleServer::Update() once per tick. Here I also add an output channel to the LogCommandParser, and output to the log once per tick.

Assuming the server is already started, you can connect as follows:

**Start telnet from the start menu**  
![Start Telnet](telnet1.jpg)

**Connect to your server with telnet**  
![Connect to localhost](telnet2.jpg)

**The system should handle everything else**  
![Help](telnet3.jpg)

## RakNetTransport

Secure console connections

Telnet is easy to use but not secure. If you want to send passwords or other sensitive data, you should use RakNetTransport on the server instead. This comes with an additional command parser, RakNetTransportCommandParser, which adds the functionality to change the password on the instance of RakPeer that is internal to RakNetTransport. It was designed this way so remote users connect to the command parser without connecting to the game itself, and the game and the command parser can have different passwords.

For the client-side, the sample CommandConsoleClient is an implementation of a console application that uses RakNet to connect to RakNetTransport

## Creating your own command parser

Predefine commands and/or pass the command strings directly to your scripting system

To add a new command parser, first derive a class from CommandParserInterface, as was done in RakNetCommandParser.h. You will want to override OnCommand, GetName, and SendHelp. Additionally, any functionality you need to communicate with your game, such as SetGamePointer() or SetLogger(), you should add on your own.

1\. In the constructor of your new class, call RegisterCommand for each command you want to add. Here is an example from **RakNetCommandParser.cpp**

```cpp
RegisterCommand(4, "Startup","( unsigned short maxConnections, int _threadSleepTimer, unsigned short localPort, const char *forceHostAddress );");
```

The first parameter, 4, is the number of parameters to pass to the function. The second parameter, "Startup" is the name of the command, and will show up in the abbreviated command list. The third parameter, "unsigned short maxConnections ...", defines the helpString, displayed when help is called on a particular named command.

Given this syntax, ConsoleServer will verify that the correct number of parameters was passed, and return an error to the user should this not be the case when calling a particular command.

2\. In OnCommand(), compare the command string to your registered commands, and take the desired action

```cpp
if (strcmp(command, "Startup")==0) { SocketDescriptor socketDescriptor((unsigned short)atoi(parameterList[1]), parameterList[3]); ReturnResult(peer->Startup((unsigned short)atoi(parameterList[0]), atoi(parameterList[2]), &socketDescriptor, 1), command, transport, systemAddress); }
```

The return value of OnCommand is currently not used, so just return true.

ReturnResult is a function you can optionally call that will return back a string to the requesting system.

3\. Implement GetName(), returning the name of your command parser. This will show up in the command parser listing.

4\. Implement SendHelp(), which will return extended help when queried for your particular parser. If your parser is not runnable due to failed preconditions, it is a good idea to return a notification message about that here.

**Unknown or variable number of parameters:**

Pass CommandParserInterface::VARIABLE_NUMBER_OF_PARAMETERS as the first parameter to RegisterCommand. CommandServer will not check for a valid number of parameters in this case. It is up to you in OnCommand() to deal with error conditions that may come up in this case.

**Direct string parsing**

If you don't want ConsoleServer to parse the incoming string for you, use the parameter originalString passed to OnCommand. For example, if you are controlling your scripting system, you would probably want to pass this string directly along.

**Changing delineators**

If you want to separate your commands by something other than space, or separate your strings by something other than quotation marks, the defines are found in CommandServer.cpp

```cpp
#define COMMAND_DELINATOR ' '  
#define COMMAND_DELINATOR_TOGGLE '"'
```

## See Also 

* [Index](index.html)  
* [Telnet (Wikipedia)](http://en.wikipedia.org/wiki/TELNET)  
* [TCP Interface](tcpinterface.html)  
* [Secure connections](secureconnections.html)  
