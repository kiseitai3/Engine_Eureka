#include "threading.h"
#include "rand_generators.h"

//Engine name space macro
//ENGINE_NAMESPACE


ThreadSystem::ThreadSystem()
{
    pthread_t* tmp = NULL;
    threads.push_back(pthread(tmp, 0));
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    mutex_mutex_id = 0;
    mutex_cond_id = 1;
    mutex_thread_id = 2;
    mutexes.push_back(pmutex(mutex, mutex_mutex_id));
    mutexes.push_back(pmutex(mutex, mutex_cond_id));
    mutexes.push_back(pmutex(mutex, mutex_thread_id));
}

ThreadSystem::~ThreadSystem()
{
    for(std::list<pthread>::iterator itr = threads.begin(); itr != threads.end(); itr++)
    {
        pthread_cancel(*itr->var);
    }

    for(std::list<pcond_var>::iterator itr = cond_vars.begin(); itr != cond_vars.end(); itr++)
    {
        pthread_cond_destroy(&itr->var);
    }

    for(std::list<pmutex>::iterator itr = mutexes.begin(); itr != mutexes.end(); itr++)
    {
        pthread_mutex_destroy(&itr->var);
    }
}

size_t ThreadSystem::SpawnThread(thread_func target, void_ptr arg)
{
    pthread_t* thread;
    size_t id = generateID('t');//Get id
    LockMutex(mutex_thread_id);
    if(!pthread_create(thread, NULL, target, arg))
    {
        threads.push_back(pthread(thread, id));
    }
    UnlockMutex(mutex_thread_id);
    return id;
}

size_t ThreadSystem::SpawnMutex()
{
    size_t id = generateID('m');//Get id
    LockMutex(mutex_mutex_id);
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    mutexes.push_back(pmutex(mutex, id));
    UnlockMutex(mutex_mutex_id);
    return id;
}

size_t ThreadSystem::SpawnCondVar()
{
    size_t id = generateID('c');//Get id
    LockMutex(mutex_cond_id);
    pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
    cond_vars.push_back(pcond_var(cond_var, id));
    UnlockMutex(mutex_cond_id);
    return id;
}

pthread_mutex_t& ThreadSystem::GetMutex(size_t id)//very dangerous
{
    pmutex* tmp;
    LockMutex(mutex_mutex_id);
    tmp = &mutexes[id];
    UnlockMutex(mutex_mutex_id);
    return tmp->var;
}

pthread_cond_t& ThreadSystem::GetConditionVariable(size_t id)
{
    pcond_var* tmp;
    LockMutex(mutex_cond_id);
    tmp = &cond_vars[id];
    UnlockMutex(mutex_cond_id);
    return tmp->var;
}

void ThreadSystem::LockMutex(size_t mutex_id)
{
    LockMutex(mutex_mutex_id);
    pthread_mutex_lock(&(mutexes[mutex_id].var));
    UnlockMutex(mutex_mutex_id);
}

void ThreadSystem::WaitForCond(size_t mutex_id, size_t cond_id)
{
    pthread_cond_wait(&cond_vars[cond_id].var, &mutexes[mutex_id].var);
}

void ThreadSystem::UnlockMutex(size_t mutex_id)
{
    LockMutex(mutex_mutex_id);
    pthread_mutex_unlock(&mutexes[mutex_id].var);
    UnlockMutex(mutex_mutex_id);
}

void ThreadSystem::SignalCond(size_t cond_id)
{
    LockMutex(mutex_cond_id);
    pthread_cond_signal(&cond_vars[cond_id].var);
    UnlockMutex(mutex_cond_id);
}

void ThreadSystem::CloseThread(size_t id)
{
    LockMutex(mutex_thread_id);
    if(!pthread_cancel(*threads[id].var))
    {
        for(std::list<pthread>::iterator itr = threads.begin(); itr != threads.end(); itr++)
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
    for(std::list<pcond_var>::iterator itr = cond_vars.begin(); itr != cond_vars.end(); itr++)
    {
        if(cond_vars[id] == *itr)
            cond_vars.erase(itr);
    }
    UnlockMutex(mutex_cond_id);
}

void ThreadSystem::DeleteMutex(size_t id)
{
    LockMutex(mutex_mutex_id);
    for(std::list<pmutex>::iterator itr = mutexes.begin(); itr != mutexes.end(); itr++)
    {
        if(mutexes[id] == *itr)
            mutexes.erase(itr);
    }
    UnlockMutex(mutex_mutex_id);
}

size_t ThreadSystem::generateID(char target)
{
    size_t id = randUniform((0, GetMaxValueSizeT())) ;//Get a random number
    //Continue getting a new random number if the id is already taken!
    while(hasID(id, target))
    {
        id = randUniform((0, GetMaxValueSizeT()));
    }

    return id;
}

bool ThreadSystem::hasID(size_t id, char target)
{
    switch(target)//Search in the right list for the id
    {
    case 't'://thread list
        for(std::list<pthread>::iterator itr = threads.begin(); itr != threads.end(); itr++)
        {
            if(*itr == id)
                return true;
        }
        break;
    case 'c'://condition variable list
        for(std::list<pcond_var>::iterator itr = cond_vars.begin(); itr != cond_vars.end(); itr++)
        {
            if(*itr == id)
                return true;
        }
        break;
    case 'm'://mutex list
    default:
        for(std::list<pmutex>::iterator itr = mutexes.begin(); itr != mutexes.end(); itr++)
        {
            if(*itr == id)
                return true;
        }
    }

    //If nothing was found
    return false;
}

//End of namespace macro
//ENGINE_NAMESPACE_END
