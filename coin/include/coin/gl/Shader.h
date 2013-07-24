#ifndef COIN_GL_SHADER_H_
#define COIN_GL_SHADER_H_

#include <map>
#include <string>

#include <coin/coin.h>
#include <coin/gl.h>
#include <coin/resource/Element.h>


namespace coin {

class COIN_EXPORT Shader : public Element {
public:
    class Attribute {
    private:
        GLint location_;

        std::string name_;
        GLenum type_;
        GLuint size_;
        GLuint stride_;
        GLboolean normalized_;

        void Init (const std::string& name, const GLenum type, const GLuint size, const GLuint stride, const GLboolean normalized) {
            location_ = -1;

            name_ = name;
            type_ = type;
            size_ = size;
            stride_ = stride;
            normalized_ = normalized;
        }

    public:
        Attribute (const std::string& name, const GLenum type, const GLuint size, const GLuint stride) {
            Init (name, type, size, stride, GL_FALSE);
        }

        Attribute (const std::string& name, const GLenum type, const GLuint size, const GLuint stride, const GLboolean normalized) {
            Init (name, type, size, stride, normalized);
        }

        inline GLint location () const { return location_; }
        inline void location (GLint location) { location_ = location; }
        
        inline const std::string& name () const { return name_; }
        inline GLenum type () const { return type_; }
        inline GLuint size () const { return size_; }
        inline GLuint stride () const { return stride_; }
        inline GLboolean normalized () const { return normalized_; }
    };

private:
    bool loaded_;

    GLuint handle_;
    std::map<const std::string, GLint> uniforms_;

public:
    Shader ();
    ~Shader ();

    bool Load (const std::string& path);

    void Bind ();

    /* Bind the VAO before. This call unbinds the VAO. */
    void RegisterAttributes (const Attribute* attributes, const size_t length);
    
    void SetUniformi (const std::string& name, const GLint a);
    void SetUniformu (const std::string& name, const GLuint a);
    void SetUniformMatrix4f (const std::string& name, const GLsizei count, const GLboolean transpose, const GLfloat* value);

    GLint GetUniform (const std::string& name);

    inline GLuint handle () const { return handle_; }
};

}

#endif  /* COIN_GL_SHADER_H_ */
