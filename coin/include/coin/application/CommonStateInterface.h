#ifndef COIN_APPLICATION_COMMONSTATEINTERFACE_H_
#define COIN_APPLICATION_COMMONSTATEINTERFACE_H_

#include <coin/coin.h>


namespace coin {

class COIN_DECL CommonStateInterface {
  public:
    CommonStateInterface () { }
    virtual ~CommonStateInterface () { }

    virtual void Update () { }
    virtual void Render () { }
    virtual void OnPause () { }
    virtual void OnResume () { }
    virtual void MouseDown (MouseButton b, Position x, Position y) { }
    virtual void MouseMoved (RelativePosition x, RelativePosition y) { }
    virtual void MouseUp (MouseButton b, Position x, Position y) { }
    virtual void KeyDown (Key key) { }
    virtual void KeyUp (Key key) { }
};

}

#endif  /* COIN_APPLICATION_COMMONSTATEINTERFACE_H_ */
