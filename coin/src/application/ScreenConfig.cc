#include <coin/application/ScreenConfig.h>


namespace coin {

void ScreenConfig::Resize (Size width, Size height) {
    width_ = width;
    height_ = height;
    aspect_ratio_ = (float) width / (float) height;
}

}


