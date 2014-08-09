#ifndef SCRIPTWRAP_H_INCLUDED
#define SCRIPTWRAP_H_INCLUDED
#include <vector>
#include "game.h"
#include "pywrap.h"
#include "luawrap.h"
#include "typedefs.h"

class ScriptWrap
{
public:
    ScriptWrap(const char* file);
    //Execution methods with all of the overload that are necessary to execute most script functions.
    void executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args);
    bool executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args);
    char executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args);
    std::string executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args);
    void* executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args);
    std::vector<fuzzy_obj> executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args);

    bool isInitialized() const;
    ~ScriptWrap();

private:
    Pywrap* pyScript;
    LuaWrap* luaScript;
    bool execSuccess;
    byte scriptMode;//Uses the FileTypes enum to set the mode. This
};

#endif // SCRIPTWRAP_H_INCLUDED
