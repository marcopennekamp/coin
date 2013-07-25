#include <coin/gl/TextureArray.h>


namespace coin {

bool TextureArray::Init (const std::vector<Image>& images, Setup setup) {
    // TODO(Marco): Throw exception.
    /* Check whether depth is greater than one. */
    const Size depth = (Size) images.size ();
    if (depth == 0) {
        printf ("Error: Image array size must be greater than zero!\n");
        return false;
    }

    /* Copy image data into an array. */
    const Size width = images[0].width ();
    const Size height = images[0].height ();
    const Size size = width * height * sizeof (uint32_t);
    uint32_t* data = new uint32_t[width * height * depth];
    for (Size i = 0; i < depth; ++i) {
        const Image& image = images[0];
        if (width != image.width () || height != image.height ()) {
            printf ("Error: All images in the array have to be of the same size!\n");
            delete[] data;
            return false;
        }
        memcpy (data + i * width * height, image.data (), size);
    }

    Init (width, height, depth, setup, data);
    return true;
}

void TextureArray::Init (const GLuint width, const GLuint height, const GLuint depth, Setup setup) {
    Init (width, height, depth, setup, NULL);
}

void TextureArray::Init (const GLuint width, const GLuint height, const GLuint depth, Setup setup, const void* data) {
    width_ = width;
    height_ = height;
    depth_ = depth;
    CreateHandle ();
    BufferData (data);
    ApplyTextureSetup (setup);
}

void TextureArray::TextureSetup () {
    glTexParameteri (GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 4);
}

TextureArray::TextureArray () {

}

TextureArray::TextureArray (const GLuint width, const GLuint height, const GLuint depth) {
    Init (width, height, depth, NULL);
}

TextureArray::TextureArray (const GLuint width, const GLuint height, const GLuint depth, Setup setup) {
    Init (width, height, depth, setup);
}

TextureArray::TextureArray (const std::vector<Image>& images) {
    Init (images, NULL);
}

TextureArray::TextureArray (const std::vector<Image>& images, Setup setup) {
    Init (images, setup);
}

void TextureArray::BufferData (const void* data) {
    glBindTexture (GL_TEXTURE_2D_ARRAY, handle_);
    glTexImage3D (GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width_, height_, depth_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void TextureArray::Bind (const GLuint location) {
    glActiveTexture (GL_TEXTURE0 + location);
    glBindTexture (GL_TEXTURE_2D_ARRAY, handle_);
}

}