#include <windows.h>

#include <coin/utils/directory.h>

using namespace std;


namespace coin {

bool DirectoryIsDirectory (const std::string& directory_name) {
    WIN32_FILE_ATTRIBUTE_DATA data;
    BOOL success = GetFileAttributesEx (directory_name.c_str (), GetFileExInfoStandard, &data);
    return success && (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0;
}


void DirectoryMakeDirectories (const std::string& path, bool last_name_is_directory) {
    string tmp = path;
    string existing_path = "";

    /* Remove last file name. */
    if (!last_name_is_directory) {
        tmp = tmp.substr (0, tmp.find_last_of ('/') + 1); /* '+ 1' for keeping that '/' for folder evaluation. */
    }else {
        /* Append a '/' to the end for folder evaluation. */
        if (tmp[tmp.size () - 1] != '/') {
            tmp.push_back ('/');
        }
    }

    /* Change '/' to windows style '\\'. */
    size_t size = tmp.size ();
    for (size_t i = 0; i < size; ++i) {
        if (tmp[i] == '/') {
            tmp[i] = '\\';
        }
    }

    /* Create directories. */
    size_t last_pos = 0;
    size_t pos;
    while ((pos = tmp.find_first_of ('\\', last_pos)) != string::npos) {
        existing_path += tmp.substr (last_pos, pos + 1);

        if (!DirectoryIsDirectory (existing_path.c_str ())) {
            CreateDirectory (existing_path.c_str (), NULL);
        }
        last_pos = pos + 1;
    }


}

}