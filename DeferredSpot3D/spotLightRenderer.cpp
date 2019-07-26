/*
Title: Deferred Spot Lighting
File Name: spotLightRenderer.cpp
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

#include "spotLightRenderer.h"

SpotLightRenderer::SpotLightRenderer()
{
    // In order to set up we just do a simpler version of the mesh loading code.
    std::string filePath = "../assets/cone.obj";

    // before we do anything, lets first check if the file even exists:
    std::ifstream file(filePath);

    if (!file.good())
    {
        // If we encounter an error, print a message and return.
        std::cout << "Can't read file: " << filePath << std::endl;
        return;
    }

    // Now we have to process the string
    std::string line;

    // Loop over every line in the file, storing it in the string 'line'
    while (std::getline(file, line))
    {
        // Let's get started:


        // check if it's a vertex position
        // strncmp checks if the first n characters of these strings match (n is 2 here)
        if (strncmp("v ", &line[0], 2) == 0)
        {
            // strtok takes in a string and a delimiter, storing the string internally.
            // it also returns a pointer to the first character of the first word (split by the character given, " ").
            strtok(&line[0], " ");
            // every time after the first, strtok returns the next word (splitting with the given character) until it runs out of words.
            float x = std::stof(strtok(NULL, " "));
            float y = std::stof(strtok(NULL, " "));
            float z = std::stof(strtok(NULL, " "));
            m_vertices.push_back(glm::vec3(x, y, z)); // make a vector from the given values and store it.
        }
        // faces (these should be last in the file, so we can just interpret them immediately)
        else if (strncmp("f", &line[0], 1) == 0)
        {
            // keep track of the indices from our vector/uv/normal buffer for this face
            std::vector<unsigned int> faceIndices;

            // this will store the vertices as we read over them.
            char* token = strtok(&line[0], " ");

            // loop over the vertices until we get NULL (what strtok returns at the end of the line)
            while ((token = strtok(0, " ")) != NULL)
            {
                // since we only have vertex positions here, we don't have to sort like we would for a different mesh.
                // Just add the indices to the index buffer as wwe create them
                int i = std::stoi(token) - 1;
                m_indices.push_back(i);
            }
            // we're done here
        }
        // other line, just print it out for debug purposes
        else
        {
            std::cout << line << std::endl;
        }
    }

    // After all of that nonsense close the file
    file.close();

    // create buffers for opengl just like normal]

    // Create an instance buffer, we'll fill it when rendering.
    glGenBuffers(1, &m_instanceBuffer);

    // Set up vertex buffer
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Set up index buffer
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

SpotLightRenderer::~SpotLightRenderer()
{
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteBuffers(1, &m_indexBuffer);
    glDeleteBuffers(1, &m_instanceBuffer);
}

void SpotLightRenderer::RenderLights(std::vector<SpotLight> lights, Material* spotLightMaterial)
{

    // Bind the vertex buffer and set the Vertex Attribute.
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    // Do the same thing we normally do when instancing meshes, but for light data
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
    glBufferData(GL_ARRAY_BUFFER, lights.size() * sizeof(SpotLight), lights.data(), GL_STATIC_DRAW);

    // Next, we tell OpenGL how that data is layed out.
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SpotLight), (void*)(0));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(SpotLight), (void*)(sizeof(float) * 4));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(SpotLight), (void*)(sizeof(float) * 8));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(SpotLight), (void*)(sizeof(float) * 12));
    // End of matrix, now attenuation and color
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(SpotLight), (void*)(sizeof(float) * 16));
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(SpotLight), (void*)(sizeof(float) * 20));
    // Length, radius, and exponent values
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, sizeof(SpotLight), (void*)(sizeof(float) * 24));

    // Set Divisors for instance buffer
    for (int i = 1; i < 8; i++)
    {
        glVertexAttribDivisor(i, 1);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    // Enable vertex attribute
    for (int i = 0; i < 8; i++)
    {
        glEnableVertexAttribArray(i);
    }
    // Bind element array buffer and draw all indices in the index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

    // Bind material and draw
    spotLightMaterial->Bind();

    glDrawElementsInstanced(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (void*)0, lights.size());

    spotLightMaterial->Unbind();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Disable vertex attribute and unbind index buffer.
    for (int i = 0; i < 8; i++)
    {
        glDisableVertexAttribArray(i);
    }

    // Set divisors back to default.
    for (int i = 1; i < 8; i++)
    {
        glVertexAttribDivisor(i, 0);
    }

}
