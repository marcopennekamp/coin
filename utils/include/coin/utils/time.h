#ifndef COIN_UTILS_TIME_H_
#define COIN_UTILS_TIME_H_

#include <coin/coin.h>


namespace coin {

typedef uint64_t  Time;

COIN_UTILS_EXPORT void TimeInit ();
COIN_UTILS_EXPORT Time TimeNanoseconds ();

}


#endif  /* COIN_UTILS_TIME_H_ */

