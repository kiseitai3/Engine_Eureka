#ifndef THREADING_H_INCLUDED
#define THREADING_H_INCLUDED
#include <iostream>
#include <pthread.h>
#include <list>
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


//Templates
template <typename T>
struct pthreads_opaque
{
    size_t id;
    bool running;
    T var;

    pthreads_opaque(T& val, size_t T_id)
    {
        var = val;
        id = T_id;
        running = false;
    }

    bool operator==(pthreads_opaque& t)
    {
        return id == t.id;
    }

    bool operator==(size_t& t)
    {
        return id == t;
    }
};

template <typename T>
class indexed_opaque_list : public std::list<T>
{
public:
    T& operator[] (size_t id)
    {
        typename std::list<T>::iterator itr;//iterator that will point to opaque object contained
        itr = this->begin();
        while(itr->id != id)//Search for object
        {
            itr++;
        }//This whole operation is linearly expensive, so we want to cut as many cycles as possible

        return *itr;
    }
};

//typedefs
typedef pthreads_opaque<pthread_t*> pthread;
typedef pthreads_opaque<pthread_mutex_t> pmutex;
typedef pthreads_opaque<pthread_cond_t> pcond_var;

class ThreadSystem
{
public:
    //ctors and dtor
    ThreadSystem();
    ~ThreadSystem();

    //Setter
    size_t SpawnThread(thread_func target, void_ptr arg);
    size_t SpawnMutex();//Creates a mutex and returns the mutex id
    size_t SpawnCondVar();//Creates a condition variable and return the id

    //Getter
    pthread_mutex_t& GetMutex(size_t id);
    pthread_cond_t& GetConditionVariable(size_t id);
    size_t GetErrorCode();

    //Lock
    void LockMutex(size_t mutex_id);
    void WaitForCond(size_t mutex_id, size_t cond_id);
    void SignalCond(size_t cond_id);
    void UnlockMutex(size_t mutex_id);

    //Thread
    void JoinThread(size_t id);
    void CloseThread(size_t id);
    void DeleteMutex(size_t id);
    void DeleteConditionVariable(size_t id);

private:
    indexed_opaque_list<pthread> threads;
    indexed_opaque_list<pmutex> mutexes;
    indexed_opaque_list<pcond_var> cond_vars;
    size_t mutex_mutex_id;
    size_t mutex_cond_id;
    size_t mutex_thread_id;
    size_t err_code;

    //Methods
    size_t generateID(char target);
    bool hasID(size_t id, char target);

};

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // THREADING_H_INCLUDED
