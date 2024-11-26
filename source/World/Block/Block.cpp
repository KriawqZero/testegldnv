//
// Created by Marcilio on 24/11/2024.
//

#include "Block.hpp"

#include <iostream>
#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

namespace World {
    Block::Block(const glm::vec3 position): Primitive(position) {
        glGenBuffers(1, &EBO);

        constexpr float d = 0.5;
        constexpr GLfloat vertices[] = {
            // Front face
            d, d, d,   // 0 - Top right
            -d, d, d,  // 1 - Top left
            -d, -d, d, // 2 - Bottom left
            d, -d, d,  // 3 - Bottom right
            // Back face
            d, -d, -d,  // 4 - Bottom right
            d, d, -d,   // 5 - Top right
            -d, d, -d,  // 6 - Top left
            -d, -d, -d, // 7 - Bottom left
        };

        const GLuint indices[] = {
            // Front face
            0, 1, 2, //T1 - 1
            2, 3, 0, //T2 - 2
            // Back face
            4, 5, 6, //T1 - 3
            6, 7, 4, //T2 - 4
            // Top face
            0, 5, 6, // T1 - 5
            6, 1, 0, // T2 - 6
            // Left face
            1, 6, 7, // T1 - 7
            7, 3, 1, // T2 - 8
            // Bottom face
            2, 3, 4, // T1 - 9
            4, 7, 2, // T2 - 10
            // Right Face
            3, 4, 5,
            5, 0, 3
        };
        glBindVertexArray(VAO);
        {
            sizeOfVertices = sizeof(vertices) * sizeof(GLfloat);
            sizeOfIndices = sizeof(indices) * sizeof(GLuint);
            // Vertice buffer
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);

            // Indice buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);
        }
        glBindVertexArray(0);
    }

    void Block::render(Shader* shader) const {
        glBindVertexArray(VAO);

        // Configurar a matriz modelo para a posição no mundo
        const glm::mat4 model = translate(glm::mat4(1.0f), worldPosition);
        shader->sendUniform4fvData("modelMatrix", model);

        // Desenhar o cubo com índices
        glDrawElements(GL_TRIANGLES, sizeOfVertices, GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);
    }


    Block::~Block() {
        glDeleteBuffers(1, &EBO);
    }
}
