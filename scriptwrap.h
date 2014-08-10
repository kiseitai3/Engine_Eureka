#ifndef SCRIPTWRAP_H_INCLUDED
#define SCRIPTWRAP_H_INCLUDED
#include <vector>
#include "game.h"
#include "pywrap.h"
#include "luawrap.h"
#include "typedefs.h"

#define ERROR_EXEC_FAILURE 1
#define ERROR_UNKNOWN_ARG 2
#define ERROR_NOT_A_SCRIPT 3

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

class ScriptWrap
{
public:
    ScriptWrap(const char* file);
    //Execution methods with all of the overload that are necessary to execute most script functions.
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, int& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, bool& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, char& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, std::string& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, void_ptr& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, std::vector<fuzzy_obj>& response);

    bool isInitialized() const;
    ~ScriptWrap();

private:
    Pywrap* pyScript;
    LuaWrap* luaScript;
    byte scriptMode;//Uses the FileTypes enum to set the mode. This
};

#endif // SCRIPTWRAP_H_INCLUDED
