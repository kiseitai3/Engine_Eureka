#include "eureka.h"
#include "unit.h"
#include "physics.h"
#include "sound_base.h"
#include "draw_base.h"
#include "conversion.h"
#include "scriptwrap.h"
#include <map>
#include <SDL.h>
#include <string>
#include <iostream>
#include <list>
#include "progressbar.h"

//Engine name space macro
//ENGINE_NAMESPACE
#include "data_base.h"

AIStore Unit::ai;

Unit::Unit(int BlitOrder, const std::string& path, math_point loc, SDL_Renderer* screen, size_t t_id, bool hero, bool hasPBar)
{
    DOM = NULL;
    DOM = new data_base(path.c_str());
    if(DOM > 0)
    {
        std::string names = "";
        std::string num = "";
        anim_counter = DOM->GetIntFromData("unit_texture_counter");
        for(int i = 0; i <  anim_counter; i++)//we want to add all the textures available to this creature to the animation map.
        {
            num = intToStr(i);
            names = DOM->GetStrFromData("unit_texture_" + num + "_name");
            draw_base *temp = new draw_base();
            temp->Load_Texture(DOM->GetStrFromData("unit_texture_" + num).c_str(), *screen);
            if(temp > 0)//do a validity check on the pointer
            {
                images[names] = temp;
            }
            else
            {
                std::cout<<"Error: Failed to load spritesheets or sounds into this instance of the unit class!\n\r";
            }
        }
        //Recycle anim_counter as the sound counter
        anim_counter = DOM->GetIntFromData("unit_sound_counter");
        for(int i = 0; i <  anim_counter; i++)//we want to add all the sounds available to this creature to the sound map.
        {
            num = intToStr(i);
            names = DOM->GetStrFromData("unit_sound_" + num + "_name");
            sound_base *temp = new sound_base(false);
            temp->Load_Sound(DOM->GetStrFromData("unit_sound_" + num).c_str());
            if(temp > 0)// do a validity check on the pointer! :D
            {
                sounds[names] = temp;
            }
            else
            {
                std::cout<<"Error: Failed to load spritesheets or sounds into this instance of the unit class!\n\r";
            }
        }
        soundLoops = DOM->GetIntFromData("sound_loops");
        images["default"] = images[DOM->GetStrFromData(DOM->GetStrFromData("unit_texture_default"))];
        sounds["default"] = sounds[DOM->GetStrFromData(DOM->GetStrFromData("unit_sound_default"))];
        phys = new Physics(DOM->GetStrFromData("unit_physics").c_str());
        //Load Python scripts!
        if(!hero)
        {
            LoadAI(DOM->GetStrFromData("unit_ai").c_str());
        }
        LoadScript(GeneralScripts, DOM->GetStrFromData("unit_generalscripts").c_str());
        if(DOM->GetIntFromData("unit_has_buff"))
        {
            LoadScript(BuffScripts, DOM->GetStrFromData("unit_buffscripts").c_str());
        }
        //Grab parameters
        ren = screen;
        blitOrder = BlitOrder;
        mapPoint = loc;
        gameTime = t_id;
        //Initializing internal variables
        name = DOM->GetStrFromData("unit_name");
        drawImage = "default";
        soundName = "default";
        hp = DOM->GetIntFromData("unit_hp");
        mana = DOM->GetIntFromData("unit_mana");
        ad = DOM->GetIntFromData("unit_ad");
        ap = DOM->GetIntFromData("unit_ap");
        mana = DOM->GetIntFromData("unit_mana");
        aSpeed =DOM->GetValueFromData("unit_aSpeed");
        mSpeed = DOM->GetIntFromData("unit_mSpeed");
        range = DOM->GetIntFromData("unit_range");
        vRange = DOM->GetIntFromData("unit_vRang");
        melee = bool(DOM->GetIntFromData("unit_melee"));
        showManaBar = bool(DOM->GetIntFromData("unit_mana_bar"));
        showHPBar = bool(DOM->GetIntFromData("unit_hp_bar"));
        type = DOM->GetStrFromData("unit_type");
        //Create Health and Mana Bars if necessary
        if(DOM->GetIntFromData("unit_has_bars"))
        {
            draw_base *tmpIMG = images["default"];
            //Compute location of the mana bar!
            locBar.X = mapPoint.X - (tmpIMG->GetWidthOfMainRect() / 2);
            locBar.Y = mapPoint.Y - (tmpIMG->GetHeightOfMainRect() / 2) - 2;// -2 is to keep the bars slightly off the unit
            manaB = new ProgressBar(DOM->GetStrFromData("unit_mana_bar_tex").c_str(), &mana, locBar, *screen);
            manaB->SetRectangleDimensions(DOM->GetIntFromData("unit_mana_bar_w"), DOM->GetIntFromData("unit_mana_bar_h"));
            //Compute location of the hp bar!
            locBar.Y -= DOM->GetIntFromData("unit_hp_bar_h");// -2 is to keep the bars slightly off the unit
            hpB = new ProgressBar(DOM->GetStrFromData("unit_hp_bar_tex").c_str(), &hp, locBar, *screen);
            hpB->SetRectangleDimensions(DOM->GetIntFromData("unit_hp_bar_w"), DOM->GetIntFromData("unit_hp_bar_h"));
        }
    }
    currentATime = 0;
    ID = 0;
    dead = false;
}

