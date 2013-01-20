#include <coin/gl/Texture.h>


namespace coin {

void Texture::StandardSetup (Texture* texture) {
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 4);
}

Texture::Texture (GLuint width, GLuint height) { 
    Init (width, height, Texture::StandardSetup);
}

Texture::Texture (GLuint width, GLuint height, Setup setup) {
    Init (width, height, setup);  
}

void Texture::Init (GLuint width, GLuint height, Setup setup) {
    width_ = width;
    height_ = height;
    setup_ = setup;
    CreateHandle ();
    AllocateTexture ();
}

Texture::Texture (Image& image) {
    Init (image, StandardSetup);
}

Texture::Texture (Image& image, Setup setup) {
    Init (image, setup);
}

void Texture::Init (Image& image, Setup setup) {
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

void Texture::AllocateTexture (void* data) {
    glBindTexture (GL_TEXTURE_2D, handle_);
    setup_ (this);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void Texture::SetImage (Image& image) {
    width_ = image.width ();
    height_ = image.height ();
    AllocateTexture (image.data ());
}

void Texture::Bind (GLuint sampler_uniform, GLuint location) {
    glUniform1i (sampler_uniform, location);
    glActiveTexture (GL_TEXTURE0 + location);
    glBindTexture (GL_TEXTURE_2D, handle_);
}

}


