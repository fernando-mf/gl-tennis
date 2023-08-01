//
// Created by Fernando Mamani 40169982.
//

#include "ArmWithRacketFernando.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Cube.h"
#include "SphereFernando.h"
#include "Texture.h"

using namespace glm;
using namespace std;

//
// Racket model
//

const vec3 COLOR_RACKET_BODY = vec3(0.44f, 0.0f, 0.008f);
const vec3 COLOR_RACKET_BODY_ALT = vec3(0.61f, 0.61f, 0.61f);
const vec3 COLOR_RACKET_STRINGS = vec3(0.31f, 0.68f, 0.027f);
const vec3 COLOR_TENNIS_BALL = vec3(0.0f, 1.0f, 0.0f);

RacketFernando::RacketFernando() {}

RacketFernando::RacketFernando(ShaderProgram colorShader, ShaderProgram textureShader) {
    this->transform = mat4(1.0f);
    this->colorShader = colorShader;
    this->textureShader = textureShader;

    this->racketBody = Cube(COLOR_RACKET_BODY);;
    this->racketBodyAlt = Cube(COLOR_RACKET_BODY_ALT);
    this->racketStrings = Cube(COLOR_RACKET_STRINGS);

    this->tennisBallTexture = Texture("./assets/textures/tennis_ball.png");
    this->tennisBall = SphereFernando(COLOR_TENNIS_BALL);
}

