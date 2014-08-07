#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
enum FileTypes
{
    VAR, XML, LUA, PYTHON
};

typedef struct psudo_type{
        char flag; //use the flags i, d, b, s, c, u, n for int, double, bool, string, char, unsigned (int or char) and empty respectively.
        int number;//can store an integer
        unsigned int uNumber;//can store an unsigned integer or unsigned char!
        double decimal;//can store a floating point number
        bool answer;//can store the answer of a boolean function (true or false)
        std::string str;//can store a string or character array
        char c;
        psudo_type()
        {
            flag = 'n';
        }
    }unknown_return, fuzzy_obj;//The purpose of this struct is to have a type in which I can store an unknown return from a python or lua function without having to write overloads for each c++ functions that will handle a return from python.

//Global functions


#endif // GAME_H_INCLUDED
