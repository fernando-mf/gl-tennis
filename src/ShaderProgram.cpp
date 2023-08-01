//
// Created by Fernando on 2023-07-31.
//

#include <iostream>

#include "ShaderProgram.h"

using namespace std;

ShaderProgram::ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderPath);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

    int shaderProgram = glCreateProgram();

    // link shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // link program
    glLinkProgram(shaderProgram);

    // check linking status
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "failed to link shader program\n%s\n", infoLog);
    }

    // delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // store matrices locations
    glUseProgram(shaderProgram);

    this->viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    this->projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    this->worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");

    // store shader program id
    this->id = shaderProgram;
}

void ShaderProgram::setViewMatrix(glm::mat4 viewMatrix) {
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void ShaderProgram::setProjectionMatrix(glm::mat4 projectionMatrix) {
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void ShaderProgram::setWorldMatrix(glm::mat4 worldMatrix) {
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
}

const char *readFile(const char *filePath) {
    FILE *f = fopen(filePath, "rb");
    if (f == NULL) {
        fprintf(stderr, "failed to open file %s\n", filePath);
        exit(1);
    }
    fseek(f, 0, SEEK_END);

    long fileSize = ftell(f);
    rewind(f);

    char *contents = new char[fileSize + 1];
    fread(contents, fileSize, 1, f);
    fclose(f);

    contents[fileSize] = 0; // Add null terminator
    return contents;
}

int compileShader(GLenum shaderType, const char *shaderPath) {
    int shader = glCreateShader(shaderType);
    const char *shaderSource = readFile(shaderPath);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "failed to compile shader %s\n%s\n", shaderPath, infoLog);
    }

    return shader;
}