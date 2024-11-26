#version 460

layout(location = 0) in vec3 pos; // Agora usando 3 componentes para posição (x, y, z)
layout(location = 1) in vec3 colorIn;

uniform mat4 projectionMatrix; // Matriz de projeção enviada pela câmera
uniform mat4 viewMatrix;       // Matriz de view enviada pela câmera
uniform mat4 modelMatrix;

//out colorOut;

void main() {
    // Aplicar as transformações de view e projeção
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);

//    colorOut = colorIn;
}
