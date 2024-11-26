//
// Created by Marcilio on 24/11/2024.
//

#ifndef WINDOWTOOL_HPP
#define WINDOWTOOL_HPP
#include <imgui_impl_glfw.h>

class WindowTool {
    public:
        WindowTool();
        ~WindowTool();
        void init(GLFWwindow* window);
        void renderMainWindow() const;
        void mainDebugWindow() const;

        private:
            GLFWwindow* window;

};

#endif //WINDOWTOOL_HPP
