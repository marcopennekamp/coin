#include <coin/resource/Image.h>


namespace coin {

Image::Image () {
    data_ = NULL;
}

Image::Image (const Size width, const Size height) {
    Create (width, height);
}

Image::~Image () {
    if (data_ != NULL) {
        delete[] data_;
    }
}

void Image::Create (const Size width, const Size height) {
    width_ = width;
    height_ = height;
    data_ = new u32 [width * height];
}

}
