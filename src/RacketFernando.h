//
// Created by Fernando Mamani 40169982.
//

#ifndef ASSIGNMENT_1_RACKETFERNANDO_H
#define ASSIGNMENT_1_RACKETFERNANDO_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Cube.h"

using namespace glm;

class RacketFernando {
private:
    mat4 transform;
    GLuint worldMatrixLocation;
    Cube racketBody;
    Cube racketBodyAlt;
    Cube racketStrings;
public:
    RacketFernando();

    RacketFernando(GLuint worldMatrixLocation);

    void update(mat4 transform);

    void draw(GLuint renderingMode);
};


#endif //ASSIGNMENT_1_RACKETFERNANDO_H
