# Basic OpenGL with GLFW: 3D Deferred Spot Lighting

This demo adds spot lights to the previous deferred point lighting example.
For our point lighting, sphere volume, and rendered it at a position on screen.
For a spot light, we'll need a cone volume, which makes things slightly more complicated.
Instead of sending a single position, we'll need to send a world matrix to rotate and position the cone correctly.

# Setup

You will need to have CMake installed on your computer, and properly added to your path.
In order to setup, run the following in a shell, then open the project in your preferred editor.
Windows setup has been configured for use with Visual Studio.

Windows:
```
cd path/to/folder
setup.cmd
```
Linux:
```
cd path/to/folder
./setup
```
