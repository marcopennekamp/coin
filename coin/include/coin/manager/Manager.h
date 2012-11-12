#ifndef COIN_MANAGER_MANAGER_H_
#define COIN_MANAGER_MANAGER_H_

#include <map>
#include <string>


namespace coin {

template <typename T>
class Manager {
  protected:
    typedef std::map<std::string, T*> TMap;
    typedef typename TMap::iterator TMapIterator;

    std::string load_path_;

    virtual void DeleteElement (T* element) = 0;

    bool FindElement (const std::string& path, TMap*& element_map, TMapIterator& it) {
        it = persistent_elements_.find (path);
        if (it != persistent_elements_.end ()) {
            element_map = &persistent_elements_;
            return true;
        }else {
            it = elements_.find (path);
            if (it != elements_.end ()) {
                element_map = &elements_;
                return true;
            }
        }
        return false;
    }

    void RegisterElement (const std::string& path, T* element, bool persistent) {
        TMap* element_map;
        if (persistent) element_map = &persistent_elements_;
        else element_map = &elements_;
        (*element_map)[path] = element;
    }

  private:
    TMap persistent_elements_;
    TMap elements_;

    void ClearMap (TMap& element_map) {
        auto it = element_map.begin ();
        for (; it != element_map.end (); it++) {
            DeleteElement (it->second);
        }
        element_map.clear ();
    }

  public:
    virtual ~Manager () {
        Clear ();
    }

    virtual T* LoadElement (const std::string& path, bool persistent = false) = 0;

    Manager (const std::string& load_path) {
        load_path_ = load_path;
    }

    void DeletePersistentElements () {
        ClearMap (persistent_elements_);
    }

    void DeleteElements () {
        ClearMap (elements_);
    }

    void Clear () {
        DeleteElements ();
        DeletePersistentElements ();
    }

    void ReloadElements () {
        // TODO(Marco): Implement
    }

    void DeleteElement (const std::string& path) {
        TMap* element_map;
        TMapIterator it;
        if (FindElement (path, element_map, it)) {
            DeleteElement (it->second);
            element_map->erase (it);
        }
    }

    T* GetElement (const std::string& path, bool load = true) {
        TMap* element_map;
        TMapIterator it;
        if (FindElement (path, element_map, it)) {
            return it->second;
        }
        if (load) {
            return LoadElement (path, false);
        }
        return NULL;
    }
};

}

#endif  /* COIN_MANAGER_MANAGER_H_ */