Unit::~Unit()
{
    //dtor
    std::string names = "";
    std::string num = "";
    anim_counter = DOM->GetIntFromData("unit_texture_counter");
    for(int i = 0; i <  anim_counter; i++)//I want to clean up the heap like a good programmer. Then, I want to set the pointers to the special 0 address.
    {
        num = intToStr(i);
        names = DOM->GetStrFromData("unit_texture_" + num + "_name");
        draw_base *temp = images[names];
        if(temp > 0)
        {
            delete(temp);
        }
        images[names] = 0;
    }
    anim_counter = DOM->GetIntFromData("unit_sound_counter");
    for(int i = 0; i <  anim_counter; i++)//I want to clean up the heap like a good programmer. Then, I want to set the pointers to the special 0 address.
    {
        num = intToStr(i);
        names = DOM->GetStrFromData("unit_sound_" + num + "_name");
        sound_base *temp = sounds[names];
        if(temp > 0)
        {
            delete(temp);
        }

        sounds[names] = 0;
    }
    if(DOM > 0)
    {
        delete(DOM);
        DOM = 0;
    }
    if(phys > 0)
    {
       delete(phys);
       phys = 0;
    }
    if(GeneralScripts > 0)
    {
       ai.DeleteUniqueAI(GeneralScripts);
       GeneralScripts = 0;
    }
    if(AI > 0)
    {
       ai.DeleteUniqueAI(AI);
       AI = 0;
    }
    if(BuffScripts > 0)
    {
       ai.DeleteUniqueAI(BuffScripts);
       BuffScripts = 0;
    }
    ren = 0;
}

void Unit::LoadAI(const char *file)
{
    if(strcmp(file, ""))
    {
        ai.LoadUniqueAI(file);
        if(!AI)
        {
            hasAI = false;
            std::cout<<"Error: AI for this object was unable to load!\n\r";
        }
        else if(AI->isInitialized())
        {
            hasAI = true;
        }
    }
}

bool Unit::isNPC() const
{
    return hasAI;
}

//Internal updaters
void Unit::Update_OldTime()
{
    oldTime = t;
}

void Unit::Update_NewTime()
{
    t = owner_ref->GetTicks(gameTime);
}

double Unit::GetTimeChange() const//based on seconds. Remember that .get_ticks() is based on milliseconds
{
    return (double)(t - oldTime) / 1000;
}

//Question methods
bool Unit::isMelee() const
{
    return melee;
}

//AI methods
void Unit::MoveAI()
{
    if(hasAI)
    {
        AI->ClearArgs(1);//Make sure previous arguments have been released and create a new set
        AI->AddArgument(this);//Compile new argument list
        AI->executeFunction("Move", AI->NO_ARGS);
    }
}

