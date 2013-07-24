#ifndef COIN_GL_TEXTURE2D_H_
#define COIN_GL_TEXTURE2D_H_

#include <coin/gl/Texture.h>


namespace coin {

class COIN_EXPORT Texture2D : public Texture {
private:
    GLuint width_;
    GLuint height_;

    void Init (const Image& image, Setup setup);
    void Init (const GLuint width, const GLuint height, Setup setup);
    void Init (const GLuint width, const GLuint height, Setup setup, const void* data);

    void TextureSetup ();

public:
    Texture2D ();

    Texture2D (const GLuint width, const GLuint height);
    Texture2D (const GLuint width, const GLuint height, Setup setup);

    Texture2D (const Image& image);
    Texture2D (const Image& image, Setup setup);

    using Texture::Load;

    void BufferData (const void* data);
    bool Load (const std::string& path, Setup setup);
    void Bind (const GLuint location);
};

}


#endif  /* COIN_GL_TEXTURE2D_H_ */