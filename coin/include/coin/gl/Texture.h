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

    void Init (GLuint width, GLuint height, Setup setup);
    void Init (Image& image, Setup setup);
    void CreateHandle ();

public:
    static void StandardSetup (Texture* texture);

    /*
     * Allocates the texture.
     */
    Texture (GLuint width, GLuint height);
    Texture (GLuint width, GLuint height, Setup setup);

    /* 
     * Uses the image to construct the texture with 'SetImage'.
     */
    Texture (Image& image);
    Texture (Image& image, Setup setup);

    ~Texture ();



    void AllocateTexture ();
    void AllocateTexture (void* data);

    /* 
     * Allocates the Texture.
     */
    void SetImage (Image& image);

    /*
     * Binds the texture to the texture unit 'location'.
     */
    void Bind (GLuint uniform, GLuint location = 0);
    
    inline Setup setup () { return setup_; }
    inline void setup (Setup setup) { setup_ = setup; }

    inline GLuint handle () { return handle_; }
    inline Size width () { return width_; }
    inline Size height () { return height_; }
};

}

#endif  /* COIN_GL_TEXTURE_H_ */
