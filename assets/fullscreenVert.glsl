/*
Title: Deferred Spot Lighting
File Name: fullscreenVert.glsl
Copyright ? 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#version 400 core


void main(void)
{
	// Calculate coordinates based on the index.
	// With more vertices, this algorithm would create an endless strip of triangles.

	/*
	   [2]
	    |
	    |
	    +---------+
	    |         |
	    |         |  
	   [0]--------+--------[1]
	*/
	vec2 coord;
	coord.x = mod(gl_VertexID, 2) * 4 - 1;
	coord.y = floor(gl_VertexID / 2) * 4 - 1;

	gl_Position = vec4(coord, 0, 1);
}