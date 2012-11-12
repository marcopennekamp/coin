#include <coin/image/Image.h>


namespace coin {

void Image::Create (const Size width, const Size height) {
    width_ = width;
    height_ = height;
    data_ = new u32 [width * height];
}

void Image::Free () {
    delete[] data_;
}

}
