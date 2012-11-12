#ifndef COIN_APPLICATION_STATE_H_
#define COIN_APPLICATION_STATE_H_

#include <coin/coin.h>
#include <coin/application/CommonStateInterface.h>


namespace coin {

class COIN_DECL State : public CommonStateInterface {
  public:
    State () { }
    virtual ~State () { }
    virtual void Init () { }
};

}

#endif  /* COIN_APPLICATION_STATE_H_ */
