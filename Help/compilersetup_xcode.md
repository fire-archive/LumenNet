# Xcode notes 

Although Raknet is cross-platform, not all of the samples provided will compile/run on Mac OS X or iOS. Here I'll show you how to compile Raknet for Mac OS X and iOS, along with one of the samples for testing | ## | ![](spacer.gif)Compiling as a static library for Mac OS X

Create an empty workspace

1.  Create a folder named _RakNetTests_, and then create a new empty Workspace. Name it _RakNetTests_, and save it inside the new folder

    ![](xcode_newworkspace.jpg)

Create the RakNet static library project

1.  Using _File->New->New Project_, create a new Mac OS X C/C++ library project

    [![](xcode_librarysmall.jpg)](xcode_library.jpg)

    Name it _RakNet_ and use the following options:
    ![](xcode_libraryname.jpg)
    Save it inside the same folder as the workspace

2.  Using Finder, copy RakNet's source code (_Source_ folder) to where RakNet project file was created

    ![](xcode_sourcefolder.jpg)

3.  Right-click the _RakNet_ project, and select _Add Files to "RakNet"..._ , and select the new _Source_ folder you should have in the same folder as the _RakNet_ Project file. Use the following options:

    ![](xcode_addfiles.jpg)

    This should create a _Source_ group, like this:
    ![](xcode_addfiles_newgroup.jpg)

4.  The files inside the _cat_ folder aren't supposed to be compiled, so remove the _Source/cat_ group from the project files.
    When prompted for the deletion method, pick **_Remove References Only_**.
    ![](xcode_remove_cat.jpg)

5.  Build Raknet using _Product->Build_
    You should get a successful compilation.

## ![](spacer.gif)Testing the static library |

A simple sample...

For testing, we're going to use the sample _"Chat Example"_ provided with the Raknet. You can find it the _"Samples/Chat Example"_ folder. This sample has 2 source files, named _"Chat Example Server.cpp"_ and _"Chat Example Client.cpp"_. We are going to create two projects from those files (one project for the Server, and another for the Client).

Inside the folder where you have your workspace, create another folder named _Samples_, and copy _"Chat Example Server.cpp"_ and _"Chat Example Client.cpp"_ into that folder.

The server

1.  Create a _Command Line Tool_ project for the Server:
    ![](xcode_newcommandlinetool.jpg)
    In the next window where it asks for the options for your new project, name it _ChatExampleServer_, leave _Type_ as _C++_, and _"Use Automatic Reference Counting"_ unchecked.
    Save the project inside your _Samples_ folder.

2.  Inside the newly created ChatExampleServer, you should have a group named _ChatExampleServer_. Delete the _main.cpp_ you'll find inside that group, and add the _"Chat Example Server.cpp"_ file

3.  Specify where to look for the RakNet header files, by changing the Build Settings of the ChatExampleServer project. This can be done in the **_Header Search Paths_** option, under the **_Search Paths_** section:
    ![](xcode_headersearchpaths.jpg)
    If your folder structure is exactly the same as the one used for this tutorial, then the search path should be what you see in the above image. If not then you need to adjust it accordingly.
    **NOTE:** The search path is relative to the project file's location.

4.  Link _ChatExampleServer_ project with our RakNet static library, by going to **_Build Phases_**, section **_Link Binary With Libraries_**, clicking the **'+'** button and picking our RakNet library as shown:
    ![](xcode_linkwithlibrary.jpg)

5.  You should be able to successfully build and run the Server now.

The Client

The steps to create the client project are the same as the ones for the Server:

1.  Create a _"Command Line Tool"_ project, and name it _ChatExampleClient_
2.  Delete the file _main.cpp_ and add the file _"Chat Example Client.cpp"_
3.  Change the C/C++ compiler to **_LLVM GCC_**
4.  Set the header search paths
5.  Add _RakNet_ library to the list of libraries to link with.

Running the sample

You should now have 2 products ready to run (ChatExampleClient and ChatExampleServer). You can run one of them from inside Xcode, and run the other externally by right-clicking on it and selecting **"Open With External Editor"**. ## ![](spacer.gif)Compiling as a static library for iOS | Compiling Raknet as a static library for iOS is essentially the same as for Mac OS X. You can create a new project for the iOS library, or you can just create another Target for your Mac OS X static library project, and change what SDK to use: ![](xcode_changesdk.jpg) You can find some iOS samples in the **Samples/iOS** folder. ## ![](spacer.gif)

## See Also

* [Index](index.html)
* [3rd party dependencies](dependencies.html)
* [Introduction](introduction.html)
* [System Overview](systemoverview.html)
* [Detailed Implementation](detailedimplementation.html)
* [Tutorial](tutorial.html)
[Preprocessor directives](preprocessordirectives.html)
