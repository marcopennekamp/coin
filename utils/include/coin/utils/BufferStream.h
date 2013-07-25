#ifndef COIN_UTILS_BUFFERSTREAM_H_
#define COIN_UTILS_BUFFERSTREAM_H_

#include <coin/utils/Stream.h>


namespace coin {

class COIN_UTILS_EXPORT BufferStream : public Stream {
  private:
    uint8_t* buffer_;
    size_t position_;
    size_t buffer_size_;

  public:
    BufferStream (uint8_t* buffer, const size_t buffer_size, const Mode mode);
    ~BufferStream ();

    const size_t Size ();
    const size_t Position ();

    void SetPosition (const size_t position);

    void Read (uint8_t* buffer, const size_t buffer_size);
    void Write (const uint8_t* buffer, const size_t buffer_size);
    void Flush ();
};

}


#endif  /* COIN_UTILS_BUFFERSTREAM_H_ */