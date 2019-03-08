#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks() const;

    //Checks the status of the timer
    bool is_started() const;
    bool is_paused() const;
};

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // TIMER_H_INCLUDED
