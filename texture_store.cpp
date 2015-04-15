#include "texture_store.h"
#include <cstdlib>

TextureStore::TextureStore()
{
    objPtr = NULL;
    mutex = PTHREAD_MUTEX_INITIALIZER;
    instances = 0;
}

void* TextureStore::operatornew(size_t s)
{
    if(objPtr)
    {
        instances++;
        return (void*)objPtr;
    }
    else
    {
        objPtr = malloc(s);
        if(objPtr)
            instances++;
        return objPtr;
    }
}

void TextureStore::operatordelete(void* ptr)
{
    if(ptr)
    {
        if(instances)
            instances--;
        else
          free(ptr);
    }
}

SDL_Texture* TextureStore::LoadUniqueTexture(cstr file, SDL_Renderer& ren, bool duplicate)
{
    uint64_t crc_hash = 0;

    //

}

