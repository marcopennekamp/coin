#ifndef COIN_UTILS_DIRECTORY_H_
#define COIN_UTILS_DIRECTORY_H_

#include <dirent.h>

#include <functional>
#include <string>

#include <coin/coin.h>


namespace coin {

COIN_UTILS_DECL void DirectoryCrawl (std::string& directory_name, std::function<void(std::string&)>& file_callback, std::function<bool(std::string&)>& should_crawl_directory);
COIN_UTILS_DECL bool DirectoryIsDir (const char* name);

}

#endif  /* COIN_UTILS_DIRECTORY_H_ */