#ifndef COIN_UTILS_STREAM_H_
#define COIN_UTILS_STREAM_H_

#include <stdio.h>

#include <string>

#include <coin/coin.h>


namespace coin {

namespace StreamMode {

enum T {
    read = 0x00,
    write,
    append
};

}


class COIN_UTILS_DECL Stream {
  protected:
    StreamMode::T mode_;

  public:
    Stream (const StreamMode::T mode) {
        mode_ = mode;
    }

    virtual ~Stream () { }

    virtual const coin::Size Size () { return 0; }
    virtual const coin::Position Position () { return 0; }

    virtual void SetPosition (const coin::Position position) { }

    virtual void Read (u8* buffer, const coin::Size buffer_size) { }
    virtual void Write (const u8* buffer, const coin::Size buffer_size) { }
    virtual void Flush () { }

    /* Endianness independent IO. */
    void ReadU8 (u8& out);
    void ReadU16 (u16& out);
    void ReadU32 (u32& out);
    void ReadU64 (u64& out);
    void ReadString (std::string& out);

    void WriteU8 (u8 in);
    void WriteU16 (u16 in);
    void WriteU32 (u32 in);
    void WriteU64 (u64 in);

    inline StreamMode::T mode () { return mode_; }
};


class COIN_UTILS_DECL FileStream : public Stream {
  private:
    FILE* stream_;

  public:
    FileStream (const char* path, const StreamMode::T mode);
    ~FileStream ();

    const coin::Size Size ();
    const coin::Position Position ();

    void SetPosition (const coin::Position position);

    void Read (u8* buffer, const coin::Size buffer_size);
    void Write (const u8* buffer, const coin::Size buffer_size);
    void Flush ();
};


class COIN_UTILS_DECL BufferStream : public Stream {
  private:
    u8* buffer_;
    coin::Position position_;
    coin::Size buffer_size_;

  public:
    BufferStream (u8* buffer, const coin::Size buffer_size, const StreamMode::T mode);
    ~BufferStream ();

    const coin::Size Size ();
    const coin::Position Position ();

    void SetPosition (const coin::Position position);

    void Read (u8* buffer, const coin::Size buffer_size);
    void Write (const u8* buffer, const coin::Size buffer_size);
    void Flush ();
};

}

#endif  /* COIN_UTILS_STREAM_H_ */

