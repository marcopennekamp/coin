#ifndef COIN_UTILS_ARRAY_H_
#define	COIN_UTILS_ARRAY_H_

#include <stdlib.h>
#include <string.h>

#include <coin/coin.h>


namespace coin {

template<typename T, typename SIZE_T = size_t>
class Array {
  private:
    T* array_;
    SIZE_T size_;

  public:
    inline Array () { 
        array_ = NULL;
        size_ = 0;
    }

    inline explicit Array (const SIZE_T size) {
        Create (size);
    }

    inline ~Array () {
        Delete ();
    }

    inline void Create (const SIZE_T size) {
        array_ = new T[size];
        size_ = size;
    }

    inline void Delete () {
        if (array_ != NULL) {
            delete[] array_;
        }
    }

    inline void Set (const T value) {
        for (SIZE_T i = 0; i < size_; ++i) {
            this[i] = value;
        }
    }

    inline void SetMemory (const u8 value) {
        memset (array_, value, size_ * sizeof (T));
    }

    inline T& operator[] (const SIZE_T index) const {
        return array_[index];
    }

    inline T* array () {
        return array_;
    }

    inline const SIZE_T size () const {
        return size_;
    }
};

}


#endif  /* COIN_UTILS_ARRAY_H_ */