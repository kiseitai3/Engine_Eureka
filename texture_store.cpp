<<<<<<< HEAD
#include <cstdlib>
#include "texture_store.h"
#include <crc.h>
#include <SDL.h>
#include <SDL_image.h>

TextureStore::TextureStore()
{
    mutex = PTHREAD_MUTEX_INITIALIZER;
}

bool TextureStore::hasTexture(uint64_t hash)
{
    SDL_Texture* tmp = NULL;
    return storage.search(hash, tmp);
}

SDL_Texture* TextureStore::createTexture(cstr file, SDL_Renderer& ren)
{
    SDL_Texture* tex = NULL;
    SDL_Surface* tmp = IMG_Load(file);
    if(!tmp)
    {
        std::cout << "Failed to load the surface!" << std::endl;
    }
    else
    {
        SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB( tmp->format, 0xFF, 0xFF, 0xFF ));
        tex = SDL_CreateTextureFromSurface(&ren, tmp);
        SDL_FreeSurface(tmp);
    }

    if(tex)
        return tex;
    return NULL;
}

SDL_Texture* TextureStore::LoadUniqueTexture(cstr file, SDL_Renderer& ren)
{
    uint64_t crc_hash = 0;
    SDL_Texture* tmp = NULL;

    //Let's compute the crc hash
    crc_hash = crc64_on_file_fast(file);

    //For safety's sake, let's lock the mutex
    pthread_mutex_lock(&mutex);

    //Let's see if the texture was already loaded!
    if(hasTexture(crc_hash))
    {
        tmp = storage[crc_hash];
        textureLife[tmp]++;
        //For sanity's sake, let's unlock the mutex so we don't get stuck!
        pthread_mutex_unlock(&mutex);
        return tmp;
    }

    //If we get here, the caller wants a texture handle but the texture was never loaded in the first place
    tmp = createTexture(file, ren);
    storage.insert(crc_hash, tmp);
    hashCache.insert(tmp, crc_hash);
    textureLife.insert(tmp, 1);

    //For sanity's sake, let's unlock the mutex so we don't get stuck!
    pthread_mutex_unlock(&mutex);

    return tmp;
}

void TextureStore::DeleteUniqueTexture(SDL_Texture* tex)
{
    uint64_t crc_hash;
    uint64_t tex_life = 0;
    //For safety's sake, let's lock the mutex
    pthread_mutex_lock(&mutex);
    if(hasHash(tex))
    {
        crc_hash = hashCache[tex];
        tex_life = textureLife[tex];
        if(hasTexture(crc_hash) && tex_life == 0)
        {
            storage.remove(crc_hash);
            hashCache.remove(tex);
            textureLife.remove(tex);
        }
        else
            textureLife[tex]--;//Decrement the life of the texture!
    }
    //For sanity's sake, let's unlock the mutex so we don't get stuck!
    pthread_mutex_unlock(&mutex);

    //Destroy the texture
    if(tex_life == 0)
        SDL_DestroyTexture(tex);
}

bool TextureStore::hasHash(SDL_Texture* tex)
{
    uint64_t hash;
    return hashCache.search(tex, hash);
=======
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

>>>>>>> origin/TheIllusiveMan
}

