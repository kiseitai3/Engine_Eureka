#include <iostream>
#include <vector>
#include "../data_base.h"

/*This class is highly tested since my thesis project and open source project.
What I am testing here is mostly the new feature of loading a file by passing
a const char pointer that is tagged with the buffer directive. Normally, passing
the const char* to the constructor meant passing a file path, but the new feature
allows loading a file by passing the the contents from a memory buffer!*/
int main()
{
    std::string contents = data_base::BUFFER;
     contents += "test = 1; test2 = 2.1; test3 = Hello World!;\0";
    data_base tmp(contents.c_str());
    std::cout << tmp.GetIntFromData("test") << std::endl;
    std::cout << tmp.GetValueFromData("test2") << std::endl;
    std::cout << tmp.GetStrFromData("test3") << std::endl;
    return 0;
}