void Unit::MoveTowardsAI(double force, const char axis)
{
    if(hasAI)
    {
        AI->ClearArgs(3);//Make sure previous arguments have been released and create a new set
        AI->AddArgument(this);//Compile new argument list
        AI->AddArgument(force);//Compile new argument list
        AI->AddArgument(axis);//Compile new argument list
        AI->executeFunction("MoveTowards", AI->NO_ARGS);
    }
}

void Unit::AttackAI(Unit *target)
{
    if(hasAI)
    {
        AI->ClearArgs(2);//Make sure previous arguments have been released and create a new set
        AI->AddArgument(this);//Compile new argument list
        AI->AddArgument(target);//Compile new argument list
        AI->executeFunction("Attack", AI->NO_ARGS);
    }
}

void Unit::ExecuteAI(Unit *target, const char axis)
{
    int d = CalculateDistance(phys->GetLoc(), target->phys->GetLoc()); //Grab distance between both units
    int sign = phys->math_Sign(target->phys, axis);
    if(d <= (2 * vRange) && d > range)
    {
        if(hasAI)
        {
            if(sign < 0 && axis == 'x')
            {
                drawImage = "Move_Left";
                soundName = "Move_Left";
            }
            else if(sign > 0 && axis == 'x')
            {
                drawImage = "Move_Right";
                soundName = "Move_Right";
            }
            else if(sign < 0 && axis == 'y')
            {
                drawImage = "Move_Down";
                soundName = "Move_Down";
            }
            else if(sign > 0 && axis == 'y')
            {
                drawImage = "Move_Up";
                soundName = "Move_Up";
            }
        }
        MoveTowardsAI(mSpeed * GetTimeChange() * phys->GetMass() * sign, axis);
    }
    else if(d <= range)
    {
        if(hasAI)
        {
            drawImage = std::string("Combat_") + axis + intToStr(sign);
        }
        AttackAI(target);
    }
    else
    {
        if(hasAI)
        {
            if(sign < 0 && axis == 'x')
            {
                drawImage = "Move_Left";
            }
            else if(sign > 0 && axis == 'x')
            {
                drawImage = "Move_Right";
            }
            else if(sign < 0 && axis == 'y')
            {
                drawImage = "Move_Down";
            }
            else if(sign > 0 && axis == 'y')
            {
                drawImage = "Move_Up";
            }
        }
        MoveAI();
    }

}

void Unit::SetTimer(size_t timer_id)
{
    gameTime = timer_id;
}

//General getters and Setters
std::string Unit::GetName() const
{
    return name;
}

Physics *Unit::GetPhysics() const
{
    return phys;
}

draw_base *Unit::GetDefaultDrawObject()
{
    return images["default"];
}

void Unit::ToggleMelee()
{
    if(melee == true)
    {
        melee = false;
    }
    else
    {
        melee = true;
    }
}

int Unit::GetHP() const
{
    return hp;
}

int Unit::GetMana() const
{
    return mana;
}

int Unit::GetAD() const
{
    return ad;
}

int Unit::GetAP() const
{
    return ap;
}

int Unit::GetAttackSpeed() const
{
    return aSpeed;
}

int Unit::GetRange() const
{
    return range;
}

int Unit::GetVisionRange() const
{
    return vRange;
}

unsigned int Unit::GetID() const
{
    return ID;
}

double Unit::GetMovementSpeed() const
{
    return mSpeed;
}

std::string Unit::GetType() const
{
    return type;
}

int Unit::GetBlitOrder() const
{
    return blitOrder;
}

void Unit::SetHP(int val)
{
    hp = val;
}

void Unit::SetMana(int val)
{
    mana = val;
}

void Unit::SetAD(int val)
{
    ad = val;
}

void Unit::SetAP(int val)
{
    ap = val;
}

void Unit::SetAttackSpeed(int val)
{
    aSpeed = val;
}

