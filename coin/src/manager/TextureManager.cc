#include <coin/manager/TextureManager.h>

#include <coin/coin.h>
#include <coin/gl/Texture.h>
#include <coin/utils/Stream.h>
#include <coin/image/Image.h>
#include <coin/image/png.h>

#include <iostream>

using namespace std;


namespace coin {

TextureManager::TextureManager (const std::string& load_path, Texture::Setup texture_setup) : Manager<Texture> (load_path) {
    texture_setup_ = texture_setup;
}


TextureManager::~TextureManager () {
    // TODO(Marco): Delete textures.
}


Texture* TextureManager::LoadElement (const string& path, const bool persistent) {
    return LoadElement (path, persistent, texture_setup_);
}


Texture* TextureManager::LoadElement (const string& path, const bool persistent, Texture::Setup texture_setup) {
    FileStream stream ((load_path_ + "/" + path).c_str (), StreamMode::read);
    Image image;
    PngLoad (stream, image);
    Texture* texture = new Texture (image, texture_setup);
    image.Free ();

    RegisterElement (path, texture, persistent);
    return texture;
}

}
