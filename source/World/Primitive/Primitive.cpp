//
// Created by Marcilio on 24/11/2024.
//

#include <GL/glew.h>
#include "Primitive.hpp"

#include <iostream>
#include <glm/ext/matrix_transform.hpp>

#include "../../Shader/Shader.hpp"

namespace World {
    Primitive::Primitive(const glm::vec3 _worldPosition):
    VAO(0), VBO(0), EBO(0),
    worldPosition(_worldPosition),
    sizeOfVertices(0), sizeOfIndices(0){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    Primitive::~Primitive() {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void Primitive::render(Shader* shader) const {
        glBindVertexArray(VAO);

        const glm::mat4 model = translate(glm::mat4(1.0f), worldPosition);
        shader->sendUniform4fvData("modelMatrix", model);

        glDrawArrays(GL_TRIANGLES, 0, sizeOfVertices);

        glBindVertexArray(0);
    }

    unsigned int Primitive::getVBO() const {
        return VBO;
    }

    unsigned int Primitive::getVAO() const {
        return VAO;
    }

    glm::vec3 Primitive::getWorldPosition() const {
        return worldPosition;
    }
}
