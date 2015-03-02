#include "timersystem.h"
#include "rand_generators.h"
#include "eureka.h"

TimerSystem::TimerSystem(Game* owner)
{
    owner_ref = owner;
    mutex_timers_id = owner->SpawnMutex();
}

TimerSystem::~TimerSystem()
{
    owner_ref->DeleteMutex(mutex_timers_id);
}

size_t TimerSystem::CreateTimer()
{
    size_t id = randUniform(Range(0, GetMaxValueSizeT()));
    //Lock mutex
    owner_ref->LockMutex(mutex_timers_id);
    //Make sure we have a unique id
    while(hasID(id))
    {
        id = randUniform(Range(0, GetMaxValueSizeT()));
    }
    //Create Timer object
    timers.insert(id, Timer());
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_timers_id);
    //Return
    return id;
}

void TimerSystem::DeleteTimer(size_t t_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_timers_id);
    //Delete object
    timers.remove(t_id);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_timers_id);
}

bool TimerSystem::isTimerPaused(size_t t_id)
{
    bool val;
    //Lock mutex
    owner_ref->LockMutex(mutex_timers_id);
    val = timers[t_id].is_paused();
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_timers_id);
    return val;
}

bool TimerSystem::isTimerStarted(size_t t_id)
{
    bool val;
    //Lock mutex
    owner_ref->LockMutex(mutex_timers_id);
    val = timers[t_id].is_started();
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_timers_id);
    return val;
}

size_t TimerSystem::GetTicks(size_t t_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_timers_id);
    timers[t_id].get_ticks();
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_timers_id);
}

void TimerSystem::StartTimer(size_t t_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_timers_id);
    timers[t_id].start();
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_timers_id);
}

void TimerSystem::StopTimer(size_t t_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_timers_id);
    timers[t_id].stop();
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_timers_id);
}

void TimerSystem::PauseTimer(size_t t_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_timers_id);
    timers[t_id].pause();
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_timers_id);
}

void TimerSystem::UnpauseTimer(size_t t_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_timers_id);
    timers[t_id].unpause();
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_timers_id);
}

bool TimerSystem::hasID(size_t t_id)
{
    Timer tmp;
    return timers.search(t_id, tmp);
}
