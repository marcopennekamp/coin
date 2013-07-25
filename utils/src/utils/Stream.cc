#include <stdio.h>

#include <coin/utils/Stream.h>


namespace coin {

namespace {

template<typename T>
inline void get (uint8_t* buffer, size_t pos, T& out) {
    const size_t shl = (sizeof(T) - (pos + 1)) * 8;
    out = out | (((T) buffer[pos]) << shl);
}

template<size_t size, typename T>
inline void read (Stream& stream, T& out) {
    uint8_t buffer [size];
    stream.Read (buffer, size);
    for (size_t i = 0; i < size; ++i) {
        get (buffer, i, out);
    }
}


template<typename T>
inline void set (T in, uint8_t* buffer, size_t pos) {
    const size_t shr = (sizeof(T) - (pos + 1)) * 8;
    buffer[pos] = (uint8_t) (in >> shr);
}

template<size_t size, typename T>
inline void write (Stream& stream, T in) {
    uint8_t buffer [size];
    for (size_t i = 0; i < size; ++i) {
        set (in, buffer, i);
    }
    stream.Write (buffer, size);
}

}


void Stream::ReadU8 (uint8_t& out) {
    out = 0;
    Read (&out, 1);
}

void Stream::ReadU16 (uint16_t& out) {
    out = 0;
    read<2> (*this, out);
}

void Stream::ReadU32 (uint32_t& out) {
    out = 0;
    read<4> (*this, out);
}

void Stream::ReadU64 (uint64_t& out) {
    out = 0;
    read<8> (*this, out);
}

void Stream::ReadString (std::string& out) {
    uint16_t size; 
    ReadU16 (size);
    if (size > 0) {
        out.resize (size);
        Read ((uint8_t*) &out[0], size);
    }
}

void Stream::WriteU8 (const uint8_t in) {
    Write (&in, 1);
}

void Stream::WriteU16 (const uint16_t in) {
    write<2> (*this, in);
}

void Stream::WriteU32 (const uint32_t in) {
    write<4> (*this, in);
}

void Stream::WriteU64 (const uint64_t in) {
    write<8> (*this, in);
}

void Stream::WriteString (const std::string& in) {
    uint16_t size = (uint16_t) in.size (); 
    WriteU16 (size);
    if (size > 0) {
        Write ((const uint8_t*) in.data (), size);
    }
}


}