#ifndef MODADAPTER_H_INCLUDED
#define MODADAPTER_H_INCLUDED

#include "plugin.h"
#include "scriptwrap.h"
#include "typedefs.h"
#include "game.h"
#include "data_base.h"
#include "conversion.h"
#include <vector>
#include <string>

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


#endif // MODADAPTER_H_INCLUDED
