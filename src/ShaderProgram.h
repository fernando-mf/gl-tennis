//
// Created by Fernando on 2023-07-31.
//

#ifndef ASSIGNMENT_1_SHADERPROGRAM_H
#define ASSIGNMENT_1_SHADERPROGRAM_H

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class ShaderProgram {
public:
    int id;
    int viewMatrixLocation;
    int projectionMatrixLocation;
    int worldMatrixLocation;

    ShaderProgram();

    ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath);

    void setViewMatrix(mat4 viewMatrix);

    void setProjectionMatrix(mat4 projectionMatrix);

    void setWorldMatrix(mat4 worldMatrix);

    void initializeTextures();
};

const char *readFile(const char *filePath);

int compileShader(GLenum shaderType, const char *shaderPath);


#endif //ASSIGNMENT_1_SHADERPROGRAM_H
