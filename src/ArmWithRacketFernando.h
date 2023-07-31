//
// Created by Fernando Mamani 40169982.
//

#ifndef ASSIGNMENT_1_ARMWITHRACKETFERNANDO_H
#define ASSIGNMENT_1_ARMWITHRACKETFERNANDO_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Cube.h"
#include "RacketFernando.h"

class ArmWithRacketFernando {
private:
    mat4 transform;
    GLuint worldMatrixLocation;
    RacketFernando racket;
    Cube arm;
public:
    ArmWithRacketFernando(GLuint worldMatrixLocation);

    void update(mat4 transform);

    void animate(float lastFrameTime, float dt);

    void draw(GLuint renderingMode);

};


#endif //ASSIGNMENT_1_ARMWITHRACKETFERNANDO_H
