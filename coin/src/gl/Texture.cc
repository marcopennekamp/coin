#include <coin/gl/Texture.h>


namespace coin {

void Texture::StandardSetup (Texture* texture) {
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 4);
}

Texture::Texture (const GLuint width, const GLuint height) { 
    Init (width, height, Texture::StandardSetup);
}

Texture::Texture (const GLuint width, const GLuint height, Setup setup) {
    Init (width, height, setup);  
}

void Texture::Init (const GLuint width, const GLuint height, Setup setup) {
    width_ = width;
    height_ = height;
    setup_ = setup;
    CreateHandle ();
    AllocateTexture ();
}

Texture::Texture (const Image& image) {
    Init (image, StandardSetup);
}

Texture::Texture (const Image& image, Setup setup) {
    Init (image, setup);
}

void Texture::Init (const Image& image, Setup setup) {
    setup_ = setup;
    CreateHandle ();
    SetImage (image);
}

void Texture::CreateHandle () {
    glGenTextures (1, &handle_);
}


Texture::~Texture () {
    glDeleteTextures (1, &handle_);
}



void Texture::AllocateTexture () {
    AllocateTexture (NULL);
}

void Texture::AllocateTexture (const void* data) {
    glBindTexture (GL_TEXTURE_2D, handle_);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    setup_ (this);
}

void Texture::SetImage (const Image& image) {
    width_ = image.width ();
    height_ = image.height ();
    AllocateTexture (image.data ());
}

void Texture::Bind (const GLuint location) {
    glActiveTexture (GL_TEXTURE0 + location);
    glBindTexture (GL_TEXTURE_2D, handle_);
}

}


