#ifndef COIN_GL_SHADER_H_
#define COIN_GL_SHADER_H_

#include <coin/coin.h>
#include <coin/gl.h>


namespace coin {

class COIN_DECL Shader {
  private:
    GLuint handle_;

  public:
    Shader (GLuint handle);

    void Bind ();
    void Unbind ();

    inline GLuint handle () { return handle_; }
};

}

#endif  /* COIN_GL_SHADER_H_ */
