#ifndef LUAWRAP_H_INCLUDED
#define LUAWRAP_H_INCLUDED
#include <lua.hpp>
#include <string>
#include <iostream>
<<<<<<< HEAD
#include <stack>
#include <vector>
#include "game.h"
#include "globals.h"
=======
#include <queue>
#include <vector>
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE

>>>>>>> TheIllusiveMan

#define LUA_TOPITEM -1
#define LUA_ERASE_ALL -1

<<<<<<< HEAD
class LuaWrap
=======
class EUREKA LuaWrap
>>>>>>> TheIllusiveMan
{
public:
    LuaWrap(const char* file);
    bool executeFunction(const std::string& funcName);
    bool ClearArgs(int n);
    bool isResultVoid() const;
<<<<<<< HEAD
    char GetResultType(lua_State* result) const;//Returns i, b, d, s for int, boolean, double, and string.
=======
    char GetResultType() const;//Returns i, b, d, s for int, boolean, double, and string.
>>>>>>> TheIllusiveMan
    void ClearResult();
    lua_State* GetInternalState() const;
    size_t GetArgCount() const;
    size_t GetResultSize() const;

    ~LuaWrap();

    //return value extraction methods
    /*All functions in this block take care of the extraction of a C type from a generalized object
    or list! :D*/
<<<<<<< HEAD
    int lua_extractInt(lua_State *results) const;
    bool lua_extractBool(lua_State *results) const;
    char lua_extractChar(lua_State *results) const;
    std::string lua_extractStr(lua_State *results) const;
    double lua_extractDouble(lua_State *results) const;
    void_ptr lua_extractPtr(lua_State *results) const;
=======
    int lua_extractInt() const;
    bool lua_extractBool() const;
    char lua_extractChar() const;
    std::string lua_extractStr() const;
    double lua_extractDouble() const;
    void_ptr lua_extractPtr() const;
>>>>>>> TheIllusiveMan
    std::vector<fuzzy_obj> GenerateListFromLuaTable();

    //Argument methods
    void AddArgument (int argument);
    void AddArgument (const std::string& argument);
    void AddArgument (char argument);
    void AddArgument (double argument);
    void AddArgument(unsigned int argument);
    void AddArgument (bool argument);
    void AddArgument (void_ptr argument);

private:
    //methods
    void PushToLua(lua_State* lua, const fuzzy_obj& obj);
    void ErrF(lua_State* result, int status);
    static int traceback(lua_State* lua);
    //vars
    lua_State* Lua;
    std::string path;
    bool hasResult;
<<<<<<< HEAD
    std::stack<fuzzy_obj> *argStack; /*Once upon a time, I learned how to use stacks, which I used to make packs of elegant code without hacks!
                                    Seriously though, first time I find a very good reason to use stacks in this engine! Since Lua uses stacks
                                    to run and pass arguments to functions, there's no other way I can pass arguments that is as elegant as the
                                    implemented scheme!*/
};


=======
    std::queue<fuzzy_obj> *argStack; /*Once upon a time, I learned how to use stacks, which I used to make packs of elegant code without hacks!
                                    Seriously though, first time I find a very good reason to use stacks in this engine! Since Lua uses stacks
                                    to run and pass arguments to functions, there's no other way I can pass arguments that is as elegant as the
                                    implemented scheme!*//*Ha! Joke's on me! I switched to a queue!*/
};


//End of namespace macro
//ENGINE_NAMESPACE_END
>>>>>>> TheIllusiveMan
#endif // LUAWRAP_H_INCLUDED
