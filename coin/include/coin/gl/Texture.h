#ifndef COIN_GL_TEXTURE_H_
#define COIN_GL_TEXTURE_H_

#include <coin/coin.h>
#include <coin/gl.h>


namespace coin {

class COIN_DECL Texture {
  private:
    GLuint handle_;
    Size width_;
    Size height_;

  public:
    Texture (GLuint handle, GLuint width, GLuint height);

    inline GLuint handle () { return handle_; }
    inline Size width () { return width_; }
    inline Size height () { return height_; }
};

}

#endif  /* COIN_GL_TEXTURE_H_ */
