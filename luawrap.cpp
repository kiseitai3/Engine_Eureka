#include "luawrap.h"
#include <cmath>

LuaWrap::LuaWrap(const char* file)
{
    Lua = NULL;
    //Initialization of the Lua State variable
    Lua = lua_open();
    luaL_openlibs(Lua);
    //Let's open the file!
    if(luaL_loadfile(Lua, file))
    {
        std::cout << "Error loading Lua Script: " << file << std::endl;
    }
    path = file;
}


LuaWrap::~LuaWrap()
{
    //Let's delete the Lua State and Argument Stack pointers
    if(Lua)
        lua_close(Lua);

    if(argStack)
        delete argStack;
}

bool LuaWrap::executeFunction(const std::string& funcName)
{
    size_t argCount = 0;
    int errStatus = 0;
    if(hasResult)
    {
        ClearResult();
    }

    if(argStack->size())
    {
        ClearArgs(LUA_ERASE_ALL);
    }

    //Now, let's set the function!
    lua_setglobal(Lua, funcName.c_str());
    if(lua_isfunction(L, LUA_TOPITEM))
    {
        std::cout << "Error attempting to run function: " << funcName <<". Check that the name is a valid Lua function in the current Engine Version!"
                  << std::end;
        return false;
    }

    //Check for the presence of arguments before deciding how to run the function!
    if(!argStack->empty())
    {
        //Let's reverse the order of the stack. A queue would have done the same job, but I like stacks!
        argStack = reverseOrderStack(*argStack);
        argCount = argStack->size();
        while(!argStack->empty())
        {
            PushToLua(argStack->top())
            argStack->pop();
        }
    }

    //Let's run the function!
    /*The following function uses a mixture of the Lua documentation (http://pgl.yoyo.org/luai/i/lua_pcall) and a stack overflow
    question about how to extract the stacktrace from the pcall execution function
    (http://stackoverflow.com/questions/12256455/print-stacktrace-from-c-code-with-embedded-lua)
    */
    errStatus = lua_pcall(Lua, argCount, LUA_MULTRET, lua_gettop() - LUA_TOPITEM - argCount);

    //Check status code
    ErrF(Lua, errStatus);
}

//Argument methods
void LuaWrap::AddArgument(int argument)
{
    fuzzy_obj tmp;
    tmp.number = argument;
    tmp.flag = 'i';
    argStack.push(tmp);
}

void LuaWrap::AddArgument(const std::string& argument)
{
    fuzzy_obj tmp;
    tmp.str = argument;
    tmp.flag = 's';
    argStack.push(tmp);
}

void LuaWrap::AddArgument(char argument)
{
    fuzzy_obj tmp;
    tmp.c = argument;
    tmp.flag = 'c';
    argStack.push(tmp);
}

void LuaWrap::AddArgument(double argument)
{
    fuzzy_obj tmp;
    tmp.decimal = argument;
    tmp.flag = 'd';
    argStack.push(tmp);
}

void LuaWrap::AddArgument(unsigned int argument)
{
    fuzzy_obj tmp;
    tmp.uNumber = argument;
    tmp.flag = 'u';
    argStack.push(tmp);
}

void LuaWrap::AddArgument(bool argument)
{
    fuzzy_obj tmp;
    tmp.answer = argument;
    tmp.flag = 'b';
    argStack.push(tmp);
}

