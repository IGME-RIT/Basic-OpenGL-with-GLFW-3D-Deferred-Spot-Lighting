/*
Title: Deferred Spot Lighting
File Name: spotLightVert.glsl
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

// Structs in glsl are used to pass collections of data more conveniently
// You have to define the struct at the top of every shader that uses it.
struct spotLight
{
	vec3 position;
	vec3 direction;
	vec4 attenuation;
	vec4 color;
	float range;
	float angle;
	float exponent;
};

// Vertex attribute for position
layout(location = 0) in vec3 in_vertex;
// Matrix is actually 1, 2, 3 and 4
layout(location = 1) in mat4 in_worldMat;

layout(location = 5) in vec4 in_attenuation;
layout(location = 6) in vec4 in_color;
layout(location = 7) in vec3 in_rangeAngleExponent;

uniform mat4 cameraView;

//uniform pointLight in_light;

out spotLight light;
out vec3 screenPosition;

void main(void)
{
	// Compose world and view matrices
	mat4 worldView = cameraView * in_worldMat;
	// Use that matrix to transform our spotlight source position, and direction.
	vec4 sourcePosition = worldView * vec4(0, 0, 0, 1);
	vec3 direction = mat3(worldView) * vec3(0, 0, -1);

	// Pass the light data forward to the fragment step
	light.position = vec3(sourcePosition);
	light.direction = normalize(direction);
	light.attenuation = in_attenuation;
	light.color = in_color;
	light.range = in_rangeAngleExponent.x;
	light.angle = in_rangeAngleExponent.y;
	light.exponent = in_rangeAngleExponent.z;

	// Here we have to change the dimensions of the geometry based on our parameters
	vec4 vertexPosition = vec4(in_vertex, 1);
	vertexPosition.xyz *= in_rangeAngleExponent.x;
	// The width of the cone is scaled by the tanget of our angle (approaches infinity as angle reaches 90 deg)
	vertexPosition.xy *= tan(in_rangeAngleExponent.y);

	// Now we add that position to the light source position
	vertexPosition = in_worldMat * vertexPosition;

	// Transform that position into view space for our final vertex position.
	gl_Position = cameraView * vertexPosition;

	// Get the position of the vertex in screen space.
	screenPosition = vec3(gl_Position);
}