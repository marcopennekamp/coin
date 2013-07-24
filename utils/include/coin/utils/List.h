#ifndef COIN_UTILS_LIST_H_
#define COIN_UTILS_LIST_H_

#include <stdlib.h>
#include <algorithm>


namespace coin {

template<typename T>
class List {
private:
    T* data_;
    size_t iterator_;
    size_t size_;

    void CheckAllocationError () {
        if (data_ == NULL) {
            exit (1);
        }
    }

public:
    List (size_t initial_size = 8) {
        size_ = initial_size;
        data_ = (T*) malloc (size_ * sizeof (T));
        CheckAllocationError ();
        ResetIterator ();
    }

    ~List () {
        free (data_);
    }

    void Resize (size_t new_size) {
        const float kResizeTreshold = 0.2f;

        /* Resize by at least 20%. */
        bool resize = false;
        if (new_size > size_) {
            new_size = std::max (new_size, size_ + (size_t) (size_ * kResizeTreshold));
            resize = true;
        }else if (new_size < size_) {
            resize = true;
        }
        
        if (resize) {
            size_ = new_size;
            void* new_data = realloc (data_, size_ * sizeof (T));
            data_ = (T*) new_data;
            CheckAllocationError ();
        }
    }

    inline T& operator[] (size_t index) {
        return data_[index];
    }

    inline const T& operator[] (size_t index) const {
        return data_[index];
    }

    inline T& Next () {
        T& next = data_[iterator_];
        ++iterator_;
        return next;
    }

    inline T& NextChecked () {
        if (iterator_ >= size_) {
            Resize (iterator_ + 1);
        }
        return Next ();
    }

    inline T& Previous () {
        --iterator_;
        return data_[iterator_];;
    }

    inline void ResetIterator () {
        iterator_ = 0;
    }
    
    inline T* data () { return data_; }
    inline const T* data () const { return data_; }
    inline size_t iterator () const { return iterator_; }
    inline size_t size () const { return size_; }
};

}


#endif  /* COIN_UTILS_LIST_H_ */