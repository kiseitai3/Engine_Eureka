#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED
#include <iostream>
#include <string>
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


//For compatibility purposes, I looked up the compiler os detection macros at
//http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system#Howtodetecttheoperatingsystemtype

#if defined(__linux__) || defined(__APPLE__)//Under unix systems
#include <dlfcn.h>
#define openLib dlopen
#define loadF dlsym
#define closeLib dlclose
#define lib_ptr void_ptr
#define fcn_ptr void_ptr

#elif defined(__CYGWIN__)//Under unix in Windows
#include <dlfcn.h>
#define openLib dlopen
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

class Plugin
{
public:
    Plugin(const char* file);//Load the module!
    func_ptr GetFunction(const std::string& name);//Extract a pointer to a function within the library!
    bool isLoaded() const;//Let us know if the library loaded!
    ~Plugin();
private:
    lib_ptr lib;
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // PLUGIN_H_INCLUDED
