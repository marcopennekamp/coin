#include <coin/manager/TextureManager.h>

#include <coin/coin.h>
#include <coin/gl/Texture.h>
#include <coin/utils/Stream.h>
#include <coin/image/Image.h>
#include <coin/image/png.h>

#include <iostream>

using namespace std;


namespace coin {

void TextureManager::StandardTextureSetup (Texture* texture) {
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 4);
}


void TextureManager::DeleteElement (Texture* element) {
    GLuint id = element->handle ();
    glDeleteTextures (1, &id);
    delete element;
}


TextureManager::TextureManager (const std::string& load_path) : Manager<Texture> (load_path) {
    texture_setup_ = &StandardTextureSetup;
}


TextureManager::TextureManager (const std::string& load_path, std::function<void(Texture*)>& texture_setup) : Manager<Texture> (load_path) {
    texture_setup_ = texture_setup;
}


TextureManager::~TextureManager () {

}


Texture* TextureManager::LoadElement (const std::string& path, bool persistent) {
    return LoadElement (path, persistent, texture_setup_);
}


Texture* TextureManager::LoadElement (const string& path, bool persistent, std::function<void(Texture*)>& texture_setup) {
    FileStream stream ((load_path_ + "/" + path).c_str (), StreamMode::read);
    Image image;
    PngLoad (stream, image);

    GLuint textureId;
    glGenTextures (1, &textureId);
    Texture* texture = new Texture (textureId, image.width (), image.height ());

    glEnable (GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, textureId);
    texture_setup (texture);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, (int) texture->width (), (int) texture->height (), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data ());
    glDisable (GL_TEXTURE_2D);

    image.Free ();

    RegisterElement (path, texture, persistent);
    return texture;
}

}
