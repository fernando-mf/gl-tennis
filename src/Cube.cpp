#include "Cube.h"
#include "TexturedColorVertex.h"

Cube::Cube(vec3 color) {
    TexturedColoredVertex vertexArray[] = {  // position,                           color               uv
            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), color, vec2(0.0f, 0.0f)), //left
            TexturedColoredVertex(vec3(-0.5f, -0.5f, 0.5f), color, vec2(0.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), color, vec2(1.0f, 1.0f)),

            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), color, vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), color, vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, -0.5f), color, vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, -0.5f), color, vec2(1.0f, 1.0f)), // far
            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), color, vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, -0.5f), color, vec2(0.0f, 1.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, -0.5f), color, vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(0.5f, -0.5f, -0.5f), color, vec2(1.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), color, vec2(0.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, -0.5f, 0.5f), color, vec2(1.0f, 1.0f)), // bottom
            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), color, vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(0.5f, -0.5f, -0.5f), color, vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, -0.5f, 0.5f), color, vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, -0.5f, 0.5f), color, vec2(0.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), color, vec2(0.0f, 0.0f)),

            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), color, vec2(0.0f, 1.0f)), // near
            TexturedColoredVertex(vec3(-0.5f, -0.5f, 0.5f), color, vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(0.5f, -0.5f, 0.5f), color, vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), color, vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), color, vec2(0.0f, 1.0f)),
            TexturedColoredVertex(vec3(0.5f, -0.5f, 0.5f), color, vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), color, vec2(1.0f, 1.0f)), // right
            TexturedColoredVertex(vec3(0.5f, -0.5f, -0.5f), color, vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(0.5f, 0.5f, -0.5f), color, vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, -0.5f, -0.5f), color, vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), color, vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(0.5f, -0.5f, 0.5f), color, vec2(0.0f, 1.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), color, vec2(1.0f, 1.0f)), // top - yellow
            TexturedColoredVertex(vec3(0.5f, 0.5f, -0.5f), color, vec2(1.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, -0.5f), color, vec2(0.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), color, vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, -0.5f), color, vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), color, vec2(0.0f, 1.0f))
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedColoredVertex), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedColoredVertex), (void *) sizeof(vec3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedColoredVertex), (void *) (2 * sizeof(vec3)));
    glEnableVertexAttribArray(2);

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