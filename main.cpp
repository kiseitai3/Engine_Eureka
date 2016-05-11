#include <iostream>
#include "eureka.h"

//Prototypes
void displayTest(const char* const input, int size);

int main(int argc, char* argv[]){
    //Call runing function or test function here
    Game g(argc, argv));
    g.LoadCursors();
    return 0;
}
void displayTest(const char* const input, int size)
{
    std::cout<<"\n\r";
    for(int i = 0; i < size; i++)
    {
        std::cout << input[i];
    }
}

std::stack<fuzzy_obj> reverseOrderStack(const std::stack<fuzzy_obj>& in)
{
    std::stack<fuzzy_obj> out;
    std::stack<fuzzy_obj> In = in;
    while(!in.empty())
    {
        out.push(In.top());
        In.pop();
    }
    return out;
}
