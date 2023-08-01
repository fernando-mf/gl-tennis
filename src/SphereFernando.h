//
// Created by Fernando on 2023-08-01.
//

#ifndef ASSIGNMENT_1_SPHEREFERNANDO_H
#define ASSIGNMENT_1_SPHEREFERNANDO_H

#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace glm;

class SphereFernando {
public:
    GLuint vao;
    GLuint vbo;

    SphereFernando(vec3 color);

    SphereFernando();

    void draw(GLuint renderingMode);

    void draw();

    void bind();

private:
    int vertexCount;

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
    };
};


#endif //ASSIGNMENT_1_SPHEREFERNANDO_H
