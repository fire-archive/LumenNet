<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  --------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Preprocessor directives
  --------------------------------------------------------------

+--------------------------------------------------------------------------+
| Define any of these values in RakNetDefinesOverrides.h to override.      |
| These are the defaults as set in RakNetDefines.h. Also see               |
| NativeFeatureIncludes.h to not compile in features you do not use.       |
|                                                                          |
| /// Define \_\_GET\_TIME\_64BIT to have RakNet::TimeMS use a 64, rather  |
| than 32 bit value. A 32 bit value will overflow after about 5 weeks.\    |
| /// However, this doubles the bandwidth use for sending times, so don't  |
| do it unless you have a reason to.\                                      |
| /// Comment out if you are using the iPod Touch TG. See                  |
| http://www.jenkinssoftware.com/forum/index.php?topic=2717.0\             |
| /// This must be the same on all systems, or they won't connect\         |
| \#define \_\_GET\_TIME\_64BIT 1                                          |
|                                                                          |
| // Define \_FILE\_AND\_LINE\_ to "",0 if you want to strip out file and  |
| line info for memory tracking from the EXE\                              |
| \#define \_FILE\_AND\_LINE\_ \_\_FILE\_\_,\_\_LINE\_\_                   |
|                                                                          |
| /// Define \_\_BITSTREAM\_NATIVE\_END to NOT support endian swapping in  |
| the BitStream class. This is faster and is what you should use\          |
| /// unless you actually plan to have different endianness systems        |
| connect to each other\                                                   |
| /// Enabled by default.\                                                 |
| // \#define \_\_BITSTREAM\_NATIVE\_END                                   |
|                                                                          |
| /// Maximum (stack) size to use with \_alloca before using new and       |
| delete instead.\                                                         |
| \#define MAX\_ALLOCA\_STACK\_ALLOCATION 1048576                          |
|                                                                          |
| // Use WaitForSingleObject instead of sleep.\                            |
| // Defining it plays nicer with other systems, and uses less CPU, but    |
| gives worse RakNet performance\                                          |
| // Undefining it uses more CPU time, but is more responsive and faster.\ |
| \#define USE\_WAIT\_FOR\_MULTIPLE\_EVENTS                                |
|                                                                          |
| /// Uncomment to use RakMemoryOverride for custom memory tracking\       |
| /// See RakMemoryOverride.h.\                                            |
| \#define \_USE\_RAK\_MEMORY\_OVERRIDE 0                                  |
|                                                                          |
| /// If defined, OpenSSL is enabled for the class TCPInterface\           |
| /// This is necessary to use the SendEmail class with Google POP         |
| servers\                                                                 |
| /// Note that OpenSSL carries its own license restrictions that you      |
| should be aware of. If you don't agree, don't enable this define\        |
| /// This also requires that you enable header search paths to            |
| DependentExtensions\\openssl-0.9.8g\                                     |
| \#define OPEN\_SSL\_CLIENT\_SUPPORT 0                                    |
|                                                                          |
| /// Threshold at which to do a malloc / free rather than pushing data    |
| onto a fixed stack for the bitstream class\                              |
| /// Arbitrary size, just picking something likely to be larger than most |
| packets\                                                                 |
| \#define BITSTREAM\_STACK\_ALLOCATION\_SIZE 256                          |
|                                                                          |
| // Redefine if you want to disable or change the target for debug        |
| RAKNET\_DEBUG\_PRINTF\                                                   |
| \#define RAKNET\_DEBUG\_PRINTF printf                                    |
|                                                                          |
| // Maximum number of local IP addresses supported\                       |
| \#define MAXIMUM\_NUMBER\_OF\_INTERNAL\_IDS 10                           |
|                                                                          |
| /// This controls the amount of memory used per connection. If more than |
| this many datagrams are sent without an ack, then the ack has no effect\ |
| \#define DATAGRAM\_MESSAGE\_ID\_ARRAY\_LENGTH 512                        |
|                                                                          |
| /// This is the maximum number of reliable user messages that can be on  |
| the wire at a time\                                                      |
| \#define RESEND\_BUFFER\_ARRAY\_LENGTH 512\                              |
| \#define RESEND\_BUFFER\_ARRAY\_MASK 511                                 |
|                                                                          |
| /// Uncomment if you want to link in the DLMalloc library to use with    |
| RakMemoryOverride\                                                       |
| // \#define \_LINK\_DL\_MALLOC                                           |
|                                                                          |
| /// Workaround for http://support.microsoft.com/kb/274323\               |
| /// If two calls between RakNet::GetTime() happen farther apart than     |
| this time in microseconds, this delta will be returned instead\          |
| /// Note: This will cause ID\_TIMESTAMP to be temporarily inaccurate if  |
| you set a breakpoint that pauses the UpdateNetworkLoop() thread in       |
| RakPeer\                                                                 |
| /// Define in RakNetDefinesOverrides.h to enable (non-zero) or disable   |
| (0)\                                                                     |
| \#define GET\_TIME\_SPIKE\_LIMIT 0                                       |
|                                                                          |
| // Use sliding window congestion control instead of ping based           |
| congestion control\                                                      |
| \#define USE\_SLIDING\_WINDOW\_CONGESTION\_CONTROL 1                     |
|                                                                          |
| <span class="RakNetCode">// When a large message is arriving,            |
| preallocate the memory for the entire block\                             |
| // This results in large messages not taking up time to reassembly with  |
| memcpy, but is vulnerable to attackers causing the host to run out of    |
| memory\                                                                  |
| \#define PREALLOCATE\_LARGE\_MESSAGES 0\                                 |
| </span>                                                                  |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ----------------------
  [Index](index.html)\
  ----------------------


