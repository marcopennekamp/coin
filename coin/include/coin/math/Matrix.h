#ifndef COIN_MATH_MATRIX4_H_
#define COIN_MATH_MATRIX4_H_

#include <coin/coin.h>


namespace coin {

/* TODO(Marco): template matrix implementation. */


class COIN_EXPORT Matrix4 {
  private:
    float data_ [16];

  public:
    void Set (
        const float _00, const float _01, const float _02, const float _03,
        const float _10, const float _11, const float _12, const float _13,
        const float _20, const float _21, const float _22, const float _23,
        const float _30, const float _31, const float _32, const float _33
    );
    void Set (const float* new_data);

    void Identity ();
    void Multiply (const Matrix4& with, Matrix4& result) const;
    bool Inverse ();

    void CreateTranslationMatrix (const float x, const float y, const float z);
    void CreateScalationMatrix (const float x, const float y, const float z);
    void CreateRotationXMatrix (const float radians);
    void CreateRotationYMatrix (const float radians);
    void CreateRotationZMatrix (const float radians);

    void Ortho (const float left, const float right, const float bottom, const float top, const float near, const float far);
    void Perspective (const float aov, const float aspect, const float near, const float far);

    void Print () const;

    inline float* data () { return data_; }
    inline const float* data () const { return data_; }
};

}

#endif  /* COIN_MATH_MATRIX4_H_ */
