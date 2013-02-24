#ifndef COIN_RESOURCE_ELEMENT_H_
#define COIN_RESOURCE_ELEMENT_H_

#include <string>


namespace coin {

class Element {
public:
    /* returns whether loading the element was successful. */
    virtual bool Load (const std::string& path) = 0;
};

}


#endif  /* COIN_RESOURCE_ELEMENT_H_ */