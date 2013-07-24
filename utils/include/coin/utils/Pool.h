#ifndef COIN_UTILS_POOL_H_
#define COIN_UTILS_POOL_H_

#include <coin/coin.h>
#include <coin/utils/List.h>


namespace coin {

template<typename T> 
class Pool {
private:
    List<T*> stack_;

public:
    Pool () {

    }

    virtual ~Pool () {
        
    }

    void Free () {
        while (stack_.iterator () > 0) {
            DeleteElement (stack_.Previous ());
        }
    }

    T* Get () {
        if (stack_.iterator () == 0) {
            return CreateElement ();
        }
        return stack_.Previous ();
    }

    void Add (T* element) {
        stack_.NextChecked () = element;
    }

    virtual T* CreateElement () = 0;
    virtual void DeleteElement (T* element) = 0;
};

}


#endif  /* COIN_UTILS_POOL_H_ */