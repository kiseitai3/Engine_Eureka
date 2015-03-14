//#define EUREKA_EXPORT
#include "unitmanager.h"
#include "eureka.h"
#include "rand_generators.h"
#include "data_base.h"

//Engine name space macro
//ENGINE_NAMESPACE


UnitNode::UnitNode(Game* owner, char type, int BlitOrder, math_point loc, cstr file, bool hero, bool hasBars)
{
    Type = type;
    pData = NULL;
    pData = new Unit(BlitOrder, file, loc, owner->GetRenderer(), owner->GetMainTimer(), hero, hasBars);
}

UnitNode::UnitNode()
{
    Type = 'n';
    pData = NULL;
}

UnitManager::UnitManager(Game* owner)
{
    owner_ref = owner;
    mutex_id = owner->SpawnMutex();
    UnitNode* tmp = new UnitNode();
    gameObjects.insert(0, tmp);
}

void UnitManager::SetSDLEvent(SDL_Event* ev)
{
    event = ev;
}

size_t UnitManager::SpawnUnit(const char type, int BlitOrder, math_point loc, std::string file, bool hero, bool hasBars)
{
    size_t id = hasher();
    UnitNode* tmp =  NULL;
    owner_ref->LockMutex(mutex_id);
    UnitNode *pUnit = new UnitNode(owner_ref, type, BlitOrder, loc, file.c_str(), hero, hasBars);
    while(gameObjects.search(id, tmp))
    {
        id = hasher();
    }
    gameObjects.insert(id, pUnit);
    owner_ref->UnlockMutex(mutex_id);
    return id;
}

std::vector<size_t> UnitManager::SpawnUnitFromList(cstr file, int BlitOrder)
{
    //Vars needed to initialize a Unit
    std::vector<size_t> ids;
    bool hero = false;
    bool hasBars = false;
    math_point loc;
    char type = 'u';
    std::string unitFile = "";
    //Load file
    data_base f(file);
    size_t count = f.GetIntFromData("unit_count");
    size_t id = hasher();
    std::string unit = "";

    //Let's load the objects
    for(size_t i = 0; i < count; i++)
    {
        //Let's lock the container
        unit = "unit_" + intToStr(i);
        //Load constants
        hero = f.GetIntFromData(unit + "_hero");
        hasBars = f.GetIntFromData(unit + "_bars");
        loc.X = f.GetIntFromData(unit + "_X");
        loc.Y = f.GetIntFromData(unit + "_Y");
        loc.Z = f.GetIntFromData(unit + "_Z");
        type = f.GetStrFromData(unit + "_type")[0];
        unitFile = f.GetStrFromData(unit + "_file");
        //Create object
        UnitNode* hasID;
        UnitNode* tmp = new UnitNode(owner_ref, type, BlitOrder, loc, file, hero, hasBars);
        tmp->pData->SetID(id);
        owner_ref->LockMutex(mutex_id);
        while(gameObjects.search(id, hasID))
        {
            id = hasher();
        }
        gameObjects.insert(id, tmp);
        ids.push_back(id);
        //Release the container
        owner_ref->UnlockMutex(mutex_id);
    }
    //Return set of ids
    return ids;
}

size_t UnitManager::SpawnUnitFromFile(cstr file, int BlitOrder)
{
    bool hero = false;
    bool hasBars = false;
    math_point loc;
    char type = 'u';
    std::string unitFile = "";
    //Load file
    data_base f(file);
    size_t count = f.GetIntFromData("unit_count");
    size_t id = hasher();
    std::string unit = "";

    //Let's lock the container
    owner_ref->LockMutex(mutex_id);
    unit = "unit_";
    //Load constants
    hero = f.GetIntFromData(unit + "_hero");
    hasBars = f.GetIntFromData(unit + "_bars");
    loc.X = f.GetIntFromData(unit + "_X");
    loc.Y = f.GetIntFromData(unit + "_Y");
    loc.Z = f.GetIntFromData(unit + "_Z");
    type = f.GetStrFromData(unit + "_type")[0];
    unitFile = f.GetStrFromData(unit + "_file");
    //Create object
    UnitNode* hasID;
    UnitNode* tmp = new UnitNode(owner_ref, type, BlitOrder, loc, file, hero, hasBars);
    tmp->pData->SetID(id);
    owner_ref->LockMutex(mutex_id);
    while(gameObjects.search(id, hasID))
    {
        id = hasher();
    }
    gameObjects.insert(id, tmp);
    //Release the container
    owner_ref->UnlockMutex(mutex_id);

}

Unit& UnitManager::GetUnit(size_t id)
{
    Unit* tmp;
    owner_ref->LockMutex(mutex_id);//Lock container
    tmp = gameObjects[id]->pData;
    //owner_ref->UnlockMutex(mutex_id);//Unlock container
    return *tmp;
}

Unit& UnitManager::GetUnitByName(const std::string& name)
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
    //owner_ref->UnlockMutex(mutex_id);//Unlock container
    return *tmp;
}

