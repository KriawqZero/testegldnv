//
// Created by Marcilio on 23/11/2024.
//

#ifndef SHADERHELPER_HPP
#define SHADERHELPER_HPP
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <GL/glew.h>

class shader_helper {
    public:
        static void checkCompileErrors(const unsigned int shader, const std::string& type) {
            int success;
            char infoLog[1024];
            if (type != "PROGRAM") {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                    std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                              << infoLog << "\n -- --------------------------------------------------- -- "
                              << std::endl;
                }
            } else {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                    std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                              << infoLog << "\n -- --------------------------------------------------- -- "
                              << std::endl;
                }
            }
        }
        static std::string readFile(const std::string& filePath) {
            std::fstream file(filePath);

            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + filePath);
            }

            std::stringstream ss;
            std::string line;

            while (std::getline(file, line)) {
                ss << line << "\n";
            }
            file.close();

            return ss.str();
        }

};

#endif //SHADERHELPER_HPP
