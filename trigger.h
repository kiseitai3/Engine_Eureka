#ifndef TRIGGER_H_INCLUDED
#define TRIGGER_H_INCLUDED
<<<<<<< HEAD
#include "data_base.h"
#include "scriptwrap.h"
#include "unit.h"
=======
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


class ScriptWrap;
class Game;
class Unit;
>>>>>>> TheIllusiveMan

class Trigger
{
private:
    int height, width, x, y, z, duration;
    size_t ID;
    bool death;
    ScriptWrap *Scripts;
<<<<<<< HEAD
=======
    math_point loc;
    data_base *TriggerDOM;
>>>>>>> TheIllusiveMan

public:
    Trigger();
    Trigger(cstr file);
    ~Trigger();
    //Getters and setters
    size_t GetID() const;
    void SetID(size_t id);
    bool GetDeath() const;
    math_point GetLoc() const;
    void ToggleDeath();
    //Behavior
    bool isUnitOnTrigger(Unit *target) const;
    void ConsumeTrigger(Unit *target);
    void UpdateTriggerLoc(int X, int Y, int Z = 0);
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // TRIGGER_H_INCLUDED