void Unit::SetRange(int val)
{
    range = val;
}

void Unit::SetVisionRange(int val)
{
    vRange = val;
}

void Unit::SetMovementSpeed(double val)
{
    mSpeed = val;
}

void Unit::SetID(unsigned int id)
{
    ID = id;
}

void Unit::SetOwner(Game* owner)
{
    owner_ref = owner;
}

void Unit::SetCurrentAnimation(const std::string& name)
{
    drawImage = name;
}

void Unit::SetCurrentSound(const std::string& name)
{
    soundName = name;
}

bool Unit::GetDeath() const
{
    return dead;
}

void Unit::ToggleDeath()
{
    if(dead == false)
    {
        dead = true;
    }
    else
    {
        dead = false;
    }
}

void Unit::copy(const Unit& obj)
{
    //Copy variables
}

//Physics handling
std::string Unit::isColliding(Unit *target)
{
    //Grab some variables from the target unit
    draw_base *pDTarget = target->GetDefaultDrawObject();
    math_point targetLoc = target->GetPhysics()->GetLoc();
    int tLenTop = pDTarget->GetHeightOfMainRect() / 2;
    int tLenLeft = pDTarget->GetWidthOfMainRect() / 2;//getting distances to the sides from the center point
    //Grab some variables from this unit
    draw_base *pDraw = images["default"];
    int uLenTop = pDraw->GetHeightOfMainRect() / 2;
    int uLenLeft = pDraw->GetWidthOfMainRect() / 2;

    //Compute collisions
    //bottom side
    if(((targetLoc.Y + tLenTop) >= (phys->GetLoc().Y - uLenTop) && ((targetLoc.X + tLenLeft) >= (phys->GetLoc().X - uLenLeft))) || ((targetLoc.Y + tLenTop) >= (phys->GetLoc().Y - uLenTop) && ((targetLoc.X - tLenLeft) <= (phys->GetLoc().X + uLenLeft))))
    {
        return "bottom";
    }
    //top side
    if(((targetLoc.Y - tLenTop) <= (phys->GetLoc().Y + uLenTop) && ((targetLoc.X + tLenLeft) >= (phys->GetLoc().X - uLenLeft))) || ((targetLoc.Y + tLenTop) >= (phys->GetLoc().Y - uLenTop) && ((targetLoc.X - tLenLeft) <= (phys->GetLoc().X + uLenLeft))))
    {
        return "top";
    }
    //left side
    if(((targetLoc.Y + tLenTop) >= (phys->GetLoc().Y - uLenTop) && ((targetLoc.X + tLenLeft) >= (phys->GetLoc().X - uLenLeft))) || ((targetLoc.Y - tLenTop) <= (phys->GetLoc().Y + uLenTop) && ((targetLoc.X + tLenLeft) >= (phys->GetLoc().X - uLenLeft))))
    {
        return "left";
    }
    //right side
    if(((targetLoc.Y + tLenTop) >= (phys->GetLoc().Y - uLenTop) && ((targetLoc.X - tLenLeft) <= (phys->GetLoc().X + uLenLeft))) || ((targetLoc.Y - tLenTop) <= (phys->GetLoc().Y + uLenTop) && ((targetLoc.X - tLenLeft) <= (phys->GetLoc().X + uLenLeft))))
    {
        return "right";
    }
    return "";
}

