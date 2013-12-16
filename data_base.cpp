#include <fstream>
#include <string>
#include "conversion.h"
#include "data_base.h"

//Reading section
    bool data_base::LoadData(const char* location, bool readMode)
    {
        /*Opens the file handle*/
        if(readMode)
        {
            file.open(location, std::fstream::in);
        }
        else
        {
            output.open(location, std::ios::out | std::ios::trunc);
            lastOutputLocation = location;
        }
        return file.is_open();
    }
    void data_base::LoadStringBuffer(bool closeFile)
    {
        /*Loads file into internal string buffer line by line*/
        std::string temp = "";
        if (file.is_open())
        {
            while ( file.good() )
            {
                std::getline (file,temp);
                temp += "\n\r";
                buffer += temp;
                lines++;
            }
        }
        if(closeFile)
        {
            file.close();
        }
    }
    std::string data_base::GetStrBuffer()
    {
        return buffer;
    }
    double data_base::GetValueFromData(std::string search)
    {
        /*This function takes a search string (aka. keyword) and looks for the index of the beginning of the keyword.
        Then, it slices the internal buffer and cleans it of non-numeric characters that are known to be in the internal string buffer.
        Finally, it sends the number string into a conversion function that returns the number equivalent of the string.*/
        int start = findString((char*)search.c_str(), buffer.c_str())+ search.length();
        int end = searchCharIndex(';', buffer, start);
        if(end < 0)
        {
            end = searchCharIndex('\n', buffer.c_str(), start);
        }
        std::string numberStr = sliceStr(buffer,start, end);//Get slice
        numberStr = removeCharFromStr('=', numberStr.c_str());
        return cStrToNum(numberStr.c_str());
    }
    std::string data_base::GetStrFromData(std::string search)
    {
        /* Extracts the string in much the same way the GetValueFromData does.*/
        int start = findString((char*)search.c_str(), buffer.c_str())+ search.length();
        int end = searchCharIndex(';', buffer, start);//Get's end of line
        if(end < 0)
        {
            end = searchCharIndex('\n', buffer.c_str(), start);
        }
        std::string Str = sliceStr(buffer,start, end);
        Str = removeCharFromStr('=', Str.c_str());//Cleans value string from the = sign
        while(Str[0] == ' ')//remover initial spaces left after removing '='.
        {
            Str = removeCharFromStr(' ', Str.c_str());
        }
        return Str;
    }
    int data_base::GetIntFromData(std::string search)
    {
        return numToInt(GetValueFromData(search));
    }
    void data_base::OpenFile(const char* location, bool readMode)
    {
        switch(readMode)
        {
            case true:
            if(file.is_open())
            {
                file.close();
            }
            if(LoadData(location))//Checks if internal file buffer was properly started.
            {
                LoadStringBuffer();//reads the file buffer into the internal string buffer
                isBufferLoaded = true;//sets this flag true so other processes know the task was successful!
            }
            break;
            default:
            if(LoadData(location))//Checks if internal file buffer was properly started.
            {
                writeMode = true;
                LoadStringBuffer();//Get an internal copy of the contents in the file and close the file
                LoadData(location, readMode);//Reopen the same file but in output mode, which erases all previous data.
            }
        }

    }

    void data_base::OpenFileForQuickWrite(const char *location)
    {
        /*Will open the output stream in append mode. It assumes you just want to ad some new stuff to the file immediately.*/
        if(output.is_open())//we don't want to leak handles or anything
        {
            output.close();
        }
        output.open(location, std::ios::out | std::ios::app);
        buffer = "";
    }

    double data_base::GetValueFromDataWithLine(std::string search, int instanceIndex)
    {
         /*Note: instanceIndex is the number of times a search word can be found in the target file. i.e. value = 1; value = 3;
        has 2 instances, so if inctanceIndex is 1 the result will be 1 and if instanceIndex is 2 the result will be 3.
        This method gets the value from an specific instance of a keyword.*/
        int start = GetLineIndex(search, instanceIndex);
        int end = searchCharIndex(';', buffer, start);
        if(end == ERROR)
        {
            end = searchCharIndex('\n', buffer, start);
        }
        std::string numberStr = sliceStr(buffer,start, end);//Get slice
        numberStr = removeCharFromStr('=', numberStr.c_str());
        return cStrToNum(numberStr.c_str());
    }

    std::string data_base::GetStrFromDataWithLine(std::string search, int instanceIndex)
    {
        /*Note: instanceIndex is the number of times a search word can be found in the target file. i.e. value = 1; value = 3;
        has 2 instances, so if inctanceIndex is 1 the result will be 1 and if instanceIndex is 2 the result will be 3.
        This method gets the value from an specific instance of a keyword.*/
        int start = GetLineIndex(search, instanceIndex);
        int end = searchCharIndex(';', buffer, start);
        if(end == ERROR)
        {
            end = searchCharIndex('\n', buffer, start);
        }
        std::string Str = sliceStr(buffer,start, end);
        Str = removeCharFromStr('=', Str.c_str());//Cleans value string from the = sign
        while(Str[0] == ' ')//remover initial spaces left after removing '='.
        {
            Str = removeCharFromStr(' ', Str.c_str());
        }
        return Str;
    }

