//
// Created by Marcilio on 23/11/2024.
//

#include <GL/glew.h>

#include "Game.hpp"

#include <imgui_impl_opengl3.h>
#include <iostream>
#include <memory>
#include <vector>

#include "../World/Block/Block.hpp"
#include "../World/Triangle/Triangle.hpp"

Game::Game(const float fpsLimit) {
    this->fpsLimit = fpsLimit;
}

std::vector<World::Primitive*> worldObjects;

void Game::init() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    camera.setWindow(window);

    shader.CompileShader("vertex_shader.vert", "fragment_shader.frag");
    shader.LinkShader();

    constexpr int numberOfObjects = 4;

    for (int i = 0; i < numberOfObjects; i++) {
        const glm::vec3 pos(i*2, 0.0f, i*2);
        const auto triangle = new World::Triangle(pos);

        std::cout << "Adding triangle VAO: " << triangle->getVAO() << ", VBO: " << triangle-> getVBO() << std::endl;
        std::cout << "in: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
        worldObjects.push_back(triangle);
    }
    const auto block = new World::Block(glm::vec3(5.0f, 0.0f, -5.0f));
    worldObjects.push_back(block);

    imGuiWindow.init(window);

    // worldObjects[0] = triangle;
}

void Game::update() {
    DeltaTime();

    imGuiWindow.renderMainWindow();
    imGuiWindow.mainDebugWindow();

    camera.refresh(deltaTime, &shader);

    shader.Use();

    // worldObjects[0].render(&shader);

    for (const auto& object : worldObjects) {
        object->render(&shader);
    }


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Game::finish() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void Game::DeltaTime() {
    do {
        currentFrame = static_cast<GLfloat>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;

    } while (deltaTime < 1 / fpsLimit);
    lastFrame = currentFrame;
}


