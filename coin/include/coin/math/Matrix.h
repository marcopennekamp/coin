#ifndef COIN_MATH_MATRIX4_H_
#define COIN_MATH_MATRIX4_H_

#include <coin/coin.h>


namespace coin {

/* TODO(Marco): template matrix implementation. */


class COIN_DECL Matrix4 {
  private:
    float data_ [16];

  public:
    void Set (
        float _00, float _01, float _02, float _03,
        float _10, float _11, float _12, float _13,
        float _20, float _21, float _22, float _23,
        float _30, float _31, float _32, float _33
    );
    void Set (float*);

    void Identity ();
    void Multiply (Matrix4& with, Matrix4& result);
    bool Inverse ();

    void CreateTranslationMatrix (float x, float y, float z);
    void CreateScalationMatrix (float x, float y, float z);
    void CreateRotationXMatrix (float radians);
    void CreateRotationYMatrix (float radians);
    void CreateRotationZMatrix (float radians);

    void Ortho (float left, float right, float bottom, float top, float near, float far);
    void Perspective (float aov, float aspect, float near, float far);

    void Print ();

    inline float* data () { return data_; }
};

}

#endif  /* COIN_MATH_MATRIX4_H_ */
