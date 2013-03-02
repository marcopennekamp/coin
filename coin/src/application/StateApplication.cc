#include <stdlib.h>

#include <coin/gl.h>
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

void StateApplication::InitState () {
    if (init_state_) {
        state_->Init ();
        if (state_->GrabMouse ()) {
            SDL_SetWindowGrab (GetWindow (), SDL_TRUE);
            SDL_SetRelativeMouseMode (SDL_TRUE);
            SDL_ShowCursor (SDL_FALSE);
        }
        init_state_ = false;
    }
}

}



