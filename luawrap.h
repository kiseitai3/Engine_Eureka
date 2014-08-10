#ifndef LUAWRAP_H_INCLUDED
#define LUAWRAP_H_INCLUDED
#include <lua.hpp>
#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include "game.h"
#include "globals.h"

#define LUA_TOPITEM -1
#define LUA_ERASE_ALL -1

class LuaWrap
{
public:
    LuaWrap(const char* file);
    bool executeFunction(const std::string& funcName);
    bool ClearArgs(int n);
    bool isResultVoid() const;
    char GetResultType(lua_State* result, size_t length = 0) const;//Returns i, b, d, s for int, boolean, double, and string. Use the length parameter to distinguish between char and string.
    void ClearResult();
    lua_State* GetInternalState() const;
    size_t GetArgCount() const;
    size_t GetResultSize() const;

    ~LuaWrap();

    //return value extraction methods
    /*All functions in this block take care of the extraction of a C type from a generalized object
    or list! :D*/
    int lua_extractInt(lua_State *results) const;
    bool lua_extractBool(lua_State *results) const;
    char lua_extractChar(lua_State *results) const;
    std::string lua_extractStr(lua_State *results) const;
    double lua_extractDouble(lua_State *results) const;
    void *lua_extractPtr(lua_State *results) const;
    std::vector<fuzzy_obj> GenerateListFromLuaTable();

    //Argument methods
    void AddArgument (int argument);
    void AddArgument (const std::string& argument);
    void AddArgument (char argument);
    void AddArgument (double argument);
    void AddArgument(unsigned int argument);
    void AddArgument (bool argument);

private:
    //methods
    void PushToLua(lua_State* lua, const fuzzy_obj& obj);
    void ErrF(lua_State* result, int status);
    static int traceback(lua_State* lua);
    //vars
    lua_State* Lua;
    std::string path;
    bool hasResult;
    std::stack<fuzzy_obj> *argStack; /*Once upon a time, I learned how to use stacks, which I used to make packs of elegant code without hacks!
                                    Seriously though, first time I find a very good reason to use stacks in this engine! Since Lua uses stacks
                                    to run and pass arguments to functions, there's no other way I can pass arguments that is as elegant as the
                                    implemented scheme!*/
};


#endif // LUAWRAP_H_INCLUDED
