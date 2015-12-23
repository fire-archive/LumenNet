# Before you begin 

## Use the source, static lib, or a DLL?

RakNet includes the source, along with the projects to make the DLL and static lib, and samples. It no longer includes pre-built DLLs or libraries - this is due to incompatibilities across compilers. We recommend using the source directly, however you can also use the DLL or static lib projects to build your own. Projects to build the DLL/Static Lib, and the samples, are provided for Microsoft Visual Studio .Net 2003 and 2005\. Users of other compilers will have to make their own projects.

## DLL Users

Creating a DLL

1.  Create a DLL project. I'll assume you know how to do this. In MSVC 7 you would create an empty project, then under Application Settings you check DLL and empty project.
2.  Add the source files under the /Source directory to the project.
3.  Add to "Additional Include Directories" your directory with the source files.
4.  Import ws2_32.lib, or wsock32.lib if you don't have Winsock 2 installed. In MSVC 7 you can right click on the project, select configuration properties / linker / input / additional dependencies and type "ws2_32.lib" in there.
5.  Set your project to use multi-threaded runtime libraries. In MSVC 7 you can right click on the project, select configuration properties / C/C++ / Code Generation / Runtime Library and change it to Multi-threaded (/MT).
6.  Add _RAKNET_DLL to the Preprocessor Definitions. In VS Project Properties -> Configuration Properties -> C/C++ -> PreProcessor -> Preprocessor Definitions
7.  Set the character set to "not set".In VS Project Properties -> Configuration Properties -> General-> Character Set
8.  Optionally set your [preprocessor directives.](preprocessordirectives.html)
9.  Then hit F7 or the equivalent to build your DLL and Lib.

[![](makedllsmall.jpg)](makedll.jpg)
 
**Creating an empty DLL project in .net 2003** 

[![](multithreadeddebugsmall.jpg)](multithreadeddebug.jpg)
 
**Setting Multithreaded debug in .net 2003** 

[![](ws2_32includesmall.jpg)](ws2_32include.jpg)
 
**Including ws2_32.lib in .net 2003** 

Game Setup

1.  Copy the DLL you just created to your game in the same directory as the exe. The lib can be in any directory you want.
2.  Add the .lib to your project
3.  Add all header files from /Source to your project

If you want to jump right in, refer to the [Basic code tutorial](tutorial.html)
For more detail, refer to [Detailed Implementation](detailedimplementation.html) 

## Source users 

**Game Setup**

1.  Add the files under the /Source directory to the project. While not all of these are strictly necessary, the ones you don't use won't hurt you.
2.  Import ws2_32.lib, or wsock32.lib if you don't have Winsock 2 installed. In MSVC 7 you can right click on the project, select configuration properties / linker / input / additional dependencies and type "ws2_32.lib" in there.
3.  Set your project to use multi-threaded runtime libraries. In MSVC 7 you can right click on the project, select configuration properties / C/C++ / Code Generation / Runtime Library and change it to Multi-threaded (/MT).
4.  Set an additional include path to include the RakNet source (if you copied the source files to a different directory).
5.  Optionally set your [preprocessor directives.](preprocessordirectives.html)

[![](multithreadeddebugsmall.jpg)](multithreadeddebug.jpg)

**Setting Multithreaded debug in .net 2003**

[![](ws2_32includesmall.jpg)](ws2_32include.jpg)

**Including ws2_32.lib in .net 2003**

## 3rd party dependencies 

<span class="RakNetBlueHeader">Projects that won't compile by default</span> Not all projects will build without installing 3rd party dependencies. These are not required to use the majority of RakNet, however you will be missing specific features or demos without them. [3rd party dependencies page](dependencies.html)

## See Also

* [Index](index.html)
* [3rd party dependencies](dependencies.html)
* [Introduction](introduction.html)
* [System Overview](systemoverview.html)
* [Detailed Implementation](detailedimplementation.html)
* [Tutorial](tutorial.html)
* [Preprocessor directives](preprocessordirectives.html)
