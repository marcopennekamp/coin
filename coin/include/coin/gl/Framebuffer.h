#ifndef COIN_GL_FRAMEBUFFER_H_
#define COIN_GL_FRAMEBUFFER_H_

#include <coin/coin.h>
#include <coin/gl/Texture.h>


namespace coin {

class COIN_DECL Framebuffer {
private:
    GLuint handle_;
    GLuint depth_buffer_handle_;

    Texture texture_;

public:
    Framebuffer (const Size width, const Size height);
    ~Framebuffer ();

    void Bind ();

    /* 
     * Binds the standard framebuffer.
     */
    void Unbind ();
   
    Texture& texture () { return texture_; }
};

}

#endif  /* COIN_GL_FRAMEBUFFER_H_ */