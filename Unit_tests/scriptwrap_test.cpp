#include <iostream>
#include <string>
#include "../scriptwrap.h"

int main()
{
    int math_res = 0;
    int res = 0;
    //Python
    ScriptWrap script("pyMod.py");

    //Initial Hellow World
    std::cout << "Hi! The next hello will come from a program loaded into this program!" << std::endl;
    script.executeFunction("printHello", ScriptWrap::NO_ARGS);
    script.executeFunction("printFollowUp", ScriptWrap::NO_ARGS);
    //Math
    std::cout << "Now we ask Python to calculate some math for us because I'm lazy! :P" << std::endl;
    script.AddArgument(-3);
    script.AddArgument(5);
    script.executeFunction("Add", ScriptWrap::NO_ARGS, math_res);
    std::cout << "The result of -3 + 5: " << math_res << std::endl;

    //Factorial
    script.AddArgument(4);
    script.executeFunction("fact", ScriptWrap::NO_ARGS, math_res);
    std::cout << "The factorial of 4 is: " << math_res << std::endl;


    //Lua
    ScriptWrap script2("luaMod.lua");
    //Initial Hellow World
    std::cout << "Hi! The next hello will come from a program loaded into this program!" << std::endl;
    script2.executeFunction("printHello", ScriptWrap::NO_ARGS);
    //Math
    std::cout << "Now we ask Python to calculate some math for us because I'm lazy! :P" << std::endl;
    script2.AddArgument(-3);
    script2.AddArgument(5);
    script2.executeFunction("Add", ScriptWrap::NO_ARGS, math_res);
    std::cout << "The result of -3 + 5: " << math_res << std::endl;

    //Factorial
    script2.AddArgument(4);
    script2.executeFunction("fact", ScriptWrap::NO_ARGS, math_res);
    std::cout << "The factorial of 4 is: " << math_res << std::endl;

    std::cin >> res;

    return 0;
}
