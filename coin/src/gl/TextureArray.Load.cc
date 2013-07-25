#include <coin/utils/FileStream.h>
#include <coin/gl/TextureArray.h>
#include <coin/resource/png.h>

using namespace std;


namespace coin {

namespace {

void readTextureArrayFile (const std::string& path, vector<std::string>& files) {
    FileStream stream (path, Stream::Mode::read);

    const size_t file_size = stream.Size ();
    char* source = new char [file_size];
    stream.Read ((uint8_t*) source, file_size);

    const std::string text (source, file_size);
    const std::string base_path = path.substr (0, path.find_last_of ('/') + 1); /* Preserves the '/'. */
    size_t last_pos = 0;
    size_t pos = 0;
    while ((pos = text.find_first_of ('\n', last_pos)) != std::string::npos 
        || (pos = text.size () + 1) > last_pos /* '\n' does not need to be the last character. */) {
        size_t length = (pos - 1) - last_pos;
        if (length > 0) {
            std::string file_name = text.substr (last_pos, length);
            files.push_back (base_path + file_name);
        }
        last_pos = pos + 1;
    }

    delete[] source;
}

}

bool TextureArray::Load (const std::string& path, Setup setup) {
    std::vector<std::string> files;
    readTextureArrayFile (path, files);

    /* Load all images. */
    vector<Image> images (files.size ());
    for (size_t i = 0; i < files.size (); ++i) {
        FileStream stream (files[i], Stream::Mode::read);
        bool success = PngLoad (stream, images[i]);

        /* Texture loading failed. */
        if (!success) {
            return false;
        }
    }

    return Init (images, setup);
}

}