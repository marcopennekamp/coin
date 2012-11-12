#ifndef COIN_IMAGE_IMAGE_H_
#define COIN_IMAGE_IMAGE_H_

#include <coin/coin.h>
#include <coin/gl.h>


namespace coin {

class COIN_DECL Image {
  private:
    Size width_;
    Size height_;
    u32* data_;

  public:
    /*
     * Allocates 'data_'.
     */
    void Create (const Size width, const Size height);

    /*
     * Frees 'data_'.
     */
    void Free ();

    inline const Size width () { return width_; }
    inline const Size height () { return height_; }
    inline u32* data () { return data_; }
};

}

#endif  /* COIN_IMAGE_IMAGE_H_ */

