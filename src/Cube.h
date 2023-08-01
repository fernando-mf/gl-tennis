#ifndef ASSIGNMENT_1_CUBE_H
#define ASSIGNMENT_1_CUBE_H

#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace glm;

class Cube {
public:
    GLuint vbo;
    GLuint vao;

    Cube(vec3 color);

    Cube();

    void draw(GLuint renderingMode);

    void draw();
};


#endif //ASSIGNMENT_1_CUBE_H
