#include <coin/gl/TextureRegion.h>
#include <coin/gl/Texture.h>


namespace coin {

TextureRegion::TextureRegion (Texture* texture, Size x, Size y, Size x_end, Size y_end) {
    Init (texture, x, y, x_end, y_end);
}

TextureRegion::TextureRegion (Texture* texture) {
    Init (texture, 0, 0, texture->width (), texture->height ());
}

void TextureRegion::Init (Texture* texture, Size x, Size y, Size x_end, Size y_end) {
    texture_ = texture;
    x_ = x;
    y_ = y;
    x_end_ = x_end;
    y_end_ = y_end;
}

}