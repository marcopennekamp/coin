#ifndef COIN_H_
#define COIN_H_

#ifdef COIN_EXPORT
#define COIN_DECL __declspec (dllexport)
#else
#define COIN_DECL __declspec (dllimport)
#endif

#ifdef COIN_UTILS_EXPORT
#define COIN_UTILS_DECL __declspec (dllexport)
#else
#define COIN_UTILS_DECL __declspec (dllimport)
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

COIN_DECL void Start (Application* application, Size window_width, Size window_height, bool fullscreen, bool vsync);
COIN_DECL void Stop ();

}

#endif
