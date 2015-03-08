#ifndef TRIGGERMANAGER_H_INCLUDED
#define TRIGGERMANAGER_H_INCLUDED
#include <iostream>
#include <string>
#include "typedefs.h"
#include "trigger.h"
#include "BST.h"

//Engine name space macro
//ENGINE_NAMESPACE


class Game;
class Unit;

class EUREKA TriggerManager
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
    void UpdateTriggers(size_t unit_id);
    void UpdateTrigger(size_t trigger_id, size_t unit_id);
    void UpdateTriggerLocation(math_point loc, size_t trigger_id);
private:
    Game* owner_ref;
    size_t mutex_trigger_id;
    BinarySearchTree<size_t, Trigger> triggers;
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // TRIGGERMANAGER_H_INCLUDED
