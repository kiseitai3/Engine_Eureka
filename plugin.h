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
#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED
#include <iostream>
#include <string>
#include "def.h"

//Engine name space macro
//ENGINE_NAMESPACE


//For compatibility purposes, I looked up the compiler os detection macros at
//http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system#Howtodetecttheoperatingsystemtype

#if defined(__linux__) || defined(__APPLE__)//Under unix systems
#include <dlfcn.h>
#define openLib(a) dlopen(a,RTLD_LAZY)
#define loadF dlsym
#define closeLib dlclose
#define lib_ptr void_ptr
#define fcn_ptr void_ptr

#elif defined(__CYGWIN__)//Under unix in Windows
#include <dlfcn.h>
#define openLib dlopen(a,RTLD_LAZY)
#define loadF dlsym
#define closeLib dlclose
#define lib_ptr void_ptr
#define fcn_ptr void_ptr

#elif defined(__WIN32__) || defined(__WIN64__)//Under Windows systems
#include <windows.h>
#define openLib LoadLibrary
#define loadF GetProcAddress
#define closeLib FreeLibrary
#define lib_ptr HMODULE
#define fcn_ptr FARPROC
#endif

/** \brief Plugin. This class is a simple interface for loading modules, obtaining an address to a library symbol, and unloading.
 *  The macros defined in this header attempt to standardize and abstract away the specific dynamic library loading mechanisms
 *  of the underlying architecture! The macros define openLib, loadF, and closeLib, which are used internally by this class.
 */

class Plugin
{
public:
    Plugin(const char* file);//Load the module!
    void_ptr GetFunction(const std::string& name);//Extract a pointer to a function within the library!
    bool isLoaded() const;//Let us know if the library loaded!
    ~Plugin();
private:
    lib_ptr lib;
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // PLUGIN_H_INCLUDED
