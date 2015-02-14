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
    UnitManager(Game* owner, SDL_Event& events);
    ~UnitManager();

    //Setters
    size_t SpawnUnit(const char type, int BlitOrder, math_point loc, std::string file, bool hero, bool hasBars);
    void SpawnUnitFromList(cstr file, int BlitOrder);

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
    void GC();//Units garbage collector

private:
    Game* owner_ref;
    SDL_Event* event;
    BinarySearchTree<size_t, UnitNode*> gameObjects;
    size_t mutex_id;

    //Methods
    bool OnScreen(const Unit& unit) const;

};

void_ptr helperSoundFunction(void_ptr game);
void_ptr helperDrawFunction(void_ptr game);
void_ptr helperPhysicsFunction(void_ptr game);
void_ptr helperEventsFunction(void_ptr game);
void_ptr helperUnitGCFunction(void_ptr game);

#endif // UNITMANAGER_H_INCLUDED
