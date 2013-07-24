#include <dirent.h>

#include <coin/utils/Directory.h>
#include <coin/utils/Time.h>

using namespace std;


namespace coin {

void DirectoryCrawl (const std::string& directory_name, std::function<void(const std::string&)>& file_callback, std::function<bool(const std::string&)>& should_crawl_directory) {
    DIR* dir = opendir (directory_name.c_str ());

    /* Load all block textures from directory. */
    if (dir != NULL) {
        struct dirent* entry;
        while ((entry = readdir (dir)) != NULL) {
            string name = entry->d_name;

            /* Ignore top directory and self reference. */
            if (name == "." || name == "..") {
                continue;
            }

            string new_path = directory_name + "\\" + name;
            bool is_directory = DirectoryIsDirectory (new_path);
            if (is_directory) {
                if (should_crawl_directory (new_path)) {
                    DirectoryCrawl (new_path, file_callback, should_crawl_directory);
                }
            }else {
                file_callback (new_path);
            }
        }
        closedir (dir);
    } else {
        printf ("Could not open directory '%s'!\n", directory_name);
        return;
    }

}

}