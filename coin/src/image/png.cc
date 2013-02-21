#include <png.h>
#include <zlib/zlib.h>

#include <coin/image/png.h>
#include <coin/image/Image.h>
#include <coin/utils/Stream.h>


namespace coin {

namespace {

/* Custom I/O functions. */

void pngCallbackRead (png_structp png, png_bytep buffer, png_size_t length) {
    Stream* stream = (Stream*) png_get_io_ptr (png);
    stream->Read (buffer, (Size) length);
}

void pngCallbackWrite (png_structp png, png_bytep buffer, png_size_t length) {
    Stream* stream = (Stream*) png_get_io_ptr (png);
    stream->Write (buffer, (Size) length);
}

void pngCallbackFlush (png_structp png) {
    Stream* stream = (Stream*) png_get_io_ptr (png);
    stream->Flush ();
}

}


/* Note: Most of the code in PngLoad and PngSave is duplicated,
 * but can not necessarily be merged into a function, using macros could
 * quickly get quite a mess.
 * I may look into it later.
 */


bool PngLoad (Stream& stream, Image& image) {
    /* Check if stream is READ stream. */
    if (stream.mode () != StreamMode::read) {
        printf ("Supplied stream is not a read stream.\n");
        return false;
    }

    /* Check if stream is valid PNG. */
    {
        u8 header [8];
        stream.Read (header, 8);
        if (png_sig_cmp (header, 0, 8)) { /* NOT PNG. */
            printf ("Supplied stream does not represent a PNG image.\n");
            return false;
        }
    }

    /* Set up PNG. */
    png_structp png = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png == NULL) {
        printf ("PNG could not be created.\n");
        return false;
    }

    png_infop png_info = png_create_info_struct (png);
    if (png_info == NULL) {
        png_destroy_read_struct (&png, NULL, NULL);
        printf ("PNG info could not be created.\n");
        return false;
    }

    png_set_sig_bytes (png, 8);
    png_set_read_fn (png, &stream, &pngCallbackRead);

    png_read_info (png, png_info);

    png_byte color_type = png_get_color_type (png, png_info);

    /* Error when image is neither RGBA nor RGB. */
    if (color_type != PNG_COLOR_TYPE_RGBA && color_type != PNG_COLOR_TYPE_RGB) {
        png_destroy_read_struct (&png, &png_info, NULL);
        printf ("PNG image is neither in RGB nor RGBA format. Can't process.\n");
        return false;
    }

    /* Create image. */
    image.Create (png_get_image_width (png, png_info), png_get_image_height (png, png_info));

    /* Transform RGB to RGBA image. */
    if (color_type == PNG_COLOR_TYPE_RGB) {
        printf ("PNG type is RGB. Adding alpha channel.\n");
        png_set_add_alpha(png, 0xFF, PNG_FILLER_AFTER);
        png_read_update_info (png, png_info);
    }

    /* Create fallback routine. */
    if (setjmp (png_jmpbuf (png))) {
        image.Free ();
        png_destroy_read_struct (&png, &png_info, NULL);
        printf ("Error during PNG reading!\n");
        return false;
    }

    /* Read the actual image. */
    png_bytep target = (png_bytep) image.data ();
    u32 target_offset = 0;
    for (u32 i = 0; i < image.height (); ++i) {
        png_read_row (png, (png_bytep) (target + target_offset), NULL);
        target_offset += (u32) png_get_rowbytes (png, png_info);
    }

    /* Cleanup. */
    png_read_end (png, NULL);
    png_destroy_read_struct (&png, &png_info, NULL);

    return true;
}


bool PngSave (Stream& stream, Image& image, const bool flipped) {
     /* Check if stream is WRITE stream. */
    if (stream.mode () != StreamMode::write) {
        printf ("Supplied stream is not a write stream.\n");
        return false;
    }

    /* Set up PNG. */
    png_structp png = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png == NULL) {
        printf ("PNG could not be created.\n");
        return false;
    }

    png_infop png_info = png_create_info_struct (png);
    if (png_info == NULL) {
        png_destroy_write_struct (&png, NULL);
        printf ("PNG info could not be created.\n");
        return false;
    }

    /* Fallback routine. */
    if (setjmp (png_jmpbuf (png))) {
        printf ("Error during PNG writing.\n");
        png_destroy_write_struct (&png, &png_info);
        return false;
    }

    /* Set and write info. */
    png_set_IHDR (png, png_info,
            image.width (), image.height (), 8,
            PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_set_write_fn (png, &stream, &pngCallbackWrite, &pngCallbackFlush);
    png_set_compression_level (png, Z_BEST_COMPRESSION);

    png_write_info (png, png_info);

    /* Write image. */
    png_bytep target = (png_bytep) image.data ();
    s32 target_offset = 0;
    s32 direction = 1;
    if (flipped) {
        target_offset = image.width () * (image.height () - 1) * sizeof (u32);
        direction = -1;
    }

    for (u32 i = 0; i < image.height (); ++i) {
        png_write_row (png, (png_bytep) (target + target_offset));
        target_offset += ((s32) image.width () * sizeof (u32)) * direction;
    }

    /* Cleanup. */
    png_write_end (png, NULL);
    png_destroy_write_struct (&png, &png_info);

    return true;
}

}
