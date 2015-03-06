#ifndef UNITMANAGER_H_INCLUDED
#define UNITMANAGER_H_INCLUDED
#include "unit.h"
#include "BST.h"
#include "typedefs.h"


struct UnitNode
{
    Unit* pData;
    char Type;
    size_t id;

    //ctor
    UnitNode(Game* owner, char type, int BlitOrder, math_point loc, cstr file, bool hero, bool hasBars);
    UnitNode();
};

class UnitManager
{
public:
    //ctors and dtor
    UnitManager(Game* owner);
    ~UnitManager();

    //Setters
    size_t SpawnUnit(const char type, int BlitOrder, math_point loc, std::string file, bool hero, bool hasBars);
    size_t SpawnUnitFromFile(cstr file);
    std::vector<size_t> SpawnUnitFromList(cstr file, int BlitOrder);
    void SetSDLEvent(SDL_Event* ev);

    //Getter
    Unit& GetUnit(size_t id);
    Unit& GetUnitByName(const std::string& name);
    Unit* FindNearbyUnit(Unit *pUnit);
    bool hasUnit(const std::string& name);
    bool hasUnit(size_t id);

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
    void DrawUnits();
    void RunEvents();
    void PlaySounds();
    void GC();//Units garbage collector
    void UnlockUnit();

private:
    Game* owner_ref;
    SDL_Event* event;
    BinarySearchTree<size_t, UnitNode*> gameObjects;
    size_t mutex_id;

    //Methods
    bool OnScreen(Unit& unit);

};

void_ptr helperSoundFunction(void_ptr game);
void_ptr helperPhysicsFunction(void_ptr game);
void_ptr helperEventsFunction(void_ptr game);
void_ptr helperUnitGCFunction(void_ptr game);

#endif // UNITMANAGER_H_INCLUDED
