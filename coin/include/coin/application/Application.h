#ifndef COIN_APPLICATION_APPLICATION_H_
#define COIN_APPLICATION_APPLICATION_H_

#include <coin/coin.h>
#include <coin/application/CommonStateInterface.h>
#include <coin/application/ScreenConfig.h>


namespace coin {

class State;

class COIN_EXPORT Application : public CommonStateInterface {
private:
    ScreenConfig screen_config_;

public:
    Application () { }
    virtual ~Application () { }

    virtual State& GetState () = 0;
    virtual void InitGl () { }
    virtual void Resize (const Size width, const Size height);
    virtual void Destroy () { }

    inline const ScreenConfig& screen_config () { return screen_config_; }
};

}

#endif  /* COIN_APPLICATION_APPLICATION_H_ */