bool data_base::SearchTermExists(std::string search)
{
    if(findString(search.c_str(), GetStrBuffer().c_str()) == std::string::npos)
    {
        return false;
    }
    return true;
}
    //Writing
    void data_base::FlushData()
    {
        FileClear();
        output << buffer;//write buffer into file stream
        output.flush();//flush the stream into the storage device so that the file is updated
    }

    void data_base::WriteValue(std::string value, std::string search)
    {
        /*Writes value into an specific 'tag' in file. i.e. value = 3; [search = value, value = 5] -> value = 5;*/
        if(buffer != "" && search != "")
        {
            int start = findString(search.c_str(), buffer.c_str()) + search.length() + 3;//3 is the number of spaces in the line that form the string " = ". Check the syntax of files
            int end = searchCharIndex(';', buffer, start);
            int size = end - start;
            buffer.replace(start, size, value);
            FlushData();
        }
        else if(buffer == "" && search != "")
        {
            std::cout<<"Error: File is empty!\n\r";
        }
        else
        {
            buffer = value;
            FlushData();
        }
    }

    void data_base::WriteValueWithLineIndex(std::string value, std::string search, int instanceIndex)
    {
        /*This methods find the instance of a keyword and modifies its value. i.e. value = 3;\nvalue = 4 [mod line 2 with 3] -> value = 3;\nvalue = 3.*/
        int start = GetLineIndex(search, instanceIndex) + 3;
        int end = searchCharIndex(';', buffer, start);
        int size = end - start;
        if(end == ERROR)
        {
            end = searchCharIndex('\n', buffer, start);
        }
        if(buffer != "")
        {
            buffer.replace(start, size, value);
            FlushData();
        }
    }

    void data_base::WriteValueAndFlush(std::string value)
    {
        /*Meant to be used with OpenFileForQuickWrite(). Unlike in the regular output mode, value will contain a manually
        created string. In other words, this function will not edit search terms within the file.*/
        output << value;
        output.flush();
    }

    //General methods
    int data_base::GetLineCount()
    {
        return lines;
    }
    int data_base::GetNumInstances(std::string search)
    {
        /*Searches for the search keyword until and increments the instance count (line count) each time it finds the search word.
        Then, the method returns this number.*/
        int index = 0;
        int line = 0;
        int start = 0;
        while(true)
        {
            start = findString(search.c_str(), buffer.c_str(), index) + search.length();
            line++;
            if(index < start)
            {
                index = start;
            }
            else
            {
                return line - 1;//Unfortunately, this function also includes the end of string as an instance of the keyword. I adjust for this false positive by substracting 1.
            }
        }
    }
    bool data_base::GetStateOfInternalBuffer()
    {
        return isBufferLoaded;
    }
    int data_base::GetLineIndex(std::string search, int lineNum)
    {
        int index = 0;
        int line = 0;
        int start = 0;
        while(true)
        {
            start = findString(search.c_str(), buffer.c_str(), index) + search.length();
            line++;
            index = start;
            if(line == lineNum)
            {
                return index;
            }
        }

    }

    void data_base::FileClear()
    {
        /*Clears the file. WARNING: do not invoke this method if you are reading a file and the internal buffer does not have a copy of the file.
        This will surely empty the file!!!!!!!!!!!!!!!!!!!*/
        if(GetMode())//Despite warnings, I still check the class is in writing mode. I know someone may misuse this class.
        {
            if(output.is_open())
            {
                output.close();
            }
            output.open(lastOutputLocation.c_str(), std::ios::out | std::ios::trunc);
        }
    }

    bool data_base::GetMode()
    {
        return writeMode;
    }
    void data_base::CloseFile(std::string streamsToClose)
    {
        /*streamsToClose flags are all for all stream, in for input stream, and out for output stream. the flag is set to all by default.
        This method makes some checks*/
        writeMode = false;
        isBufferLoaded = false;
        lines = 0;
        if(streamsToClose == "all" && (file.is_open() && output.is_open()))
        {
            file.close();
            output.close();
        }
        else if(streamsToClose == "all" && (file.is_open()&& !output.is_open()))
        {
            file.close();
        }
        else if(streamsToClose == "all" && (!file.is_open()&& output.is_open()))
        {
            output.close();
        }
        else if(streamsToClose == "in" && file.is_open())
        {
            file.close();
        }
        else if(streamsToClose == "out" && output.is_open())
        {
            output.close();
        }
    }
    data_base::data_base(const char location[], bool read)
    {
        /*Constructor. This class will be used for reading files by default. However, changing the read flag to false will
        make the constructor prep the object for writing purposes instead*/
        isBufferLoaded = false;
        writeMode = false;
        buffer = "";
        lines = 0;
        switch(read)
        {
            case false:
            if(LoadData(location))
            {
                writeMode = true;
                LoadStringBuffer();//Get an internal copy of the contents in the file and close the file
                LoadData(location, read);//Reopen the same file but in output mode, which erases all previous data.
                }
            break;
            default:
            if(LoadData(location))//Checks if internal file buffer was properly started.
            {
                LoadStringBuffer();//reads the file buffer into the internal string buffer
                isBufferLoaded = true;//sets this flag true so other processes know the task was successful!
            }
        }
    }
    data_base::~data_base()
    {
        /*Makes sure the file handle is properly closed from the constructor event. It helps prevent file handle leaks.*/
        if(file.is_open())
        {
            file.close();
        }

    }
