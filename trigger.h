#ifndef TRIGGER_H_INCLUDED
#define TRIGGER_H_INCLUDED
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


class ScriptWrap;
class Game;
class Unit;

class Trigger
{
private:
    int height, width, x, y, z, duration;
    size_t ID;
    bool death;
    ScriptWrap *Scripts;
    math_point loc;

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
    void ConsumeTrigger(Game* owner, Unit *target);
    void UpdateTriggerLoc(int X, int Y, int Z);
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // TRIGGER_H_INCLUDED
