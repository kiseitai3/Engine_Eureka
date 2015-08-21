#include <cstdlib>
#include "ai_store.h"
#include <crc.h>

AIStore::AIStore()
{
    mutex = PTHREAD_MUTEX_INITIALIZER;
}

bool AIStore::hasAI(uint64_t hash)
{
    ScriptWrap* tmp = NULL;
    return storage.search(hash, tmp);
}

ScriptWrap* AIStore::createAI(cstr file)
{
    ScriptWrap* ai = new ScriptWrap(file);

    if(ai)
        return ai;
    return NULL;
}

ScriptWrap* AIStore::LoadUniqueAI(cstr file)
{
    uint64_t crc_hash = 0;
    ScriptWrap* tmp = NULL;

    //Let's compute the crc hash
    crc_hash = crc64_on_file_fast(file);

    //For safety's sake, let's lock the mutex
    pthread_mutex_lock(&mutex);

    //Let's see if the texture was already loaded!
    if(hasAI(crc_hash))
    {
        tmp = storage[crc_hash];
        AILife[tmp]++;
        //For sanity's sake, let's unlock the mutex so we don't get stuck!
        pthread_mutex_unlock(&mutex);
        return tmp;
    }

    //If we get here, the caller wants a script handle but the script was never loaded in the first place
    tmp = createAI(file);
    storage.insert(crc_hash, tmp);
    hashCache.insert(tmp, crc_hash);
    AILife.insert(tmp, 1);

    //For sanity's sake, let's unlock the mutex so we don't get stuck!
    pthread_mutex_unlock(&mutex);

    return tmp;
}

void AIStore::DeleteUniqueAI(ScriptWrap* script)
{
    uint64_t crc_hash;
    uint64_t ai_life = 0;
    //For safety's sake, let's lock the mutex
    pthread_mutex_lock(&mutex);
    if(hasHash(script))
    {
        crc_hash = hashCache[script];
        ai_life = AILife[script];
        if(hasAI(crc_hash) && ai_life == 0)
        {
            storage.remove(crc_hash);
            hashCache.remove(script);
            AILife.remove(script);
        }
        else
            AILife[script]--;//Decrement the life of the texture!
    }
    //For sanity's sake, let's unlock the mutex so we don't get stuck!
    pthread_mutex_unlock(&mutex);

    //Destroy the script
    if(ai_life == 0)
        delete script;
}

bool AIStore::hasHash(ScriptWrap* script)
{
    uint64_t hash;
    return hashCache.search(script, hash);
}

void AIStore::IncrementTextLife(ScriptWrap* script)
{
    AILife[script]++;
}

