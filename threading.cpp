#include "threading.h"

ThreadSystem::ThreadSystem()
{
    threads.push_back(NULL);
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    mutexes.push_back(mutex);
    mutex_mutex_id = mutexes.size() - 1;
    mutexes.push_back(mutex);
    mutex_cond_id = mutexes.size() - 1;
    mutexes.push_back(mutex);
    mutex_thread_id = mutexes.size() - 1;
}

ThreadSystem::~ThreadSystem()
{
    for(std::vector<pthread_t*>::iterator itr = threads.begin(); itr != threads.end(); itr++)
    {
        pthread_cancel(**itr);
    }

    for(std::vector<pthread_cond_t>::iterator itr = cond_vars.begin(); itr != cond_vars.end(); itr++)
    {
        pthread_cond_destroy(&(*itr));
    }

    for(std::vector<pthread_mutex_t>::iterator itr = mutexes.begin(); itr != mutexes.end(); itr++)
    {
        pthread_mutex_destroy(&(*itr));
    }
}

size_t ThreadSystem::SpawnThread(thread_func target, void_ptr arg)
{
    pthread_t* thread;
    LockMutex(mutex_thread_id);
    if(!pthread_create(thread, NULL, target, arg))
    {
        threads.push_back(thread);
        return threads.size() - 1;
    }
    return 0;
    UnlockMutex(mutex_thread_id);
}

size_t ThreadSystem::SpawnThread(func target, void_ptr arg)
{
    thread_func tmp = helperMethod_r(target);//Convert regular void function into a void* function
    return SpawnThread(tmp, arg);
}

size_t ThreadSystem::SpawnMutex()
{
    LockMutex(mutex_mutex_id);
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    mutexes.push_back(mutex);
    return mutexes.size() - 1;
    UnlockMutex(mutex_mutex_id);
}

size_t ThreadSystem::SpawnCondVar()
{
    LockMutex(mutex_cond_id);
    pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
    cond_vars.push_back(cond_var);
    return cond_vars.size() - 1;
    UnlockMutex(mutex_cond_id);
}

pthread_mutex_t& ThreadSystem::GetMutex(size_t id)
{
    LockMutex(mutex_mutex_id);
    return mutexes[id];
    UnlockMutex(mutex_mutex_id);
}

pthread_cond_t& ThreadSystem::GetConditionVariable(size_t id)
{
    LockMutex(mutex_cond_id);
    return cond_vars[id];
    UnlockMutex(mutex_cond_id);
}

void ThreadSystem::LockMutex(size_t mutex_id)
{
    LockMutex(mutex_mutex_id);
    pthread_mutex_lock(&mutexes[mutex_id]);
    UnlockMutex(mutex_mutex_id);
}

void ThreadSystem::WaitForCond(size_t mutex_id, size_t cond_id)
{
    pthread_cond_wait(&cond_vars[cond_id], &mutexes[mutex_id]);
}

void ThreadSystem::UnlockMutex(size_t mutex_id)
{
    LockMutex(mutex_mutex_id);
    pthread_mutex_unlock(&mutexes[mutex_id]);
    UnlockMutex(mutex_mutex_id);
}

void ThreadSystem::SignalCond(size_t cond_id)
{
    LockMutex(mutex_cond_id);
    pthread_cond_signal(&cond_vars[cond_id]);
    UnlockMutex(mutex_cond_id);
}

void ThreadSystem::CloseThread(size_t id)
{
    LockMutex(mutex_thread_id);
    if(!pthread_cancel(*threads[id]))
    {
        for(std::vector<pthread_t*>::iterator itr = threads.begin(); itr != threads.end(); itr++)
        {
            if(threads[id] == *itr)
                threads.erase(itr);
        }
    }
    UnlockMutex(mutex_thread_id);
}

void ThreadSystem::DeleteConditionVariable(size_t id)
{
    LockMutex(mutex_cond_id);
    for(std::vector<pthread_cond_t>::iterator itr = cond_vars.begin(); itr != cond_vars.end(); itr++)
    {
        if(cond_vars[id] == *itr)
            threads.erase(itr);
    }
    UnlockMutex(mutex_cond_id);
}

void ThreadSystem::DeleteMutex(size_t id)
{
    LockMutex(mutex_mutex_id);
    for(std::vector<pthread_mutex_t>::iterator itr = mutexes.begin(); itr != mutexes.end(); itr++)
    {
        if(mutexes[id] == *itr)
            threads.erase(itr);
    }
    UnlockMutex(mutex_mutex_id);
}

void* helperMethod_r(func target)
{
    return (void*)target;
}
