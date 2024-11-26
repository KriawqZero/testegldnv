//
// Created by Marcilio on 23/11/2024.
//

#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>
#include <unordered_map>
#include <glm/fwd.hpp>

class Shader {
    public:
        Shader();
        ~Shader();

        int getUniformLocation(const std::string &uniformVariableName);
        void sendUniform4fvData(const std::string &uniformName, const glm::mat4 &data);

        void Use() const;

        void CompileShader(const std::string &vertexPath, const std::string &fragmentPath);
        void LinkShader() const;


    private:
        unsigned int programID;
        unsigned int vertexShaderID;
        unsigned int fragmentShaderID;

        std::unordered_map<std::string, int> uniformLocationCache;
};

#endif //SHADER_HPP
