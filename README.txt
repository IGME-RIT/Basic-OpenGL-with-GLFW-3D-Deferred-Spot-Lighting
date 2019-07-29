Documentation Author: Niko Procopi 2019

This tutorial was designed for Visual Studio 2017 / 2019
If the solution does not compile, retarget the solution
to a different version of the Windows SDK. If you do not
have any version of the Windows SDK, it can be installed
from the Visual Studio Installer Tool

Welcome to the 3D Deferred Spotlight Tutorial!
Prerequesites: 3D Deferred Pointlight, (Intro Graphics) Point lighting and Spot lighting

The difference between the last tutorial and this tutorial,
is the same difference between Intro Graphics point light tutorial,
and Intro Graphics. Anyone who has gone through all these prerequisites
should be able to understand this tutorial without any additional explanation,
but we will explain some things anyways.

In the final shader program, compositionFrag.glsl removes directional sunlight,
this was just a matter of preference, it can be put back.
Instead of using icosphere OBJs for the light's geometry, we use cone OBJs.
Light calculation is the same as point light, except with the addition of the light's 
direction, and radius, where all pixels outside the radius are not lit.

How to improve:
Create a Deferred Rendreing system that supports Spotlights, point lights, and directional lights
Create a Deferred Rendering system with shadow mapping
Integrate Deferred Rendering into a game
Port this demo to consoles (Switch, PS4, etc)
