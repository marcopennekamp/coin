#ifndef COIN_APPLICATION_STATEAPPLICATION_H_
#define COIN_APPLICATION_STATEAPPLICATION_H_

#include <coin/coin.h>
#include <coin/application/Application.h>


namespace coin {

class State;

class COIN_DECL StateApplication : public Application {
  private:
    State* state_;
    bool init_state_;

  public:
    StateApplication ();
    virtual ~StateApplication ();

    State& GetState ();
    void ChangeState (State* state);

    void InitState (); /* Note: State changes only in main (i.e. render) thread! */
};

}

#endif  /* COIN_APPLICATION_STATEAPPLICATION_H_ */
