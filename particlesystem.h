#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED
#include <string>
#include <pthread.h>
#include <queue>
#include "unit.h"
#include "draw_base.h"
#include "physics.h"
#include "BST.h"
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


class ParticleNode;
void traversalRender(const size_t& id, ParticleNode*& node);//Renders each element as it traverses

class Particle: public Physics
{
public:
    //ctors and dtor
    Particle(Game* owner, cstr file, const math_point& location, draw_base* refParticle = NULL);
    ~Particle();

    //Render
    void RenderParticle();

    //Overrides
    void OverrideParticlePos(const math_point& newPos);

    //Getters
    draw_base* GetParticle();
    bool isDead();

    //Setters
    void SetParticle(draw_base* other);

private:
    draw_base* particle;
    Game* owner_ref;
    Timer* t;
    bool dead;
    bool clone;
    int life;
};

class ParticleNode
{
public:
    //ctors and dtor
    ParticleNode(Game* owner, cstr file, const math_point& loc, char axis, double force = 0);
    ParticleNode(Game* owner, cstr file, const math_point& reference, const math_point& loc, char axis, double force = 0);
    ~ParticleNode();

    //Render
    void RenderParticles();
    void RenderParticlesByProximity(const math_point& loc, size_t radius = 100);

    //Setter
    void SetInitialForce(double force);

private:
    Particle* particle;
    Game* owner_ref;
    const math_point* refLoc;//reference location
    math_point spawnLoc;//Location to spawn particles on object
    math_point finalLoc;//Actual location
    cstr file_path;
    std::queue<Particle*> particles;
    size_t particleMaxCount;
    char xis;
    double initForce;
    bool stickToUnit;
    bool singleParticle;

    //Methods
    //Generator
    void GenerateParticle();
};

class ParticleCluster
{
public:
    //ctors and dtor
    ParticleCluster(Game* owner);
    ~ParticleCluster();

    //Getters
    size_t GetParticleCount();

    //Setter
    void SetInitialForce(size_t id, double force);

    //Render
    void RenderParticleById(size_t id);
    void RenderAllParticles();
    void RenderParticlesByProximity(const math_point& loc, size_t radius = 100);

    //Register
    size_t RegisterParticle(const math_point& loc, cstr particle, char axis = 'a', double force = 0, const Unit* unit = NULL);

    //Delete
    void DeleteParticle(size_t id);
    void DeleteAllParticles();

private:
    Game* owner_ref;
    BinarySearchTree<size_t, ParticleNode*> particleSet;
};

class EUREKA ParticleSystem
{
public:
    //Constructors and Destructor
    ParticleSystem(Game* owner);
    ~ParticleSystem();

    //Resgister
    size_t RegisterUnitParticle(Unit& target, const math_point& loc, cstr particle, char axis = 'a');
    size_t RegisterGameParticle(const math_point& loc, cstr particle, char axis = 'a');

    //Render
    void RenderParticleFromUnit(Unit& unit, size_t id);
    void RenderAllParticlesFromUnit(Unit& unit);
    void RenderUnitParticlesByProximity(Unit& unit, size_t radius = 100);
    void RenderGameParticlesByProximity(const math_point& loc, size_t radius = 100);
    void RenderAllParticlesFromGame();

    //Delete
    void DeleteUnitParticle(Unit& unit, size_t id);
    void DeleteGameParticle(size_t id);
    void ClearUnitParticles();
    void ClearGameParticles();
    void ClearAllParticles();

    //Getters
    size_t GetUnitParticleCount(Unit& unit);
    size_t GetGameParticleCount();

    //Setter
    void SetInitialForceOfUnitParticle(Unit& unit, size_t id, double force);
    void SetInitialForceOfGameParticle(size_t id, double force);


private:
    Game* owner_ref;
    BinarySearchTree<Unit*, ParticleCluster*> unitCluster;
    ParticleCluster* gameCluster;
    size_t mutex_id_unit, mutex_id_game;
    size_t cond_id;
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // PARTICLESYSTEM_H_INCLUDED
