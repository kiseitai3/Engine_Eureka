#define EUREKA_EXPORT
#include "luawrap.h"
#include <cmath>
#include "conversion.h"

//Engine name space macro
//ENGINE_NAMESPACE


LuaWrap::LuaWrap(const char* file)
{
    Lua = NULL;
    //Initialization of the Lua State variable
    Lua = luaL_newstate();
    luaL_openlibs(Lua);
    //Let's open the file!
    if(luaL_dofile(Lua, file))
    {
        std::cout << "Error loading Lua Script: " << file << std::endl;
    }
    path = file;

    argStack = new std::queue<fuzzy_obj>;

    hasResult = false;
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
    int errindex = 0;
    if(hasResult)
    {
        ClearResult();
    }

    //Now, let's set the function!
    lua_getglobal(Lua, funcName.c_str());
    if(!lua_isfunction(Lua, LUA_TOPITEM))
    {
        std::cout << "Error attempting to run function: " << funcName << " Lua stack size: " << lua_gettop(Lua)<<". Check that the name is a valid Lua function in the current Engine Version!"
                  << std::endl;
        return false;
    }

    lua_getglobal(Lua, "debug");
    lua_getfield(Lua, -1, "traceback");
    lua_remove(Lua, -2);
    argCount = argStack->size();
    errindex = -argCount - 2;
    lua_insert(Lua, errindex);

    //Check for the presence of arguments before deciding how to run the function!
    if(!argStack->empty())
    {
        //*Old* Let's reverse the order of the stack. A queue would have done the same job, but I like stacks!
        //It's now a queue, but to maintain the same feel as the Lua stack, I kept the name
        while(!argStack->empty())
        {
            PushToLua(Lua, argStack->front());
            argStack->pop();
        }
    }

    //Let's run the function!
    /*The following function uses a mixture of the Lua documentation (http://pgl.yoyo.org/luai/i/lua_pcall) and a stack overflow
    question about how to extract the stacktrace from the pcall execution function
    (http://stackoverflow.com/questions/12256455/print-stacktrace-from-c-code-with-embedded-lua)
    */
    errStatus = lua_pcall(Lua, argCount, LUA_MULTRET, errindex);

    //Check status code
    ErrF(Lua, errStatus);
    return true;
}

//Argument methods
void LuaWrap::AddArgument(int argument)
{
    fuzzy_obj tmp;
    tmp.number = argument;
    tmp.flag = 'i';
    argStack->push(tmp);
}

void LuaWrap::AddArgument(const std::string& argument)
{
    fuzzy_obj tmp;
    tmp.str = argument;
    tmp.flag = 's';
    argStack->push(tmp);
}

void LuaWrap::AddArgument(char argument)
{
    fuzzy_obj tmp;
    tmp.c = argument;
    tmp.flag = 'c';
    argStack->push(tmp);
}

void LuaWrap::AddArgument(double argument)
{
    fuzzy_obj tmp;
    tmp.decimal = argument;
    tmp.flag = 'd';
    argStack->push(tmp);
}

void LuaWrap::AddArgument(unsigned int argument)
{
    fuzzy_obj tmp;
    tmp.uNumber = argument;
    tmp.flag = 'u';
    argStack->push(tmp);
}

void LuaWrap::AddArgument(bool argument)
{
    fuzzy_obj tmp;
    tmp.answer = argument;
    tmp.flag = 'b';
    argStack->push(tmp);
}

void LuaWrap::AddArgument(void_ptr argument)
{
    fuzzy_obj tmp;
    tmp.ptr = argument;
    tmp.flag = 'v';
    argStack->push(tmp);
}

