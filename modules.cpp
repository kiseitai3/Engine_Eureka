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
    modules.push_back(NULL);
}

ModuleSystem::~ModuleSystem()
{
    owner_ref->LockMutex(mutex_id);
    for(size_t i = 0; i < modules.size(); i++)
    {
        if(modules[i].module)
        {
            if(modules[i].threaded)//If a thread is using this object, let's close it before attempting to erase it.
                owner_ref->CloseThread(modules[i].thread_id);
            delete modules[i].module;
        }
    }
    owner_ref->UnlockMutex(mutex_id);
    owner_ref->DeleteMutex(mutex_id);
}

size_t ModuleSystem::RegisterModule(cstr file, bool threaded)
{
    size_t mod_id = 0;
    Module* tmp = new Module(*owner_ref, file, threaded)
    owner_ref->LockMutex(mutex_id);
    modules.push_back(tmp);
    mod_id = modules.size() - 1;
    if(threaded)
    {
        tmp->thread_id = owner_ref->SpawnThread(&helperModFunction, (void_ptr)tmp);
    }
    owner_ref->UnlockMutex(mutex_id);
    return mod_id;
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
    for(size_t i = 0; i < modules.size(); i++)
    {
        if(modules[mod_id] && !modules[mod_id]->threaded)
            modules[mod_id]->module->RunFunctions();
    }
    owner_ref->UnlockMutex(mutex_id);
}
