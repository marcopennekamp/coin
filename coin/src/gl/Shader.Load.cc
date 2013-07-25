#include <coin/gl/Shader.h>
#include <coin/utils/FileStream.h>

using namespace std;


namespace coin {

namespace {

void printLog (GLuint shader, const string& name) {
    int length;
    int log_length;
    glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &log_length);
    GLchar* log = new GLchar [log_length];
    glGetShaderInfoLog (shader, log_length, &length, log);
    printf ("Could not load Shader '%s':\n%s\n", name.c_str (), log);
    fflush (stdout);
    delete[] log;
}

char* ReadShaderSource (const std::string& path) {
    FileStream stream (path, Stream::Mode::read);

    size_t file_size = stream.Size ();
    char* source = new char [file_size + 1];
    stream.Read ((uint8_t*) source, file_size);
    source[file_size] = '\0';

    return source;
}

}

bool Shader::Load (const std::string& path) {
    char* vs_source = ReadShaderSource (path + ".vs");
    char* fs_source = ReadShaderSource (path + ".fs");

    /* Compile Shader. */
    GLuint vs, fs;

    vs = glCreateShader (GL_VERTEX_SHADER);
    fs = glCreateShader (GL_FRAGMENT_SHADER);

    const GLint vs_source_length = (GLint) strlen (vs_source);
    const GLint fs_source_length = (GLint) strlen (fs_source);

    glShaderSource (vs, 1, (const char**) &vs_source, &vs_source_length);
    glShaderSource (fs, 1, (const char**) &fs_source, &fs_source_length);

    glCompileShader (vs);
    glCompileShader (fs);

    delete[] vs_source;
    delete[] fs_source;

    /* Check whether compilation was successful. */
    GLint successful;

    glGetShaderiv (vs, GL_COMPILE_STATUS, &successful);
    if (successful == GL_FALSE) {
        printLog (vs, path);
        return false;
    }

    glGetShaderiv (fs, GL_COMPILE_STATUS, &successful);
    if (successful == GL_FALSE) {
        printLog (fs, path);
        return false;
    }

    /* Create program. */
    handle_ = glCreateProgram ();
    

    glAttachShader (handle_, vs);
    glAttachShader (handle_, fs);

    glLinkProgram (handle_);

    glGetProgramiv (handle_, GL_LINK_STATUS, &successful);
    if (successful == GL_FALSE) {
        return false;
    }

    return true;
}

}