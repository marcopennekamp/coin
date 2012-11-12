#include <stdint.h>
#include <time.h>

#include <coin/utils/time.h>


namespace coin {

void TimeInit () {

}


Time TimeNanoseconds () {
    struct timespec ts;
    clock_gettime (CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

}