#include "localesystem.h"


LocaleNode::LocaleNode(const std::string& content)
{
    m_string = content;
}

size_t LocaleNode::GetLocaleStringSize() const
{
    return m_string.size();
}

std::string LocaleNode::GetLocaleString()
{
    return m_string;
}



LocaleReader::LocaleReader(cstr file)
{
    data_base f(file);
    std::string buff = f.GetStrBuffer();
    std::string line;
    size_t line_start = 0;
    size_t line_end = 0;
    size_t pointer = buff.find("\n");
    locale_name = f.GetStrFromData("name");


    while(true)
    {
        pointer = buff.find('@', pointer);
        if(pointer >= buff.size())
        {
            break;
        }
        line_start = pointer + 1;
        line_end = buff.find(';', pointer);
        line = buff.substr(line_start, line_end - line_start);
        doc.push_back(LocaleNode(line));
        pointer = line_end;
    }
}

std::string LocaleReader::GetLocaleName() const
{
    return locale_name;
}

std::string LocaleReader::ExpandInputString(const std::string& raw_input)
{
    std::string line;
    std::string output = raw_input;
    size_t line_start = 0;
    size_t line_end = 0;
    size_t pointer = 0;
    size_t index = 0;


    while(true)
    {
        pointer = raw_input.find('@', pointer);
        if(pointer >= raw_input.size())
        {
            break;
        }
        line_start = pointer + 1;
        line_end = raw_input.find(':', pointer);
        line = raw_input.substr(line_start , line_end - line_start);
        index = cStrToInt(line.c_str());
        output = replaceStrInStr(output, "@" + line + ":", doc[index].GetLocaleString());
        pointer = line_end;
    }

    return output;
}

std::string LocaleReader::CondenseInputString(const std::string& raw_input)
{
    std::string line;
    std::string output = raw_input;
    size_t line_start = 0;
    size_t line_end = 0;
    size_t pointer = 0;


    while(pointer < raw_input.size())
    {
        line_start = pointer;
        line_end = raw_input.find(";;", pointer);
        line = raw_input.substr(line_start , line_end - line_start);
        for(size_t i = 0; i < doc.size(); i++)
        {
            if(doc[i] == line)
            {
              output = replaceStrInStr(output, line + ";;", "@" + intToStr(i) + ":");
              break;
            }
        }

        pointer = raw_input.find(";;", pointer);
        if(pointer >= raw_input.size())
        {
            break;
        }
        else
            pointer += 2;
        if(raw_input.find("\n\r", pointer) == pointer)
            pointer += 2;
        else if (raw_input.find("\n", pointer) == pointer)
            pointer += 1;
        else if (raw_input.find("\r", pointer) == pointer)
            pointer += 1;
    }

    return output;
}

