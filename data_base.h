/*
    Copyright (C) 2014 Luis M. Santos
    Contact: luismigue1234@hotmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DATA_BASE_H_INCLUDED
#define DATA_BASE_H_INCLUDED
#define ENDOFFILE -1
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
    std::fstream::pos_type s;
    std::fstream file;
    std::string buffer;
    std::ofstream output;
    std::string lastLocation;
    //methods
    bool LoadData(const char* location, bool readMode = true);
    void LoadStringBuffer(bool closeFile = true);
    void FlushData();
    int GetLineIndex(std::string search, int lineNum) const;
    void FileClear();
    void CleanFileContentsOfArtifacts();
    void TrimEndOfFile();
    public:
    //methods
    data_base(const char location[]="", bool read = true);
    std::string GetStrBuffer() const;
    double GetValueFromData(std::string search) const;
    std::string GetStrFromData(std::string search) const;
    int GetIntFromData(std::string search) const;
    double GetValueFromDataWithLine(std::string search, int lineIndex) const;
    std::string GetStrFromDataWithLine(std::string search, int lineIndex) const;
    bool GetStateOfInternalBuffer() const;
    std::string OpenFileAndGetBinBuffer(const char* location);
    void OpenFile(const char* location, bool readMode = true);
    void OpenFileForQuickWrite(const char* location);// Will open the output stream in append mode. It assumes you just want to ad some new stuff to the file immediately.
    void OpenBinFileForQuickWrite(const char* location); //Will open a file in binary mode
    void CloseFile(std::string streamsToClose = "all");
    bool GetMode() const;
    void WriteValue(std::string value, std::string search = "");
    void WriteValueWithLineIndex (std::string value, std::string search, int lineIndex);
    void WriteValueAndFlush(std::string value);//Meant to be used with OpenFileForQuickWrite
    int GetLineCount() const;
    int GetNumInstances(std::string search) const;
    std::string GetLastOutput() const;
    bool isOutputOpen() const;
    bool SearchTermExists(std::string search) const;
    void RestoreFileContents();
    void RefreshFile();
    void CreateNewFile(const char* location = "");
    static void CreateNewFile_static(const char* location);
    ~data_base();
};

bool copyfile(const std::string& source, const std::string destination, bool binary = true);
#endif // DATA_BASE_H_INCLUDED
