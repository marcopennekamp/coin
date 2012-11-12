#ifndef COIN_IMAGE_PNG_H_
#define COIN_IMAGE_PNG_H_

#include <coin/utils/Stream.h>

#include <coin/coin.h>
#include <coin/image/Image.h>


namespace coin {

COIN_DECL bool PngLoad (Stream& stream, Image& image);
COIN_DECL bool PngSave (Stream& stream, Image& image, bool flipped = false);

}

#endif  /* COIN_IMAGE_PNG_H */