int LuaWrap::lua_extractInt() const
{
    if(lua_isnumber(Lua, LUA_TOPITEM))
        return lua_tointeger(Lua, LUA_TOPITEM);
    std::cout << "Warning: Lua result is not an integer. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

double LuaWrap::lua_extractDouble() const
{
    if(lua_isnumber(Lua, LUA_TOPITEM))
        return lua_tonumber(Lua, LUA_TOPITEM);
    std::cout << "Warning: Lua result is not a double. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0.0f;
}

char LuaWrap::lua_extractChar() const
{
    if(lua_isstring(Lua, LUA_TOPITEM))
        return lua_tostring(Lua, LUA_TOPITEM)[0];
    std::cout << "Warning: Lua result is not a char. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return 0;
}

std::string LuaWrap::lua_extractStr() const
{
    if(lua_isstring(Lua, LUA_TOPITEM))
        return lua_tostring(Lua, LUA_TOPITEM);
    std::cout << "Warning: Lua result is not a string. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return "";
}

bool LuaWrap::lua_extractBool() const
{
    if(lua_isboolean(Lua, LUA_TOPITEM))
        return bool(lua_tointeger(Lua, LUA_TOPITEM));
    std::cout << "Warning: Lua result is not boolean. Undefined behavior may occur! Warning in script: " << path
            << std::endl;
    return false;
}

void_ptr LuaWrap::lua_extractPtr() const
{
    return (void_ptr)lua_topointer(Lua, LUA_TOPITEM);
}

std::vector<fuzzy_obj> LuaWrap::GenerateListFromLuaTable()
{
    /*If I read the documentation correctly, lua_next empties the table and I end up cleaning the pushed key-value
    pairs, so I will flag this method as a single use method that calls clean stack and resets the state of result!
    Make sure you limit your script-engine communication such that this method is called once or the spawning
    script function is called multiple times!
    */
    std::vector<fuzzy_obj> tmp;
    lua_gettable(Lua, LUA_TOPITEM);//index of table
    size_t t = lua_tointeger(Lua, 2);
    if(lua_isnil(Lua, LUA_TOPITEM))//check the table is valid
        return tmp;

    lua_pushnil(Lua);//Push top key? http://pgl.yoyo.org/luai/i/lua_next //http://eliasdaler.wordpress.com/2013/10/20/lua_and_cpp_pt2/
    while(lua_next(Lua, t))//Obtain key-value pairs
    {
        fuzzy_obj obj;
        obj.flag = GetResultType();
        switch(obj.flag)
        {
        case 'i':
            obj.number = lua_extractInt();
            break;
        case 'd':
            obj.decimal = lua_extractDouble();
            break;
        case 'b':
            obj.answer = lua_extractBool();
            break;
        case 'c':
            obj.c = lua_extractChar();
            break;
        case 's':
            obj.str = lua_extractStr();
            break;
        case 'v':
            obj.ptr = lua_extractPtr();
            break;
        default:
            std::cout << "Error: Argument from array returned by script function is not a valid type! "
            << "Wow, the cake is a lie!" << std::endl;
        }
        tmp.push_back(obj);
    }

    //Let's clean the stack from the new items
    ClearResult();
    hasResult = false;//Flag the result as destroyed
    //Return copy of the vector!
    return tmp;
}

bool LuaWrap::isResultVoid() const
{
    return lua_isnoneornil(Lua, lua_gettop(Lua));
}

char LuaWrap::GetResultType() const
{
    if(lua_isboolean(Lua, LUA_TOPITEM))
        return 'b';

    if(lua_isnumber(Lua, LUA_TOPITEM))
    {
        if(lua_tonumber(Lua, LUA_TOPITEM)/round(lua_tonumber(Lua, LUA_TOPITEM)))
            return 'i';
        else
            return 'd';
    }

    if(lua_isstring(Lua, LUA_TOPITEM))
    {
        if(std::string(lua_tostring(Lua, LUA_TOPITEM)).length() == 1)
            return 'c';
        return 's';
    }

    return 'v';
}

lua_State* LuaWrap::GetInternalState() const
{
    return Lua;
}

bool LuaWrap::ClearArgs(int n)
{
    //Here I pop all of the elements in the Argument Stack!
    //Passing -1 should yield a full stack cleanup because stackSize + n != argStack->size()--; use LUA_ERASE_ALL
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
    //This method also clears all other items from the stack!
    lua_pop(Lua, lua_gettop(Lua));
}

size_t LuaWrap::GetResultSize() const
{
    //This method is not 100% safe if the lua table conforms to some special cases
    //(http://stackoverflow.com/questions/4815588/request-a-lua-table-size-in-c-before-iterating-it)!
    return lua_rawlen(Lua, LUA_TOPITEM);
}
//Private methods
int LuaWrap::traceback(lua_State* lua)
{
    /*This method was built using the different responses to a stack overflow question!
    http://stackoverflow.com/questions/12256455/print-stacktrace-from-c-code-with-embedded-lua
    */
    if (!lua_isstring(lua, 1))  /* 'message' not a string? */
        return 1;  /* keep it intact */
    lua_getfield(lua, LUA_REGISTRYINDEX, "debug");//LUA_GLOBALINDEX for lua 5.1 and LUA_REGISTRYINDEX for > 5.2
                                    //http://stackoverflow.com/questions/10087226/lua-5-2-lua-globalsindex-alternative
    if (!lua_istable(lua, -1))
    {
        std::cerr << lua_tostring(lua, LUA_TOPITEM) << std::endl;/*Get item string for the stacktrace!*/
        lua_pop(lua, 1);
        return 1;
    }
    lua_getfield(lua, -1, "traceback");
    if (!lua_isfunction(lua, -1))
    {
        std::cerr << lua_tostring(lua, LUA_TOPITEM) << std::endl;/*Get item string for the stacktrace!*/
        lua_pop(lua, 2);
        return 1;
    }
    lua_pushvalue(lua, 1);  /* pass error message */
    lua_pushinteger(lua, 2);  /* skip this function and traceback */
    lua_call(lua, 2, 1);  /* call debug.traceback */
    std::cerr << lua_tostring(lua, LUA_TOPITEM) << std::endl;/*Get item string for the stacktrace!*/
    return 1;
}

void LuaWrap::ErrF(lua_State* result, int status)
{
    /*This method will leave a notice in the standard output so the user checks the stacktrace.
    It will let you know the status code regardless of whether a stacktrace was made for the
    script!
    */
    if(status && !lua_isnil(result, -1))
    {
        //std::cerr << lua_tostring(Lua, LUA_TOPITEM) << std::endl;/*Get item string for the stacktrace!*/
        traceback(result);
        /*Leave an error notice in the standard output!*/
        std::cout << "Error executing Lua script! Execution ended with status: " << status <<std::endl
                  <<"For more information, check the Lua documentation and the standard error stacktrace (cerr) if any!"
                  << std::endl;
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
        lua_pushinteger(Lua, reinterpret_cast<unsigned int>(obj.uNumber));
        break;
    default:
        std::cout << "Warning: Argument object does not contain a valid flag or is empty (flag = 'n')! This object has the flag "
                  << obj.flag << "!" << std::endl;
    }
}

//End of namespace macro
//ENGINE_NAMESPACE_END
