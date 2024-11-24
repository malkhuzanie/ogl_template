#include <texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
    : id {0}
{
}

Texture::Texture(const std::string& filename, GLenum cl) 
{
    glGenTextures(1, &id);
    load(filename, cl);
}

void Texture::load(const std::string& filename, GLenum cl, int width, int height, int n)
{
    bind();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &n, 0);
    if (!data) {
        error(stbi_failure_reason());
    }

    gluBuild2DMipmaps(GL_TEXTURE_2D, cl, width, height, cl, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
