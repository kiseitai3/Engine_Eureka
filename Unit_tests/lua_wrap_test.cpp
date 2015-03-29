#include <iostream>
#include <string>
#include "../luawrap.h"

int main()
{
    int res;
    int math_res = 0;
    LuaWrap luaModule("luaMod.lua");

    //Initial Hellow World
    std::cout << "Hi! The next hello will come from a program loaded into this program!" << std::endl;
    luaModule.executeFunction("printHello");
    //Math
    std::cout << "Now we ask Lua to calculate some math for us because I'm lazy! :P" << std::endl;
    luaModule.AddArgument(-3);
    luaModule.AddArgument(5);
    luaModule.executeFunction("Add");
    if(luaModule.GetResultType() == 'i')
        std::cout << "The result of -3 + 5: " << luaModule.lua_extractInt() << std::endl;

    //Factorial
    luaModule.AddArgument(4);
    luaModule.executeFunction("fact");
    if(luaModule.GetResultType() == 'i')
        std::cout << "The factorial of 4 is: " << luaModule.lua_extractInt() << std::endl;

    //Blocking instruction
    std::cin >> res;

    return 0;
}
