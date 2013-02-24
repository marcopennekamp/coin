#ifndef COIN_RESOURCE_TEXTUREMANAGER_H_
#define COIN_RESOURCE_TEXTUREMANAGER_H_

#include <map>
#include <string>

#include <coin/resource/Manager.h>


namespace coin {

/* 
 * T should be a subclass of Texture.
 */
template<typename T>
class TextureManager : public Manager<T> {
protected:
    typename T::Setup texture_setup_;

    bool LoadElement (const std::string& path, T* element) {
        return element->Load (load_path_ + "/" + path, texture_setup_);
    }

public:
    TextureManager (const std::string& load_path) : Manager<T> (load_path) {
        texture_setup_ = NULL;
    }

    TextureManager (const std::string& load_path, typename T::Setup texture_setup) : Manager<T> (load_path) {
        texture_setup_ = texture_setup;
    }
};

}


#endif  /* COIN_RESOURCE_TEXTUREMANAGER_H_ */
