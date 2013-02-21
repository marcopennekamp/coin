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
    BufferObject (const GLenum type);
    ~BufferObject ();

    void Allocate (const GLsizeiptr size, const GLenum drawMode);
    void BufferData (const void* data, const GLsizei data_size, const GLintptr buffer_offset = 0L);
    void Bind ();
    void Unbind ();

    inline GLuint handle () const { return handle_; }
    inline GLenum type () const { return type_; }
};

}

#endif  /* COIN_GL_BUFFEROBJECT_H_ */
