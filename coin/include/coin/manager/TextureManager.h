#ifndef COIN_MANAGER_TEXTUREMANAGER_H_
#define COIN_MANAGER_TEXTUREMANAGER_H_

#include <map>
#include <string>
#include <functional>

#include <coin/gl/Texture.h>
#include <coin/manager/Manager.h>

/* TODO(Marco): Resource not found "exceptions"... */


namespace coin {

class TextureManager : public Manager<Texture> {
protected:
    Texture::Setup texture_setup_;

public:
    COIN_DECL TextureManager (const std::string& load_path, Texture::Setup texture_setup = Texture::StandardSetup);
    COIN_DECL ~TextureManager ();

    COIN_DECL Texture* LoadElement (const std::string& path, const bool persistent = false);
    COIN_DECL Texture* LoadElement (const std::string& path, const bool persistent, Texture::Setup texture_setup);
};

}

#endif  /* COIN_MANAGER_TEXTUREMANAGER_H_ */
