<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  --------------------
   Irrlicht FPS Demo
  --------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Demonstrates peer to peer connectivity in |
| a first person shooter</span>\                                           |
| \                                                                        |
| ![](IrrlichtRakNetDemo.jpg)\                                             |
|                                                                          |
| The FPS demo uses the game engine Irrlicht to move actors and bullets    |
| around.                                                                  |
|                                                                          |
| To run it, download [Irrlicht](http://irrlicht.sourceforge.net/), a free |
| game engine. By default, it is assumed to be installed at                |
| C:\\irrlicht-1.6\                                                        |
|                                                                          |
| In the solution, open Samples / 3D Demos / Irrlicht Demo. Right click    |
| and build.                                                               |
|                                                                          |
| Most of the network code is found in RakNetStuff.cpp under               |
| DependentExtensions\\IrrlichtDemo. For a technical description of how    |
| the code was implemented, see readme.txt in that same directory. As the  |
| sample is peer to peer, it requires the NAT punchthrough server to be    |
| running. The jenkinssoftware.com website provides a free server, pointed |
| to by DEFAULT\_NAT\_PUNCHTHROUGH\_FACILITATOR\_IP. If you can't connect, |
| it's likely that the server is down for testing. You can also run your   |
| own server, as the code that is running is the sample code found in the  |
| NAT punchthrough project.                                                |
|                                                                          |
| *The code is located at DependentExtensions\\IrrlichtDemo*               |
+--------------------------------------------------------------------------+

  ---------------
   Dependencies
  ---------------

  -----------------------------------------------------------------------------------------------------------------------------------------
  Irrlicht must be installed. It assumes it was installed to c:\\irrlicht-1.6. It also requires irrKlang for sound, provided by default.\
  -----------------------------------------------------------------------------------------------------------------------------------------

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [ReplicaManager3](replicamanager3.html)\                                 |
| [Index](index.html)\                                                     |
+--------------------------------------------------------------------------+


