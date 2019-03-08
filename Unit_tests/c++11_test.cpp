#include <iostream>
#include <vector>

template<typename A>
using opaque = A;

template<typename A>
using opaqueF = void (*) (A& val);

template<typename A>
void printVal(A& v)
{
    std::cout << v << std::endl;
}

int main()
{
    //templated aliases
    float val = 132.5;
    opaque<char> myval = 132;
    std::cout << myval << std::endl;
    opaqueF<float> printfunc = printVal<float>;
    printfunc(val);

    //vector instantiation
    /*int* x = new int(5);
    std::vector<int*> mainContainer;
    std::vector<int*&> secondContainer;
    mainContainer.push_back(x);
    secondContainer.push_back(mainContainer[0]);
    delete x;
    //Doesn't work!
    */

    return 0;
}


