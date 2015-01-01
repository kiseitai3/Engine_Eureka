#include "particlesystem.h"

void traversalRender(const size_t& id, const ParticleNode& node)
{
    node.RenderParticles();
}

/*Particle*/
Particle::Particle(Game& owner, cstr file, const math_point location, draw_base* refParticle) : Physics()
{
    data_base settings(file);
    particle = NULL;
    if(settings.GetStateOfInternalBuffer())//Let's make sure we could actually load the particle file
    {
        if(!Load_Physics(settings.GetStrFromData("phys_file").c_str()))//Let's make sure we loaded the proper physics
        {
            std::cout << "Error opening physics settings file! Make sure the file in " << settings.GetStrFromData("phys_file").c_str() <<
            " exists! Object physics are uninitialized and could cause erratic behaviors and crashes!" << std::endl;
        }

        //Let's create an actual managed texture object
        /*The following part will check to see if we have to reference a previously loaded texture or if we have to
        allocate a brand new texture!*/
        if(!refParticle)
        {
            particle = new draw_base();
            clone = false;
        }
        else
        {
           particle = refParticle;
           clone = true;
        }

        if(particle && !refParticle)//If allocation was successful, try to load settings for the particle texture
        {
            particle.Load_Texture(settings.GetStrFromData("texture_file").c_str(), owner.GetRenderer(), settings.GetIntFromData("fps"));
        }
        else
        {
            std::cout << "Allocation of texture object for this particle failed! *Tears* Expect something to go awfully wrong, like a sig_seg! *More Tears*"
            << std::endl;
        }

        //Now, let's set the lifetime of the particle
        life = settings.GetIntFromData("life"); //milliseconds
    }
    loc = location;
    owner_ref = &owner;
    dead = false;

    //Set up timer
    t = NULL;
    if(life > 0)//0 = infinite life
    {
        t = new Timer;
        if(t)
            t->start();
        else
            std::cout << "Failed to create timer for Particle!" << std::endl;
    }

}

void Particle::RenderParticle()//Let's draw the texture
{
    particle->apply_surface(loc.X, loc.Y, owner_ref->GetRenderer());
    if(t && t.get_ticks() >= life)
    {
        dead = true;
    }
}

void Particle::OverrideParticlePos(const math_point& newPos)
{
    loc = newPos;
}

draw_base* Particle::GetParticle()
{
    return particle;
}

bool Particle::isDead()
{
    return dead;
}

void Particle::SetParticle(draw_base* other)
{
    particle = other;
}

Particle::~Particle()
{
    if(particle && !clone)
        delete particle;
    if(t)
        delete t;
}

/*ParticleNode*/
ParticleNode::ParticleNode(Game& owner, cstr file, const math_point& loc, double force)
{
    data_base settings(file);
    particle = NULL;
    refLoc = NULL;
    owner_ref = &owner;
    file_path = file;
    stickToUnit = false;
    singleParticle = false;

    if(settings.GetStateOfInternalBuffer())
    {
        particleMaxCount = settings.GetIntFromData("max_count");
        stickToUnit = settings.GetIntFromData("on_unit");
    }

    particle = new Particle(owner, file, loc);
    if(!particle)//Check allocation status
    {
        std::cout << "Failed to allocate and initialize Particle object!" << std::endl;
    }

    spawnLoc = loc;
    initForce = force;
}

ParticleNode::ParticleNode(Game& owner, cstr file, const math_point& reference, const math_point& loc, double force)
{
    ParticleNode(owner, file, loc, force);
    refLoc = &loc;
}

void ParticleNode::GenerateParticle()
{
    Particle* tmp =  NULL;
    if(particles.size() < particleMaxCount)//Fill the queue with new particles
    {
        tmp =  new Particle(owner_ref, file_path, finalLoc, particle->GetParticle());
        tmp->SetForceCount(initForce);
        particles.push(tmp);
    }
    else//If the queue is filled, clean it if possible
    {
        Particle* current = particles.top();
        if(current->isDead())
        {
            delete current;
            tmp = new Particle(owner_ref, file_path, finalLoc, particle->GetParticle());
            tmp->SetForceCount(initForce)
            particles.push(tmp);
        }
        else
        {
            particles.push(current);
        }
    }
}

