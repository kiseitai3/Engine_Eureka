#ifndef MODULES_H_INCLUDED
#define MODULES_H_INCLUDED
#include "modadapter.h"
#include "typedefs.h"

typedef struct ModuleNode
{
    ModAdapter* module;
    size_t thread_id;
    size_t mod_id;
    bool threaded;

    ModuleNode(cstr file, bool independent = false, size_t pthread_id = 0);
}Module;

class ModuleSystem
{
public:
    //ctors and dtor
    ModuleSystem(Game* owner);
    ~ModuleSystem();

    //Module
    size_t RegisterModule(cstr file, bool threaded = false);
    void RegisterFunction(const std::string& name, size_t mod_id);
    void RegisterFunctionFromFile(const char* file, size_t mod_id);

    //Getter
    bool isFuncRegistered(const std::string& name, size_t mod_id) const;
    size_t GetModuleThreadID(size_t mod_id) const;
    bool isModuleIndependent(size_t mod_id) const;

    //Setter
    void MarkModuleAsIndependent(size_t mod_id);//This method is hard to interpret but the idea is that some modules register their own separate threads

    //Execution
    int RunFunctionsInModule(size_t mod_id) const;
    void RunAllFunctions()const;
private:
    BinarySearchTree<size_t, Module*> modules;
    Game* owner_ref;
    size_t mutex_id;

    //Methods
    size_t generateID();
    bool hasID(size_t id);
};


#endif // MODULES_H_INCLUDED
