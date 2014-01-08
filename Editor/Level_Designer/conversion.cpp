#define ERROR -1
#include "conversion.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <unistd.h>
int charToInt(const char buffer)
{
    /*Base function that converts a single character into a number. This function is the heart of the string conversion functions.*/
    int answer = buffer - '0';
    return answer;
}

std::string intToStr (const int num)
{
    char buffer[33];
    snprintf(buffer, 33, "%d", num);//convert and store in buffer. this function used to be done with itoa but it wasn't standard so I changed it (MinGW vs. Cygwin capabilities).
    return std::string(buffer);
}

int cStrToInt(const char buffer[])
{
    /*Same as cStrToNum but this one assumes the string yields an integer. The code is somewhat shorter and should execute much faster.*/
    return atoi(buffer);
}

double cStrToNum(const char buffer[])
{
    /*Converts a string buffer into its number equivalent. A.k.a. "123" = 123 or "12.3" = 12.3. This function returns a number in floating point
    because its purpose is general.*/
    return atof(buffer);
}

int numToInt(double value)
{
    int extra = 0;
    if(value - (int)value > 0.5)
    {
        extra++;
    }
    return int(value + extra);
}

int searchCharIndex(char character, char buffer[]){
  /*This function will search for a character and tell me where it exists in the buffer.*/
for(unsigned int i =0; i < sizeof(buffer)-1; i++)
{
    if(character == buffer[i])
    {
        return i;
    }
}
return ERROR;
}

int searchCharIndex(const char character, std::string buffer, int start)
{
      /*This function will search for a character and tell me where it exists in the buffer.*/
    for(unsigned int i =start; i < buffer.length(); i++)
    {
        if(character == buffer[i])
        {
            return i;
        }
    }
    return ERROR;
}

bool searchChar(const char character, const char buffer[]){
/*This function will search for a character and tell me if it exists.*/
for(unsigned int i =0; i < sizeof(buffer)-1; i++)
{
    if(character == buffer[i])
    {
        return 1;
    }
}
return 0;
}

int findString(const char target[], const char stringSource[], int pos)
{
    /*This function searches for a string and returns the index of the first character in the target string.*/
    std::string StringSource = stringSource;
    return StringSource.find(target, pos);
}

void transferStr(pChar* const input, char* const array)
{
    /*This function extracts the characters in the pBuffer field of input and save them in the array from the caller. */
    for(unsigned int i = 0; i < input->size; i++)
    {
        if(i < sizeof(array))
        {
            array[i] = input->pBuffer[i];
        }
    }
}

std::string removeCharFromStr(char target, const char cString[])
{
    std::string piece = cString;
    int index = 0;
    index = piece.find(target);
    if(index >= 0)
    {
        piece.erase(index,1);
    }
    return piece;
}
std::string removeMultipleCharFromStr(char target, const char cString[])
{
    std::string piece = cString;
    int index = 0;
    index = piece.find(target);
    while(index >= 0)
    {
        piece.erase(index,1);
        index = piece.find(target);
    }
    return piece;

}
pChar* createPCharFromBuffer(char buffer[], int size)
{
    /*This function can create a simple pChar structure on the heap from a given C string and size.
    The function checks the heap pointers to make sure they are not null.*/
    pChar* holder = new pChar;
    holder->size = size;
    char* content = new char[holder->size + 1];
    content[holder->size] = '\0';
    if(!content)//Chacks for validity of pointer
    {
        holder->pBuffer = 0;//makes sure the pointer goes to the special address if the validity check fails.
    }
    else if(!holder)
    {
        return 0;
    }
    else
    {
        for(unsigned int i = 0; i<holder->size; i++)
        {
            content[i] = buffer[i];
        }
    }
    holder->pBuffer = content;
    return holder;
}
pChar* slice(char* const input, int start, int end)
{
    /*Slices a c-string and returns the slice. This emulates the behavior of the python slice.
    Pretty handy for string manipulation and extraction. */
    char* answer = new char[end - start + 1];
    answer[end - start] = '0';
    pChar* holder = new pChar;
    holder->size = end - start;
    for(int i = 0; i < (end - start); i++)
    {
        answer[i] = input[i + start];
    }
    holder->pBuffer = answer;
    return holder;
}

std::string sliceStr(std::string input, int start, int end)
{
    if(input == "")
    {
      return "";
    }
    /*This function takes a string and returns a slice from the start position to the desired end position*/
    char answer[end - start + 1];
    answer[end-start] = '\0'; //Append end of string character so the string is not misdisplayed or misused later on.
    if(end < 0)
    {
        return input;
    }
    for(int i = 0; i<end-start; i++)
    {
        answer[i] = input[i+start];
    }
    return std::string(answer);
}
pChar* shiftArrayLeft(char* input, int size)
{
    /*Default version of this function. It returns a slice of the original c-string that does
    not contain the first element of the array.*/
    pChar* holder = slice(input, 1, size);
    if(!holder)
    {
        return NULL;
    }
    return holder;
}

pChar* shiftArrayLeft(char* input, int size, int elements)
{
    /*Overload version of this function. It returns a slice of the original c-string that does
    not contain the number of elements (elements) in the array. For example, "ABCDE" => "DE" if elements = 3*/
    pChar* holder = slice(input, elements, size);
    if(!holder)
    {
        return NULL;
    }
    return holder;
}

std::string fuseStrs(std::string Str1, std::string Str2)
{
    return Str1 + Str2;
}

double round(double value, int precision)
{
    int precisionFactor = 10 ^ precision;
    double tmpValue = value * precisionFactor;
    double decimals = tmpValue - (int)(tmpValue);
    if(decimals > 0.5)
    {
        return ceil(tmpValue) / precisionFactor;
    }
    return floor(tmpValue) / precisionFactor;
}

int iround(double value, int precision)
{
    return (int)(round(value, precision));
}

std::string numToStr(const double num)
{
    std::stringstream s;
    s << num;
    return s.str();
}

bool changeProgramWorkingDirectory(const char* newPath)
{
    //This function allows the calling program to change the current working directory
    if(chdir(newPath) == ERROR)
    {
        return false;
    }
    return true;
}
