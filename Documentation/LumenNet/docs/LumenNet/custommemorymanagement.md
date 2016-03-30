<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ------------------------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}<span class="RakNetWhiteHeader">Custom Memory Management</span>
  ------------------------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| Override new, delete, malloc, free, and realloc                          |
| Users wishing to provide custom memory management functions can do so    |
| via RakMemoryOverride.cpp.                                               |
|                                                                          |
| There are 3 global pointers defined in this file, with predefined        |
| defaults:                                                                |
|                                                                          |
| void\* (\*rakMalloc) (size\_t size) = RakMalloc;\                        |
| void\* (\*rakRealloc) (void \*p, size\_t size) = RakRealloc;\            |
| void (\*rakFree) (void \*p) = RakFree;                                   |
|                                                                          |
| To override, simply set the values of these variables to something else. |
|                                                                          |
| For example, to override malloc, you may write:                          |
|                                                                          |
| \#include "RakMemoryOverride.h"                                          |
|                                                                          |
| void \*MyMalloc(size\_t size)\                                           |
| {\                                                                       |
| return malloc(size);\                                                    |
| }                                                                        |
|                                                                          |
| int main()\                                                              |
| {\                                                                       |
| rakMalloc=MyMalloc;\                                                     |
| // ...\                                                                  |
| }                                                                        |
|                                                                          |
| Then edit the file RakNetDefinesOverrides.h and add                      |
|                                                                          |
| \#define \_USE\_RAK\_MEMORY\_OVERRIDE 1                                  |
|                                                                          |
| Alternatively, edit RakNetDefines.h \_USE\_RAK\_MEMORY\_OVERRIDE         |
+--------------------------------------------------------------------------+

  --------------------------------------------------------------------------------------
  ![](spacer.gif){width="8" height="1"}<span class="RakNetWhiteHeader">See Also</span>
  --------------------------------------------------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| [NetworkIDObject](networkidobject.html)                                  |
+--------------------------------------------------------------------------+


