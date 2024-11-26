//
// Created by Marcilio on 24/11/2024.
//

#include "WindowTool.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "../Camera/Camera.hpp"

WindowTool::WindowTool(): window(nullptr) {
}

WindowTool::~WindowTool() = default;

void WindowTool::init(GLFWwindow* window) { // NOLINT(*-convert-member-functions-to-static)
    // Setup Dear ImGui context
    this->window = window;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

}

void WindowTool::renderMainWindow() const {
    // New ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void WindowTool::mainDebugWindow() const {
    const auto* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    ImGui::SetNextWindowPos(ImVec2(10, 10)); // Topo esquerdo com 10px de margem
    ImGui::SetNextWindowSize(ImVec2(200, 380)); // Define um tamanho padrão para a janela
    ImGui::Begin("F3");
    const glm::vec3 pos = camera->getPosition();
    const glm::vec3 dir = camera->getDirection();
    const glm::vec3 left = camera->getMovementVector();

    ImGui::Text("Player Position>\n X: %.3f,\n Y: %.3f,\n Z: %.3f", pos.x, pos.y, pos.z);
    ImGui::Text("Player Direction>\n X: %.3f,\n Y: %.3f,\n Z: %.3f", dir.x, dir.y, dir.z);
    ImGui::Text("Player Left>\n X: %.3f,\n Y: %.3f,\n Z: %.3f", left.x, left.y, left.z);

    const std::string key_w = camera->keyState[GLFW_KEY_W] ? "True" : "False";
    const std::string key_s = camera->keyState[GLFW_KEY_S] ? "True" : "False";
    const std::string key_d = camera->keyState[GLFW_KEY_D] ? "True" : "False";
    const std::string key_a = camera->keyState[GLFW_KEY_A] ? "True" : "False";
    // ImGui::Text(" W: %s\n A: %s,\n S: %s,\n D: %s", key_w.c_str(), key_a.c_str(), key_s.c_str(), key_d.c_str());
    // const char* grounded = game->camera.isGrounded ? "Grounded" : "Not grounded";
    const glm::vec3 mV = camera->getMovementVector();
    ImGui::Text("\nVelocity: \nX: %.2f\nY: %.2f\nZ: %.2f", mV.x, mV.y, mV.z);
    // ImGui::Text("VelocityY: %.1f", camera.currentVelocityY);

    // ImGui::Text("\nFPS: %f", camera->);
    ImGui::Text("MS: %.1f", camera->getDeltaTime() * 100.0f);
    ImGui::End();
}
