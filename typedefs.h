#ifndef TYPEDEFS_H_INCLUDED
#define TYPEDEFS_H_INCLUDED

typedef unsigned char byte;
typedef void* void_ptr;
typedef void (*func_ptr)(...);
typedef const char* cstr;

//Struct
typedef struct psudo_type{
        char flag; //use the flags i, d, b, s, c, u, v, l, n for int, double, bool, string, char, unsigned (int or char), void pointer, blob and empty respectively.
        int number;//can store an integer
        unsigned int uNumber;//can store an unsigned integer or unsigned char!
        double decimal;//can store a floating point number
        bool answer;//can store the answer of a boolean function (true or false)
        std::string str;//can store a string or character array
        std::string blob;
        char c;
        void_ptr ptr;
        psudo_type()
        {
            flag = 'n';
            number = 0; answer = false; c = 0; str = ""; blob = ""; uNumber = 0; decimal = 0.0f; ptr = NULL;// var init!
        }
    }unknown_return, fuzzy_obj;//The purpose of this struct is to have a type in which I can store an unknown return from a python or lua function without having to write overloads for each c++ functions that will handle a return from python.

//Enums
enum FileTypes
{
    NONE, VAR, XML, LUA, PYTHON, SQLITE, MYSQL
};
#endif // TYPEDEFS_H_INCLUDED
