#ifndef COIN_GL_TEXTURE_H_
#define COIN_GL_TEXTURE_H_

#include <functional>

#include <coin/coin.h>
#include <coin/gl.h>
#include <coin/image/Image.h>


namespace coin {

class COIN_DECL Texture {
public:
    typedef void (*Setup) (Texture*);

private:
    GLuint handle_;
    Size width_;
    Size height_;

    Setup setup_;

    void Init (const GLuint width, const GLuint height, Setup setup);
    void Init (const Image& image, Setup setup);
    void CreateHandle ();

public:
    static void StandardSetup (Texture* texture);

    /*
     * Allocates the texture.
     */
    Texture (const GLuint width, const GLuint height);
    Texture (const GLuint width, const GLuint height, Setup setup);

    /* 
     * Uses the image to construct the texture with 'SetImage'.
     */
    Texture (const Image& image);
    Texture (const Image& image, Setup setup);

    ~Texture ();



    void AllocateTexture ();
    void AllocateTexture (const void* data);

    /* 
     * Allocates the Texture.
     */
    void SetImage (const Image& image);

    /*
     * Binds the texture to the texture unit 'location'.
     */
    void Bind (const GLuint location);
    
    inline Setup setup () const { return setup_; }
    inline void setup (Setup setup) { setup_ = setup; }

    inline GLuint handle () const { return handle_; }
    inline Size width () const { return width_; }
    inline Size height () const { return height_; }
};

}

#endif  /* COIN_GL_TEXTURE_H_ */
