#include <windows.h>

#include <coin/utils/directory.h>

using namespace std;


namespace coin {

bool DirectoryIsDir (const char* name) {
    WIN32_FILE_ATTRIBUTE_DATA data;
    GetFileAttributesEx (name, GetFileExInfoStandard, &data);
    return (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0;
}

}