#include <math.h>
#include <string.h>

#include <coin/math/Matrix.h>

#include <iostream>

#include "SDL2/SDL_stdinc.h"


using namespace std;

namespace coin {

void Matrix4::Set (
        float _00, float _01, float _02, float _03,
        float _10, float _11, float _12, float _13,
        float _20, float _21, float _22, float _23,
        float _30, float _31, float _32, float _33
) {
    data_[0]    = _00;
    data_[5]    = _11;
    data_[10]   = _22;
    data_[15]   = _33;

    data_[1]    = _10;
    data_[2]    = _20;
    data_[3]    = _30;

    data_[4]    = _01;
    data_[6]    = _21;
    data_[7]    = _31;

    data_[8]    = _02;
    data_[9]    = _12;
    data_[11]   = _32;

    data_[12]   = _03;
    data_[13]   = _13;
    data_[14]   = _23;
}

void Matrix4::Set (float* matrix) {
    memcpy (&data_, matrix, sizeof (data_));
}

void Matrix4::Identity () {
    data_[0]    = 1.0f;
    data_[5]    = 1.0f;
    data_[10]   = 1.0f;
    data_[15]   = 1.0f;

    data_[1]    = 0.0f;
    data_[2]    = 0.0f;
    data_[3]    = 0.0f;
    data_[4]    = 0.0f;
    data_[6]    = 0.0f;
    data_[7]    = 0.0f;
    data_[8]    = 0.0f;
    data_[9]    = 0.0f;
    data_[11]   = 0.0f;
    data_[12]   = 0.0f;
    data_[13]   = 0.0f;
    data_[14]   = 0.0f;
}

void Matrix4::Multiply (Matrix4& withm, Matrix4& resultm) {
    float* with = withm.data ();
    float* result = resultm.data ();

    /* First Column. */
    result[0] = data_[0]*with[0] + data_[4]*with[1] + data_[8]*with[2] + data_[12]*with[3];
    result[1] = data_[1]*with[0] + data_[5]*with[1] + data_[9]*with[2] + data_[13]*with[3];
    result[2] = data_[2]*with[0] + data_[6]*with[1] + data_[10]*with[2] + data_[14]*with[3];
    result[3] = data_[3]*with[0] + data_[7]*with[1] + data_[11]*with[2] + data_[15]*with[3];

    /* Second Column. */
    result[4] = data_[0]*with[4] + data_[4]*with[5] + data_[8]*with[6] + data_[12]*with[7];
    result[5] = data_[1]*with[4] + data_[5]*with[5] + data_[9]*with[6] + data_[13]*with[7];
    result[6] = data_[2]*with[4] + data_[6]*with[5] + data_[10]*with[6] + data_[14]*with[7];
    result[7] = data_[3]*with[4] + data_[7]*with[5] + data_[11]*with[6] + data_[15]*with[7];

    /* Third Column. */
    result[8] = data_[0]*with[8] + data_[4]*with[9] + data_[8]*with[10] + data_[12]*with[11];
    result[9] = data_[1]*with[8] + data_[5]*with[9] + data_[9]*with[10] + data_[13]*with[11];
    result[10] = data_[2]*with[8] + data_[6]*with[9] + data_[10]*with[10] + data_[14]*with[11];
    result[11] = data_[3]*with[8] + data_[7]*with[9] + data_[11]*with[10] + data_[15]*with[11];

    /* Fourth Column. */
    result[12] = data_[0]*with[12] + data_[4]*with[13] + data_[8]*with[14] + data_[12]*with[15];
    result[13] = data_[1]*with[12] + data_[5]*with[13] + data_[9]*with[14] + data_[13]*with[15];
    result[14] = data_[2]*with[12] + data_[6]*with[13] + data_[10]*with[14] + data_[14]*with[15];
    result[15] = data_[3]*with[12] + data_[7]*with[13] + data_[11]*with[14] + data_[15]*with[15];
}

bool Matrix4::Inverse () {
    float l_det =
        data_[3] * data_[6] * data_[9] * data_[12] -
        data_[2] * data_[7] * data_[9] * data_[12] -
        data_[3] * data_[5] * data_[10] * data_[12] +
        data_[1] * data_[7] * data_[10] * data_[12] +
        data_[2] * data_[5] * data_[11] * data_[12] -
        data_[1] * data_[6] * data_[11] * data_[12] -
        data_[3] * data_[6] * data_[8] * data_[13] +
        data_[2] * data_[7] * data_[8] * data_[13] +
        data_[3] * data_[4] * data_[10] * data_[13] -
        data_[0] * data_[7] * data_[10] * data_[13] -
        data_[2] * data_[4] * data_[11] * data_[13] +
        data_[0] * data_[6] * data_[11] * data_[13] +
        data_[3] * data_[5] * data_[8] * data_[14] -
        data_[1] * data_[7] * data_[8] * data_[14] -
        data_[3] * data_[4] * data_[9] * data_[14] +
        data_[0] * data_[7] * data_[9] * data_[14] +
        data_[1] * data_[4] * data_[11] * data_[14] -
        data_[0] * data_[5] * data_[11] * data_[14] -
        data_[2] * data_[5] * data_[8] * data_[15] +
        data_[1] * data_[6] * data_[8] * data_[15] +
        data_[2] * data_[4] * data_[9] * data_[15] -
        data_[0] * data_[6] * data_[9] * data_[15] -
        data_[1] * data_[4] * data_[10] * data_[15] +
        data_[0] * data_[5] * data_[10] * data_[15];

    if (l_det == 0.0f) {
        return false;
    }


    float inv_det = 1.0f / l_det;

    float tmp [16];

    tmp[0] =
        data_[9] * data_[14] * data_[7] -
        data_[13] * data_[10] * data_[7] +
        data_[13] * data_[6] * data_[11] -
        data_[5] * data_[14] * data_[11] -
        data_[9] * data_[6] * data_[15] +
        data_[5] * data_[10] * data_[15];

    tmp[4] =
        data_[12] * data_[10] * data_[7] -
        data_[8] * data_[14] * data_[7] -
        data_[12] * data_[6] * data_[11] +
        data_[4] * data_[14] * data_[11] +
        data_[8] * data_[6] * data_[15] -
        data_[4] * data_[10] * data_[15];

    tmp[8] =
        data_[8] * data_[13] * data_[7] -
        data_[12] * data_[9] * data_[7] +
        data_[12] * data_[5] * data_[11] -
        data_[4] * data_[13] * data_[11] -
        data_[8] * data_[5] * data_[15] +
        data_[4] * data_[9] * data_[15];

    tmp[12] =
        data_[12] * data_[9] * data_[6] -
        data_[8] * data_[13] * data_[6] -
        data_[12] * data_[5] * data_[10] +
        data_[4] * data_[13] * data_[10] +
        data_[8] * data_[5] * data_[14] -
        data_[4] * data_[9] * data_[14];

    tmp[1] =
        data_[13] * data_[10] * data_[3] -
        data_[9] * data_[14] * data_[3] -
        data_[13] * data_[2] * data_[11] +
        data_[1] * data_[14] * data_[11] +
        data_[9] * data_[2] * data_[15] -
        data_[1] * data_[10] * data_[15];

    tmp[5] =
        data_[8] * data_[14] * data_[3] -
        data_[12] * data_[10] * data_[3] +
        data_[12] * data_[2] * data_[11] -
        data_[0] * data_[14] * data_[11] -
        data_[8] * data_[2] * data_[15] +
        data_[0] * data_[10] * data_[15];

    tmp[9] =
        data_[12] * data_[9] * data_[3] -
        data_[8] * data_[13] * data_[3] -
        data_[12] * data_[1] * data_[11] +
        data_[0] * data_[13] * data_[11] +
        data_[8] * data_[1] * data_[15] -
        data_[0] * data_[9] * data_[15];

    tmp[13] =
        data_[8] * data_[13] * data_[2] -
        data_[12] * data_[9] * data_[2] +
        data_[12] * data_[1] * data_[10] -
        data_[0] * data_[13] * data_[10] -
        data_[8] * data_[1] * data_[14] +
        data_[0] * data_[9] * data_[14];

    tmp[2] =
        data_[5] * data_[14] * data_[3] -
        data_[13] * data_[6] * data_[3] +
        data_[13] * data_[2] * data_[7] -
        data_[1] * data_[14] * data_[7] -
        data_[5] * data_[2] * data_[15] +
        data_[1] * data_[6] * data_[15];

    tmp[6] =
        data_[12] * data_[6] * data_[3] -
        data_[4] * data_[14] * data_[3] -
        data_[12] * data_[2] * data_[7] +
        data_[0] * data_[14] * data_[7] +
        data_[4] * data_[2] * data_[15] -
        data_[0] * data_[6] * data_[15];

    tmp[10] =
        data_[4] * data_[13] * data_[3] -
        data_[12] * data_[5] * data_[3] +
        data_[12] * data_[1] * data_[7] -
        data_[0] * data_[13] * data_[7] -
        data_[4] * data_[1] * data_[15] +
        data_[0] * data_[5] * data_[15];

    tmp[14] =
        data_[12] * data_[5] * data_[2] -
        data_[4] * data_[13] * data_[2] -
        data_[12] * data_[1] * data_[6] +
        data_[0] * data_[13] * data_[6] +
        data_[4] * data_[1] * data_[14] -
        data_[0] * data_[5] * data_[14];

    tmp[3] =
        data_[9] * data_[6] * data_[3] -
        data_[5] * data_[10] * data_[3] -
        data_[9] * data_[2] * data_[7] +
        data_[1] * data_[10] * data_[7] +
        data_[5] * data_[2] * data_[11] -
        data_[1] * data_[6] * data_[11];

    tmp[7] =
        data_[4] * data_[10] * data_[3] -
        data_[8] * data_[6] * data_[3] +
        data_[8] * data_[2] * data_[7] -
        data_[0] * data_[10] * data_[7] -
        data_[4] * data_[2] * data_[11] +
        data_[0] * data_[6] * data_[11];

    tmp[11] =
        data_[8] * data_[5] * data_[3] -
        data_[4] * data_[9] * data_[3] -
        data_[8] * data_[1] * data_[7] +
        data_[0] * data_[9] * data_[7] +
        data_[4] * data_[1] * data_[11] -
        data_[0] * data_[5] * data_[11];

    tmp[15] =
        data_[4] * data_[9] * data_[2] -
        data_[8] * data_[5] * data_[2] +
        data_[8] * data_[1] * data_[6] -
        data_[0]  * data_[9] * data_[6] -
        data_[4] * data_[1] * data_[10] +
        data_[0] * data_[5] * data_[10];


    data_[0] = tmp[0] * inv_det;
    data_[4] = tmp[4] * inv_det;
    data_[8] = tmp[8] * inv_det;
    data_[12] = tmp[12] * inv_det;

    data_[1] = tmp[1] * inv_det;
    data_[5] = tmp[5] * inv_det;
    data_[9] = tmp[9] * inv_det;
    data_[13] = tmp[13] * inv_det;

    data_[2] = tmp[2] * inv_det;
    data_[6] = tmp[6] * inv_det;
    data_[10] = tmp[10] * inv_det;
    data_[14] = tmp[14] * inv_det;

    data_[3] = tmp[3] * inv_det;
    data_[7] = tmp[7] * inv_det;
    data_[11] = tmp[11] * inv_det;
    data_[15] = tmp[15] * inv_det;

    return true;
}


void Matrix4::CreateTranslationMatrix (float x, float y, float z) {
    Identity ();
    data_[12] = x;
    data_[13] = y;
    data_[14] = z;
}

void Matrix4::CreateScalationMatrix (float x, float y, float z) {
    Identity ();
    data_[0] = x;
    data_[5] = y;
    data_[10] = z;
}

void Matrix4::CreateRotationXMatrix (float radians) {
    Identity ();
    float c = cosf (radians);
    float s = sinf (radians);
    data_[5] = c;
    data_[6] = -s;
    data_[9] = s;
    data_[10] = c;
}

void Matrix4::CreateRotationYMatrix (float radians) {
    Identity ();
    float c = cosf (radians);
    float s = sinf (radians);
    data_[0] = c;
    data_[2] = s;
    data_[8] = -s;
    data_[10] = c;
}

void Matrix4::CreateRotationZMatrix (float radians) {
    Identity ();
    float c = cosf (radians);
    float s = sinf (radians);
    data_[0] = c;
    data_[1] = s;
    data_[4] = -s;
    data_[5] = c;
}


void Matrix4::Ortho (float left, float right, float bottom, float top, float near, float far) {
    float width = right - left;
    float height = top - bottom;
    float fn = far - near;

    Set (
        2 / width,  0.0f,           0.0f,       0.0f,
        0.0f,       2.0f / height,  0.0f,       0.0f,
        0.0f,       0.0f,           1.0f / fn,  -near / fn,
        0.0f,       0.0f,           0.0f,       1.0f
    );
}


void Matrix4::Perspective (float aov, float aspect, float near, float far) {
    float xymax = near * tanf (aov * (float) M_PI / 180.0f / 2.0f);
    float ymin = -xymax;
    float xmin = -xymax;

    float width = xymax - xmin;
    float height = xymax - ymin;

    float depth = far - near;
    float q = -(far + near) / depth;
    float qn = -2 * (far * near) / depth;

    float w = 2 * near / width;
    w = w / aspect;
    float h = 2 * near / height;

    Set (
        w,     0.0f,  0.0f,   0.0f,
        0.0f,  h,     0.0f,   0.0f,
        0.0f,  0.0f,  q,      qn,
        0.0f,  0.0f,  -1.0f,  1.0f
    );

}


void Matrix4::Print () {
    // TODO(Marco): Change to fleeLog ...
    cout << data_[0] << "\t\t" << data_[4] << "\t\t" << data_[8] << "\t\t" << data_[12] << endl;
    cout << data_[1] << "\t\t" << data_[5] << "\t\t" << data_[9] << "\t\t" << data_[13] << endl;
    cout << data_[2] << "\t\t" << data_[6] << "\t\t" << data_[10] << "\t\t" << data_[14] << endl;
    cout << data_[3] << "\t\t" << data_[7] << "\t\t" << data_[11] << "\t\t" << data_[15] << endl;
}


}
