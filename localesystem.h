#ifndef LOCALE_H_INCLUDED
#define LOCALE_H_INCLUDED
#include <list>
#include "BST.h"
#include "data_base.h"
#include "typedefs.h"


class LocaleNode
{
public:
    /*Constructor and destructor
    id = the line number described by the locale file
    */
    LocaleNode(const std::string& content);
    //~LocaleNode();

    //Getters
    size_t GetLocaleStringSize() const;
    std::string GetLocaleString();

    bool operator==(const std::string& input)
    {
        return m_string == input;
    }

private:
    std::string m_string;
};

class LocaleReader
{
public:
    //Constructor and destructor
    LocaleReader(cstr file);
    //~LocaleReader();

    std::string ExpandInputString(const std::string& raw_input);
    std::string CondenseInputString(const std::string& raw_input);

    std::string GetLocaleName() const;
private:
    std::vector<LocaleNode> doc;
    std::string locale_name;
};

#endif // LOCALE_H_INCLUDED
