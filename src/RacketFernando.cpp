//
// Created by Fernando Mamani 40169982.
//

#include "RacketFernando.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Cube.h"

using namespace glm;
using namespace std;

const vec3 COLOR_RACKET_BODY = vec3(0.44f, 0.0f, 0.008f);
const vec3 COLOR_RACKET_BODY_ALT = vec3(0.61f, 0.61f, 0.61f);
const vec3 COLOR_RACKET_STRINGS = vec3(0.31f, 0.68f, 0.027f);

RacketFernando::RacketFernando() {}

RacketFernando::RacketFernando(GLuint worldMatrixLocation) {
    this->transform = mat4(1.0f);
    this->worldMatrixLocation = worldMatrixLocation;
    this->racketBody = Cube(COLOR_RACKET_BODY);;
    this->racketBodyAlt = Cube(COLOR_RACKET_BODY_ALT);
    this->racketStrings = Cube(COLOR_RACKET_STRINGS);
}

void RacketFernando::draw(GLuint renderingMode) {
    //
    // handle
    //
    const float racketSize = 0.3f;
    const float racketHandleLength = 3.0f;

    mat4 partMatrix = translate(mat4(1.0f), vec3(0.0f, racketHandleLength / 2, 0.0f)) *
                      scale(mat4(1.0f), vec3(racketSize, racketHandleLength, racketSize));
    mat4 groupMatrix = this->transform;

    mat4 worldMatrix = groupMatrix * partMatrix;
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
    racketBody.draw(renderingMode);

    //
    // racket rim
    //
    const float racketRimWidth = 2.2f;
    const float racketRimHeight = 3.0f;

    //
    // bottom
    //
    partMatrix = translate(mat4(1.0f), vec3(0.0f, racketSize / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth, racketSize, racketSize));
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, racketHandleLength, 0.0f));

    worldMatrix = groupMatrix * partMatrix;
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
    racketBodyAlt.draw(renderingMode);

    //
    // left
    //
    partMatrix = translate(mat4(1.0f), vec3(-racketRimWidth / 2, racketRimHeight / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketSize, racketRimHeight, racketSize));
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, racketSize, 0.0f));

    worldMatrix = groupMatrix * partMatrix;
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
    racketBodyAlt.draw(renderingMode);

    //
    // right
    //
    partMatrix = translate(mat4(1.0f), vec3(racketRimWidth / 2, racketRimHeight / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketSize, racketRimHeight, racketSize));

    worldMatrix = groupMatrix * partMatrix;
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
    racketBodyAlt.draw(renderingMode);

    //
    // top
    //
    partMatrix = translate(mat4(1.0f), vec3(0.0f, racketRimHeight, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth, racketSize, racketSize));

    worldMatrix = groupMatrix * partMatrix;
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
    racketBodyAlt.draw(renderingMode);

    //
    // racket strings
    //
    const float verticalStringCount = racketRimWidth / 10;
    const float horizontalStringCount = racketRimHeight / 10;
    const float racketStringSize = 0.05f;

    for (int i = 0; i <= 10; i++) {
        partMatrix =
                translate(mat4(1.0f),
                          vec3(-(racketRimWidth / 2) + i * verticalStringCount, racketRimHeight / 2, 0.0f)) *
                scale(mat4(1.0f), vec3(racketStringSize, racketRimHeight, racketStringSize));

        worldMatrix = groupMatrix * partMatrix;
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
        racketStrings.draw(renderingMode);
    }
    for (int i = 0; i <= 10; i++) {
        partMatrix =
                translate(mat4(1.0f),
                          vec3(0.0f, i * horizontalStringCount, 0.0f)) *
                scale(mat4(1.0f), vec3(racketRimWidth, racketStringSize, racketStringSize));

        worldMatrix = groupMatrix * partMatrix;
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
        racketStrings.draw(renderingMode);
    }
}

void RacketFernando::update(mat4 transform) {
    this->transform = transform;
}
