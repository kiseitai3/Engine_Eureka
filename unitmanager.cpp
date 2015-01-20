#include "unitmanager.h"

UnitNode::UnitNode(Game& owner, char type, int BlitOrder, math_point loc, cstr file, bool hero, bool hasBars)
{
    Type = type;
    pData = NULL;
    pData = new Unit(BlitOrder, file, loc, owner.GetRenderer(), owner.GetTimer(), hero, hasBars);
}

UnitNode::UnitNode()
{
    Type = 'n';
    pData = NULL;
}

UnitManager::UnitManager(Game& owner, SDL_Event& events)
{
    owner_ref = &owner;
    event = &events;
    mutex_id = owner.SpawnMutex();
    UnitNode* tmp = new UnitNode();
    gameObjects.resize(owner.GetDefaultUnitCount());
    gameObjects.push_back(tmp);
}

size_t UnitManager::SpawnUnit(const char type, int BlitOrder, math_point loc, std::string file, bool hero, bool hasBars)
{
    size_t id = owner_ref->hasher();
    UnitNode* tmp =  NULL;
    owner_ref->LockMutex(mutex_id);
    UnitNode *pUnit = new UnitNode(*owner_ref, type, BlitOrder, loc, file, hero, hasBars);
    while(gameObjects.search(id, tmp))
    {
        id = owner_ref->hasher();
    }
    gameObjects.insert(id, pUnit);
    owner_ref->UnlockMutex(mutex_id);
    return id;
}

void UnitManager::SpawnUnitFromList(cstr file, int BlitOrder)
{
    //Vars needed to initialize a Unit
    bool hero = false;
    bool hasBars = false;
    math_point loc;
    char type = 'u';
    std::string unitFile = "";
    //Load file
    data_base f(file);
    size_t count = f.GetIntFromData("unit_count");
    size_t id = owner_ref->hasher();
    std::string unit = "";

    //Let's load the objects
    for(size_t i = 0; i < count; i++)
    {
         //Let's lock the container
        unit = "unit_" + intToStr(i);
        //Load constants
        hero = f.GetIntFromData(name + "_hero");
        hasBars = f.GetIntFromData(name + "_bars");
        loc.X = f.GetIntFromData(name + "_X");
        loc.Y = f.GetIntFromData(name + "_Y");
        loc.Z = f.GetIntFromData(name + "_Z");
        type = f.GetStrFromData(name + "_type")[0];
        unitFile = f.GetStrFromData(name + "_file");
        //Create object
        UnitNode* hasID;
        UnitNode* tmp = new UnitNode(*owner_ref, type, BlitOrder, loc, unitFile.c_str(), hero, hasBars);
        owner_ref->LockMutex(mutex_id);
        while(gameObjects.search(id, hasID))
        {
            id = owner_ref->hasher();
        }
        gameObjects.insert(id, tmp);
        //Release the container
        owner_ref->UnlockMutex(mutex_id);
    }
}

Unit& UnitManager::GetUnit(size_t id) const
{
    Unit* tmp;
    owner_ref->LockMutex(mutex_id);//Lock container
    tmp = gameObjects[id]->pData;
    owner_ref->UnlockMutex(mutex_id);//Unlock container
    return *tmp;
}

