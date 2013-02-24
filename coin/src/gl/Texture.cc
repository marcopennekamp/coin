#include <coin/gl/Texture.h>


namespace coin {

Texture::~Texture () {
    glDeleteTextures (1, &handle_);
}

void Texture::ApplyTextureSetup (Setup setup) {
    if (setup == NULL) {
        TextureSetup ();
    }else {
        setup (this);
    }
}

void Texture::CreateHandle () {
    glGenTextures (1, &handle_);
}

bool Texture::Load (const std::string& path) {
    return Load (path, NULL);
}

}