int LuaWrap::lua_extractInt(lua_State* results) const
{
    if(lua_isnumber(results, LUA_TOPITEM))
        return lua_tointeger(results, LUA_TOPITEM);
    std::cout << "Warning: Lua result is not an integer. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

double LuaWrap::lua_extractDouble(lua_State* results) const
{
    if(lua_isnumber(results, LUA_TOPITEM))
        return lua_tonumber(results, LUA_TOPITEM);
    std::cout << "Warning: Lua result is not a double. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0.0f;
}

char LuaWrap::lua_extractChar(lua_State* results) const
{
    if(lua_isstring(results, LUA_TOPITEM))
        return lua_tostring(results, LUA_TOPITEM)[0];
    std::cout << "Warning: Lua result is not a char. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

std::string LuaWrap::lua_extractStr(lua_State* results) const
{
    if(lua_isstring(results, LUA_TOPITEM))
        return lua_tostring(results, LUA_TOPITEM);
    std::cout << "Warning: Lua result is not a string. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return "";
}

bool LuaWrap::lua_extractBool(lua_State* results) const
{
    if(lua_isboolean(results, LUA_TOPITEM))
        return bool(lua_tointeger(results, LUA_TOPITEM));
    std::cout << "Warning: Lua result is not boolean. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return false
}

void* LuaWrap::lua_extractPtr(lua_State* results) const
{
    return lua_topointer(results, LUA_TOPITEM);
}

int LuaWrap::lua_extractIntFromList(lua_State* results, unsigned int index) const
{
    if(lua_istable(results, LUA_TOPITEM))
        return lua_tointeger(results, lua_gettop(Lua) - index);
    std::cout << "Warning: Lua result is not an array. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

bool LuaWrap::lua_extractBoolFromList(lua_State* results, unsigned int index) const
{
    if(lua_istable(results, LUA_TOPITEM))
        return bool(lua_tointeger(results, lua_gettop(Lua) - index));
    std::cout << "Warning: Lua result is not an array. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return false;
}

char LuaWrap::lua_extractCharFromList(lua_State* results, unsigned int index) const
{
    if(lua_istable(results, LUA_TOPITEM))
        return lua_tostring(results, lua_gettop(Lua) - index)[0];
    std::cout << "Warning: Lua result is not an array. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

double LuaWrap::lua_extractDoubleFromList(lua_State* results, unsigned int index) const
{
    if(lua_istable(results, LUA_TOPITEM))
        return lua_tonumber(results, lua_gettop(Lua) - index);
    std::cout << "Warning: Lua result is not an array. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0.0f;
}

int LuaWrap::lua_extractStrFromList(lua_State* results, unsigned int index) const
{
    if(lua_istable(results, LUA_TOPITEM))
        return lua_tostring(results, lua_gettop(Lua) - index);
    std::cout << "Warning: Lua result is not an array. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return "";
}

void* LuaWrap::lua_extractPtrFromList(lua_State* results, unsigned int index) const
{
    if(lua_istable(results, LUA_TOPITEM))
        return lua_topointer(results, lua_gettop(Lua) - index);
    std::cout << "Warning: Lua result is not an array. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return NULL;
}

bool LuaWrap::isResultVoid() const
{
    return lua_isnoneornil(Lua, lua_gettop(Lua));
}

char LuaWrap::getResultType(size_t& length = 0) const
{
    if(lua_isboolean(Lua))
        return 'b';

    if(lua_isnumber(Lua))
    {
        if(lua_tonumber(Lua, LUA_TOPITEM)/round(lua_tonumber(Lua, LUA_TOPITEM)))
            return 'i';
        else
            return 'd';
    }

    if(lua_isstring(Lua, LUA_TOPITEM))
    {
        length = std::string(lua_tostring(Lua, LUA_TOPITEM)).length();
        return 's';
    }

    return 'v';
}

bool LuaWrap::ClearArgs(int n)
{
    //Here I pop all of the elements in the Argument Stack!
    size_t stackSize = argStack->size();
    while(!argStack->empty() && (stackSize - n) != argStack->size())
    {
        argStack->pop();
    }
}

void LuaWrap::ClearResult()
{
    //This method is a just-in-case method. It may never get used.
    //This method will pop the result from the lua state stack!
    lua_pop(Lua, LUA_TOPITEM);
}

//Private methods
int LuaWrap::traceback(lua_State* lua)
{
    /*This method was built using the different responses to a stack overflow question!
    http://stackoverflow.com/questions/12256455/print-stacktrace-from-c-code-with-embedded-lua
    */
    if (!lua_isstring(L, 1))  /* 'message' not a string? */
        return 1;  /* keep it intact */
    lua_getfield(L, LUA_GLOBALSINDEX, "debug");
    if (!lua_istable(L, -1))
    {
        std::cerr << lua_tostring(Lua, LUA_TOPITEM) << std::endl;/*Get item string for the stacktrace!*/
        lua_pop(L, 1);
        return 1;
    }
    lua_getfield(L, -1, "traceback");
    if (!lua_isfunction(L, -1))
    {
        std::cerr << lua_tostring(Lua, LUA_TOPITEM) << std::endl;/*Get item string for the stacktrace!*/
        lua_pop(L, 2);
        return 1;
    }
    lua_pushvalue(L, 1);  /* pass error message */
    lua_pushinteger(L, 2);  /* skip this function and traceback */
    lua_call(L, 2, 1);  /* call debug.traceback */
    std::cerr << lua_tostring(Lua, LUA_TOPITEM) << std::endl;/*Get item string for the stacktrace!*/
    return 1;
}

void LuaWrap::ErrF(lua_State* result, int status)
{
    /*This method will leave a notice in the standard output so the user checks the stacktrace.
    It will let you know the status code regardless of whether a stacktrace was made for the
    script!
    */
    if(status)
    {
        std::cerr << lua_tostring(Lua, LUA_TOPITEM) << std::endl;/*Get item string for the stacktrace!*/
        /*Leave an error notice in the standard output!*/
        std::cout << "Error executing Lua script! Execution ended with status: " << status <<std::endl
                  <<"For more information, check the Lua documentation and the standard error stacktrace (cerr) if any!
    }
}

void LuaWrap::PushToLua(lua_State* lua, const fuzzy_obj& obj)
{
    switch(obj.flag)
    {
    case 'i':
        lua_pushinteger(Lua, obj.number);
        break;
    case 'd':
        lua_pushnumber(Lua, obj.decimal);
        break;
    case 'b':
        lua_pushboolean(Lua, obj.answer);
        break;
    case 's':
        lua_pushstring(Lua, obj.str.c_str());
        break;
    case 'c':
        lua_pushinteger(Lua, (int)obj.c);
        break;
    case 'u':
        lua_pushinteger(Lua, reinterpret_cast<unsigned integer>(obj.uNumber));
        break;
    default:
        std::cout << "Warning: Argument object does not contain a valid flag or is empty (flag = 'n')! This object has the flag "
                  << obj.flag << "!" << std::endl;
    }
}