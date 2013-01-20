#include <string.h>

#include <coin/coin.h>
#include <coin/gl/Shader.h>
#include <coin/manager/ShaderManager.h>
#include <coin/utils/Stream.h>

using namespace std;


namespace coin {


namespace {

void printLog (GLuint shader) {
    int length;
    int log_length;
    glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &log_length);
    GLchar* log = new GLchar [log_length];
    glGetShaderInfoLog (shader, log_length, &length, log);
    const char* text = (const char*) log;
    printf ("Could not load Shader!\n");
    printf (text);
    delete log;
}


char* ReadShaderSource (const char* path) {
    FileStream stream (path, StreamMode::read);

    Size file_size = stream.Size ();
    char* source = new char [file_size + 1];
    stream.Read ((u8*) source, file_size);
    source[file_size] = '\0';

    return source;
}

}


void ShaderManager::DeleteElement (Shader* element) {
    delete element;
}


ShaderManager::ShaderManager (const std::string& load_path) : Manager (load_path) {

}


ShaderManager::~ShaderManager () {

}


Shader* ShaderManager::LoadElement (const std::string& path, bool persistent) {
    string local_path = load_path_ + "\\" + path;
    string final_path = local_path;
    final_path += ".vs";
    char* vs_source = ReadShaderSource (final_path.c_str ());

    final_path = local_path;
    final_path += ".fs";
    char* fs_source = ReadShaderSource (final_path.c_str ());

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

    free (vs_source);
    free (fs_source);

    /* Check whether compilation was successful. */
    GLint successful;

    glGetShaderiv (vs, GL_COMPILE_STATUS, &successful);
    if (successful == GL_FALSE) {
        printLog (vs);
        return NULL;
    }

    glGetShaderiv (fs, GL_COMPILE_STATUS, &successful);
    if (successful == GL_FALSE) {
        printLog (fs);
        return NULL;
    }

    /* Create program. */
    GLuint id = glCreateProgram ();
    Shader* shader = new Shader (id);

    glAttachShader (id, vs);
    glAttachShader (id, fs);

    glLinkProgram (id);

    glGetProgramiv (id, GL_LINK_STATUS, &successful);
    if (successful == GL_FALSE) {
        return NULL;
    }

    RegisterElement (path, shader, persistent);
    return shader;
}


}