void Unit::Update_Physics(Unit *target)
{
    /*Before updating this unit's physics, let's make sure it is movable! In the engine, I allow for
    certain units to be marked as unmovable no matter what! Since this will be a property more often
    applied to environment objects and these objects are numerous, I can terminate the method's
    execution and thus save some processing time!
    */
    if(GetPhysics()->isUnmovable())
        return;
    //Process collisions
    std::string collisionSide = isColliding(target);
    if(collisionSide != "")
    {
        if(collisionSide == "bottom" || collisionSide == "top")
        {
            phys->UpdateForce(target->GetPhysics(), 3, owner_ref->GetRelativity(), 'x');
        }
        else if(collisionSide == "right" || collisionSide == "left")
        {
            phys->UpdateForce(target->GetPhysics(), 3, owner_ref->GetRelativity(), 'y');
        }
        OnCollision(target, collisionSide);
    }
    //Process Newtonian forces
    if(blitOrder == target->GetBlitOrder())
        phys->UpdateForce(target->GetPhysics(), 1);
    //process the other forces
    phys->UpdateForce(target->GetPhysics(), 2);//electric forces
    phys->UpdateForce(target->GetPhysics(), 0);//magnetic forces
    //Update the object's position
    phys->Update_Position(GetTimeChange());
}

void Unit::OnCollision(Unit *target, std::string side)
{
    GeneralScripts->ClearArgs(3);
    GeneralScripts->AddArgument(owner_ref);
    GeneralScripts->AddArgument(this);
    GeneralScripts->AddArgument(target);
    GeneralScripts->AddArgument(side);
    GeneralScripts->executeFunction("OnCollision", GeneralScripts->NO_ARGS);
}

//Handle buffs like spells that add extra damage or defenses
void Unit::AddBuff(std::string buffName)
{
    buffs.push_back(buffName);
}

void Unit::RemoveBuff(std::string buffName)
{
    buffs.remove(buffName);
}

bool Unit::BuffExists(std::string buffName)
{
    /*Checks if the buff name is present in the list*/
    for(std::list<std::string>::iterator it = buffs.begin(); it != buffs.end(); it++)
    {
        if(*it == buffName)
        {
            return true;
        }
    }
    return false;
}

void Unit::ApplyBuffs()
{
    for(std::list<std::string>::iterator it = buffs.begin(); it != buffs.end(); it++)
    {
        BuffScripts->ClearArgs(3);
        BuffScripts->AddArgument(owner_ref);
        BuffScripts->AddArgument(this);
        std::string names = *it;
        BuffScripts->AddArgument(names);
        BuffScripts->executeFunction("HandleBuffs", BuffScripts->NO_ARGS);
    }
}


//Handle assets
void Unit::FlipSprite(draw_base* sprite, size_t direction)
{
    //This method will allow users to manipulate the graphics such that you only need half the animations to obtain the full animation set.
    sprite->flip(direction);
}

void Unit::RotateSprite(draw_base* sprite, double degrees)
{
    sprite->rotate(degrees);
}

void Unit::ResetRotation(draw_base* sprite)
{
    sprite->resetRotation();
}

void Unit::PlaySounds(const math_point& screenLoc)
{
    sound_base *tmp = sounds["default"];
    if(sounds["default"] != sounds[soundName])
    {
        tmp->FadeOut(100);
        sounds["default"] = sounds[soundName];
    }
    tmp = sounds["default"];
    tmp->Update_Sound_Position(phys->GetLoc().X, phys->GetLoc().Y);
    tmp->Update_Sound_Distance(screenLoc, owner_ref->GetMasterVolume());
    if(tmp->SoundType()=='e' || tmp->SoundType() == 'a')
    {
        tmp->PlayEffect(soundLoops);
    }
}

void Unit::DrawImages()
{
    draw_base *tmpImage;
    int dx, dy; //Offsets from center point
    if(images["default"] != images[drawImage])
    {
        images["default"] = images[drawImage];
    }
    tmpImage = images["default"];
    dx = tmpImage->GetWidthOfMainRect() / 2;
    dy = tmpImage->GetHeightOfMainRect() / 2;
    tmpImage->apply_surface(phys->GetLoc().X - dx, phys->GetLoc().Y - dy, *ren);
}

void LoadScript(ScriptWrap* script, const char *file)
{
    if(strcmp(file, ""))
    {
        script = Unit::ai.LoadUniqueAI(file);
        if(!script)
        {
            std::cout<<"Error: Scripts file for this object was unable to load!\n\r";
        }
    }
}

//End of namespace macro
//ENGINE_NAMESPACE_END



