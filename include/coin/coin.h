#ifndef COIN_H_
#define COIN_H_

#include <stdint.h>


#ifdef COIN_EXPORT_DLL
#define COIN_EXPORT __declspec (dllexport)
#else
#define COIN_EXPORT __declspec (dllimport)
#endif

#ifdef COIN_UTILS_EXPORT_DLL
#define COIN_UTILS_EXPORT __declspec (dllexport)
#else
#define COIN_UTILS_EXPORT __declspec (dllimport)
#endif


namespace coin {

class Application;

typedef uint32_t    Size;
typedef uint32_t    Position;
typedef int32_t     RelativePosition;
typedef int32_t     Key;
typedef int32_t     MouseButton;

COIN_EXPORT void Start (Application* application, const Size window_width, const Size window_height, const bool fullscreen, const bool vsync);
COIN_EXPORT void Stop ();

}

#endif
