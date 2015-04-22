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

<<<<<<< HEAD
<<<<<<< HEAD
    SDL_Texture* LoadUniqueTexture(cstr file, SDL_Renderer& ren);
    void DeleteUniqueTexture(SDL_Texture* tex);
    bool hasTexture(uint64_t hash);
    bool hasHash(SDL_Texture* tex);

private:
    BinarySearchTree<uint64_t, SDL_Texture*> storage;//Storage of unmodified textures
    BinarySearchTree<SDL_Texture*, uint64_t> hashCache;//Cache of hashes that can be accessed when we get the texture pointer
    BinarySearchTree<SDL_Texture*, uint64_t> textureLife;//Storage of lifetime of texture!
    pthread_mutex_t mutex;

    //Methods

    SDL_Texture* createTexture(cstr file, SDL_Renderer& ren);
=======
=======
>>>>>>> origin/TheIllusiveMan
    SDL_Texture* LoadUniqueTexture(cstr file, SDL_Renderer& ren, bool duplicate = true);

    //the magic of a singleton
    void* operator new(size_t s);
    void operator delete(void* ptr);

private:
    uint64_t instances;
    BinarySearchTree<uint64_t, SDL_Texture*> storage;
    pmutex mutex;

    static TextureStore* objPtr;
<<<<<<< HEAD
>>>>>>> origin/TheIllusiveMan
=======
>>>>>>> origin/TheIllusiveMan
};


#endif // TEXTURE_STORE_H_INCLUDED
