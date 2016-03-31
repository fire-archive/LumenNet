![Oculus VR, Inc.](RakNet_Icon_Final-copy.jpg){width="150"
height="150"}\
\
\
  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}Overview
  -----------------------------------------------

  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  <span class="RakNetBlueHeader"></span>This file contains additional instructions for using Swig with the optional dependent extension options.\
  \
  The base instructions are available in the [Swig Tutorial](swigtutorial.html)\
  <span class="RakNetBlueHeader"></span><span class="RakNetBlueHeader"></span><span class="RakNetBlueHeader"></span><span style="font-weight: bold;"></span><span style="font-weight: bold;"></span><span style="font-weight: bold;"></span><span style="font-weight: bold;"></span><span style="font-weight: bold;"></span><span class="RakNetBlueHeader"></span>
  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  ----------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Autopatcher MySql Version
  ----------------------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Windows\                                  |
| \                                                                        |
| <span class="RakNetManualTextBody">The below instructions detail the     |
| extra configuration needed on the Visual Studio Project.</span>\         |
| \                                                                        |
| Extra Project Options\                                                   |
| \                                                                        |
| </span><span class="RakNetManualTextBody">Under General-&gt;Common       |
| Language Runtime support the option needs to be set to No Common         |
| Language Runtime support</span><span class="RakNetBlueHeader">\          |
| \                                                                        |
| Additional Include Directories\                                          |
| \                                                                        |
| </span><span class="RakNetManualTextBody">Under Dependent Extensions the |
| following additional directories need to be in the include               |
| configuration.\                                                          |
| \                                                                        |
| -Autopatcher/AutopatcherMySQLRepository\                                 |
| -Autopatcher\                                                            |
| -bzip2-1.0.3\                                                            |
| -MySQLInterface\                                                         |
| \                                                                        |
| MySql header directory needs to be included.\                            |
| \                                                                        |
| For 5.1 on Vista the directory looks like: C:\\Program Files             |
| (x86)\\MySQL\\MySQL Server 5.1\\include</span><span                      |
| class="RakNetBlueHeader">\                                               |
| \                                                                        |
| Additional sources\                                                      |
| \                                                                        |
| </span><span class="RakNetManualTextBody">Under Dependent Extensions the |
| following additional source files need to be included in the project.\   |
| \                                                                        |
| </span><span class="RakNetManualTextBody">-bzip2-1.0.3/blocksort.c\      |
| -</span><span class="RakNetManualTextBody">bzip2-1.0.3/</span><span      |
| class="RakNetManualTextBody">bzip2.c\                                    |
| -</span><span class="RakNetManualTextBody">bzip2-1.0.3/</span><span      |
| class="RakNetManualTextBody">bzlib.c\                                    |
| -</span><span class="RakNetManualTextBody">bzip2-1.0.3/</span><span      |
| class="RakNetManualTextBody">compress.c\                                 |
| -</span><span class="RakNetManualTextBody">bzip2-1.0.3/</span><span      |
| class="RakNetManualTextBody">crctable.c\                                 |
| -</span><span class="RakNetManualTextBody">bzip2-1.0.3/</span><span      |
| class="RakNetManualTextBody">decompress.c\                               |
| -</span><span class="RakNetManualTextBody">bzip2-1.0.3/</span><span      |
| class="RakNetManualTextBody">dlltest.c\                                  |
| -</span><span class="RakNetManualTextBody">bzip2-1.0.3/</span><span      |
| class="RakNetManualTextBody">huffman.c\                                  |
| -</span><span class="RakNetManualTextBody">bzip2-1.0.3/</span><span      |
| class="RakNetManualTextBody">randtable.c\                                |
| \                                                                        |
| -Autopatcher/ApplyPatch.cpp\                                             |
| -</span><span class="RakNetManualTextBody">Autopatcher/</span><span      |
| class="RakNetManualTextBody">AutopatcherClient.cpp\                      |
| -</span><span class="RakNetManualTextBody">Autopatcher/</span><span      |
| class="RakNetManualTextBody">AutopatcherMySQLRepository/</span><span     |
| class="RakNetManualTextBody">AutopatcherMySQLRepository.cpp\             |
| -</span><span class="RakNetManualTextBody">Autopatcher/</span><span      |
| class="RakNetManualTextBody">AutopatcherServer.cpp\                      |
| -</span><span class="RakNetManualTextBody">Autopatcher/</span><span      |
| class="RakNetManualTextBody">CreatePatch.cpp\                            |
| -</span><span class="RakNetManualTextBody">Autopatcher/</span><span      |
| class="RakNetManualTextBody">MemoryCompressor.cpp\                       |
| -</span><span class="RakNetManualTextBody">MySQLInterface/</span><span   |
| class="RakNetManualTextBody">MySQLInterface.cpp\                         |
| \                                                                        |
| Additional Libraries\                                                    |
| \                                                                        |
| </span><span class="RakNetManualTextBody">The MySql library needs to be  |
| included.</span>\                                                        |
| <span class="RakNetManualTextBody">\                                     |
| </span><span class="RakNetManualTextBody">For 5.1 on Vista the location  |
| looks like:\                                                             |
| \                                                                        |
| </span><span class="RakNetManualTextBody">For debug:\                    |
| C:\\Program Files (x86)\\MySQL\\MySQL Server                             |
| 5.1\\lib\\debug\\libmysql.lib\                                           |
| \                                                                        |
| </span><span class="RakNetManualTextBody">For release:\                  |
| C:\\Program Files (x86)\\MySQL\\MySQL Server                             |
| 5.1\\lib\\opt\\libmysql.lib</span>\                                      |
|                                                                          |
| <span class="RakNetBlueHeader">Replacement Swig File Generation Tool     |
| Steps\                                                                   |
| \                                                                        |
| <span class="RakNetManualTextBody">These are replacement steps. If the   |
| dll project is used the PreBuild.bat needs to be modified, the last      |
| steps are instructions on how to do that.</span>\                        |
| </span>                                                                  |
| 1.  Click the start menu and click on run. In Vista click                |
|     start-&gt;search type "run" hit enter.                               |
| 2.  Type cmd and hit enter.                                              |
| 3.  In the next command PATH\_TO\_RAKNET\_SWIG\_FILES is the path to the |
|     swig directory. For example C:\\RakNet\\DependentExtensions\\Swig    |
| 4.  Type cd PATH\_TO\_RAKNET\_SWIG\_FILES hit enter                      |
| 5.  In the next command PATH\_TO\_RAKNETSOURCE is the path to the swig   |
|     source directory. For example: C:\\RakNet\\Source. PATH\_TO\_SWIG is |
|     an unquoted path with a trailing slash to the Swig directory         |
|     Example: C:\\Swig\\. If you added swig to your path variable         |
|     then PATH\_TO\_SWIG is not needed and can be ignored or set to       |
|     "". PATH\_TO\_DEPENDENTEXTENSIONS is the path to the Dependent       |
|     Extensions directory Example: C:\\RakNet\\DependentExtensions.       |
|     OPTION1 in this case will be MYSQL\_AUTOPATCHER.                     |
| 6.  Type MakeSwigWithExtras.bat PATH\_TO\_RAKNETSOURCE PATH\_TO\_SWIG    |
|     PATH\_TO\_DEPENDENTEXTENSIONS OPTION1 hit enter\                     |
| 7.  If you want to use SQLiteClientLoggerPlugin skip \#6, the next steps |
|     will be used instead.                                                |
| 8.  If you have added swig to your path variable, just use "" for        |
|     PATH\_TO\_SWIG                                                       |
| 9.  PATH\_TO\_SQLITEPLUGIN is the path to the SQLite plugin directory.   |
|     EX: C:\\RakNet\\DependentExtensions\\SQLite3Plugin                   |
| 10. Type MakeSwig.bat PATH\_TO\_RAKNETSOURCE PATH\_TO\_SWIG              |
|      PATH\_TO\_SQLITEPLUGIN hit enter                                    |
| 11. If you are not using the DLL\_Swig project goto "Creating the Swig   |
|     Wrapped DLL Project" in the [Swig Tutorial](swigtutorial.html)       |
| 12. If you are using the DLL\_Swig project, in the project directory     |
|     there is a file called Prebuild.bat, open it for editing.            |
| 13. Replace the line "MakeSwig.bat "../../Source"" with the command      |
|     created in these steps.                                              |
| 14. Now goto "Creating the Swig Wrapped DLL Project" in the [Swig        |
|     Tutorial](swigtutorial.html). Make sure the extra configuration in   |
|     this help file is followed.                                          |
|                                                                          |
| <span class="RakNetBlueHeader"></span><span class="RakNetBlueHeader">\   |
| Replacement Swig File Generation Manual Steps\                           |
| </span>                                                                  |
| 1.  Click the start menu and click on run. In Vista click                |
|     start-&gt;search type "run" hit enter.                               |
| 2.  Type cmd and hit enter.                                              |
| 3.  In the next command PATH\_TO\_RAKNET\_SWIG\_FILES is the path to the |
|     swig directory. For example C:\\RakNet\\DependentExtensions\\Swig    |
| 4.  Type cd PATH\_TO\_RAKNET\_SWIG\_FILES hit enter                      |
| 5.  In the next command PATH\_TO\_RAKNETSOURCE is the path to the swig   |
|     source directory. For example:                                       |
|     C:\\RakNet\\Source. PATH\_TO\_DEPENDENTEXTENSIONS is the path to the |
|     Dependent Extensions directory                                       |
|     Example: C:\\RakNet\\DependentExtensions.                            |
| 6.  Type C:\\Swig\\swig -c++ -csharp -namespace RakNet                   |
|     -I"PATH\_TO\_RAKNETSOURCE" -I"SwigInterfaceFiles"                    |
|     -I"PATH\_TO\_DEPENDENTEXTENSIONS"                                    |
|     -DSWIG\_ADDITIONAL\_AUTOPATCHER\_MYSQL -outdir                       |
|     SwigOutput\\SwigCSharpOutput -o                                      |
|     SwigOutput\\CplusDLLIncludes\\RakNet\_wrap.cxx                       |
|     SwigInterfaceFiles\\RakNet.i hit enter                               |
| 7.  Goto "Creating the Swig DLL" in the [Swig                            |
|     Tutorial](swigtutorial.html). Make sure the extra configuration in   |
|     this help file is followed.[](swigtutorial.html)                     |
|                                                                          |
| <span class="RakNetBlueHeader"></span><span                              |
| class="RakNetBlueHeader">Linux</span>\                                   |
| \                                                                        |
| <span class="RakNetBlueHeader">Replacement Swig File Tool Steps\         |
| \                                                                        |
| </span><span class="RakNetBlueHeader"> <span                             |
| class="RakNetManualTextBody">Note: The Linux batch <span                 |
| class="RakNetBlueHeader"></span><span                                    |
| class="RakNetBlueHeader"></span>requires Wget,Tar,Make and GCC  to be    |
| installed, unless swig is already installed. Most of the time            |
| </span></span><span class="RakNetBlueHeader"><span                       |
| class="RakNetManualTextBody">Wget,Tar,Make and GCC                       |
| are</span></span><span class="RakNetBlueHeader"><span                    |
| class="RakNetManualTextBody"> already installed.</span>\                 |
| </span>                                                                  |
| 1.  Open a terminal if you are not already at one.\                      |
| 2.  In the next command PATH\_TO\_RAKNET\_SWIG\_FILES is the path to the |
|     swig directory. For example                                          |
|     /home/usr/RakNet/DependentExtensions/Swig                            |
| 3.  Type cd PATH\_TO\_RAKNET\_SWIG\_FILES hit enter                      |
| 4.  Type chmod u+x MakeSwig.sh\                                          |
| 5.  In the next command PATH\_TO\_RAKNETSOURCE is the path to the swig   |
|     source directory. For                                                |
|     example: /home/usr/RakNet/Source. PATH\_TO\_DEPENDENTEXTENSIONS is   |
|     the path to the Dependent Extensions                                 |
|     directory Example: /home/usr/RakNet/DependentExtensions. OPTION1 in  |
|     this case will be MYSQL\_AUTOPATCHER.                                |
| 6.  Type MakeSwigWithExtras.sh PATH\_TO\_RAKNETSOURCE                    |
|      PATH\_TO\_DEPENDENTEXTENSIONS OPTION1 hit enter                     |
| 7.  If you want to use SQLiteClientLoggerPlugin skip \#6, the next steps |
|     will be used instead.\                                               |
| 8.  PATH\_TO\_SQLITEPLUGIN is the path to the SQLite plugin directory.   |
|     EX: /home/usr/RakNet/DependentExtensions/SQLite3Plugin\              |
| 9.  Type MakeSwig.sh PATH\_TO\_RAKNETSOURCE PATH\_TO\_SQLITEPLUGIN hit   |
|     enter\                                                               |
| 10. Skip to "Creating the C\# project" in the [Swig                      |
|     Tutorial](swigtutorial.html).                                        |
|                                                                          |
| \                                                                        |
| <span class="RakNetBlueHeader">Replacement Manual Swig File Generation   |
| Steps</span>\                                                            |
| \                                                                        |
| 1.  Open a terminal\                                                     |
| 2.  In the next command PATH\_TO\_RAKNET\_SWIG\_FILES is the path to the |
|     swig directory. For example                                          |
|     /home/usr/RakNet/DependentExtensions/Swig                            |
| 3.  Type cd PATH\_TO\_RAKNET\_SWIG\_FILES hit enter                      |
| 4.  In the next command PATH\_TO\_RAKNETSOURCE is the path to the swig   |
|     source directory. For example: /home/usr/RakNet/Source               |
| 5.  Type swig -c++ -csharp -namespace RakNet -I"PATH\_TO\_RAKNETSOURCE"  |
|     -I"SwigInterfaceFiles" -outdir SwigOutput/SwigCSharpOutput -o        |
|     SwigOutput/CplusDLLIncludes/RakNet\_wrap.cxx                         |
|     SwigInterfaceFiles/RakNet.i and hit enter                            |
| 6.  Goto the next section below.                                         |
|                                                                          |
| Replacement Creating the Swig  Dynamic Link Steps                        |
|                                                                          |
| <span class="RakNetManualTextBody">Note: If you ran the linux batch tool |
| it will have made the dynamic link and attempted to install it, so you   |
| may skip these steps if it ran successfully.</span>\                     |
|                                                                          |
| 1.  In the next command PATH\_TO\_RAKNET\_SWIG\_FILES is the path to the |
|     swig directory. <span                                                |
|     style="font-size: 12pt; font-family: &quot;Times New Roman&quot;;">  |
|     EX:: </span>../DependentExtensions/Swig<span                         |
|     style="font-size: 12pt; font-family: &quot;Times New Roman&quot;;">< |
| /span>                                                                   |
| 2.  In the next command PATH\_TO\_DEPENDENTEXTENSIONS is the path to the |
|     Dependent Extensions directory. EX:                                  |
|     /home/usr/RakNet/DependentExtensions                                 |
| 3.  First we need to compile the C files seperatly with GCC in C mode    |
|     type the following command and hit enter: gcc                        |
|     -c PATH\_TO\_DEPENDENTEXTENSIONS/bzip2-1.0.3/blocksort.c PATH\_TO\_D |
| EPENDENTEXTENSIONS/bzip2-1.0.3/bzip2.c PATH\_TO\_DEPENDENTEXTENSIONS/bzi |
| p2-1.0.3/bzlib.c PATH\_TO\_DEPENDENTEXTENSIONS/bzip2-1.0.3/compress.c PA |
| TH\_TO\_DEPENDENTEXTENSIONS/bzip2-1.0.3/crctable.c PATH\_TO\_DEPENDENTEX |
| TENSIONS/bzip2-1.0.3/decompress.c PATH\_TO\_DEPENDENTEXTENSIONS/bzip2-1. |
| 0.3/dlltest.c PATH\_TO\_DEPENDENTEXTENSIONS/bzip2-1.0.3/huffman.c        |
|     \$2/bzip2-1.0.3/randtable.c\                                         |
| 4.  Now we use those object files and compile the C++ files with C++     |
|     mode type the following command and hit enter: g++                   |
|     \*.cpp PATH\_TO\_RAKNET\_SWIG\_FILE/SwigOutput/CplusDLLIncludes/RakN |
| et\_wrap.cxx                                                             |
|     blocksort.o bzip2.o bzlib.o compress.o crctable.o decompress.o       |
|     dlltest.o huffman.o                                                  |
|     randtable.o PATH\_TO\_DEPENDENTEXTENSIONS/Autopatcher/ApplyPatch.cpp |
|  PATH\_TO\_DEPENDENTEXTENSIONS/Autopatcher/AutopatcherClient.cpp PATH\_T |
| O\_DEPENDENTEXTENSIONS/Autopatcher/AutopatcherMySQLRepository/Autopatche |
| rMySQLRepository.cpp PATH\_TO\_DEPENDENTEXTENSIONS/Autopatcher/Autopatch |
| erServer.cpp PATH\_TO\_DEPENDENTEXTENSIONS/Autopatcher/CreatePatch.cpp P |
| ATH\_TO\_DEPENDENTEXTENSIONS/Autopatcher/MemoryCompressor.cpp PATH\_TO\_ |
| DEPENDENTEXTENSIONS/MySQLInterface/MySQLInterface.cpp                    |
|     -l pthread -lmysqlclient -I/usr/include/mysql/ -I./                  |
|     -IPATH\_TO\_DEPENDENTEXTENSIONS/Autopatcher/AutopatcherMySQLReposito |
| ry                                                                       |
|     -IPATH\_TO\_DEPENDENTEXTENSIONS/Autopatcher                          |
|     -IPATH\_TO\_DEPENDENTEXTENSIONS/bzip2-1.0.3                          |
|     -IPATH\_TO\_DEPENDENTEXTENSIONS/MySQLInterface -shared -o RakNet     |
|                                                                          |
| 5.  Note: In the previous command -l pthread is lower case L while -I./  |
|     is uppercase i.                                                      |
| 6.  If you wish to use SQLiteClientLoggerPlugin in the place of \#2 use  |
|     the below instructions                                               |
| 7.   PATH\_TO\_SQLITEPLUGIN is the path to the SQLite plugin directory.  |
|     EX: /home/usr/RakNet/DependentExtensions/SQLite3Plugin               |
| 8.  g++                                                                  |
|     \*.cpp PATH\_TO\_RAKNET\_SWIG\_FILES/SwigOutput/CplusDLLIncludes/Rak |
| Net\_wrap.cxx                                                            |
|     PATH\_TO\_SQLITEPLUGIN\\SQLite3ClientPlugin.cpp                      |
|     PATH\_TO\_SQLITEPLUGIN \\SQLite3PLuginCommon.cpp                     |
|     PATH\_TO\_SQLITEPLUGIN                                               |
|     \\Logger\\ClientOnly\\SQLiteClientLoggerPlugin.cpp                   |
|     PATH\_TO\_SQLITEPLUGIN \\Logger\\SQLliteLoggerCommon.cpp  -l pthread |
|     -I./ -IPATH\_TO\_SQLITEPLUGIN\\Logger\\ClientOnly -IPATH\_TO\_SQLITE |
| PLUGIN\\Logger -IPATH\_TO\_SQLITEPLUGIN                                  |
|     -shared -o RakNet                                                    |
| 9.  A file called RakNet should be created that will be copied in the    |
|     next section                                                         |
| 10. Go to "Creating the C\# project" in the [Swig                        |
|     Tutorial](swigtutorial.html).[](swigtutorial.html)                   |
|                                                                          |
| \                                                                        |
| <span class="RakNetBlueHeader">\                                         |
| </span>                                                                  |
+--------------------------------------------------------------------------+

\
  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Swig Tutorial\                                                          |
| Index](index.html)                                                       |
+--------------------------------------------------------------------------+


