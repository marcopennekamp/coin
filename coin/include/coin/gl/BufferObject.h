#ifndef COIN_GL_BUFFEROBJECT_H_
#define COIN_GL_BUFFEROBJECT_H_

#include <coin/coin.h>
#include <coin/gl.h>


namespace coin {

class COIN_DECL BufferObject {
  private:
    GLuint handle_;
    GLenum type_;

  public:
    BufferObject (GLenum type);
    ~BufferObject ();

    void Allocate (GLsizeiptr size, GLenum drawMode);
    void BufferData (void* data, GLsizei data_size, GLintptr buffer_offset = 0L);
    void Bind ();
    void Unbind ();

    inline GLuint handle () { return handle_; }
    inline GLenum type () { return type_; }
};

}

#endif  /* COIN_GL_BUFFEROBJECT_H_ */