void RacketFernando::draw(GLuint renderingMode) {
    // handle
    const float racketSize = 0.3f;
    const float racketHandleLength = 3.0f;

    mat4 partMatrix = translate(mat4(1.0f), vec3(0.0f, racketHandleLength / 2, 0.0f)) *
                      scale(mat4(1.0f), vec3(racketSize, racketHandleLength, racketSize));
    mat4 groupMatrix = this->transform;

    mat4 worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBody.draw(renderingMode);

    // racket rim
    const float racketRimWidth = 2.2f;
    const float racketRimHeight = 3.0f;

    // calculate desired width based on inclination angle
    const float racketRimWidthBottom = (racketRimWidth / 2) / cos(radians(50.0f));

    // bottom - left
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, racketHandleLength, 0.0f));

    partMatrix = rotate(mat4(1.0f), radians(-45.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3(-racketRimWidthBottom / 2, racketSize / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidthBottom, racketSize, racketSize));

    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBodyAlt.draw(renderingMode);

    // bottom - right
    partMatrix = rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3(racketRimWidthBottom / 2, racketSize / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidthBottom, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBodyAlt.draw(renderingMode);

    // bottom - straight
    partMatrix = translate(mat4(1.0f), vec3(0.0f, 1.0f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidthBottom - 0.5f, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBody.draw(renderingMode);

    // left
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, 1.2f, 0.0f));

    partMatrix = translate(mat4(1.0f), vec3(-racketRimWidth / 2, racketRimHeight / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketSize, racketRimHeight, racketSize));

    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBody.draw(renderingMode);

    // right
    partMatrix = translate(mat4(1.0f), vec3(racketRimWidth / 2, racketRimHeight / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketSize, racketRimHeight, racketSize));

    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBody.draw(renderingMode);

    // top left base
    partMatrix = translate(mat4(1.0f), vec3(-racketRimWidth / 2, racketRimHeight - 0.05f, 0.0f)) *
                 rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3((racketRimWidth / 4) / 2, 0.0f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth / 4, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBodyAlt.draw(renderingMode);

    // top left base 2
    partMatrix = translate(mat4(1.0f), vec3(-racketRimWidth / 2 + 0.3f, racketRimHeight + 0.3f, 0.0f)) *
                 rotate(mat4(1.0f), radians(25.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3((racketRimWidth / 4) / 2, 0.0f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth / 4, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBody.draw(renderingMode);

    // top
    partMatrix = translate(mat4(1.0f), vec3(0.0f, racketRimHeight + 0.5f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth / 3.5, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBodyAlt.draw(renderingMode);

    // top right base 2
    partMatrix = translate(mat4(1.0f), vec3(racketRimWidth / 2 - 0.3f, racketRimHeight + 0.3f, 0.0f)) *
                 rotate(mat4(1.0f), radians(155.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3((racketRimWidth / 4) / 2, 0.0f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth / 4, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBody.draw(renderingMode);

    // top right base
    partMatrix = translate(mat4(1.0f), vec3(racketRimWidth / 2, racketRimHeight - 0.05f, 0.0f)) *
                 rotate(mat4(1.0f), radians(135.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3((racketRimWidth / 4) / 2, 0.0f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth / 4, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    racketBodyAlt.draw(renderingMode);

    // racket strings
    const float verticalStringCount = racketRimWidth / 10;
    const float horizontalStringCount = racketRimHeight / 10;
    const float racketStringSize = 0.05f;

    for (int i = 0; i <= 10; i++) {
        float height = i > 2 && i < 8 ? racketRimHeight + 0.7f : racketRimHeight;

        partMatrix =
                translate(mat4(1.0f),
                          vec3(-(racketRimWidth / 2) + i * verticalStringCount, racketRimHeight / 2, 0.0f)) *
                scale(mat4(1.0f), vec3(racketStringSize, height, racketStringSize));

        worldMatrix = groupMatrix * partMatrix;
        colorShader.setWorldMatrix(worldMatrix);
        racketStrings.draw(renderingMode);
    }
    for (int i = 0; i <= 10; i++) {
        partMatrix =
                translate(mat4(1.0f),
                          vec3(0.0f, i * horizontalStringCount, 0.0f)) *
                scale(mat4(1.0f), vec3(racketRimWidth, racketStringSize, racketStringSize));

        worldMatrix = groupMatrix * partMatrix;
        colorShader.setWorldMatrix(worldMatrix);
        racketStrings.draw(renderingMode);
    }

    // draw tennis ball
    float tennisBallRadius = 0.8f;
    partMatrix = scale(mat4(1.0f), vec3(tennisBallRadius));
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, racketRimHeight / 2, tennisBallRadius * 2));
    worldMatrix = groupMatrix * partMatrix;

    tennisBallTexture.use();
    textureShader.setWorldMatrix(worldMatrix);
    tennisBall.draw(renderingMode);
}

void RacketFernando::update(mat4 transform) {
    this->transform = transform;
}

//
// Arm with racket
//

const vec3 COLOR_ARM = vec3(0.75f, 0.63f, 0.46f);

const float armSize = 0.5f;
const float armLength = 4.0f;

float modelInitialAngle = -50.0f;
float upperArmAngle = -modelInitialAngle;

ArmWithRacketFernando::ArmWithRacketFernando(ShaderProgram colorShader, ShaderProgram textureShader) {
    this->transform = mat4(1.0f);
    this->colorShader = colorShader;
    this->textureShader = textureShader;

    this->racket = RacketFernando(colorShader, textureShader);
    this->arm = Cube(COLOR_ARM);
}

void ArmWithRacketFernando::update(glm::mat4 transform) {
    this->transform = transform;
}

void ArmWithRacketFernando::animate(float lastFrameTime, float dt) {
    upperArmAngle += 35 * cos(lastFrameTime - 10) * dt;
}

void ArmWithRacketFernando::draw(GLuint renderingMode) {
    // lower arm
    mat4 partMatrix = translate(mat4(1.0f), vec3(0.0f, armLength / 2, 0.0f)) *
                      scale(mat4(1.0f), vec3(armSize, armLength, armSize));

    mat4 groupMatrix = this->transform *
                       rotate(mat4(1.0f), radians(modelInitialAngle), vec3(0.0f, 0.0f, 1.0f));
    mat4 worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    arm.draw(renderingMode);

    // upper arm
    partMatrix = translate(mat4(1.0f), vec3(0.0f, armLength / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(armSize, armLength, armSize));
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, armLength, 0.0f)) *
                  rotate(mat4(1.0f), radians(upperArmAngle), vec3(0.0f, 0.0f, 1.0f));

    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    arm.draw(renderingMode);

    float handSize = 1.0f;

    // hand
    partMatrix = translate(mat4(1.0f), vec3(0.0f, handSize / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(handSize, handSize, handSize));
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, armLength, 0.0f));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    arm.draw(renderingMode);


    // draw racket
    racket.update(groupMatrix * translate(mat4(1.0f), vec3(0.0f, handSize, 0.0f)));
    racket.draw(renderingMode);
}