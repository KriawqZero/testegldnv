//
// Created by Marcilio on 25/11/2024.
//

#include "Terrain.hpp"

#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>

namespace World {
    Terrain::Terrain(const float _y, const float size): Primitive(glm::vec3(0.0f, 0.0f, 0.0f)) {
        this->y = _y;
        std::vector<glm::vec3> vertices;
        std::vector<GLuint> indices;

        for (float z = -size; z <= size; z+=1.f) {
            for (float x = -size; x <= size; x+=1.f) {
                vertices.emplace_back(x, y, z);
            }
        }

        // Create Indices
        const unsigned int columnSize = 2 * static_cast<unsigned int>(size) + 1;

        for (unsigned int row = 0; row < columnSize - 1; row++)
        {
            for (unsigned int col = 0; col < columnSize - 1; col++)
            {
                indices.push_back(columnSize * row + col);//upper left
                indices.push_back(columnSize * row + col + 1);//upper right

                indices.push_back(columnSize * row + col);//upper left
                indices.push_back(columnSize * row + col + columnSize);//bottom left

                indices.push_back(columnSize * row + col + columnSize + 1);//bottom right
                indices.push_back(columnSize * row + col + columnSize);//bottom left

                if (col == columnSize - 2)
                {
                    indices.push_back(columnSize * row + col + 1);//upper right
                    indices.push_back(columnSize * row + col + columnSize + 1);//bottom right
                }
            }
        }

        sizeOfVertices = vertices.size();
        sizeOfIndices = indices.size();

        glBindVertexArray(VAO);
        {
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeOfVertices * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 3 * sizeof(GLubyte), 0);
        }
        glBindVertexArray(0);
    }
}
