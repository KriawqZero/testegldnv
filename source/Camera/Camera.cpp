//
// Created by Marcilio on 24/11/2024.
//

#include "Camera.hpp"

#include <ios>
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#define MOVE_SPEED 10.0F
#define MOUSE_SENSITIVITY 0.1F

Camera::Camera(): deltaTime(0), yaw(0),
    pitch(0), lastMouseX(0),
    lastMouseY(0),
    firstTimeMouse(true),
    position(0.0f, 0.0f, 0.0f),
    direction(0.0f, 0.0f, 1.0f),
    left(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
    view(), projection() {
}

Camera::~Camera() = default;

void Camera::refresh(const float deltaTime, Shader *shader) {
    processInput();
    projection = SetAndGetViewport(window);

    position += movementVector * MOVE_SPEED * deltaTime;

    view = lookAt(position, position + direction, up);

    this->deltaTime = deltaTime;

    shader->sendUniform4fvData("projectionMatrix", projection);
    shader->sendUniform4fvData("viewMatrix", view);
    movementVector = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Camera::setWindow(GLFWwindow *window) {
    this->window = window;
}

glm::vec3 Camera::getPosition() const {
    return position;
}

glm::vec3 Camera::getDirection() const {
    return direction;
}
glm::vec3 Camera::getLeft() const {
    return left;
}

float Camera::getDeltaTime() const {
    return deltaTime;
}

glm::vec3 Camera::getMovementVector() const {
    return movementVectorDebug;
}


//Chamada no callback do mouse
void Camera::updateDirection(const double xPos, const double yPos) {
    if (firstTimeMouse) {
        lastMouseX = xPos;
        lastMouseY = yPos;
        firstTimeMouse = false;
    }

    // Calcule o deslocamento do mouse
    const double dx = xPos - lastMouseX;
    const double dy = yPos - lastMouseY; // Inverter Y para o movimento correto
    lastMouseX = xPos;
    lastMouseY = yPos;

    yaw += dx * MOUSE_SENSITIVITY;
    pitch -= dy * MOUSE_SENSITIVITY;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 front;
    front.x = static_cast<float>(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
    front.y = static_cast<float>(sin(glm::radians(pitch)));
    front.z = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

    direction = normalize(front);
    left = normalize(cross(up, front)); // Vetor esquerdo, perpendicular à direção
}

void Camera::processInput() {
    // Move forward
    if (keyState[GLFW_KEY_W])
        movementVector += glm::vec3(direction.x, 0.0f, direction.z);

    // Move backward
    if (keyState[GLFW_KEY_S])
        movementVector -= glm::vec3(direction.x, 0.0f, direction.z);

    // Move left
    if (keyState[GLFW_KEY_A])
        movementVector += glm::vec3(left.x, 0.0f, left.z);

    // Move right
    if (keyState[GLFW_KEY_D])
        movementVector -= glm::vec3(left.x, 0.0f, left.z);

    // Move up
    if (keyState[GLFW_KEY_SPACE])
        movementVector.y += MOVE_SPEED * 0.08;

    // Move down
    if (keyState[GLFW_KEY_LEFT_SHIFT])
        movementVector.y -= MOVE_SPEED * 0.08;

    movementVectorDebug = movementVector;
}


glm::mat4 Camera::SetAndGetViewport(GLFWwindow *_window) {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(_window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    const float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

    const glm::mat4 projection = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 100.0f);

    return projection;
}
