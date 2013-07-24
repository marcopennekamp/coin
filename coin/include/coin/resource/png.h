#ifndef COIN_RESOURCE_PNG_H_
#define COIN_RESOURCE_PNG_H_

#include <coin/utils/Stream.h>

#include <coin/coin.h>
#include <coin/resource/Image.h>


namespace coin {

COIN_EXPORT bool PngLoad (Stream& stream, Image& image);
COIN_EXPORT bool PngSave (Stream& stream, Image& image, const bool flipped = false); // TODO(Marco): Comment/ Flip vertical or horizontal?

}

#endif  /* COIN_RESOURCE_PNG_H */

