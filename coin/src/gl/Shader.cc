#include <coin/coin.h>
#include <coin/gl/Shader.h>


namespace coin {

Shader::Shader (GLuint handle) {
    handle_ = handle;
}


void Shader::Bind () {
    glUseProgram (handle_);
}


void Shader::Unbind () {
    glUseProgram (0);
}

}

