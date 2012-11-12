#include <stdlib.h>

#include <coin/application/State.h>
#include <coin/application/StateApplication.h>


namespace coin {

StateApplication::StateApplication () : Application () {
    state_ = NULL;
    init_state_ = false;
}

StateApplication::~StateApplication ()  {
    delete state_;
}

State& StateApplication::GetState () {
    return *state_;
}

void StateApplication::ChangeState (State* state) {
    if (state_ != NULL) {
        delete state_; // Destructor finalizes State
    }
    state_ = state;
    init_state_ = true;
}

void StateApplication::Render () {
    if (init_state_) {
        state_->Init ();
        init_state_ = false;
    }
}

}



