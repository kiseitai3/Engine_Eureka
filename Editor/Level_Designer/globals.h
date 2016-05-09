#ifndef GLOBALS_H
#define GLOBALS_H
#include "typedefs.h"
#include <eureka.h>
#undef main
#undef sleep

#include <QString>

enum SoundType
{
    MUSIC, EFFECT, RANDOM
};

enum TreeViewID
{
    OBJECTLIST, UIELEMENTS, BASEASSETS, REGISTEREDOBJS
};

enum CodeType
{
    PLUGIN, SCRIPT
};

enum SearchType
{
    NOSEARCH, PARTIALSEARCH, FULLSEARCH
};

enum ObjType
{
    UNIT, PROJECTILE, OBJECT, TEXTURE, TRIGGER, CURSOR, SOUND, LAYER, LAYERSET, PHYSICS, CURSORSET
};

enum UIElements
{
    BUTTON = 1, TEXTBOX = 2
};

enum TypeType
{
    NONETYPE = 0x30,
    SOUNDTYPE = 0x40,
    CODETYPE = 0x50,
    OBJTYPE = 0x60,
    UITYPE = 0x70
};

enum SubtypeType
{
    INSTANCE = 0x10,
    BASEASSET = 0x20
};

typedef struct SearchPacket
{
    std::string prefix, suffix, term, path, fileName;
}SearchPacket;

typedef struct NodeObj
{
    size_t id;
    size_t type, subtype;
    QString name, path;
    void_ptr obj_ptr;
    std::vector<size_t> idlist;

    inline bool operator==(const NodeObj& other)
    {
        if(name == other.name || id == other.id)
            return true;
        return false;
    }
    inline bool operator==(const std::string& other)
    {
        if(name.toStdString() == other)
            return true;
        return false;
    }
    inline bool operator==(const QString& other)
    {
        if(name == other)
            return true;
        return false;
    }
    inline bool operator==(size_t other)
    {
        if(id == other)
            return true;
        return false;
    }
}AssetNode;


template<typename T> void removeValFromStack(std::stack<T>& container, const T& val)
{
    std::stack<T> storage;

    while(container.top() != val)
    {
        storage.push(container.top());
        container.pop();
    }

    container.pop();

   while(!storage.empty())
    {
        container.push(storage.top());
        storage.pop();
    }
}

#endif // GLOBALS_H
