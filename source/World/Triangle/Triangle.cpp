//
// Created by Marcilio on 23/11/2024.
//

#include "Triangle.hpp"

#include <iostream>
#include <ostream>
#include <GL/glew.h>

namespace World {
    Triangle::Triangle(const glm::vec3 position): Primitive(position) {
        constexpr GLfloat vertices[] = {
            0.0f, 0.5f, 1.0f,
            -0.5f, -0.5f, 1.0f,
            0.5f, -0.5f, 1.0f
        };

        sizeOfVertices = sizeof(vertices) * sizeof(GLfloat);

        std::cout << sizeof(vertices) << std::endl;
        std::cout << sizeof(float) << std::endl;
        std::cout << sizeOfVertices << std::endl;
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
            vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,
            0, nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

}
