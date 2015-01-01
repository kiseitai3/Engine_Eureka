#ifndef THREADING_H_INCLUDED
#define THREADING_H_INCLUDED
#include <iostream>
#include <pthread.h>
#include "typedefs.h"

class ThreadSystem
{
public:
    //ctors and dtor
    ThreadSystem();
    ~ThreadSystem();

    //Setter
    size_t SpawnThread(thread_func target, void_ptr arg);
    size_t SpawnThread(func target, void_ptr arg);//This one uses the reentrant helperMethod()
    size_t SpawnMutex();//Creates a mutex and returns the mutex id
    size_t SpawnCondVar()//Creates a condition variable and return the id

    //Getter
    pthread_mutex_t& GetMutex(size_t id);
    pthread_cond_t& GetConditionVariable(size_t id);

    //Lock
    void LockMutex(size_t mutex_id);
    void WaitForCond(size_t mutex_id, size_t cond_id);
    void SignalCond(size_t cond_id);
    void UnlockMutex(size_t mutex_id);

    //Thread
    void CloseThread(size_t id);
    void DeleteMutex(size_t id);
    void DeleteConditionVariable(size_t id);

private:
    std::vector<pthread_t*> threads;
    std::vector<pthread_mutex_t> mutexes;
    std::vector<pthread_cond_t> cond_vars;
    size_t mutex_mutex_id;
    size_t mutex_cond_id;
    size_t mutex_thread_id;

    //Methods
    void* helperMethod_r(func target);//Feed it a void function for execution in a pthread!
};


#endif // THREADING_H_INCLUDED