Unit* UnitManager::FindNearbyUnit(Unit *pUnit)

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
    //owner_ref->UnlockMutex(mutex_id);//Unlock container
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

bool UnitManager::hasUnit(const std::string& name)
{
    Unit* tmp = NULL;
    tmp = &(GetUnitByName(name));
    if(tmp)
        return true;
    return false;
}

bool UnitManager::hasUnit(size_t id)
{
    Unit* tmp = NULL;
    tmp = &(GetUnit(id));
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
                delete (*itr)->pData;
            gameObjects.remove((*itr)->id);
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
                delete (*itr)->pData;
            gameObjects.remove((*itr)->id);
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
        if((*itr)->Type == 'p')
        {
            if((*itr)->pData)
                delete (*itr)->pData;
            gameObjects.remove((*itr)->id);
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
        if((*itr)->Type == 'o')
        {
            if((*itr)->pData)
                delete (*itr)->pData;
            gameObjects.remove((*itr)->id);
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
        if((*itr)->Type == 'u')
        {
            if((*itr)->pData)
                delete (*itr)->pData;
            gameObjects.remove((*itr)->id);
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
            delete (*itr)->pData;
        gameObjects.remove((*itr)->id);
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::RunPhysics()
{
    /*This is a more complicated method. Here, I have to run the physics of each object in respect to every
    object. Also, I have to run a couple of different physics (magnetic effects, electrical forces, and
    Newtonian forces).*/
    std::string tmp;
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

void UnitManager::DrawUnits()
{
    /*Here I handle the drawing step of the units!*/
    owner_ref->LockMutex(mutex_id);//Lock container
    std::vector<UnitNode*> tmpObjs = gameObjects.getContents();
    for(size_t i = 1; i < tmpObjs.size(); i++)
    {
        if(OnScreen(*tmpObjs[i]->pData))
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
        tmpObjs[i]->pData->ProcessKeyEvent((char*)event->key.keysym.sym);
        tmpObjs[i]->pData->ProcessMouseMovement(event->motion.xrel, event->motion.yrel);
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


bool UnitManager::OnScreen(Unit& unit)
{
    draw_base *pDTarget = unit.GetDefaultDrawObject();
    math_point targetLoc = unit.GetPhysics()->GetLoc();
    int tLenTop = pDTarget->GetHeightOfMainRect() / 2;
    int tLenLeft = pDTarget->GetWidthOfMainRect() / 2;//getting distances to the sides from the center point
    //Grab some variables from this the game viewport
    int uLenTop = owner_ref->GetScreenHeight() / 2;
    int uLenLeft = owner_ref->GetScreenWidth() / 2;

    //Compute collisions
    //bottom side
    if(((targetLoc.Y + tLenTop) >= (owner_ref->GetScreenLoc().Y - uLenTop) && ((targetLoc.X + tLenLeft) >= (owner_ref->GetScreenLoc().X - uLenLeft))) || ((targetLoc.Y + tLenTop) >= (owner_ref->GetScreenLoc().Y - uLenTop) && ((targetLoc.X - tLenLeft) <= (owner_ref->GetScreenLoc().X + uLenLeft))))
    {
        return true;
    }
    //top side
    if(((targetLoc.Y - tLenTop) <= (owner_ref->GetScreenLoc().Y + uLenTop) && ((targetLoc.X + tLenLeft) >= (owner_ref->GetScreenLoc().X - uLenLeft))) || ((targetLoc.Y + tLenTop) >= (owner_ref->GetScreenLoc().Y - uLenTop) && ((targetLoc.X - tLenLeft) <= (owner_ref->GetScreenLoc().X + uLenLeft))))
    {
        return true;
    }
    //left side
    if(((targetLoc.Y + tLenTop) >= (owner_ref->GetScreenLoc().Y - uLenTop) && ((targetLoc.X + tLenLeft) >= (owner_ref->GetScreenLoc().X - uLenLeft))) || ((targetLoc.Y - tLenTop) <= (owner_ref->GetScreenLoc().Y + uLenTop) && ((targetLoc.X + tLenLeft) >= (owner_ref->GetScreenLoc().X - uLenLeft))))
    {
        return true;
    }
    //right side
    if(((targetLoc.Y + tLenTop) >= (owner_ref->GetScreenLoc().Y - uLenTop) && ((targetLoc.X - tLenLeft) <= (owner_ref->GetScreenLoc().X + uLenLeft))) || ((targetLoc.Y - tLenTop) <= (owner_ref->GetScreenLoc().Y + uLenTop) && ((targetLoc.X - tLenLeft) <= (owner_ref->GetScreenLoc().X + uLenLeft))))
    {
        return true;
    }
    return false;
}

void UnitManager::UnlockUnit()
{
    owner_ref->UnlockMutex(mutex_id);
}

//End of namespace macro
//ENGINE_NAMESPACE_END
