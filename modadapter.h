#ifndef MODADAPTER_H_INCLUDED
#define MODADAPTER_H_INCLUDED
#include "eureka.h"
#include "plugin.h"
#include "scriptwrap.h"
#include "typedefs.h"

#include "conversion.h"
#include <vector>
#include <string>

//Engine name space macro
//ENGINE_NAMESPACE


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
#endif // MODADAPTER_H_INCLUDED
