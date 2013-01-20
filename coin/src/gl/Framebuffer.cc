#include <coin/gl/Framebuffer.h>




namespace coin {

namespace {

void _TextureSetup (Texture* texture) {
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

}


Framebuffer::Framebuffer (Size width, Size height) : texture_ (width, height, _TextureSetup) {
    /* Generate framebuffer. */
    glGenFramebuffers (1, &handle_);
    
    Bind ();

    /* Create depth buffer. */
    glGenRenderbuffers (1, &depth_buffer_handle_);
    glBindRenderbuffer (GL_RENDERBUFFER, depth_buffer_handle_);
    glRenderbufferStorage (GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_handle_);

    /* Create texture for framebuffer to write to. */
    glFramebufferTexture (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_.handle (), 0);
 
    /* Set draw buffers. */
    GLenum DrawBuffers[2] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers (1, DrawBuffers);

    Unbind ();
}


Framebuffer::~Framebuffer () {
    glDeleteRenderbuffers (1, &depth_buffer_handle_);
    glDeleteFramebuffers (1, &handle_);
}


void Framebuffer::Bind () {
    glBindFramebuffer (GL_FRAMEBUFFER, handle_);
    // TODO(Marco): Use glViewport ?
}

void Framebuffer::Unbind () {
    glBindFramebuffer (GL_FRAMEBUFFER, 0);
}


}