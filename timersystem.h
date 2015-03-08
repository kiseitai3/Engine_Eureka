#ifndef TIMERSYSTEM_H_INCLUDED
#define TIMERSYSTEM_H_INCLUDED
#include "Timer.h"
#include "BST.h"
#include <iostream>
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


class Game;

class TimerSystem
{
public:
    //ctros and dtor
    TimerSystem(Game* owner);
    ~TimerSystem();

    //Manipulation
    size_t GetTicks(size_t t_id);
    void StopTimer(size_t t_id);
    void StartTimer(size_t t_id);
    void PauseTimer(size_t t_id);
    void UnpauseTimer(size_t t_id);

    //Status
    bool isTimerStarted(size_t t_id);
    bool isTimerPaused(size_t t_id);

    //Management
    size_t CreateTimer();
    void DeleteTimer(size_t t_id);

private:
    BinarySearchTree<size_t, Timer> timers;
    Game* owner_ref;
    size_t mutex_timers_id;

    bool hasID(size_t t_id);
};

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // TIMERSYSTEM_H_INCLUDED
