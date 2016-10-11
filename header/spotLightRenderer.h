/*
Title: Deferred Spot Lighting
File Name: spotLightRenderer.h
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

#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "../header/material.h"

//struct for spotlight
struct SpotLight
{
    glm::mat4 m_worldMatrix; // A matrix is required to rotate and position the cone volume for our spot light
    // Note: You could include the scale based on angle and range, but we'd have to send them for the fragment shader anyway, so we wont.
    glm::vec4 m_attenuation; // Defines light strength based on distance from light source
    glm::vec4 m_color; // RBG Color of the light
    float m_range; // Length light extends from transform position
    float m_angle; // Angle of cone used for spot light
    float m_exponent; // Exponent used to calculate light intensity based on angle

    // Defines a spotlight
    SpotLight(glm::mat4 worldMatrix, glm::vec4 attenuation, glm::vec4 color, float range, float angle, float exponent) {
        m_worldMatrix = worldMatrix;
        m_attenuation = attenuation;
        m_color = color;
        m_range = range;
        m_angle = angle;
        m_exponent = exponent;
    }
};


class SpotLightRenderer
{
public:

    SpotLightRenderer();
    ~SpotLightRenderer();
    
    void RenderLights(std::vector<SpotLight> lights, Material* spotLightMaterial);

private:

    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    GLuint m_instanceBuffer;

    std::vector<glm::vec3> m_vertices;
    std::vector<unsigned int> m_indices;
};