#include <coin/gl/Texture.h>


namespace coin {

Texture::Texture (GLuint handle, GLuint width, GLuint height) {
    handle_ = handle;
    width_ = width;
    height_ = height;
}

}


