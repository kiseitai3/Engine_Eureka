#ifndef UNITMANAGER_H_INCLUDED
#define UNITMANAGER_H_INCLUDED
#include "game.h"
#include "typedefs.h"


struct UnitNode
{
    Unit* pData;
    char Type;

    //ctor
    UnitNode(Game& owner, char type, int BlitOrder, math_point loc, cstr file, bool hero, bool hasBars);
    UnitNode();
};

class UnitManager
{
public:
    //ctors and dtor
    UnitManager(Game& owner, SDL_Event& events);
    ~UnitManager();

    //Setters
    size_t SpawnUnit(char type, math_point loc, cstr file, bool hero = false, bool hasBars = false);
    void SpawnUnitFromList(cstr file);

    //Getter
    Unit& GetUnit(size_t id) const;
    Unit& GetUnitByName(const std::string& name) const;
    Unit* FindNearbyUnit(Unit *pUnit) const;
    bool hasUnit(const std::string& name) const;
    bool hasUnit(size_t id) const;

    //Delete
    void DeleteUnit(Unit& unit);
    void DeleteUnitByID(size_t id);
    void DeleteUnitByName(const std::string& name);
    void DeleteAllProjectiles();
    void DeleteAllGameObjects();
    void DeleteAllUnits();
    void DeleteAll();

    //Execution
    void RunPhysics();
    void Draw();
    void RunEvents();
    void PlaySounds();

private:
    Game* owner_ref;
    SDL_Event* event;
    std::vector<UnitNode*> gameObjects;
    size_t mutex_id;
};

void_ptr helperSoundFunction(void_ptr game);
void_ptr helperDrawFunction(void_ptr game);
void_ptr helperPhysicsFunction(void_ptr game);
void_ptr helperEventsFunction(void_ptr game);

#endif // UNITMANAGER_H_INCLUDED
