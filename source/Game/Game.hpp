//
// Created by Marcilio on 23/11/2024.
//

#ifndef GAME_HPP
#define GAME_HPP
#include <GLFW/glfw3.h>

#include "../Camera/Camera.hpp"
#include "../Shader/Shader.hpp"
#include "../WindowTool/WindowTool.hpp"

class Game {
    public:
        explicit Game(float fpsLimit);
        void init();
        void update();
        void finish();
        int run();

    private:
        GLFWwindow* window = nullptr;
        Shader shader;
        Camera camera;
        WindowTool imGuiWindow;

        void DeltaTime();
        float fpsLimit;
        float deltaTime = 0;
        float currentFrame = 0;
        float lastFrame = 0;
};



#endif //GAME_HPP
