#ifndef INTS_H_INCLUDED
#define INTS_H_INCLUDED
#define INT128_BYTESIZE 16
#define INT64_BYTESIZE 8
#define INT64_BITSIZE 64
#define max(a,b) (a>b?a:b)
#define correction(a) (a>127?-127:0)
typedef unsigned int size_t;
typedef unsigned char byte;

typedef struct uint128_t
{
    byte val[16];

}uint128_t;

typedef struct int128_t
{
    char val[16];

}int128_t;

//Int initializer
void int128_init(int128_t*);
void uint128_init(uint128_t*);
//Converters
int128_t create_int128_s(char* num, size_t s);
uint128_t create_int128_u(char* num, size_t s);


/*Operations using arbitrary atomic types to yield a 128 bit integer*/
//Add and sub
int128_t addSigned(char* num1, size_t size1, char* num2, size_t size2);
uint128_t addUnSigned(char* num1, size_t size1, char* num2, size_t size2);
int128_t substractSigned(char* num1, size_t size1, char* num2, size_t size2);
uint128_t substractUnSigned(char* num1, size_t size1, char* num2, size_t size2);
//Multi and div
int128_t multiplySigned(char* num1, size_t size1, char* num2, size_t size2);
uint128_t multiplyUnSigned(char* num1, size_t size1, char* num2, size_t size2);
int128_t divideSigned(char* num1, size_t size1, char* num2, size_t size2);
uint128_t divideUnSigned(char* num1, size_t size1, char* num2, size_t size2);
//And and or
int128_t andSigned(char* num1, size_t size1, char* num2, size_t size2);
uint128_t andUnSigned(char* num1, size_t size1, char* num2, size_t size2);
int128_t orSigned(char* num1, size_t size1, char* num2, size_t size2);
uint128_t orUnSigned(char* num1, size_t size1, char* num2, size_t size2);
//Nand and xor
int128_t nandSigned(char* num1, size_t size1, char* num2, size_t size2);
uint128_t nandUnSigned(char* num1, size_t size1, char* num2, size_t size2);
int128_t xorSigned(char* num1, size_t size1, char* num2, size_t size2);
uint128_t xorUnSigned(char* num1, size_t size1, char* num2, size_t size2);
//Rshift and Lshift
int128_t shiftRightSigned(char* num1, size_t size1, char* num2, size_t size2);
uint128_t shiftRightUnSigned(char* num1, size_t size1, char* num2, size_t size2);
int128_t shiftLeftSigned(char* num1, size_t size1, char* num2, size_t size2);
uint128_t shiftLeftUnSigned(char* num1, size_t size1, char* num2, size_t size2);

/*Operations using int128s to yield int128s (including unsigned counterparts)*/
//Add and sub
int128_t addSigned128(const int128_t num1, const int128_t num2);
uint128_t addUnSigned128(const uint128_t num1, const uint128_t num2);
int128_t substractSigned128(const int128_t num1, const int128_t num2);
uint128_t substractUnSigned128(const uint128_t num1, const uint128_t num2);
//Multi and div
int128_t multiplySigned128(const int128_t num1, const int128_t num2);
uint128_t multiplyUnSigned128(const uint128_t num1, const uint128_t num2);
int128_t divideSigned128(const int128_t num1, const int128_t num2);
uint128_t divideUnSigned128(const uint128_t num1, const uint128_t num2);
//And and or
int128_t andSigned128(const int128_t num1, const int128_t num2);
uint128_t andUnSigned128(const uint128_t num1, const uint128_t num2);
int128_t orSigned128(const int128_t num1, const int128_t num2);
uint128_t orUnSigned128(const uint128_t num1, const uint128_t num2);
//Nand and xor
int128_t nandSigned128(const int128_t num1, const int128_t num2);
uint128_t nandUnSigned128(const uint128_t num1, const uint128_t num2);
int128_t xorSigned128(const int128_t num1, const int128_t num2);
uint128_t xorUnSigned128(const uint128_t num1, const uint128_t num2);
//Rshift and Lshift
int128_t shiftRightSigned128(const int128_t num1, const int128_t num2);
uint128_t shiftRightUnSigned128(const uint128_t num1, const uint128_t num2);
int128_t shiftLeftSigned128(const int128_t num1, const int128_t num2);
uint128_t shiftLeftUnSigned128(const uint128_t num1, const uint128_t num2);
#endif // INTS_H_INCLUDED
