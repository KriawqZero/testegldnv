//
// Created by Marcilio on 24/11/2024.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../Shader/Shader.hpp"

class Camera {
    public:
        explicit Camera();
        ~Camera();

        void refresh(float deltaTime, Shader* shader);
        void setWindow(GLFWwindow* window);

        [[nodiscard]] glm::vec3 getPosition() const;
        [[nodiscard]] glm::vec3 getDirection() const;
        [[nodiscard]] glm::vec3 getMovementVector() const;
        [[nodiscard]] glm::vec3 getLeft() const;
        float getDeltaTime() const;

        void updateDirection(double xPos, double yPos);

        bool keyState[1024] = {false};

    private:
        GLFWwindow* window = nullptr;
        float deltaTime;

        double yaw, pitch, lastMouseX, lastMouseY;
        bool firstTimeMouse;

        glm::vec3 movementVector = glm::vec3(0, 0, 0);
        glm::vec3 movementVectorDebug = glm::vec3(0, 0, 0);
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 left;
        glm::vec3 up;

        glm::mat4 view;
        glm::mat4 projection;

        void processInput();
        static glm::mat4 SetAndGetViewport(GLFWwindow* _window);
};

#endif //CAMERA_HPP
