#ifndef TRIGGER_H_INCLUDED
#define TRIGGER_H_INCLUDED
#include "data_base.h"
#include "pywrap.h"
#include "unit.h"

class Trigger
{
private:
    data_base *TriggerDOM;//Document Object Model for the trigger class
    SDL_Rect rect;
    int height, width, x, y, ID, duration;
    bool death;
    Pywrap *Scripts;

public:
    Trigger(const char *file);
    ~Trigger();
    //Getters and setters
    int GetID();
    void SetID(int id);
    //Behavior
    bool isUnitOnTrigger(Unit *target);
    void ConsumeTrigger(Unit *target);
    bool GetDeath();
    void ToggleDeath();
};


#endif // TRIGGER_H_INCLUDED
