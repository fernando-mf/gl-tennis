#include "Texture.h"

#include <iostream>

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

using namespace std;

Texture::Texture() {}

Texture::Texture(const char *texturePath) {
    // create and bind textures
    GLuint textureId = 0;
    glGenTextures(1, &textureId);
    assert(textureId != 0);

    glBindTexture(GL_TEXTURE_2D, textureId);

    // set tex parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // load Textures with dimension data
    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Error::Texture could not load texture file:" << texturePath << std::endl;
        exit(1);
    }

    // upload the texture to the PU
    GLenum format = 0;
    switch (nrChannels) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            format = 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
                 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // free resources
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    this->textureId = textureId;
}

void Texture::use() {
    glBindTexture(GL_TEXTURE_2D, this->textureId);
}