An attempt to produce 3D Rendering in C++ from scratch, using SFML.
<br>
It operates as a 3D wireframe renderer, for now. The source includes a basic cube. It is still WIP.
<br>
I might upload a post on my website breaking this down someday.

# Instructions
## Prerequisites
SFML (libsfml), g++

since I run it on my Linux install, I am completely oblivious to the method of running this on Windows, or Mac. Run it if you know how to.

## Building/Compilation/Running on Linux
To Compile on Linux

``g++ main.cpp -o renderer -lsfml-graphics -lsfml-window -lsfml-system``

Run using

``./renderer``

Move using WASD. Rotate using Arrow keys. LShift and Spacebar for moving in/out.

# To-Do
Proper meshes, <br>
Support for .stl files, maybe other formats - basically, support for  any commonly used portable 3D format, <br>
Textures(?), maybe? Along with shading, lighting. <br>
Documentation explaining the logic behind its operation.

