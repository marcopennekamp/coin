#ifndef COIN_RESOURCE_MANAGER_H_
#define COIN_RESOURCE_MANAGER_H_

#include <map>
#include <string>

#include <coin/gl/Texture.h>


namespace coin {

/* 
 * T should inherit "Element". 
 * You can write a specialisation/subclass that overwrites bool LoadElement (path, element), 
 * but the Element has to implement Load (string).
 */

template <typename T> 
class Manager {
public:
    typedef std::map<std::string, T*> TMap;
    typedef typename TMap::iterator TMapIterator;

protected:
    const std::string load_path_;

    virtual bool LoadElement (const std::string& path, T* element) {
        return element->Load (load_path_ + "/" + path);
    }

private:
    TMap persistent_elements_;
    TMap temporal_elements_;

    void ClearMap (TMap& element_map) {
        auto it = element_map.begin ();
        for (; it != element_map.end (); it++) {
            delete it->second;
        }
        element_map.clear ();
    }

    bool FindElement (const std::string& path, TMap*& element_map, TMapIterator& it) {
        it = persistent_elements_.find (path);
        if (it != persistent_elements_.end ()) {
            element_map = &persistent_elements_;
            return true;
        }else {
            it = temporal_elements_.find (path);
            if (it != temporal_elements_.end ()) {
                element_map = &temporal_elements_;
                return true;
            }
        }

        return false;
    }

    T* LoadElement (const std::string& path, const bool persistent) {
        /* Create and load element. */
        T* element = new T ();
        bool success = LoadElement (path, element);

        /* Cancel load and delete element when loading failed. */
        if (!success) {
            delete element;
            return NULL;
        }

        /* Put element in map. */
        TMap* element_map;
        if (persistent) element_map = &persistent_elements_;
        else element_map = &temporal_elements_;
        (*element_map)[path] = element;

        return element;
    }

public:
    explicit Manager (const std::string& load_path) : load_path_ (load_path) {

    }

    virtual ~Manager () {
        DeleteElements ();
    }

    void DeletePersistentElements () {
        ClearMap (persistent_elements_);
    }

    void DeleteTemporalElements () {
        ClearMap (temporal_elements_);
    }

    void DeleteElements () {
        DeleteTemporalElements ();
        DeletePersistentElements ();
    }

    void ReloadElements () {
        // TODO(Marco): Implement
    }

    void DeleteElement (const std::string& path) {
        TMap* element_map;
        TMapIterator it;
        if (FindElement (path, element_map, it)) {
            delete it->second;
            element_map->erase (it);
        }
    }

    bool LoadPersistentElement (const std::string& path) {
        return LoadElement (path, true) != NULL;
    }

    T* GetElement (const std::string& path) {
        return GetElement (path, true);
    }

    T* GetElement (const std::string& path, const bool load) {
        TMap* element_map;
        TMapIterator it;
        if (FindElement (path, element_map, it)) {
            return it->second;
        }

        if (load) {
            return LoadElement (path, false); /* Might return NULL as well. */
        }

        return NULL;
    }
};

}


#endif  /* COIN_RESOURCE_MANAGER_H_ */
