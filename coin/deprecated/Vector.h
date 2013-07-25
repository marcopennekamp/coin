#ifndef COIN_MATH_VECTOR_H_
#define COIN_MATH_VECTOR_H_

#include <stdarg.h>
#include <math.h>

#include <coin/coin.h>


namespace coin {

template <int v_size, typename T = float>
class Vector {
    static_assert (v_size > 1, "Error: Vector size must be greater than 1!");

  private:
    T data [v_size];

    typedef Vector<v_size, T> BASE;

  public:
    Vector () {
        for (int i = 0; i < v_size; i++) {
            (*this)[i] = 0;
        }
    }

    Vector (T a, ...) {
        va_list arguments;   
        va_start (arguments, a);
        (*this)[0] = a;
        for (int i = 1; i < v_size; i++) {
            (*this)[i] = va_arg (arguments, T);
        }
        va_end (arguments);
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

    inline const T x () const {
        return (*this)[0];
    }


    inline T& y () {
        return (*this)[1];
    }

    inline const T y () const {
        return (*this)[1];
    }


    inline T& z () {
        static_assert (v_size > 2, "Error: To use z (), the vector size must be at least 3!");
        return (*this)[2];
    }

    inline const T z () const {
        static_assert (v_size > 2, "Error: To use z (), the vector size must be at least 3!");
        return (*this)[2];
    }


    inline T& w () {
        static_assert (v_size > 3, "Error: To use w (), the vector size must be at least 4!");
        return (*this)[3];
    }

    inline const T w () const {
        static_assert (v_size > 3, "Error: To use w (), the vector size must be at least 4!");
        return (*this)[3];
    }


    /* Dot product. */
    inline BASE dot (const BASE& with) const {
        T product = 0;
        for (int i = 0; i < v_size; i++) {
            product += this[i] * with[i];
        }
        return product;
    }

    /* Normal vector. */
    inline BASE normal () const {
        T len = length ();
        BASE out;
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
        BASE out;
        for (int i = 0; i < v_size; i++) {
            out[i] = lhs[i] + rhs[i];
        }
        return out;
    }

    /* Subtract. */
    inline friend BASE operator- (const BASE& lhs, const BASE& rhs) {
        BASE out;
        for (int i = 0; i < v_size; i++) {
            out[i] = lhs[i] - rhs[i];
        }
        return out;
    }

    /* Multiply with scalar. */
    template <typename ST>
    inline friend BASE operator* (const BASE& lhs, const ST scalar) {
        BASE out;
        for (int i = 0; i < v_size; i++) {
            out[i] = lhs[i] * scalar;
        }
        return out;
    }


    inline friend bool operator== (const BASE& lhs, const BASE& rhs) {
        for (size_t i = 0; i < v_size; ++i) {
            if (lhs[i] != rhs[i]) return false;
        }
        return true;
    }
    
};

}

#endif  /* COIN_MATH_VECTOR_H_ */
