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
    owner_ref->LockMutex(mutex_id);
    UnitNode *pUnit = new UnitNode(*owner_ref, type, BlitOrder, loc, file, hero, hasBars);
    gameObjects.push_back(pUnit);
    size_t id = gameObjects.size() - 1;
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
    std::string unit = "";

    //Let's load the objects
    for(size_t i = 0; i < count; i++)
    {
         //Let's lock the container
        owner_ref->LockMutex(mutex_id);
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
        UnitNode* tmp = new UnitNode(*owner_ref, type, BlitOrder, loc, unitFile.c_str(), hero, hasBars);
        gameObjects.push_back(tmp);
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

    for(size_t i = gameObjects.size(); i > 0; i--)
    {
        tmp = gameObjects[i]->pData;
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
    for(size_t i = gameUnits.size(); i > 0; i--)
    {
        tmp = gameUnits[i]->pData;
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
    for(std::vector<UnitNode*>::iterator itr = (gameObjects.begin()++); itr <= gameObjects.end(); itr++)
    {
        if((*itr)->pData == &unit)
        {
            if((*itr)->pData)
                delete (*itr)->pData
            gameObjects.erase(itr);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteUnitByName(const std::string& name)
{
    owner_ref->LockMutex(mutex_id);//Lock container
    for(std::vector<UnitNode*>::iterator itr = (gameObjects.begin()++); itr <= gameObjects.end(); itr++)
    {
        if((*itr)->pData->GetName() == name)
        {
            if((*itr)->pData)
                delete (*itr)->pData
            gameObjects.erase(itr);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteUnitByID(size_t id)
{
    UnitNode* tmp = NULL;
    owner_ref->LockMutex(mutex_id);//Lock container
    tmp = gameObjects[id];
    DeleteUnit(*tmp->pData);
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteAllProjectiles()
{
    owner_ref->LockMutex(mutex_id);//Lock container
    for(std::vector<UnitNode*>::iterator itr = (gameObjects.begin()++); itr <= gameObjects.end(); itr++)
    {
        if((*itr)->type == 'p')
        {
            if((*itr)->pData)
                delete (*itr)->pData
            gameObjects.erase(itr);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteAllGameObjects()
{
    owner_ref->LockMutex(mutex_id);//Lock container
    for(std::vector<UnitNode*>::iterator itr = (gameObjects.begin()++); itr <= gameObjects.end(); itr++)
    {
        if((*itr)->type == 'o')
        {
            if((*itr)->pData)
                delete (*itr)->pData
            gameObjects.erase(itr);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteAllUnits()
{
    owner_ref->LockMutex(mutex_id);//Lock container
    for(std::vector<UnitNode*>::iterator itr = (gameObjects.begin()++); itr <= gameObjects.end(); itr++)
    {
        if((*itr)->type == 'u')
        {
            if((*itr)->pData)
                delete (*itr)->pData
            gameObjects.erase(itr);
        }
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::DeleteAll()
{
    owner_ref->LockMutex(mutex_id);//Lock container
    for(std::vector<UnitNode*>::iterator itr = (gameObjects.begin()++); itr <= gameObjects.end(); itr++)
    {
        if((*itr)->pData)
            delete (*itr)->pData
            gameObjects.erase(itr);
    }
    owner_ref->UnlockMutex(mutex_id);//Unlock container
}

void UnitManager::RunPhysics()
{

}
