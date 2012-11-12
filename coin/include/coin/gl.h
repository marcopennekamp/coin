#ifndef COIN_GL_H_
#define COIN_GL_H_

#include <stdlib.h>
#include <string.h>
#define HAVE_MEMSET

#ifdef __LINUX
/* Include the newest GL3 headers before SDL. */
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <GL/glew.h>
#endif

#include <SDL2/SDL.h>


inline char* BufferOffset (GLuint offset) {
    return (char*) NULL + offset;
}

#endif  /* COIN_GL_H_ */