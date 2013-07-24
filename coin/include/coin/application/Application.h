#ifndef COIN_APPLICATION_APPLICATION_H_
#define COIN_APPLICATION_APPLICATION_H_

#include <coin/coin.h>
#include <coin/application/CommonStateInterface.h>


namespace coin {

class State;

class COIN_EXPORT Application : public CommonStateInterface {
  public:
    Application () { }
    virtual ~Application () { }

    virtual State& GetState () = 0;
    virtual void InitGl () { }
    virtual void Resize (const Size width, const Size height) { }
    virtual void Destroy () { }
};

}

#endif  /* COIN_APPLICATION_APPLICATION_H_ */
