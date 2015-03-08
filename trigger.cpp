#include <SDL.h>
#include <iostream>
#include "data_base.h"
#include "eureka.h"
#include "unit.h"
#include "scriptwrap.h"

#include "trigger.h"

//Engine name space macro
//ENGINE_NAMESPACE


Trigger::Trigger(cstr file)
{
    data_base TriggerDOM(file);
    Scripts = 0;
    height = TriggerDOM.GetIntFromData("trigger_height");
    width = TriggerDOM.GetIntFromData("trigger_width");
    duration = TriggerDOM.GetIntFromData("trigger_length");
    x = TriggerDOM.GetIntFromData("trigger_x");
    y = TriggerDOM.GetIntFromData("trigger_y");
    z = TriggerDOM.GetIntFromData("trigger_z");
    death = false;
    Scripts = new ScriptWrap(TriggerDOM.GetStrFromData("trigger_script").c_str());
    if(!Scripts)
    {
        std::cout<<"Error: could not load this Trigger's script!" << std::endl;
    }
}

Trigger::Trigger()
{
    Scripts = 0;
    height = 0;
    width = 0;
    duration = 0;
    x = 0;
    y = 0;
    z = 0;
    death = false;
    Scripts = NULL;
}

Trigger::~Trigger()
{
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

//End of namespace macro
//ENGINE_NAMESPACE_END
