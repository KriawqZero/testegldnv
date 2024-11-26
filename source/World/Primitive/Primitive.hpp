//
// Created by Marcilio on 24/11/2024.
//

#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include <glm/vec3.hpp>

#include "../../Shader/Shader.hpp"

namespace World {
    class Primitive {
        public:
            explicit Primitive(glm::vec3 _worldPosition);

            virtual ~Primitive();

            virtual void render(Shader* shader) const;
            [[nodiscard]] unsigned int getVBO() const;
            [[nodiscard]] unsigned int getVAO() const;
            [[nodiscard]] glm::vec3 getWorldPosition() const;

        protected:
            unsigned int VAO, VBO,  EBO;
            glm::vec3 worldPosition;

            unsigned int sizeOfVertices;
            unsigned int sizeOfIndices;
    };
}

#endif //PRIMITIVE_HPP
