#ifndef COIN_UTILS_TIME_H_
#define COIN_UTILS_TIME_H_

#include <coin/coin.h>


namespace coin {

typedef u64     Time;

COIN_UTILS_DECL void TimeInit ();
COIN_UTILS_DECL const Time TimeNanoseconds ();

}

#endif  /* COIN_UTILS_TIME_H_ */

