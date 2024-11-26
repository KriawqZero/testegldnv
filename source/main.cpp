#include <iostream>
#include <GL/glew.h>

#include "Callbacks/Callback.hpp"
#include "Game/Game.hpp"

#define WIDTH 1280
#define HEIGHT 720
#define PROJECT_NAME "Minecraft: OpenGL Modern"
#define FPS_LIMIT 60

int Game::run() {
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);

    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    const GLenum err = glewInit();
    if (GLEW_OK != err) {
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << err << std::endl;
        return -1;
    }

    glfwSetWindowUserPointer(window, &camera);
    glfwSetKeyCallback(window, Callback::KeyboardCallback);
    glfwSetCursorPosCallback(window, Callback::MouseCallback);

    init();
    // const World::Triangle* triangle = new World::Triangle(glm::vec3(0.0f, 0.0f, 0.0f));
    std::cout << sizeof(GLfloat) << std::endl;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        update();
        // triangle->render(&shader);

        glfwSwapBuffers(window);
    }
    finish();
    glfwTerminate();
    return 0;
}

int main() {
    Game game(FPS_LIMIT);
    return game.run();
}
