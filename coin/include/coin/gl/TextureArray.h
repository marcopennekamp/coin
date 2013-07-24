#ifndef COIN_GL_TEXTUREARRAY_H_
#define COIN_GL_TEXTUREARRAY_H_

#include <coin/utils/Array.h>
#include <coin/gl/Texture.h>


namespace coin {

class COIN_EXPORT TextureArray : public Texture {
private:
    GLuint width_;
    GLuint height_;
    GLuint depth_;

    bool Init (const Array<Image>& images, Setup setup);
    void Init (const GLuint width, const GLuint height, const GLuint depth, Setup setup);
    void Init (const GLuint width, const GLuint height, const GLuint depth, Setup setup, const void* data);

    void TextureSetup ();

public:
    TextureArray ();

    TextureArray (const GLuint width, const GLuint height, const GLuint depth);
    TextureArray (const GLuint width, const GLuint height, const GLuint depth, Setup setup);

    TextureArray (const Array<Image>& images);
    TextureArray (const Array<Image>& images, Setup setup);

    using Texture::Load;

    void BufferData (const void* data);
    bool Load (const std::string& path, Setup setup);
    void Bind (const GLuint location);
};

}


#endif  /* COIN_GL_TEXTUREARRAY_H_ */