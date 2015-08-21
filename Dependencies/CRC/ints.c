#include "ints.h"
//Initializer
void int128_init(int128_t* num)
{
    size_t i = 0;
    for(; i < INT128_BYTESIZE; i++)
    {
        num->val[i] = 0;
    }
}

//Initializer
void uint128_init(uint128_t* num)
{
    size_t i = 0;
    for(; i < INT128_BYTESIZE; i++)
    {
        num->val[i] = 0;
    }
}
/*Let's start by defining the operations declared using int128s. With these functions in place, we can then implement
the functions that will take care of these operations with arbitrary integer types.*/

/*The following functions will add and subtract signed and unsigned int128s*/
uint128_t addUnSigned128(const uint128_t num1, const uint128_t num2)
{
    //Loop indexes
    byte i = 0;
    //byte j = 0;
    //Other variables
    unsigned short c = 0;//carry
    uint128_t result;

    //Init values
    uint128_init(&result);

    for(; i < INT128_BYTESIZE; i++)
    {
        c = num1.val[i] + num2.val[i] + c;//Store result in carry until we determine it is not an overflow
        if(c > max(num1.val[i], num2.val[i]))
            result.val[i] = c;
        else
        {
            result.val[i] = c - 0xFF;
            c = 0x01;
        }
    }

    return result;
}

int128_t addSigned128(const int128_t num1, const int128_t num2)
{
    //Loop indexes
    byte i = 0;
    //byte j = 0;
    //Other variables
    short c = 0;//carry
    int128_t result;

    //Init values
    int128_init(&result);

    for(; i < INT128_BYTESIZE; i++)
    {
        c = num1.val[i] + num2.val[i] + c;//Store result in carry until we determine it is not an overflow
        if(c > max(num1.val[i], num2.val[i]))
            result.val[i] = c;
        else
        {
            result.val[i] = c - 0xFF;
            c = 0x01;
        }
    }

    return result;
}
