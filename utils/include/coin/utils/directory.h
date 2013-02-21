#ifndef COIN_UTILS_DIRECTORY_H_
#define COIN_UTILS_DIRECTORY_H_

#include <functional>
#include <string>

#include <coin/coin.h>


namespace coin {
namespace Directory {

/*
 * Crawls a directory. When it finds a file it calls 'file_callback' with the respective file.
 * When it finds a directory, it calls 'should_crawl_directory' which should return whether the directory has to be crawled or not.
 */
COIN_UTILS_DECL void Crawl (const std::string& directory_name, std::function<void(std::string&)>& file_callback, std::function<bool(std::string&)>& should_crawl_directory);

/* 
 * Whether the specified file path is a directory.
 */
COIN_UTILS_DECL bool IsDirectory (const std::string& directory_name);

/*
 * Creates all directories named in the path.
 */
COIN_UTILS_DECL void MakeDirectories (const std::string& path, const bool last_name_is_directory);

}
}

#endif  /* COIN_UTILS_DIRECTORY_H_ */