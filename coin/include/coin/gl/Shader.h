#ifndef COIN_GL_SHADER_H_
#define COIN_GL_SHADER_H_

#include <map>
#include <string>

#include <coin/coin.h>
#include <coin/gl.h>


namespace coin {

class COIN_DECL Shader {
public:
    struct Attribute {
        GLint location;
        std::string name;
        GLenum type;
        GLuint size;
        GLuint stride;
        GLboolean normalized;

        Attribute (const std::string& name, const GLenum type, const GLuint size, const GLuint stride) {
            Init (name, type, size, stride, GL_FALSE);
        }

        Attribute (const std::string& name, const GLenum type, const GLuint size, const GLuint stride, const GLboolean normalized) {
            Init (name, type, size, stride, normalized);
        }

    private: 
        void Init (const std::string& name, const GLenum type, const GLuint size, const GLuint stride, const GLboolean normalized) {
            location = -1;
            this->name = name;
            this->type = type;
            this->size = size;
            this->stride = stride;
            this->normalized = normalized;
        }
    };

private:
    GLuint handle_;

    std::map<std::string, GLint>* uniforms_;

public:
    Shader (const GLuint handle);
    ~Shader ();

    void Bind ();

    /* Bind the VAO before. This call unbinds the VAO. */
    void RegisterAttributes (const Attribute* attributes, size_t length);
    
    void SetUniformi (const std::string& name, GLint a);
    void SetUniformu (const std::string& name, GLuint a);
    void SetUniformMatrix4f (const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value);


    GLint GetUniform (const std::string& name);
};

}

#endif  /* COIN_GL_SHADER_H_ */
