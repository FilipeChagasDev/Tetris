#ifndef TETRISTIMER_HPP
#define TETRISTIMER_HPP
#include <sys/time.h>
#include <stdint.h>

#define USEC_UNITY 1e6

class TetrisTimer
{
protected:
    uintmax_t init_time, elapsed_time;
public:
    uintmax_t my_every_interval;
    TetrisTimer(uintmax_t every_interval);
    static uintmax_t getSystemUseconds();
    void reset();
    uintmax_t update();
    uintmax_t getInitUseconds();
    uintmax_t getElapsedUseconds();
    bool every();
};

#endif // TETRISTIMER_HPP
