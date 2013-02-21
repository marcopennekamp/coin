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
    virtual void MouseDown (const MouseButton b, const Position x, const Position y) { }
    virtual void MouseMoved (const RelativePosition x, const RelativePosition y) { }
    virtual void MouseUp (const MouseButton b, const Position x, const Position y) { }
    virtual void MouseWheelScrolled (const RelativePosition scroll) { }
    virtual void KeyDown (const Key key) { }
    virtual void KeyUp (const Key key) { }
};

}

#endif  /* COIN_APPLICATION_COMMONSTATEINTERFACE_H_ */
