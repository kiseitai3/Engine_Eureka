#include <SDL.h>
#include <iostream>
#include "unit.h"
#include "trigger.h"
#include "physics.h"

Trigger::Trigger(const char *file)
{
    TriggerDOM = 0;
    TriggerDOM = new data_base(file);
    if(!TriggerDOM)
    {
        std::cout<<"Error: This trigger object failed to load its settings file!"<<std::endl;
    }
    else
    {
        Scripts = 0;
        height = TriggerDOM->GetIntFromData("trigger_height");
        width = TriggerDOM->GetIntFromData("trigger_width");
        x = TriggerDOM->GetIntFromData("trigger_x");
        y = TriggerDOM->GetIntFromData("trigger_y");
        duration = TriggerDOM->GetIntFromData("trigger_duration");
        death = false;
        Scripts = new ScriptWrap(TriggerDOM->GetStrFromData("trigger_script").c_str());
        if(!Scripts)
        {
            std::cout<<"Error: could not load this Trigger's script!\n\r";
        }
    }
}

Trigger::~Trigger()
{
    if(TriggerDOM > 0)
    {
        delete(TriggerDOM);
    }
}

//Getters and setters
size_t Trigger::GetID() const
{
    return ID;
}

void Trigger::SetID(size_t id)
{
    ID = id;
}

//Behavior
bool Trigger::isUnitOnTrigger(Unit *target) const
{
    math_point tLoc = target->GetPhysics()->GetLoc();//Grab target's position
    if(tLoc.X >= x && tLoc.X <= (x + width))
    {
        if(tLoc.Y >= y && tLoc.Y <= (y - height))
        {
            return true;
        }
    }
    return false;
}

void Trigger::ConsumeTrigger(Unit *target)
{
    Scripts->ClearArgs(1);
    Scripts->AddArgument(target);
    Scripts->executeFunction("Trigger", Scripts->NO_ARGS);
}

bool Trigger::GetDeath() const
{
    return death;
}

void Trigger::ToggleDeath()
{
    if(death == false)
    {
        death = true;
    }
    else
    {
        death = false;
    }
}
