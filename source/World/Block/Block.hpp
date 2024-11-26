//
// Created by Marcilio on 24/11/2024.
//

#ifndef BLOCK_HPP
#define BLOCK_HPP
#include <glm/vec3.hpp>

#include "../Primitive/Primitive.hpp"

namespace World {
    class Block : public Primitive {
        public:
            explicit Block(glm::vec3 position);
            void render(Shader* shader) const override;
            ~Block() override;
    };
}
#endif //BLOCK_HPP
