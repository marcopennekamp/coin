#ifndef COIN_H_
#define COIN_H_

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


typedef char                    s8;
typedef unsigned char           u8;
typedef short                   s16;
typedef unsigned short          u16;
typedef int                     s32;
typedef unsigned int            u32;
typedef long long int           s64;
typedef unsigned long long int  u64;
typedef float                   f32;
typedef double                  f64;


namespace coin {

class Application;

typedef u32                     Size;
typedef u32                     Position;
typedef s32                     RelativePosition;
typedef s32                     Key;
typedef s32                     MouseButton;

COIN_EXPORT void Start (Application* application, const Size window_width, const Size window_height, const bool fullscreen, const bool vsync);
COIN_EXPORT void Stop ();

}

#endif
