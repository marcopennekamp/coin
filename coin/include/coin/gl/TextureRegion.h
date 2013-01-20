#ifndef GL_COIN_TEXTUREREGION_H_
#define GL_COIN_TEXTUREREGION_H_

#include <coin/coin.h>





namespace coin {

class Texture;

class TextureRegion {
private:
    Texture* texture_;
    Size x_;
    Size y_;
    Size x_end_;
    Size y_end_;

    void Init (Texture* texture, Size x, Size y, Size x_end, Size y_end); 

public:
    TextureRegion (Texture* texture);
    TextureRegion (Texture* texture, Size x, Size y, Size x_end, Size y_end);

    inline Texture* texture () { return texture_; }
    inline Size x () { return x_; }
    inline Size y () { return y_; }
    inline Size x_end () { return x_end_; }
    inline Size y_end () { return y_end_; }
};



}




#endif  /* GL_COIN_TEXTUREREGION_H_ */