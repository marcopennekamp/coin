#include <coin/coin.h>
#include <coin/gl/Shader.h>

#include <vector>

using namespace std;


namespace coin {

namespace {

GLuint getGLTypeSize (GLenum type) {
    switch (type) {
    case GL_BYTE: 
    case GL_UNSIGNED_BYTE:
        return sizeof (GLubyte);

    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
        return sizeof (GLushort);

    case GL_INT:
    case GL_UNSIGNED_INT:
        return sizeof (GLuint);

    case GL_HALF_FLOAT: return sizeof (GLfloat) / 2;
    case GL_FLOAT: return sizeof (GLfloat);
    case GL_DOUBLE: return sizeof (GLdouble);

    default:
        break;
    };

    printf ("Warning: Attribute type invalid!");
    return 0;
}

}

Shader::Shader () {
    loaded_ = false;
}

Shader::~Shader () {
    if (loaded_) {
        glDeleteShader (handle_);
    }
}

void Shader::Bind () {
    glUseProgram (handle_);
}

void Shader::RegisterAttributes (const vector<Attribute>& attributes) {
    /* Find and enable attributes.*/
    GLuint offset = 0;
    for (size_t i = 0; i < attributes.size (); ++i) {
        const Attribute& attribute = attributes[i];
        GLint location = glGetAttribLocation (handle (), attribute.name ().c_str ());
        if (location > -1) {
            glVertexAttribPointer (location, attribute.size (), attribute.type (), attribute.normalized (), attribute.stride (), BufferOffset (offset));
            glEnableVertexAttribArray (location);            
            offset += attribute.size () * getGLTypeSize (attribute.type ());
        }else {
            printf ("Warning: Attribute '%str' not found!\n", attribute.name ().c_str ());
        }
    }

    /* Unbind VAO to disable attributes. */
    glBindVertexArray (0);

    /* Disable attributes. */
    for (size_t i = 0; i < attributes.size (); ++i) {
        GLint location = attributes[i].location ();
        if (location > -1) glDisableVertexAttribArray (attributes[i].location ());
    }
}
    
void Shader::SetUniformi (const std::string& name, const GLint v0) {
    GLint location = GetUniform (name);
    if (location >= 0) {
        glUniform1i (location, v0);
    }
}

void Shader::SetUniformu (const std::string& name, const GLuint v0) {
    GLint location = GetUniform (name);
    if (location >= 0) {
        glUniform1ui (location, v0);
    }
}

void Shader::SetUniformMatrix4f (const std::string& name, const GLsizei count, const GLboolean transpose, const GLfloat* value) {
    GLint location = GetUniform (name);
    if (location >= 0) {
        glUniformMatrix4fv (location, count, transpose, value);
    }
}

GLint Shader::GetUniform (const std::string& name) {
    auto element = uniforms_.find (name);
    if (element == uniforms_.end ()) {
        GLint location = glGetUniformLocation (handle_, name.c_str ());
        if (location == -1) {
            printf ("Warning: Uniform '%str' not found!\n", name.c_str ()); 
        }
        uniforms_[name] = location;
        return location;
    }
    return element->second;    
}


}

