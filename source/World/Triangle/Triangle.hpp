//
// Created by Marcilio on 23/11/2024.
//

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "../Primitive/Primitive.hpp"

namespace World {
    class Triangle final : public Primitive {
        public:
            explicit Triangle(glm::vec3 position);

    };
}
#endif //TRIANGLE_HPP
