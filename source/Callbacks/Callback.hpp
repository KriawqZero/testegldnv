//
// Created by Marcilio on 24/11/2024.
//

#ifndef CALLBACK_HPP
#define CALLBACK_HPP
#include <GLFW/glfw3.h>

class Callback {
    public:
        static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseCallback(GLFWwindow* window, double xPos, double ypos);
};

#endif //CALLBACK_HPP
