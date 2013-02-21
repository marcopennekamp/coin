#include <coin/gl/BufferObject.h>


namespace coin {

BufferObject::BufferObject (const GLenum type) {
    type_ = type;
    glGenBuffers (1, &handle_);
}


BufferObject::~BufferObject () {
    glDeleteBuffers (1, &handle_);
}


void BufferObject::Allocate (const GLsizeiptr size, const GLenum drawMode) {
    glBufferData (type_, size, NULL, drawMode);
}


void BufferObject::BufferData (const void* data, const GLsizei data_size, const GLintptr buffer_offset) {
    glBufferSubData (type_, buffer_offset, data_size, data);
}


void BufferObject::Bind () {
    glBindBuffer (type_, handle_);
}


void BufferObject::Unbind () {
    glBindBuffer (type_, 0);
}

}



