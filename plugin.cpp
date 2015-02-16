#include "plugin.h"

Plugin::Plugin(cstr file)
{
    lib = NULL;//Pre-set the pointer to NULL in case of a failure!
    lib = openLib(file);//Attempt to load the module!
    if(!lib)//Check if the module loaded! Throw an error
        std::cout << "Error: The program attempted to load a plugin but failed to so! Make sure the program is using a valid "
            << "path to a valid dynamic library! Dynamic library can be .dll, .so, .dylib, and program specified files depending "
            << "on your Operating System and/or program settings!" << std::endl;
}

func_ptr Plugin::GetFunction(const std::string& name)
{
    /*This method will extract a pointer to a function. Since func_ptr is already defined as a
    pointer to a function with a variable number of arguments, I do not have to define what those
    arguments are and therefore the pointer can refer to any function! Beware that you must
    know what the arguments for those functions are or you risk sinking the Titanic!
    */
    return (func_ptr)loadF(lib, name.c_str());//Extract a pointer to a function within the library!
}

bool Plugin::isLoaded() const
{
    return lib; //Let us know if the library loaded!
}

Plugin::~Plugin()
{
    closeLib(lib);
}
