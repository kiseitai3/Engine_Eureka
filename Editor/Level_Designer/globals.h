#ifndef GLOBALS_H
#define GLOBALS_H
#include "typedefs.h"
#include <eureka.h>
#undef main
#undef sleep

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

typedef struct SearchPacket
{
    std::string prefix, suffix, term, path, fileName;
}SearchPacket;

#endif // GLOBALS_H
