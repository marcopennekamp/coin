#include <stdio.h>

#include <coin/utils/Stream.h>


namespace coin {

namespace {

template<typename T>
inline void get (u8* buffer, u32 pos, T& out) {
    const u32 shl = (sizeof(T) - (pos + 1)) * 8;
    out = out | (buffer[pos] << shl);
}

template<u32 size, typename T>
inline void read (Stream& stream, T& out) {
    u8 buffer [size];
    stream.Read (buffer, size);
    for (u32 i = 0; i < size; ++i) {
        get (buffer, i, out);
    }
}

}


void Stream::ReadU8 (u8& out) {
    Read (&out, 1);
}

void Stream::ReadU16 (u16& out) {
    read<2> (*this, out);
    // out = ((u16) buffer[0] << 8) | buffer[1];
}

void Stream::ReadU32 (u32& out) {
    read<4> (*this, out);
}

void Stream::ReadU64 (u64& out) {
    read<8> (*this, out);
}

void Stream::WriteU8 (u8 in) {
    Write (&in, 1);
}

void Stream::WriteU16 (u16 in) {

}

void Stream::WriteU32 (u32 in) {

}

void Stream::WriteU64 (u64 in) {

}


}