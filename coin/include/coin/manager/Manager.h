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

    const std::string load_path_;

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

    void RegisterElement (const std::string& path, T* element, const bool persistent) {
        TMap* element_map;
        if (persistent) element_map = &persistent_elements_;
        else element_map = &temporal_elements_;
        (*element_map)[path] = element;
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

  public:
    Manager (const std::string& load_path) : load_path_ (load_path) {

    }

    virtual ~Manager () {
        DeleteElements ();
    }

    virtual T* LoadElement (const std::string& path, const bool persistent = false) = 0;

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
            return LoadElement (path, false);
        }

        return NULL;
    }
};

}

#endif  /* COIN_MANAGER_MANAGER_H_ */
