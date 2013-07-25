#ifndef COIN_RESOURCE_IMAGE_H_
#define COIN_RESOURCE_IMAGE_H_

#include <coin/coin.h>
#include <coin/gl.h>


namespace coin {

class COIN_EXPORT Image {
  private:
    Size width_;
    Size height_;
    uint32_t* data_;

  public:
    Image ();
    Image (const Size width, const Size height);
    ~Image ();

    /*
     * Allocates 'data_'.
     */
    void Create (const Size width, const Size height);

    inline const Size width () const { return width_; }
    inline const Size height () const { return height_; }
    inline uint32_t* data () const { return data_; }
};

}

#endif  /* COIN_RESOURCE_IMAGE_H_ */

