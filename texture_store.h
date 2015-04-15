#ifndef TEXTURE_STORE_H_INCLUDED
#define TEXTURE_STORE_H_INCLUDED
#include <iostream>
#include <string>
#include <SDL.h>
#include <pthread.h>
#include "BST.h"
#include "typedefs.h"

class TextureStore
{
public:
    TextureStore();

    SDL_Texture* LoadUniqueTexture(cstr file, SDL_Renderer& ren, bool duplicate = true);

    //the magic of a singleton
    void* operator new(size_t s);
    void operator delete(void* ptr);

private:
    uint64_t instances;
    BinarySearchTree<uint64_t, SDL_Texture*> storage;
    pmutex mutex;

    static TextureStore* objPtr;
};


#endif // TEXTURE_STORE_H_INCLUDED
