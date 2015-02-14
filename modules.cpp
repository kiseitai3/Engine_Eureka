#include "modules.h"

ModuleNode::ModuleNode(Game& owner, cstr file, bool independent, size_t pthread_id)
{
    module = new ModAdapter(file, owner);
    threaded = independent;
    thread_id = pthread_id;
}

ModuleSystem::ModuleSystem(Game& owner)
{
    owner_ref = &owner;
    mutex_id = owner.SpawnMutex();
    modules.insert(0, NULL);
}

ModuleSystem::~ModuleSystem()
{
    owner_ref->LockMutex(mutex_id);
    std::vector<Module*> tmpObjs = modules.getContents();
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        if(tmpObjs[i]->module)
        {
            if(tmpObjs[i]->threaded)//If a thread is using this object, let's close it before attempting to erase it.
                owner_ref->CloseThread(tmpObjs[i]->thread_id);
            delete (*itr)->module;
        }
    }
    owner_ref->UnlockMutex(mutex_id);
    owner_ref->DeleteMutex(mutex_id);
}

size_t ModuleSystem::RegisterModule(cstr file, bool threaded)
{
    Module* tmp = new Module(*owner_ref, file, threaded)
    owner_ref->LockMutex(mutex_id);
    tmp->mod_id = generateID();//Create an id
    modules.insert(tmp->mod_id, tmp);//add to list
    if(threaded)//Prepare module to run in separate thread
    {
        tmp->thread_id = owner_ref->SpawnThread(&helperModFunction, (void_ptr)tmp);
    }
    owner_ref->UnlockMutex(mutex_id);
    return tmp->mod_id;
}

void ModuleSystem::RegisterFunction(const std::string& name, size_t mod_id)
{
    owner_ref->LockMutex(mutex_id);
    modules[mod_id]->module->RegisterFunction(name);
    owner_ref->UnlockMutex(mutex_id);
}

void ModuleSystem::RegisterFunctionFromFile(const char* file, size_t mod_id)
{
    owner_ref->LockMutex(mutex_id);
    modules[mod_id]->module->RegisterFunctionFromFile(file);
    owner_ref->UnlockMutex(mutex_id);
}

bool ModuleSystem::isFuncRegistered(const std::string& name, size_t mod_id) const
{
    owner_ref->LockMutex(mutex_id);
    bool ans = modules[mod_id]->module->isFuncRegistered(file);
    owner_ref->UnlockMutex(mutex_id);
    return ans;
}

size_t ModuleSystem::GetModuleThreadID(size_t mod_id) const
{
    owner_ref->LockMutex(mutex_id);
    size_t ans = modules[mod_id]->thread_id;
    owner_ref->UnlockMutex(mutex_id);
    return ans;
}

bool ModuleSystem::isModuleIndependent(size_t mod_id) const
{
    owner_ref->LockMutex(mutex_id);
    bool ans = modules[mod_id]->threaded;
    owner_ref->UnlockMutex(mutex_id);
    return ans;
}

void ModuleSystem::MarkModuleAsIndependent(size_t mod_id)
{
    owner_ref->LockMutex(mutex_id);
    modules[mod_id]->threaded = true;
    owner_ref->UnlockMutex(mutex_id);
}

int ModuleSystem::RunFunctionsInModule(size_t mod_id) const
{
    size_t ans = 0;
    owner_ref->LockMutex(mutex_id);
    if(!modules[mod_id]->threaded)
        ans = modules[mod_id]->module->RunFunctions();
    owner_ref->UnlockMutex(mutex_id);
    return ans;
}

void ModuleSystem::RunAllFunctions() const
{
    owner_ref->LockMutex(mutex_id);
    std::vector<Module*> tmpObjs = modules.getContents();
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        if(tmpObjs[i] && !tmpObjs[i]->threaded)
            tmpObjs[i]->module->RunFunctions();
    }
    owner_ref->UnlockMutex(mutex_id);
}

size_t ModuleSystem::generateID()
{
    size_t id = Game::randUniform((0, Game::GetMaxValueSizeT())) ;//Get a random number
    //Continue getting a new random number if the id is already taken!
    while(hasID(id, target))
    {
        id = Game::randUniform((0, Game::GetMaxValueSizeT()));
    }

    return id;
}

bool ModuleSystem::hasID(size_t id)
{
    std::vector<Module*> tmpObjs = modules.getContents();
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        if(tmpObjs[i]->mod_id == id)
            return true;
    }
    //If nothing was found
    return false;
}

