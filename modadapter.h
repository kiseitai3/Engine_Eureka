#ifndef MODADAPTER_H_INCLUDED
#define MODADAPTER_H_INCLUDED
<<<<<<< HEAD

#include "plugin.h"
#include "scriptwrap.h"
#include "typedefs.h"
#include "game.h"
#include "data_base.h"
=======
#include "eureka.h"
#include "plugin.h"
#include "scriptwrap.h"
#include "typedefs.h"

>>>>>>> TheIllusiveMan
#include "conversion.h"
#include <vector>
#include <string>

<<<<<<< HEAD
=======
//Engine name space macro
//ENGINE_NAMESPACE


>>>>>>> TheIllusiveMan
struct Node
{
    std::string Name;
    func_ptr Ptr;
    Node(const std::string& name, func_ptr ptr = NULL);
};

class ModAdapter
{
public:
    //typedefs and enums
<<<<<<< HEAD
    typedef Node func;
    ModAdapter(const char* file);
    void RegisterFunction(const std::string& name);
    void RegisterFunctionFromFile(const char* file);
    bool isFuncRegistered(const std::string& name) const;
    int RunFunctions(Game *owner) const;
    ~ModAdapter();
private:
    ScriptWrap *sModule;
    Plugin *dlModule;
    std::vector<func> fList;
};


=======
    ModAdapter(const char* file, Game* owner);
    void RegisterFunction(const std::string& name);
    void RegisterFunctionFromFile(const char* file);
    bool isFuncRegistered(const std::string& name) const;
    void UnregisterFunction(const std::string& name);
    int RunFunctions() const;
    ~ModAdapter();
private:
    Game* owner_ref;
    ScriptWrap *sModule;
    Plugin *dlModule;
    std::vector<Node> fList;
};

void_ptr helperModFunction(void_ptr obj);

//End of namespace macro
//ENGINE_NAMESPACE_END
>>>>>>> TheIllusiveMan
#endif // MODADAPTER_H_INCLUDED
