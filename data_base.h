#ifndef DATA_BASE_H_INCLUDED
#define DATA_BASE_H_INCLUDED
#define ERROR -1
#include <fstream>
#include <string>
#include "conversion.h"
#include "data_base.h"
#include <iostream>

class data_base
{
    private:
    bool isBufferLoaded;
    bool writeMode;
    int lines;
    std::fstream file;
    std::string buffer;
    std::ofstream output;
    std::string lastOutputLocation;
    //methods
    bool LoadData(const char* location, bool readMode = true);
    void LoadStringBuffer(bool closeFile = true);
    void FlushData();
    int GetLineIndex(std::string search, int lineNum);
    void FileClear();
    public:
    //methods
    data_base(const char location[]="", bool read = true);
    std::string GetStrBuffer();
    double GetValueFromData(std::string search);
    std::string GetStrFromData(std::string search);
    int GetIntFromData(std::string search);
    double GetValueFromDataWithLine(std::string search, int lineIndex);
    std::string GetStrFromDataWithLine(std::string search, int lineIndex);
    bool GetStateOfInternalBuffer();
    void OpenFile(const char* location, bool readMode = true);
    void OpenFileForQuickWrite(const char* location);// Will open the output stream in append mode. It assumes you just want to ad some new stuff to the file immediately.
    void CloseFile(std::string streamsToClose = "all");
    bool GetMode();
    void WriteValue(std::string value, std::string search = "");
    void WriteValueWithLineIndex (std::string value, std::string search, int lineIndex);
    void WriteValueAndFlush(std::string value);//Meant to be used with OpenFileForQuickWrite
    int GetLineCount();
    int GetNumInstances(std::string search);
    bool SearchTermExists(std::string search);
    ~data_base();
};

#endif // DATA_BASE_H_INCLUDED
