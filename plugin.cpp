/*
    Copyright (C) 2015 Luis M. Santos
    Contact: luismigue1234@hotmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "plugin.h"

//Engine name space macro
//ENGINE_NAMESPACE


Plugin::Plugin(cstr file)
{
    lib = NULL;//Pre-set the pointer to NULL in case of a failure!
    std::cout << __FILE__ << ":" << __func__ << ":" << std::dec << __LINE__ << ": " << "Attempting to load library: " << file << std::endl;
    lib = openLib(file);//Attempt to load the module!
    if(!lib)//Check if the module loaded! Throw an error
        std::cout << __FILE__ << ":" << __func__ << ":" << std::dec << __LINE__ << ": " << "Error: The program attempted to load a plugin but failed to do so! Make sure the program is using a valid "
            << "path to a valid dynamic library! Dynamic library can be .dll, .so, .dylib, and program specified files depending "
            << "on your Operating System and/or program settings!" << std::endl;
}

void_ptr Plugin::GetFunction(const std::string& name)
{
    /*This method will extract a pointer to a function. Since func_ptr is already defined as a
    pointer to a function with a variable number of arguments, I do not have to define what those
    arguments are and therefore the pointer can refer to any function! Beware that you must
    know what the arguments for those functions are or you risk sinking the Titanic!
    */
    return loadF(lib, name.c_str());//Extract a pointer to a function within the library!
}

bool Plugin::isLoaded() const
{
    return lib; //Let us know if the library loaded!
}

Plugin::~Plugin()
{
    closeLib(lib);
}

//End of namespace macro
//ENGINE_NAMESPACE_END
