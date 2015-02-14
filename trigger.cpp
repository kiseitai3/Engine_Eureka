#include <SDL.h>
#include <iostream>
#include "unit.h"
#include "trigger.h"
#include "physics.h"

Trigger::Trigger(const char *file)
{
    data_base TriggerDOM(file);
    Scripts = 0;
    height = TriggerDOM.GetIntFromData("trigger_height");
    width = TriggerDOM.GetIntFromData("trigger_width");
    length = TriggerDOM.GetIntFromData("trigger_length");
    x = TriggerDOM.GetIntFromData("trigger_x");
    y = TriggerDOM.GetIntFromData("trigger_y");
    z = TriggerDOM.GetIntFromData("trigger_z");
    duration = TriggerDOM.GetIntFromData("trigger_duration");
    death = false;
    Scripts = new ScriptWrap(TriggerDOM.GetStrFromData("trigger_script").c_str());
    if(!Scripts)
    {
        std::cout<<"Error: could not load this Trigger's script!" << std::endl;
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
    if(tLoc.X >= loc.X && tLoc.X <= (loc.X + width))
    {
        if(tLoc.Y >= loc.Y && tLoc.Y <= (loc.Y - height))
        {
            return true;
        }
    }
    return false;
}

void Trigger::ConsumeTrigger(Game* owner, Unit *target)
{
    Scripts->ClearArgs(1);
    Scripts->AddArgument((void_ptr)owner);
    Scripts->AddArgument((void_ptr)target);
    Scripts->AddArgument((void_ptr)this);
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

void Trigger::UpdateTriggerLoc(int X, int Y, int Z)
{
    loc.X = X;
    loc.Y = Y;
    loc.Z = Z;
}

math_point Trigger::GetLoc() const
{
    return loc;
}
