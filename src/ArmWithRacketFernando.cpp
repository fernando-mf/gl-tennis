//
// Created by Fernando Mamani 40169982.
//

#include "ArmWithRacketFernando.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Cube.h"
#include "RacketFernando.h"

using namespace glm;
using namespace std;

const vec3 COLOR_ARM = vec3(0.75f, 0.63f, 0.46f);

const float armSize = 0.5f;
const float armLength = 4.0f;

float modelInitialAngle = -50.0f;
float upperArmAngle = -modelInitialAngle;

ArmWithRacketFernando::ArmWithRacketFernando(GLuint worldMatrixLocation) {
    this->transform = mat4(1.0f);
    this->worldMatrixLocation = worldMatrixLocation;
    this->racket = RacketFernando(worldMatrixLocation);
    this->arm = Cube(COLOR_ARM);
}

void ArmWithRacketFernando::update(glm::mat4 transform) {
    this->transform = transform;
}

void ArmWithRacketFernando::animate(float lastFrameTime, float dt) {
    upperArmAngle += 35 * cos(lastFrameTime - 10) * dt;
}

void ArmWithRacketFernando::draw(GLuint renderingMode) {
    //
    // lower arm
    //
    mat4 partMatrix = translate(mat4(1.0f), vec3(0.0f, armLength / 2, 0.0f)) *
                      scale(mat4(1.0f), vec3(armSize, armLength, armSize));

    mat4 groupMatrix = this->transform * rotate(mat4(1.0f), radians(modelInitialAngle), vec3(0.0f, 0.0f, 1.0f));
    mat4 worldMatrix = groupMatrix * partMatrix;
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
    arm.draw(renderingMode);

    //
    // upper arm
    //
    partMatrix = translate(mat4(1.0f), vec3(0.0f, armLength / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(armSize, armLength, armSize));
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, armLength, 0.0f)) *
                  rotate(mat4(1.0f), radians(upperArmAngle), vec3(0.0f, 0.0f, 1.0f));

    worldMatrix = groupMatrix * partMatrix;
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
    arm.draw(renderingMode);

    // draw racket
    racket.update(groupMatrix * translate(mat4(1.0f), vec3(0.0f, armLength, 0.0f)));
    racket.draw(renderingMode);
}