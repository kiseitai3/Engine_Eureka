#ifndef PHYSICSSYSTEM_H_INCLUDED
#define PHYSICSSYSTEM_H_INCLUDED
#include "game.h"
#include "physics.h"
#include "typedefs.h"

class PhysicsSystem
{
public:
    //ctors and dtor
    PhysicsSystem(Game& owner);
    ~PhysicsSystem();

    //Register
    void RegisterUnit

private:
    std::vector<Unit*> physObjects;
    Game* owner_ref;
};


#endif // PHYSICSSYSTEM_H_INCLUDED
