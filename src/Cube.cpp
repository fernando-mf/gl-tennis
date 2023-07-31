#include "Cube.h"

Cube::Cube(vec3 color) {
    vec3 vertexArray[] = {  // position,                  color
            vec3(-0.5f, -0.5f, -0.5f), color, //left
            vec3(-0.5f, -0.5f, 0.5f), color,
            vec3(-0.5f, 0.5f, 0.5f), color,

            vec3(-0.5f, -0.5f, -0.5f), color,
            vec3(-0.5f, 0.5f, 0.5f), color,
            vec3(-0.5f, 0.5f, -0.5f), color,

            vec3(0.5f, 0.5f, -0.5f), color, // far
            vec3(-0.5f, -0.5f, -0.5f), color,
            vec3(-0.5f, 0.5f, -0.5f), color,

            vec3(0.5f, 0.5f, -0.5f), color,
            vec3(0.5f, -0.5f, -0.5f), color,
            vec3(-0.5f, -0.5f, -0.5f), color,

            vec3(0.5f, -0.5f, 0.5f), color, // bottom
            vec3(-0.5f, -0.5f, -0.5f), color,
            vec3(0.5f, -0.5f, -0.5f), color,

            vec3(0.5f, -0.5f, 0.5f), color,
            vec3(-0.5f, -0.5f, 0.5f), color,
            vec3(-0.5f, -0.5f, -0.5f), color,

            vec3(-0.5f, 0.5f, 0.5f), color, // near
            vec3(-0.5f, -0.5f, 0.5f), color,
            vec3(0.5f, -0.5f, 0.5f), color,

            vec3(0.5f, 0.5f, 0.5f), color,
            vec3(-0.5f, 0.5f, 0.5f), color,
            vec3(0.5f, -0.5f, 0.5f), color,

            vec3(0.5f, 0.5f, 0.5f), color, // right
            vec3(0.5f, -0.5f, -0.5f), color,
            vec3(0.5f, 0.5f, -0.5f), color,

            vec3(0.5f, -0.5f, -0.5f), color,
            vec3(0.5f, 0.5f, 0.5f), color,
            vec3(0.5f, -0.5f, 0.5f), color,

            vec3(0.5f, 0.5f, 0.5f), color, // top
            vec3(0.5f, 0.5f, -0.5f), color,
            vec3(-0.5f, 0.5f, -0.5f), color,

            vec3(0.5f, 0.5f, 0.5f), color,
            vec3(-0.5f, 0.5f, -0.5f), color,
            vec3(-0.5f, 0.5f, 0.5f), color
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vec3), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vec3), (void *) sizeof(vec3));

    this->vbo = vao;
}

Cube::Cube() {}

void Cube::draw(GLuint renderingMode) {
    glBindVertexArray(this->vbo);
    glDrawArrays(renderingMode, 0, 36);
}

void Cube::draw() {
    this->draw(GL_TRIANGLES);
}