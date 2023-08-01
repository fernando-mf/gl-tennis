//
// Created by Fernando Mamani 40169982.
//

#ifndef ASSIGNMENT_1_ARMWITHRACKETFERNANDO_H
#define ASSIGNMENT_1_ARMWITHRACKETFERNANDO_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "SphereFernando.h"
#include "Cube.h"
#include "Texture.h"
#include "ShaderProgram.h"

using namespace glm;

class RacketFernando {
private:
    mat4 transform;
    Cube racketBody;
    Cube racketBodyAlt;
    Cube racketStrings;
    SphereFernando tennisBall;
    Texture tennisBallTexture;
    ShaderProgram colorShader;
    ShaderProgram textureShader;
public:
    RacketFernando();

    RacketFernando(ShaderProgram colorShader, ShaderProgram textureShader);

    void update(mat4 transform);

    void draw(GLuint renderingMode);
};

class ArmWithRacketFernando {
private:
    mat4 transform;
    RacketFernando racket;
    Cube arm;
    ShaderProgram colorShader;
    ShaderProgram textureShader;
public:
    ArmWithRacketFernando(ShaderProgram colorShader, ShaderProgram textureShader);

    void update(mat4 transform);

    void animate(float lastFrameTime, float dt);

    void draw(GLuint renderingMode);

};

#endif //ASSIGNMENT_1_ARMWITHRACKETFERNANDO_H
