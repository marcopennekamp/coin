#ifndef COIN_GL_TEXTURE_H_
#define COIN_GL_TEXTURE_H_

#include <functional>

#include <coin/coin.h>
#include <coin/gl.h>
#include <coin/resource/Element.h>
#include <coin/resource/Image.h>


namespace coin {

class COIN_DECL Texture : public Element {
public:
    typedef void (*Setup) (Texture*);

protected:
    GLuint handle_;

    void ApplyTextureSetup (Setup setup);
    void CreateHandle ();

    virtual void TextureSetup () = 0;

public:
    virtual ~Texture ();

    virtual void BufferData (const void* data) = 0;

    bool Load (const std::string& path);
    virtual bool Load (const std::string& path, Setup setup) = 0;

    /*
     * Binds the texture to the texture unit 'location'.
     */
    virtual void Bind (const GLuint location) = 0;

    inline GLuint handle () const { return handle_; }
};

}

#endif  /* COIN_GL_TEXTURE_H_ */
