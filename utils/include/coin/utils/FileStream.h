#ifndef COIN_UTILS_FILESTREAM_H_
#define COIN_UTILS_FILESTREAM_H_

#include <coin/utils/Stream.h>


namespace coin {

class COIN_UTILS_EXPORT FileStream : public Stream {
private:
    FILE* stream_;

public:
    FileStream (const std::string& path, const Mode mode);
    ~FileStream ();

    const size_t Size ();
    const size_t Position ();

    void SetPosition (const size_t position);

    void Read (uint8_t* buffer, const size_t buffer_size);
    void Write (const uint8_t* buffer, const size_t buffer_size);
    void Flush ();
};

}


#endif  /* COIN_UTILS_FILESTREAM_H_ */