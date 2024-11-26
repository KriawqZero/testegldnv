//
// Created by Marcilio on 25/11/2024.
//

#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#include "../Primitive/Primitive.hpp"

namespace World {
    class Terrain final : public Primitive {
        public:
            explicit Terrain(float _y, float size);
            ~Terrain();
            void createTerrain();

        private:
            float y;
    };
}


#endif //TERRAIN_HPP
