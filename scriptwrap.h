#ifndef SCRIPTWRAP_H_INCLUDED
#define SCRIPTWRAP_H_INCLUDED
#include <vector>
<<<<<<< HEAD
#include "game.h"
#include "pywrap.h"
#include "luawrap.h"
#include "typedefs.h"

#define ERROR_EXEC_FAILURE 1
#define ERROR_UNKNOWN_ARG 2
#define ERROR_NOT_A_SCRIPT 3
=======
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE
>>>>>>> TheIllusiveMan

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
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, double& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, std::string& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, void_ptr& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, std::vector<fuzzy_obj>& response);

    //The following methods are a way for users to add arguments manually instead of having to pass a prebuilt vector of
    //fuzzy_objs!
    //Argument methods
    void AddArgument (int argument);
    void AddArgument (const std::string& argument);
    void AddArgument (char argument);
    void AddArgument (double argument);
    void AddArgument(unsigned int argument);
    void AddArgument (bool argument);
    void AddArgument (void_ptr argument);

    void ClearArgs(size_t arg_size);
    bool isInitialized() const;
    ~ScriptWrap();

    //Static variables/ Dummy variables
    static const std::vector<fuzzy_obj> NO_ARGS;

    //Operator overloads
    //void operator=(const Pywrap)

private:
    Pywrap* pyScript;
    LuaWrap* luaScript;
    byte scriptMode;//Uses the FileTypes enum to set the mode.
};

class LuaWrap;
class Pywrap;

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
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, double& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, std::string& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, void_ptr& response);
    int executeFunction(const std::string& name, const std::vector<fuzzy_obj>& args, std::vector<fuzzy_obj>& response);

    //The following methods are a way for users to add arguments manually instead of having to pass a prebuilt vector of
    //fuzzy_objs!
    //Argument methods
    void AddArgument (int argument);
    void AddArgument (const std::string& argument);
    void AddArgument (char argument);
    void AddArgument (double argument);
    void AddArgument(unsigned int argument);
    void AddArgument (bool argument);
    void AddArgument (void_ptr argument);

    void ClearArgs(size_t arg_size);
    bool isInitialized() const;
    ~ScriptWrap();

    //Static variables/ Dummy variables
    static const std::vector<fuzzy_obj> NO_ARGS;

    //Operator overloads
    //void operator=(const Pywrap)

private:
    Pywrap* pyScript;
    LuaWrap* luaScript;
    byte scriptMode;//Uses the FileTypes enum to set the mode.
};

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // SCRIPTWRAP_H_INCLUDED
