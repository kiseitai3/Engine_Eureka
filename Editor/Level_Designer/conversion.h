#ifndef CONVERSION_H_INCLUDED
#define CONVERSION_H_INCLUDED
#include <string>
struct pChar{
char* pBuffer;//Contains the pointer to the character array
unsigned int size;//Contains the size of the array
};
int charToInt(const char buffer);//Get numbers out of chars
int cStrToInt(const char buffer[]);//Get full numbers out of character strings
std::string intToStr (const int num); //Converts a single number into a string equivalent
double cStrToNum(const char buffer[]);
std::string numToStr(const double num);
int searchCharIndex(const char character,std::string buffer, int start = 0);
bool searchChar(const char character, const char buffer[]);
int findString(const char target[], const char stringSource[], int pos = 0);
pChar* slice(char* const input, int start, int end);
pChar* shiftArrayLeft(char* const input, int size);
pChar* shiftArrayLeft(char* const input, int size, int elements);
void transferStr(pChar* const input, char* const array);
pChar* createPCharFromBuffer(char buffer[], int size);
std::string removeCharFromStr(char target, const char cString[]);
std::string removeMultipleCharFromStr(char target, const char cString[]);
int searchCharIndex(char character, char buffer[]);
std::string sliceStr(std::string input, int start, int end);
int numToInt(double value);
std::string fuseStrs(std::string Str1, std::string Str2);
template <typename N> N compareValues(N numA, N numB)
{
    if(numA > numB)
    {
        return numA;
    }
    return numB;
}
double round(double value, int precision);
int iround(double value, int precision);
bool changeProgramWorkingDirectory(const char* newPath);
#endif // CONVERSION_H_INCLUDED
