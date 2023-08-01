//
// COMP 371 - Assignment 2
//
//

#include <iostream>
#include <list>

#define GLEW_STATIC 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Cube.h"
#include "ArmWithRacketFernando.h"
#include "ShaderProgram.h"
#include "Texture.h"

using namespace glm;
using namespace std;

const vec3 COLOR_RED = vec3(1.0f, 0.0f, 0.0f);
const vec3 COLOR_BLUE = vec3(0.0f, 0.0f, 1.0f);
const vec3 COLOR_GREEN = vec3(0.0f, 1.0f, 0.0f);
const vec3 COLOR_GREEN_FLOOR = vec3(0.11f, 0.73f, 0.04f);

float randomBetween(float min, float max) {
    return min + rand() / (RAND_MAX / (max - min));
}

float clamp(float minVal, float maxVal, float value) {
    return std::max(minVal, std::min(value, maxVal));
}

int main(int argc, char *argv[]) {
    srand(time(0));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(1024, 768, "Assignment 2", NULL, NULL);
    if (window == NULL) {
        std::cerr << "failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // load textures
    Texture clayTexture("./assets/textures/clay_ground.png");

    // compile and link shaders
    ShaderProgram texturedShaderProgram("./assets/shaders/texture_vertex_shader.glsl",
                                        "./assets/shaders/texture_fragment_shader.glsl");
    texturedShaderProgram.initializeTextures();

    ShaderProgram colorShaderProgram("./assets/shaders/vertex_shader.glsl",
                                     "./assets/shaders/fragment_shader.glsl");

    // set initial view matrix
    // camera parameters for view transform
    vec3 cameraPosition(3.0f, 5.0f, 25.0f);
    vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
    vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // other camera parameters
    float cameraHorizontalAngle = 90.0f;
    float cameraVerticalAngle = 0.0f;

    mat4 viewMatrix = lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp);
    colorShaderProgram.setViewMatrix(viewMatrix);
    texturedShaderProgram.setViewMatrix(viewMatrix);

    // frame time
    float lastFrameTime = glfwGetTime();
    double lastMousePosX, lastMousePosY;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

    // instantiate models
    Cube ground = Cube(COLOR_GREEN_FLOOR);
    Cube xAxis = Cube(COLOR_RED);
    Cube yAxis = Cube(COLOR_GREEN);
    Cube zAxis = Cube(COLOR_BLUE);
    SphereFernando sphereFernando = SphereFernando(COLOR_GREEN);
    ArmWithRacketFernando armWithRacketFernando = ArmWithRacketFernando(colorShaderProgram, texturedShaderProgram);

    const float worldSize = 100; // grid size
    vec3 modelLocation(2.0f, 1.0f, 2.0f);
    vec3 modelScale(1.0f, 1.0f, 1.0f);
    float modelYAxisRotation = 0.0f;
    float modelXAxisRotation = 0.0f;
    GLuint modelRenderingMode = GL_TRIANGLES;

    float fov = 45.0f;

    float worldXAxisRotation = 0.0f;
    float worldYAxisRotation = 0.0f;

    bool texturesEnabled = true;

    while (!glfwWindowShouldClose(window)) {
        ShaderProgram textureShader = texturesEnabled ? texturedShaderProgram : colorShaderProgram;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // set up project matrix
        mat4 projectionMatrix = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.01f, 100.0f);
        colorShaderProgram.setProjectionMatrix(projectionMatrix);
        texturedShaderProgram.setProjectionMatrix(projectionMatrix);

        // set up texture
        clayTexture.use();

        mat4 globalWorldMatrix = rotate(mat4(1.0f), glm::radians(worldYAxisRotation), vec3(0.0f, 1.0f, 0.0f)) *
                                 rotate(mat4(1.0f), glm::radians(worldXAxisRotation), vec3(1.0f, 0.0f, 0.0f));

        // draw ground
        mat4 groundWM = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)) *
                        scale(mat4(1.0f), vec3(worldSize, 0.02f, worldSize));

        groundWM = globalWorldMatrix * groundWM;
        textureShader.setWorldMatrix(groundWM);
        ground.draw();

        // draw axes
        const float axisSize = 0.3f;
        const float axisLength = 5.0f;

        // draw x-axis :: red
        mat4 xAxisWM = translate(mat4(1.0f), vec3(axisLength / 2, axisSize / 2, axisSize / 2)) *
                       scale(mat4(1.0f), vec3(axisLength, axisSize, axisSize));
        xAxisWM = globalWorldMatrix * xAxisWM;
        colorShaderProgram.setWorldMatrix(xAxisWM);
        xAxis.draw();

        // draw y-axis :: green
        mat4 yAxisWM = translate(mat4(1.0f), vec3(axisSize / 2, axisLength / 2, axisSize / 2)) *
                       scale(mat4(1.0f), vec3(axisSize, axisLength, axisSize));
        yAxisWM = globalWorldMatrix * yAxisWM;
        colorShaderProgram.setWorldMatrix(yAxisWM);
        yAxis.draw();

        // draw z-axis :: blue
        mat4 zAxisWM = translate(mat4(1.0f), vec3(axisSize / 2, axisSize / 2, axisLength / 2)) *
                       scale(mat4(1.0f), vec3(axisSize, axisSize, axisLength));
        zAxisWM = globalWorldMatrix * zAxisWM;
        colorShaderProgram.setWorldMatrix(zAxisWM);
        zAxis.draw();

        //
        // Fernando - arm with racket and tennis ball
        //
        colorShaderProgram.setWorldMatrix(mat4(1.0f));
        armWithRacketFernando.update(globalWorldMatrix *
                                     translate(mat4(1.0f), modelLocation) * // translation with keys A | D | S | W
                                     rotate(mat4(1.0f), radians(modelYAxisRotation), vec3(0.0f, 1.0f, 0.0f)) *
                                     // rotation with keys a | d
                                     rotate(mat4(1.0f), radians(modelXAxisRotation), vec3(1.0f, 0.0f, 0.0f)) *
                                     // rotation with keys s | w
                                     scale(mat4(1.0f), modelScale) // scaling with keys u | j
        );
        armWithRacketFernando.animate(lastFrameTime, dt);
        armWithRacketFernando.draw(modelRenderingMode);

        //
        // <name> - arm with racket
        //
        // TODO: add your code here

        // end frame
        glfwSwapBuffers(window);
        glfwPollEvents();

        // handle inputs
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        //
        // handle space bar :: model is placed at a random location
        //
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            float min = -(worldSize / 2);
            float max = worldSize / 2;
            modelLocation = vec3(randomBetween(min, max), 0.0f, randomBetween(min, max));
        }

        //
        // handle model scale
        //
        const float scaleSpeed = 0.3f * dt;
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
            modelScale += vec3(scaleSpeed);
        }

        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            modelScale -= vec3(scaleSpeed);
        }

        //
        // handle model rendering mode
        //
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
            modelRenderingMode = GL_POINTS;
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            modelRenderingMode = GL_LINE_STRIP;
        }
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            modelRenderingMode = GL_TRIANGLES;
        }

        //
        // handle textures on/off
        //
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
            texturesEnabled = false;
        } else {
            texturesEnabled = true;
        }

        //
        // handle world rotation
        //
        float worldRotationSpeed = 10.0f;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            worldYAxisRotation += worldRotationSpeed * dt;               // rotate left 5deg
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            worldYAxisRotation -= worldRotationSpeed * dt;               // rotate right 5deg
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            worldXAxisRotation -= worldRotationSpeed * dt;               // rotate up 5deg
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            worldXAxisRotation += worldRotationSpeed * dt;               // rotate down 5deg
        }

        //
        // reset world rotation
        //
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            worldXAxisRotation = 0;
            worldYAxisRotation = 0;
        }

        //
        // handle model position and rotation
        //
        bool isUpperCase = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                           glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ||
                           glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS;

        const float modelSpeed = 2.0f * dt;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            if (isUpperCase) {
                modelLocation += vec3(-modelSpeed, 0.0f, 0.0f);     // left
            } else {
                modelYAxisRotation += 5;                                      // rotate left 5deg
            }
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            if (isUpperCase) {
                modelLocation += vec3(modelSpeed, 0.0f, 0.0f);      // right
            } else {
                modelYAxisRotation -= 5;                                      // rotate right 5deg
            }
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            if (isUpperCase) {
                modelLocation += vec3(0.0f, -modelSpeed, 0.0f);     // down
            } else {
                modelXAxisRotation += 5;                                      // rotate forward 5deg
            }
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            if (isUpperCase) {
                modelLocation += vec3(0.0f, modelSpeed, 0.0f);      // up
            } else {
                modelXAxisRotation -= 5;                                      // rotate backward 5deg
            }
        }

        //
        // handle zoom in/out
        //
        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        double dx = mousePosX - lastMousePosX;
        double dy = mousePosY - lastMousePosY;

        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            fov = clamp(25, 90, fov + 0.1f * dy); // min 25, max 90 degrees
        }

        //
        // handle camera movement tilt/pan
        //
        const float cameraAngularSpeed = 60.0f;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            cameraHorizontalAngle += dx * cameraAngularSpeed * dt;
            if (cameraHorizontalAngle > 360) {
                cameraHorizontalAngle -= 360;
            } else if (cameraHorizontalAngle < -360) {
                cameraHorizontalAngle += 360;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
            cameraVerticalAngle += dy * cameraAngularSpeed * dt;
            cameraVerticalAngle = clamp(-85.0f, 85.0f, cameraVerticalAngle);
        }

        float theta = radians(cameraHorizontalAngle);
        float phi = radians(cameraVerticalAngle);

        cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
        viewMatrix = lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp);
        colorShaderProgram.setViewMatrix(viewMatrix);
        texturedShaderProgram.setViewMatrix(viewMatrix);
    }

    glfwTerminate();
    return 0;
}
