---
title: "Irrlicht FPS Demo"
excerpt: "Demonstrates peer to peer connectivity in a first person shooter"
---
[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/zM8OWOJ8TOW9dMJ4he49",
        "IrrlichtRakNetDemo.jpg",
        "806",
        "625",
        "#8a6a42",
        ""
      ]
    }
  ]
}
[/block]
The FPS demo uses the game engine Irrlicht to move actors and bullets around.

To run it, download [Irrlicht](http://irrlicht.sourceforge.net/), a free game engine. By default, it is assumed to be installed at C:\irrlicht-1.6  

In the solution, open Samples / 3D Demos / Irrlicht Demo. Right click and build.

Most of the network code is found in RakNetStuff.cpp under DependentExtensions\IrrlichtDemo. For a technical description of how the code was implemented, see readme.txt in that same directory. As the sample is peer to peer, it requires the NAT punchthrough server to be running. The jenkinssoftware.com website provides a free server, pointed to by DEFAULT_NAT_PUNCHTHROUGH_FACILITATOR_IP. If you can't connect, it's likely that the server is down for testing. You can also run your own server, as the code that is running is the sample code found in the NAT punchthrough project.

_The code is located at DependentExtensions\IrrlichtDemo_


|---------------| |  Dependencies | |----------------------------------------------------------------------------------------------------------------------------------------| | Irrlicht must be installed. It assumes it was installed to c:\\irrlicht-1.6\. It also requires irrKlang for sound, provided by default. | |-------------------------| | ![](spacer.gif)See Also |

[ReplicaManager3](replicamanager3.html)  
[Index](index.html)