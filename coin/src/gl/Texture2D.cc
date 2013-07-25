#include <coin/utils/FileStream.h>
#include <coin/gl/Texture2D.h>
#include <coin/resource/png.h>


namespace coin {

void Texture2D::Init (const Image& image, Setup setup) {
    Init (image.width (), image.height (), setup, image.data ());
}

void Texture2D::Init (const GLuint width, const GLuint height, Setup setup) {
    Init (width, height, setup, NULL);
}

void Texture2D::Init (const GLuint width, const GLuint height, Setup setup, const void* data) {
    width_ = width;
    height_ = height;
    CreateHandle ();
    BufferData (data);
    ApplyTextureSetup (setup);
}

void Texture2D::TextureSetup () {
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 4);
}

Texture2D::Texture2D () {

}

Texture2D::Texture2D (const GLuint width, const GLuint height) {
    Init (width, height, NULL);
}

Texture2D::Texture2D (const GLuint width, const GLuint height, Setup setup) {
    Init (width, height, setup);
}

Texture2D::Texture2D (const Image& image) {
    Init (image, NULL);
}

Texture2D::Texture2D (const Image& image, Setup setup) {
    Init (image, setup);
}

void Texture2D::BufferData (const void* data) {
    glBindTexture (GL_TEXTURE_2D, handle_);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

bool Texture2D::Load (const std::string& path, Setup setup) {
    FileStream stream (path, Stream::Mode::read);
    Image image;
    bool success = PngLoad (stream, image);

    /* Texture loading failed. */
    if (!success) {
        return false;
    }

    Init (image, setup);

    return true;
}

void Texture2D::Bind (const GLuint location) {
    glActiveTexture (GL_TEXTURE0 + location);
    glBindTexture (GL_TEXTURE_2D, handle_);
}

}