Unit& UnitManager::GetUnitByName(const std::string& name) const
{
    Unit* tmp;
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(size_t i = tmpObjs.size(); i > 0; i--)
    {
        tmp = tmpObjs[i]->pData;
        if(tmp->GetName() == name)
            break;
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
    return *tmp;
}

Unit* UnitManager::FindNearbyUnit(Unit *pUnit) const

{
    Unit *tmp = 0;
    Unit *old = 0;
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(size_t i = tmpObjs.size(); i > 0; i--)
    {
        tmp = tmpObjs[i]->pData;
        int d = pUnit->GetPhysics()->GetDistance(tmp->GetPhysics()->GetLoc());
        if(abs(d) < (pUnit->GetVisionRange() * 2))
        {
            if(!old)
            {
                old = tmp;
            }
            else
            {
                int d2 = pUnit->GetPhysics()->GetDistance(old->GetPhysics()->GetLoc());
                if(d < d2)
                {
                    old = tmp;
                }
            }
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
    return old;
}

UnitManager::~UnitManager()
{
    Unit* tmp;
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(size_t i = tmpObjs.size(); i > 0; i--)
    {
        tmp = tmpObjs[i]->pData;
        if(tmp)
            delete tmp;
        tmpObjs[i] = NULL;
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container

    //Destroy mutex
    owner_ref->DeleteMutex(mutex_id);
}

bool UnitManager::hasUnit(const std::string& name) const
{
    Unit* tmp = NULL;
    tmp = GetUnitByName(name);
    if(tmp)
        return true;
    return false;
}

bool UnitManager::hasUnit(size_t id) const
{
    Unit* tmp = NULL;
    tmp = GetUnit(id);
    if(tmp)
        return true;
    return false;
}

void UnitManager::DeleteUnit(Unit& unit)
{
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(std::vector<UnitNode*>::iterator itr = (tmpObjs.begin()++); itr <= tmpObjs.end(); itr++)
    {
        if((*itr)->pData == &unit)
        {
            if((*itr)->pData)
                delete (*itr)->pData
            gameObjects.remove(*itr->id);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteUnitByName(const std::string& name)
{
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(std::vector<UnitNode*>::iterator itr = (tmpObjs.begin()++); itr <= tmpObjs.end(); itr++)
    {
        if((*itr)->pData->GetName() == name)
        {
            if((*itr)->pData)
                delete (*itr)->pData
            gameObjects.remove(*itr->id);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteUnitByID(size_t id)
{
    owner_ref->LockMutex(mutex_id);//Lock container
    gameObjects.remove(id);
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteAllProjectiles()
{
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(std::vector<UnitNode*>::iterator itr = (tmpObjs.begin()++); itr <= tmpObjs.end(); itr++)
    {
        if((*itr)->type == 'p')
        {
            if((*itr)->pData)
                delete (*itr)->pData
            gameObjects.remove(*itr->id);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteAllGameObjects()
{
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(std::vector<UnitNode*>::iterator itr = (tmpObjs.begin()++); itr <= tmpObjs.end(); itr++)
    {
        if((*itr)->type == 'o')
        {
            if((*itr)->pData)
                delete (*itr)->pData
            gameObjects.remove(*itr->id);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteAllUnits()
{
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(std::vector<UnitNode*>::iterator itr = (tmpObjs.begin()++); itr <= tmpObjs.end(); itr++)
    {
        if((*itr)->type == 'u')
        {
            if((*itr)->pData)
                delete (*itr)->pData
            gameObjects.remove(*itr->id);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteAll()
{
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(std::vector<UnitNode*>::iterator itr = (tmpObjs.begin()++); itr <= tmpObjs.end(); itr++)
    {
        if((*itr)->pData)
            delete (*itr)->pData
            gameObjects.remove(*itr->id);
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::RunPhysics()
{
    /*This is a more complicated method. Here, I have to run the physics of each object in respect to every
    object. Also, I have to run a couple of different physics (magnetic effects, electrical forces, and
    Newtonian forces).*/
    std:;string tmp;
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(size_t i = 1; i < tmpObjs.size(); i++)
    {
        //If this object is flagged for removal, save the engine some processing time! :D
        if(tmpObjs[i]->pData->GetDeath())
            continue;
        for(size_t j = 1; i < tmpObjs.size(); i++)
        {
            /*If either of the objects is flagged for removal, stop processing physics so that no
            artificial behaviors pollute the final physics experience. */
            if(!tmpObjs[j]->pData->GetDeath())
                tmpObjs[i]->pData->Update_Physics(tmpObjs[j]->pData);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::Draw()
{
    /*Here I handle the drawing step of the units!*/
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(size_t i = 1; i < tmpObjs.size(); i++)
    {
        if(OnScreen(tmpObjs[i]->pData))
            tmpObjs[i]->pData->DrawImages();
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::PlaySounds()
{
    /*Although the engine will have a smaller, but global sound system, Units can play their own sounds
    too*/
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(size_t i = 1; i < tmpObjs.size(); i++)
    {
        tmpObjs[i]->pData->PlaySounds(owner_ref->GetScreenLoc());
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::RunEvents()
{
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(size_t i = 1; i < tmpObjs.size(); i++)
    {
        tmpObjs[i]->pData->ProcessKeyEvent(event->key.keysym.sym);
        tmpObjs[i]->pData->ProcessMouseMovement(event->motion->xrel, event->motion->yrel);
        tmpObjs[i]->pData->ProcessMouseKey(event->button.button, event->button.x, event->button.y);
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::GC()
{
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmp = gameObjects.getContents();
    for(size_t i = 1; i < tmp.size(); i++)
    {
        if(tmp[i]->pData->GetDeath())
            gameObjects.remove(tmp[i]->id);
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}


bool UnitManager::OnScreen(const Unit& unit)
{
    draw_base *pDTarget = unit->GetDefaultDrawObject();
    math_point targetLoc = unit->GetPhysics()->GetLoc();
    int tLenTop = pDTarget->GetHeightOfMainRect() / 2;
    int tLenLeft = pDTarget->GetWidthOfMainRect() / 2;//getting distances to the sides from the center point
    //Grab some variables from this unit
    int uLenTop = unit->GetHeightOfMainRect() / 2;
    int uLenLeft = unit->GetWidthOfMainRect() / 2;

    //Compute collisions
    //bottom side
    if(((targetLoc.Y + tLenTop) >= (owner_ref->GetS->GetLoc().Y - uLenTop) && ((targetLoc.X + tLenLeft) >= (phys->GetLoc().X - uLenLeft))) || ((targetLoc.Y + tLenTop) >= (phys->GetLoc().Y - uLenTop) && ((targetLoc.X - tLenLeft) <= (phys->GetLoc().X + uLenLeft))))
    {
        return true;
    }
    //top side
    if(((targetLoc.Y - tLenTop) <= (phys->GetLoc().Y + uLenTop) && ((targetLoc.X + tLenLeft) >= (phys->GetLoc().X - uLenLeft))) || ((targetLoc.Y + tLenTop) >= (phys->GetLoc().Y - uLenTop) && ((targetLoc.X - tLenLeft) <= (phys->GetLoc().X + uLenLeft))))
    {
        return true;
    }
    //left side
    if(((targetLoc.Y + tLenTop) >= (phys->GetLoc().Y - uLenTop) && ((targetLoc.X + tLenLeft) >= (phys->GetLoc().X - uLenLeft))) || ((targetLoc.Y - tLenTop) <= (phys->GetLoc().Y + uLenTop) && ((targetLoc.X + tLenLeft) >= (phys->GetLoc().X - uLenLeft))))
    {
        return true;
    }
    //right side
    if(((targetLoc.Y + tLenTop) >= (phys->GetLoc().Y - uLenTop) && ((targetLoc.X - tLenLeft) <= (phys->GetLoc().X + uLenLeft))) || ((targetLoc.Y - tLenTop) <= (phys->GetLoc().Y + uLenTop) && ((targetLoc.X - tLenLeft) <= (phys->GetLoc().X + uLenLeft))))
    {
        return true;
    }
    return false;
}


//Threading entry points
void_ptr helperSoundFunction(void_ptr game)
{
    Game* tmp = game;
    while(!tmp->isEngineClosing())
    {
        tmp->PlaySounds();
    }
    return NULL;
}

void_ptr helperDrawFunction(void_ptr game)
{
    Game* tmp = game;
    while(!tmp->isEngineClosing())
    {
        tmp->Draw();
    }
    return NULL;
}

void_ptr helperEventsFunction(void_ptr game)
{
    Game* tmp = game;
    while(!tmp->isEngineClosing())
    {
        tmp->RunEvents();
    }
    return NULL;
}

void_ptr helperPhysicsFunction(void_ptr game)
{
    Game* tmp = game;
    while(!tmp->isEngineClosing())
    {
        tmp->RunPhysics();
    }
    return NULL;
}

void_ptr helperUnitGCFunction(void_ptr game)
{
    Game* tmp = game;
    while(!tmp->isEngineClosing())
    {
        tmp->GC();
        sleep(Game::randBinomial(Range(0, 10000)));
    }
    return NULL;
}
