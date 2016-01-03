#ifndef LOCALE_H_INCLUDED
#define LOCALE_H_INCLUDED
#include "data_base.h"
#include "typedefs.h"

class LocaleNode
{
public:
    /*Constructor and destructor
    id = the line number described by the locale file
    hash = hash of the actual string (used for quick comparison purposes)
    pos = starting position of the string on the file
    size = length of the string on the file
    */
    LocaleNode(size_t id, size_t hash, size_t pos, size_t size);
    ~LocaleNode();

    //Getters
    size_t GetLocaleID();
    size_t GetLocaleHash();
    size_t GetLocalePosition();
    size_t GetLocaleStringSize();
};

class LocaleReader : public data_base
{
public:
    //Constructor and destructor
    LocaleReader(cstr file);
    ~LocaleReader();

    size_t GetLocaleID(size_t hash);
    std::string GetLocaleString(size_t id);
};

#endif // LOCALE_H_INCLUDED
