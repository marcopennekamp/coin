#define _CRT_SECURE_NO_DEPRECATE

#include <coin/utils/Stream.h>


namespace coin {

FileStream::FileStream (const char* path, const StreamMode::T mode) : Stream (mode) {
    const char* fopen_mode;
    if (mode_ == StreamMode::read) {
        fopen_mode = "rb";
    }else if (mode_ == StreamMode::write) {
        fopen_mode = "wb";
    }else { /* FLEE_STREAM_APPEND */
        fopen_mode = "ab";
    }

    stream_ = fopen (path, fopen_mode);
    if (stream_ == NULL) {
        printf ("Could not open file '%s'.\n", path);
        fflush (stdout);
    }
}


FileStream::~FileStream () {
    fclose (stream_);
}


const Size FileStream::Size () {
    if (mode_ != StreamMode::read) {
        printf ("Can not get the size of a file not opened for reading.");
        return 0;
    }

    coin::Size current_pos = ftell (stream_);
    fseek (stream_, 0L, SEEK_END);
    coin::Size size = ftell (stream_);
    fseek (stream_, current_pos, SEEK_SET); /* Rewind to last position. */
    return size;
}


const u32 FileStream::Position () {
    return ftell (stream_);
}


void FileStream::SetPosition (const coin::Position position) {
    fseek (stream_, position, 0);
}


void FileStream::Flush () {
    fflush (stream_);
}


void FileStream::Read (u8* buffer, const coin::Size buffer_size) {
    fread (buffer, sizeof (u8), buffer_size, stream_);
}


void FileStream::Write (const u8* buffer, const coin::Size buffer_size) {
    fwrite (buffer, sizeof (u8), buffer_size, stream_);
}

}