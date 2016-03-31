<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -----------------------------
   Ogre 3D Interpolation Demo
  -----------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Demonstrates 3D interpolation</span>\     |
| \                                                                        |
| The Ogre 3D interpolation demo uses the graphics engine Ogre 3D to       |
| render popcorn popping.\                                                 |
| \                                                                        |
| The server has a bunch of popcorn kernels, which pops and flies around.  |
| After a short while all the popcorn is deleted and respawned.\           |
| \                                                                        |
| The client is a dumb client in that the client does not do any physics   |
| or handle the details of spawning or popping the corn kernels.\          |
| \                                                                        |
| *Specific to Ogre:*\                                                     |
| \                                                                        |
| How to interpolate between the real and the visual position using a      |
| helper class TransformationHistory. Given a time in the past, it will    |
| tell you where you were then, using interpolation. If you hold down      |
| space you can see the client run non-interpolated, which is very choppy  |
| indeed, as it only sends 4 times a second. Let go of space and it's      |
| smooth again.\                                                           |
| \                                                                        |
| *Covered as part of RakNet:*\                                            |
| \                                                                        |
| ReplicaManager3 class, which automatically handles the networking for    |
| creation, destruction, and serialization of the popcorn kernels.\        |
| \                                                                        |
| To run it, start two instances on the same computer. Press 's' for       |
| server on one instance, 'c' for client on the other. Hold down space to  |
| see the client run without interpolation.\                               |
| \                                                                        |
| If you want to run it over the internet. change the hardcoded SERVER\_IP |
| variable to the server's address.                                        |
|                                                                          |
| *The code is located at DependentExtensions\\Ogre3DInterpDemo*           |
+--------------------------------------------------------------------------+

  ---------------
   Dependencies
  ---------------

  ------------------------------------------------------------------------------------------------------------------------------------------
  Ogre 3D must be installed. It assumes you have OGRE\_SDK as an environment variable. If not, change the project properties accordingly.\
  \
  ------------------------------------------------------------------------------------------------------------------------------------------

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [ReplicaManager3](replicamanager3.html)\                                 |
| [Index](index.html)\                                                     |
+--------------------------------------------------------------------------+


