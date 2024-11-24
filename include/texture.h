#ifndef TEXTURE_H
#define TEXTURE_H

#include <utils.h>

class Texture { 
public:
    Texture();
    Texture(const std::string& filename, GLenum cl = GL_RGB);
    void load(const std::string&, GLenum cl, int = {}, int = {}, int = {});
    void bind();
    void unbind();

    unsigned int id;
};

#endif
