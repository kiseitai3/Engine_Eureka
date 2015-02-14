#ifndef TRIGGER_H_INCLUDED
#define TRIGGER_H_INCLUDED
#include "data_base.h"
#include "scriptwrap.h"
#include "unit.h"
#include "game.h"
#include "typedefs.h"

class Trigger
{
private:
    int height, width, x, y, z, duration;
    size_t ID;
    bool death;
    ScriptWrap *Scripts;
    math_point loc;

public:
    Trigger(cstr file);
    ~Trigger();
    //Getters and setters
    size_t GetID() const;
    void SetID(size_t id);
    bool GetDeath() const;
    void ToggleDeath();
    //Behavior
    bool isUnitOnTrigger(Unit *target) const;
    void ConsumeTrigger(Game* owner, Unit *target);
    void UpdateTriggerLoc(int X, int Y, int Z);
};


#endif // TRIGGER_H_INCLUDED
