#include "triggermanager.h"
#include "rand_generators.h"
#include "trigger.h"

TriggerManager::TriggerManager(Game* owner)
{
    mutex_trigger_id = owner->SpawnMutex();
    owner_ref = owner;
}

TriggerManager::~TriggerManager()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_trigger_id);
    std::vector<Trigger*> tmpObjs = triggers.getContents();
    //Delete triggers
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        if(tmpObjs[i])
            delete tmpObjs[i];
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_trigger_id);
    //Delete the mutex
    owner_ref->DeleteMutex(mutex_trigger_id);
}

size_t TriggerManager::RegisterTrigger(cstr file)
{
    Trigger* tmp;
    size_t id = 0;
    //Lock mutex
    owner_ref->LockMutex(mutex_trigger_id);
    id = hasher();
    while(triggers.search(id, tmp))//Make sure the id is not already in use
    {
        id = hasher();
    }
    tmp = NULL; //Reset value of tmp just in case
    tmp = new Trigger(file);
    if(tmp)
    {
        //Insert new trigger into the tree
        triggers.insert(id, tmp);
    }
    else
        id = 0;//Set to 0 if unable to allocate!
    //Release mutex
    owner_ref->UnlockMutex(mutex_trigger_id);
    //Return id
    return id;
}
