#ifndef COIN_MATH_VECTOR2_H_
#define COIN_MATH_VECTOR2_H_

#include <stdarg.h>
#include <math.h>

#include <coin/coin.h>


namespace coin {

template <int v_size, typename T = float>
class COIN_DECL Vector {
    static_assert (v_size > 1, "Error: Vector size must be greater than 1!");

  private:
    T data [v_size];

    typedef Vector<v_size, T> BASE;

  public:
    inline Vector (bool clear = true) {
        if (clear) {
            for (int i = 0; i < v_size; i++) {
                (*this)[i] = (T) 0;
            }
        }
    }

    inline Vector (va_list arguments) {
        for (int i = 0; i < v_size; i++) {
            (*this)[i] = va_arg (arguments, T);
        }
    }

    inline T& operator[] (const int i) {
        return data[i];
    }

    inline const T operator[] (const int i) const {
        return data[i];
    }

    inline T& x () {
        return (*this)[0];
    }

    inline T& y () {
        return (*this)[1];
    }

    inline T& z () {
        static_assert (v_size > 2, "Error: To use z (), the vector size must be at least 3!");
        return (*this)[2];
    }

    inline T& w () {
        static_assert (v_size > 3, "Error: To use w (), the vector size must be at least 4!");
        return (*this)[3];
    }


    /* Dot product. */
    inline BASE dot (const BASE& with) {
        T product = 0;
        for (int i = 0; i < v_size; i++) {
            product += this[i] * with[i];
        }
        return product;
    }

    /* Normal vector. */
    inline BASE normal () {
        T len = length ();
        BASE out (false);
        if (len > 0) {
            out = (*this) * (((T) 1) / len);
        }
        return out;
    }

    inline T length () const {
        T sum = 0;
        for (int i = 0; i < v_size; i++) {
            sum += this[i] * this[i];
        }
        return sqrt ((double) sum);
    }

    /* Add. */
    inline friend BASE operator+ (const BASE& lhs, const BASE& rhs) {
        BASE out (false);
        for (int i = 0; i < v_size; i++) {
            out[i] = lhs[i] + rhs[i];
        }
        return out;
    }

    /* Subtract. */
    inline friend BASE operator- (const BASE& lhs, const BASE& rhs) {
        BASE out (false);
        for (int i = 0; i < v_size; i++) {
            out[i] = lhs[i] - rhs[i];
        }
        return out;
    }

    /* Multiply with scalar. */
    template <typename ST>
    inline friend BASE operator* (const BASE& lhs, const ST scalar) {
        BASE out (false);
        for (int i = 0; i < v_size; i++) {
            out[i] = lhs[i] * scalar;
        }
        return out;
    }
    
};

}

#endif  /* COIN_MATH_VECTOR2_H_ */
