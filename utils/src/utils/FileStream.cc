#include <coin/utils/FileStream.h>


namespace coin {

FileStream::FileStream (const std::string& path, const Mode mode) : Stream (mode) {
    const char* fopen_mode;
    if (mode_ == Stream::Mode::read) {
        fopen_mode = "rb";
    }else if (mode_ == Stream::Mode::write) {
        fopen_mode = "wb";
    }else { /* Stream::Mode::append */
        fopen_mode = "ab";
    }

    fopen_s (&stream_ , path.c_str (), fopen_mode);
    if (stream_ == NULL) {
        printf ("Could not open file '%s'.\n", path.c_str ());
        fflush (stdout);
    }
}


FileStream::~FileStream () {
    fclose (stream_);
}


const size_t FileStream::Size () {
    if (mode_ != Stream::Mode::read) {
        printf ("Can not get the size of a file not opened for reading.");
        return 0;
    }

    coin::Size current_pos = ftell (stream_);
    fseek (stream_, 0L, SEEK_END);
    coin::Size size = ftell (stream_);
    fseek (stream_, current_pos, SEEK_SET); /* Rewind to last position. */
    return size;
}


const size_t FileStream::Position () {
    return (size_t) ftell (stream_);
}


void FileStream::SetPosition (const size_t position) {
    fseek (stream_, (long) position, 0);
}


void FileStream::Flush () {
    fflush (stream_);
}


void FileStream::Read (uint8_t* buffer, const size_t buffer_size) {
    fread (buffer, sizeof (uint8_t), buffer_size, stream_);
}


void FileStream::Write (const uint8_t* buffer, const size_t buffer_size) {
    fwrite (buffer, sizeof (uint8_t), buffer_size, stream_);
}

}