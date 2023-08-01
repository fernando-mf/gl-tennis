//
// Created by Fernando on 2023-07-31.
//

#ifndef ASSIGNMENT_1_TEXTUREDCOLORVERTEX_H
#define ASSIGNMENT_1_TEXTUREDCOLORVERTEX_H


#include <glm/glm.hpp>

using namespace glm;

class TexturedColoredVertex {
public:
    TexturedColoredVertex(vec3 _position, vec3 _color, vec2 _uv)
            : position(_position), color(_color), uv(_uv) {}

private:
    vec3 position;
    vec3 color;
    vec2 uv;
};


#endif //ASSIGNMENT_1_TEXTUREDCOLORVERTEX_H
