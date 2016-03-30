<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -----------------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}<span class="RakNetWhiteHeader">Marmalade support</span>
  -----------------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">How to integrate with the Marmalade SDK   |
| </span>                                                                  |
| [Marmalade](http://www.madewithmarmalade.com/) is a SDK that enables you |
| to write games for the IOS and Android using Native C++. It is not a     |
| game engine, although it includes graphic libraries and other tools. As  |
| Marmalade can compile Native C++, it can compile RakNet and therefore    |
| enable you to use RakNet on those platforms in a consistent way.         |
|                                                                          |
| **Step 1 - Download Marmalde:**                                          |
|                                                                          |
| [Download](http://www.madewithmarmalade.com/downloads) and install       |
| Marmalade Beta 5.1 or later. This requires registration and other steps  |
| with Marmalade.                                                          |
|                                                                          |
| **Step 2 - Create RakNet solution:**                                     |
|                                                                          |
| Assuming you have RakNet downloaded, go to                               |
| DependentExtensions\\Marmalade and double click RakNet.mkb. If Marmalade |
| is installed correctly, this will create a directory build\_raknet\_vc9  |
| or similar. If necessary to add or remote RakNet source files, edit in a |
| text editor the .mkb and .mkf files where the RakNet source files are    |
| listed and double click the .mkb again.                                  |
|                                                                          |
| **Step 3 - Build RakNet library:**                                       |
|                                                                          |
| Find the .sln solution file in the directory created in step 2. Open it, |
| and build for all platforms you care about. Build / batch build / select |
| all / build will do this as well. Assuming this worked, you will now     |
| have object files created in a directory such as                         |
| DependentExtensions\\Marmalade\\build\_raknet\_vc9\\Debug\_RakNet\_vc9\_ |
| x86                                                                      |
|                                                                          |
| **Step 4 - Link RakNet to your application:**                            |
|                                                                          |
| Add these two lines to your application .mkb file                        |
|                                                                          |
| option module\_path="../../DependentExtensions/Marmalade"\               |
| subproject RakNet                                                        |
|                                                                          |
| The path under option module\_path should modified to point to wherever  |
| you installed RakNet. There is an example of this under                  |
| Samples\\Marmalade . After doing so you will need to double click the    |
| .mkb file to regenerate your project solution.                           |
|                                                                          |
| If, upon building RakNet, you get a build error "unresolved external     |
| symbol \_strtoull ..." then you need to either update Marmalade to a     |
| newer version, or comment out the last strtoull in                       |
| RakNetGUID::FromString in RakNetTypes.h, then build step 3 again.        |
|                                                                          |
| **Step 5 - Fix allocator:**                                              |
|                                                                          |
| The Marmalade bucket system is not threadsafe. Be sure you have this     |
| code in main()                                                           |
|     #include "RakMemoryOverride.h"                                       |
|                                                                          |
|     void* MarmaladeMalloc(size_t size)                                   |
|     {                                                                    |
|         return s3eMallocBase(size);                                      |
|     }                                                                    |
|     void* MarmaladeRealloc(void *p, size_t size)                         |
|     {                                                                    |
|         return s3eReallocBase(p, size);                                  |
|     }                                                                    |
|     void MarmaladeFree(void *p)                                          |
|     {                                                                    |
|         s3eFreeBase(p);                                                  |
|     }                                                                    |
|     SetMalloc(MarmaladeMalloc);                                          |
|     SetRealloc(MarmaladeRealloc);                                        |
|     SetFree(MarmaladeFree);                                              |
+--------------------------------------------------------------------------+

  --------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}<span class="RakNetWhiteHeader">See Also</span>
  --------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)                                                      |
+--------------------------------------------------------------------------+