void ParticleNode::RenderParticles()
{
    Particle* current = NULL;
    if(stickToUnit)//Let's update the spawn position
    {
        finalLoc.X = refLoc->X + spawnLoc.X;
        finalLoc.Y = refLoc->Y + spawnLoc.Y;
        finalLoc.Z = refLoc->Z + spawnLoc.Z;
    }

    //Clean the queue of expired particles and generate new ones
    GenerateParticle();

    //Render all of the particles
    for(size_t i = 0; i < particles.size(); i++)
    {
        current = particles.top();
        //Render particle and return it to the queue if it is not NULL
        if(current)
        {
            current->RenderParticle();
            particles.push(current);
        }
    }
}

void ParticleNode::RenderParticlesByProximity(const math_point& loc, size_t radius)
{
    Particle* current = NULL;
    //Render all of the particles that are close to the position of interest
    for(size_t i = 0; i < particles.size(); i++)
    {
        current = particles.top();
        //Render particle and return it to the queue if it is not NULL
        if(current && (CalculateDistance(current->GetLoc(), loc) <= radius))
        {
            current->RenderParticle();
            particles.push(current);
        }
        else if(current)
            particles.push(current);
    }
}

void ParticleNode::SetInitialForce(double force)
{
    initForce = force;
}

ParticleNode::~ParticleNode()
{
    //Clean the queue
    while(particles.size() > 0)
    {
        Particle* tmp = particles.top();
        if(tmp)
            delete tmp;
    }

    //Delete reference particle
    if(particle)
        delete particle;
}

/*particleCluster*/
ParticleCluster::ParticleCluster(Game& owner)
{
    owner_ref = &owner;
    searchLoc = NULL;
    searchRadius = 0;
}

ParticleCluster::~ParticleCluster()
{

}

size_t ParticleCluster::GetParticlecount()
{
    return particleSet.size();
}

void ParticleCluster::SetInitialForce(size_t id, double force)
{
    particleSet[id].SetInitialForce(force);
}

void ParticleCluster::RenderParticleById(size_t id)
{
    particleSet[id].RenderParticles();
}

void ParticleCluster::RenderAllParticles()
{
    particleSet.preorder(traversalRender);
}

void ParticleCluster::RenderParticlesByProximity(const math_point& loc, size_t radius)
{
    std::vector<ParticleNode&> tmp = particleSet.getContents();
    for(size_t i = 0; i < tmp.size(); i++)
    {
        tmp[i].RenderParticleByProximity(loc, radius);
    }
}

size_t ParticleCluster::RegisterParticle(const math_point& loc, cstr particle, double force, const Unit* unit)
{
    size_t id = 0;
    ParticleNode holder(*owner_ref, particle, loc, force);
    //Let's generate a random number that is available in the BST
    do
    {
        id = Game::hasher();
    }
    while(particleSet.search(id, holder));

    if(unit)//If the particles are 'owned' by a Unit object, include the reference loc
        particleSet.insert(id, ParticleNode(*owner_ref, particle, unit->GetPhysics()->GetLoc(), loc, force));
    else
        particleSet.insert(id, ParticleNode(*owner_ref, particle, loc, force));
    return id;//Return the key to access this particle node in the cluster
}

void ParticleCluster::DeleteParticle(size_t id)
{
    particleSet.remove(id);
}

void ParticleCluster::DeleteAllParticles()
{
    particleSet.clear();
}

/*ParticleSystem*/
ParticleSystem::ParticleSystem(Game& owner)
{
    owner_ref = &owner;
    gameCluster = new ParticleCluster(&owner);
    mutex_id_unit = owner.SpawnMutex();
    mutex_id_game = owner.SpawnMutex();
    cond_id =  owner.SpawnCondVar();
}

ParticleSystem::~ParticleSystem()
{
    if(gameCluster)
        delete gameCluster;
}

size_t ParticleSystem::RegisterUnitParticle(const Unit& target, const math_point& loc, cstr particle)
{
    ParticleCluster holder(*owner_ref);
    owner_ref->LockMutex(mutex_id_unit);//Lock the mutex to prevent any weird access to our datamembers
    if(unitCluster.search(&target, holder))
    {
        return unitCluster[&target].RegisterParticle(loc, particle, 0, &target);
    }
    else
    {
        unitCluster.insert(&target, ParticleCluster(*owner_ref));
        return unitCluster[&target].RegisterParticle(loc, particle, 0, &target);
    }
    owner_ref->UnlockMutex(mutex_id_unit);//Release the mutex
}

size_t ParticleSystem::RegisterGameParticle(const math_point& loc, cstr particle)
{
    owner_ref->LockMutex(mutex_id_game);//Lock the mutex to prevent any weird access to our datamembers
    return gameCluster.RegisterParticle(loc, particle);
    owner_ref->UnlockMutex(mutex_id_game);//Release the mutex
}

