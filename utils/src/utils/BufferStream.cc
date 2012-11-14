#include <stdlib.h>
#include <string.h>

#include <coin/utils/Stream.h>


namespace coin {

BufferStream::BufferStream (u8* buffer, const coin::Size buffer_size, const StreamMode::T mode) : Stream (mode) {
    buffer_size_ = buffer_size;
    position_ = 0;

    if (buffer == NULL) {
        printf ("The buffer may not be null!");
        return;
    }
    buffer_ = buffer;
}


BufferStream::~BufferStream () {
    return; /* Nothing to do here! */
}


const coin::Size BufferStream::Size () {
    return buffer_size_;
}


const coin::Position BufferStream::Position () {
    return position_;
}


void BufferStream::SetPosition (const coin::Position position) {
    position_ = position;
}


void BufferStream::Read (u8* buffer, const coin::Size buffer_size) {
    if (buffer_size + position_ > buffer_size_) {
        printf ("Read call exceeds buffer size!\n");
        position_ = buffer_size_;
        return;
    }
    memcpy (buffer, buffer_ + position_, buffer_size);
    position_ += buffer_size;
}


void BufferStream::Write (const u8* buffer, const coin::Size buffer_size) {
    if (buffer_size + position_ > buffer_size_) {
        printf ("Write call exceeds buffer size!\n");
        position_ = buffer_size_;
        return;
    }
    memcpy (buffer_ + position_, buffer, buffer_size);
    position_ += buffer_size;
}


void BufferStream::Flush () {
    return; /* One does not need to flush a buffer. */
}

}