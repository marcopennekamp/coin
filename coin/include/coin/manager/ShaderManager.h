#ifndef COIN_MANAGER_SHADERMANAGER_H_
#define COIN_MANAGER_SHADERMANAGER_H_

#include <map>
#include <string>

#include <coin/gl/Shader.h>
#include <coin/manager/Manager.h>


namespace coin {

class ShaderManager : public Manager<Shader> {
  private:
    void DeleteElement (Shader* element);

  public:
    COIN_DECL ShaderManager (const std::string& load_path);
    COIN_DECL ~ShaderManager ();

    COIN_DECL Shader* LoadElement (const std::string& path, bool persistent = false);
};

}

#endif  /* COIN_MANAGER_SHADERMANAGER_H_ */
