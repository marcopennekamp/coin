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
    void DeleteElement (Texture* element);
    static void StandardTextureSetup (Texture* texture);

  private:
    std::function<void(Texture*)> texture_setup_;

  public:
    COIN_DECL TextureManager (const std::string& load_path);
    COIN_DECL TextureManager (const std::string& load_path, std::function<void(Texture*)>& texture_setup);
    COIN_DECL ~TextureManager ();

    COIN_DECL Texture* LoadElement (const std::string& path, bool persistent = false);
    COIN_DECL Texture* LoadElement (const std::string& path, bool persistent, std::function<void(Texture*)>& texture_setup);
};

}

#endif  /* COIN_MANAGER_TEXTUREMANAGER_H_ */
