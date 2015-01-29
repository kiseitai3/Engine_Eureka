#ifndef MODADAPTER_H_INCLUDED
#define MODADAPTER_H_INCLUDED
#include "game.h"
#include "plugin.h"
#include "scriptwrap.h"
#include "typedefs.h"
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
    ModAdapter(const char* file, Game& owner);
    void RegisterFunction(const std::string& name);
    void RegisterFunctionFromFile(const char* file);
    bool isFuncRegistered(const std::string& name) const;
    int RunFunctions() const;
    ~ModAdapter();
private:
    static Game* owner_ref;
    ScriptWrap *sModule;
    Plugin *dlModule;
    std::vector<func> fList;
};

void_ptr helperModFunction(void_ptr obj);

#endif // MODADAPTER_H_INCLUDED