void ParticleSystem::RenderParticleFromUnit(const Unit& unit, size_t id)
{
    ParticleCluster holder(*owner_ref);
    owner_ref->LockMutex(mutex_id_unit);//Lock the mutex to prevent any weird access to our datamembers
    if(unitCluster.search(&target, holder))
    {
        unitCluster[&unit].RenderParticleById(id);
    }
    owner_ref->UnlockMutex(mutex_id_unit);//Release the mutex
}

void ParticleSystem::RenderAllParticlesFromUnit(const Unit& unit)
{
    ParticleCluster holder(*owner_ref);
    owner_ref->LockMutex(mutex_id_unit);//Lock the mutex to prevent any weird access to our datamembers
    if(unitCluster.search(&target, holder))
    {
        unitCluster[&unit].RenderAllParticles();
    }
    owner_ref->UnlockMutex(mutex_id_unit);//Release the mutex
}

void ParticleSystem::RenderAllParticlesFromGame()
{
    owner_ref->LockMutex(mutex_id_game);//Lock the mutex to prevent any weird access to our datamembers
    gameCluster->RenderAllParticles();
    owner_ref->UnlockMutex(mutex_id_game);//Release the mutex
}

void ParticleSystem::RenderUnitParticlesByProximity(const Unit& unit, size_t radius)
{
    owner_ref->LockMutex(mutex_id_unit);//Lock the mutex to prevent any weird access to our datamembers
    unitCluster[&unit].RenderParticlesByProximity(unit.GetPhysics()->GetLoc(), radius);
    owner_ref->UnlockMutex(mutex_id_unit);//Release the mutex
}

void ParticleSystem::RenderGameParticlesByProximity(const math_point& loc, size_t radius)
{
    owner_ref->LockMutex(mutex_id_game);//Lock the mutex to prevent any weird access to our datamembers
    gameCluster->RenderParticlesByProximity(loc, radius);
    owner_ref->UnlockMutex(mutex_id_game);//Release the mutex
}

void ParticleSystem::DeleteUnitParticle(const Unit& unit, size_t id)
{
    owner_ref->LockMutex(mutex_id_unit);//Lock the mutex to prevent any weird access to our datamembers
    unitCluster[&unit].DeleteParticle(id);
    owner_ref->UnlockMutex(mutex_id_unit);//Release the mutex
}

void ParticleSystem::DeleteGameParticle(size_t id)
{
    owner_ref->LockMutex(mutex_id_game);//Lock the mutex to prevent any weird access to our datamembers
    gameCluster.DeleteParticle(id);
    owner_ref->UnlockMutex(mutex_id_game);//Release the mutex
}

void ParticleSystem::ClearUnitParticles()
{
    owner_ref->LockMutex(mutex_id_unit);//Lock the mutex to prevent any weird access to our datamembers
    unitCluster.clear();
    owner_ref->UnlockMutex(mutex_id_unit);//Release the mutex
}

void ParticleSystem::ClearGameParticles()
{
    owner_ref->LockMutex(mutex_id_game);//Lock the mutex to prevent any weird access to our datamembers
    gameCluster.DeleteAllParticles();
    owner_ref->UnlockMutex(mutex_id_game);//Release the mutex
}

size_t ParticleSystem::GetGameParticleCount()
{
    owner_ref->LockMutex(mutex_id_game);//Lock the mutex to prevent any weird access to our datamembers
    return gameCluster.GetParticleCount();
    owner_ref->UnlockMutex(mutex_id_game);//Release the mutex
}

size_t ParticleSystem::GetUnitParticleCount(const Unit& unit)
{
    owner_ref->LockMutex(mutex_id_unit);//Lock the mutex to prevent any weird access to our datamembers
    return unitCluster[&unit].GetParticleCount();
    owner_ref->UnlockMutex(mutex_id_unit);//Release the mutex
}

void PaticleSystem::SetInitialForceOfUnitParticle(const Unit& unit, size_t id, double force)
{
    owner_ref->LockMutex(mutex_id_unit);//Lock the mutex to prevent any weird access to our datamembers
    unitCluster[&unit].SetInitialForce(id, force);
    owner_ref->UnlockMutex(mutex_id_unit);//Release the mutex
}

void ParticleSystem::SetInitialForceOfGameParticle(size_t id, double force)
{
    owner_ref->LockMutex(mutex_id_game);//Lock the mutex to prevent any weird access to our datamembers
    gameCluster.SetInitialForce(id, force);
    owner_ref->UnlockMutex(mutex_id_game);//Release the mutex
}
