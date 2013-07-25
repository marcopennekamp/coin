#include <windows.h>

#include <coin/coin.h>
#include <coin/utils/time.h>


namespace coin {

namespace {

double frequency;
double frequency_nanoseconds;

HANDLE timer = NULL;

}

void TimeInit () {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency (&freq);
    frequency = 1.0 / ((double) freq.QuadPart);
    frequency_nanoseconds = ((double) freq.QuadPart) / 1000000000.0;

    /* Create waitable timer- */
    timer = CreateWaitableTimer (NULL, TRUE, NULL);
    // TODO Throw error!
}

Time TimeNanoseconds () {
    LARGE_INTEGER time;
    QueryPerformanceCounter (&time);
    return (Time) (time.QuadPart / frequency_nanoseconds);
}

}