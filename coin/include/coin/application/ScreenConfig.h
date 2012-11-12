#ifndef COIN_APPLICATION_SCREENCONFIG_H_
#define COIN_APPLICATION_SCREENCONFIG_H_

#include <coin/coin.h>


namespace coin {

class COIN_DECL ScreenConfig {
  private:
    Size width_;
    Size height_;
    float aspect_ratio_;

  public:
    void Resize (Size width, Size height);

    inline Size width () { return width_; }
    inline Size height () { return height_; }
    inline float aspect_ratio () { return aspect_ratio_; }
};


}

#endif  /* COIN_APPLICATION_SCREENCONFIG_H_ */
