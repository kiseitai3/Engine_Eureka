#define EUREKA_EXPORT
#include "triggermanager.h"
#include "rand_generators.h"
#include "eureka.h"

//Engine name space macro
//ENGINE_NAMESPACE


TriggerManager::TriggerManager(Game* owner)
{
    mutex_trigger_id = owner->SpawnMutex();
    owner_ref = owner;
}

TriggerManager::~TriggerManager()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_trigger_id);
    //Delete the mutex
    owner_ref->DeleteMutex(mutex_trigger_id);
}

size_t TriggerManager::RegisterTrigger(cstr file)
{
    Trigger tmp;
    size_t id = 0;
    //Lock mutex
    owner_ref->LockMutex(mutex_trigger_id);
    id = hasher();
    while(triggers.search(id, tmp))//Make sure the id is not already in use
    {
        id = hasher();
    }
    triggers.insert(id, Trigger(file));
    triggers[id].SetID(id);
    //Release mutex
    owner_ref->UnlockMutex(mutex_trigger_id);
    //Return id
    return id;
}

void TriggerManager::UnRegisterTrigger(size_t trigger_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_trigger_id);
    triggers.remove(trigger_id);
    //Release mutex
    owner_ref->UnlockMutex(mutex_trigger_id);
}

Trigger& TriggerManager::GetTrigger(size_t trigger_id)
{
    Trigger* tmp = NULL;
    //Lock mutex
    owner_ref->LockMutex(mutex_trigger_id);
    tmp = &triggers[trigger_id];
    //Release mutex
    owner_ref->UnlockMutex(mutex_trigger_id);
    return *tmp;
}

void TriggerManager::UpdateTriggers(size_t unit_id)
{
    std::vector<Trigger> tmpObjs;
    //Lock mutex
    owner_ref->LockMutex(mutex_trigger_id);
    tmpObjs = triggers.getContents();
    for(std::vector<Trigger>::iterator itr = tmpObjs.begin(); itr < tmpObjs.end(); itr++)
    {
        if(itr->isUnitOnTrigger(&owner_ref->GetUnit(unit_id)))
            itr->ConsumeTrigger(owner_ref, &owner_ref->GetUnit(unit_id));
        owner_ref->UnlockUnit();
    }
    //Release mutex
    owner_ref->UnlockMutex(mutex_trigger_id);
}

void TriggerManager::UpdateTrigger(size_t trigger_id, size_t unit_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_trigger_id);
    Trigger tmp = triggers[trigger_id];
    if(tmp.isUnitOnTrigger(&owner_ref->GetUnit(unit_id)))
        tmp.ConsumeTrigger(owner_ref, &owner_ref->GetUnit(unit_id));
    owner_ref->UnlockUnit();
    //Release mutex
    owner_ref->UnlockMutex(mutex_trigger_id);
}

void TriggerManager::UpdateTriggerLocation(math_point loc, size_t trigger_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_trigger_id);
    Trigger tmp = triggers[trigger_id];
    tmp.UpdateTriggerLoc(loc.X, loc.Y, loc.Z);
    owner_ref->UnlockUnit();
    //Release mutex
    owner_ref->UnlockMutex(mutex_trigger_id);
}

//End of namespace macro
//ENGINE_NAMESPACE_END
