//
// Created by Marcilio on 23/11/2024.
//

#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "shaderHelper.hpp"

Shader::Shader(): // NOLINT(*-easily-swappable-parameters)
    programID(0), vertexShaderID(0), fragmentShaderID(0)
{

}

Shader::~Shader() {
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

int Shader::getUniformLocation(const std::string &uniformVariableName) {
    //Verifica se já existe essa variável no cache do shaders
    if (uniformLocationCache.contains(uniformVariableName)) {
        return uniformLocationCache[uniformVariableName];
    }

    // Se não existir, procura na GPU e adiciona ao cache
    const int id = glGetUniformLocation(programID, uniformVariableName.c_str());
    uniformLocationCache[uniformVariableName] = id;

    // Joga um erro se esse id não existir dentro da GPU
    if (id == -1) throw std::invalid_argument("uniform variable not found");

    return id;
}

void Shader::sendUniform4fvData(const std::string &uniformName, const glm::mat4 &data) {
    const int id = getUniformLocation(uniformName);
    glUniformMatrix4fv(id, 1, GL_FALSE, value_ptr(data));
}

void Shader::Use() const {
    //Linka o programa no codigo
    glUseProgram(programID);
}

/**
 * Compila e binda o shaders no programa e exclui variaveis desnecessárias
 * @param vertexPath Caminho do vertex_shader
 * @param fragmentPath Caminho do fragment_shader
 * Ambos devem ser relativos
 */
void Shader::CompileShader(const std::string &vertexPath, const std::string &fragmentPath) {
    //Criando objetos
    programID = glCreateProgram();
    std::cout << programID << std::endl;
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    std::cout << vertexShaderID << std::endl;
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::cout << fragmentShaderID << std::endl;

    //Passando o conteudo dos arquivos glsl para a string char
    const std::string vShaderCode = shader_helper::readFile(vertexPath);
    const std::string fShaderCode = shader_helper::readFile(fragmentPath);

    const char* vertexShaderCode = vShaderCode.c_str();
    const char* fragmentShaderCode = fShaderCode.c_str();

    std::cout << vertexShaderCode << std::endl;
    std::cout << fragmentShaderCode << std::endl;

    //Copiando o codigo pros shader IDs
    glShaderSource(vertexShaderID, 1, &vertexShaderCode, nullptr);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, nullptr);
}

/**
 * Linka o shaders bindadado em Shader::CompileShader no programa
 */
void Shader::LinkShader() const {
    //Compila o shader
    glCompileShader(vertexShaderID);
    shader_helper::checkCompileErrors(vertexShaderID, "VERTEX");
    glCompileShader(fragmentShaderID);
    shader_helper::checkCompileErrors(fragmentShaderID, "FRAGMENT");

    //Anexa o shader
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    //Linkar programa
    glLinkProgram(programID);
    shader_helper::checkCompileErrors(programID, "PROGRAM");

    //Deleta pra otimização
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}
