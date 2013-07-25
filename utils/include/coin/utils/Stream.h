#ifndef COIN_UTILS_STREAM_H_
#define COIN_UTILS_STREAM_H_

#include <string>

#include <coin/coin.h>


namespace coin {

class COIN_UTILS_EXPORT Stream {
public:
    enum class Mode {
        read,
        write,
        append
    };

protected:
    const Mode mode_;

public:
    Stream (const Mode mode) : mode_ (mode) { }
    virtual ~Stream () { }

    virtual const size_t Size () { return 0; }
    virtual const size_t Position () { return 0; }

    virtual void SetPosition (const size_t position) { }

    virtual void Read (uint8_t* buffer, const size_t buffer_size) { }
    virtual void Write (const uint8_t* buffer, const size_t buffer_size) { }
    virtual void Flush () { }

    /* Endianness independent IO. */
    void ReadU8 (uint8_t& out);
    void ReadU16 (uint16_t& out);
    void ReadU32 (uint32_t& out);
    void ReadU64 (uint64_t& out);
    void ReadString (std::string& out);

    void WriteU8 (const uint8_t in);
    void WriteU16 (const uint16_t in);
    void WriteU32 (const uint32_t in);
    void WriteU64 (const uint64_t in);
    void WriteString (const std::string& in);

    inline Mode mode () { return mode_; }
};

}


#endif  /* COIN_UTILS_STREAM_H_ */

