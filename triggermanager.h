#include "eureka.h"

#ifndef TRIGGERMANAGER_H_INCLUDED
#define TRIGGERMANAGER_H_INCLUDED
#include <iostream>
#include <string>
#include "trigger.h"
#include "typedefs.h"

class TriggerManager
{
public:
    //ctors and dtor
    TriggerManager(Game* owner);
    ~TriggerManager();

    //Setters
    size_t RegisterTrigger(cstr file);
    void UnRegisterTrigger(size_t trigger_id);

    //Getters
    Trigger& GetTrigger(size_t trigger_id);

    //Updaters
    void UpdateTriggers(Unit* unit);
private:
    Game* owner_ref;
    size_t mutex_trigger_id;
    BinarySearchTree<size_t, Trigger> triggers;
};


#endif // TRIGGERMANAGER_H_INCLUDED
