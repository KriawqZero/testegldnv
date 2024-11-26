//
// Created by Marcilio on 24/11/2024.
//

#include "Callback.hpp"

#include <iostream>
#include <ostream>

#include "../Camera/Camera.hpp"

void Callback::KeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (action == GLFW_PRESS) camera->keyState[key] = true;

    else if (action == GLFW_RELEASE) camera->keyState[key] = false;
}

void Callback::MouseCallback(GLFWwindow *window, const double xPos, const double ypos) {
    auto* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    camera->updateDirection(xPos, ypos);
}