#include <iostream>
#include <string>
#include "../plugin.h"

int main()
{
    func_ptr hello = NULL;
    int res;
    Plugin plug("Core.dll");

    std::cout << "Loading dynamic library: " << (plug.isLoaded() ? "Yes" : "No") << std::endl;
    std::cout << "Obtaining function pointer: " << ((bool)(hello = plug.GetFunction("printHello")) ? "Yes" : "No") << std::endl;
    std::cout << "Executing function..." << std::endl;
    hello();

    std::cin >> res;
}
