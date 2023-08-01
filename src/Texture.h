//
// Created by Fernando on 2023-08-01.
//

#ifndef ASSIGNMENT_1_TEXTURE_H
#define ASSIGNMENT_1_TEXTURE_H

class Texture {
private:
    unsigned int textureId;
public:
    Texture();

    Texture(const char *texturePath);

    void use();
};


#endif //ASSIGNMENT_1_TEXTURE_H
