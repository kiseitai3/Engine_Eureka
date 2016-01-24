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
    UNIT, PROJECTILE, OBJECT, TEXTURE, TRIGGER, CURSOR, SOUND
};

enum TypeType
{
    NONETYPE = 0x30,
    SOUNDTYPE = 0x40,
    CODETYPE = 0x50,
    OBJTYPE = 0x60
};

typedef struct SearchPacket
{
    std::string prefix, suffix, term, path, fileName;
}SearchPacket;

typedef struct NodeObj
{
    size_t id;
    size_t type;
    QString name, path;
    void_ptr obj_ptr;

    inline bool operator==(const NodeObj& other)
    {
        if(name == other.name || id == other.id)
            return true;
        return false;
    }
}AssetNode;

#endif // GLOBALS_H
