An attempt to produce 3D Rendering in C++ from scratch, using SFML (A wrapper of OpenGL).
<br>
It operates as a 3D wireframe renderer, for now. The source includes a basic cube. It is still WIP.
<br>
I might upload a post on my website  breaking this down someday.

# Instruction
## Prerequisites
SFML, g++ since I run it on my Debian install; I am completely oblivious to the fact of running this on Windows.

## Building/Compilation/Running
To Compile on Linux
``g++ main.cpp -o renderer -lsfml-graphics -lsfml-window -lsfml-system``

Run using,
``./renderer``

Move using WASD. Rotate using Arrow keys. LShift and Spacebar for moving in/out.
