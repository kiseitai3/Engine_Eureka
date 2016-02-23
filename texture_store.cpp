#include <cstdlib>
#include "texture_store.h"
#include "data_base.h"
#include <crc.h>
#include <SDL.h>
#include <SDL_image.h>

typedef struct TexturePacket
{
    SDL_Texture* texture;
    SDL_Surface* tmp;
    uint64_t hash;
    uint64_t textureLife;
}TextureNode;

SDL_Texture* getTextureFromNode(TextureNode* tex)
{
    return tex->texture;
}

uint64_t getTextureHash(TextureNode* tex)
{
    tex->hash;
}

TextureStore::TextureStore()
{
    mutex = PTHREAD_MUTEX_INITIALIZER;
}

bool TextureStore::hasTexture(uint64_t hash)
{
    TextureNode* tmp;
    return storage.search(hash, tmp);
}

TextureNode TextureStore::createTexture(const std::string& file, SDL_Renderer& ren)
{
    TextureNode tex;
    tex.texture = NULL;

    if(file.find(data_base::BUFFER) < file.size())
    {
        SDL_RWops* rwops = SDL_RWFromMem((void*)file.substr(strlen(data_base::BUFFER)).c_str(), file.size());
        if(rwops)
            tex.tmp = IMG_Load_RW(rwops, 0);
        else
            std::cout << "TextureStore: SDL failed to build rwops for texture buffer!" << std::endl;
    }
    else
        tex.tmp = IMG_Load(file.c_str());

    if(!tex.tmp)
    {
        std::cout << "Failed to load the surface!" << std::endl;
    }
    else
    {
        SDL_SetColorKey(tex.tmp, SDL_TRUE, SDL_MapRGB( tex.tmp->format, 0xFF, 0xFF, 0xFF ));
        tex.texture = SDL_CreateTextureFromSurface(&ren, tex.tmp);
        //SDL_FreeSurface(tmp);
    }

    return tex;
}

TextureNode* TextureStore::LoadUniqueTexture(const std::string& file, SDL_Renderer& ren)
{
    uint64_t crc_hash = 0;
    TextureNode* tmp = new TextureNode;

    //Let's compute the crc hash
    if(file.find(data_base::BUFFER) > file.size())
        crc_hash = crc64_on_file_fast(file.c_str());
    else
        crc_hash = crc64(file.c_str(), file.size());

    //For safety's sake, let's lock the mutex
    pthread_mutex_lock(&mutex);

    //Let's see if the texture was already loaded!
    if(hasTexture(crc_hash))
    {
        storage[crc_hash]->textureLife++;
        //For sanity's sake, let's unlock the mutex so we don't get stuck!
        pthread_mutex_unlock(&mutex);
        return storage[crc_hash];
    }

    //If we get here, the caller wants a texture handle but the texture was never loaded in the first place
    *tmp = createTexture(file, ren);
    tmp->hash = crc_hash;
    tmp->textureLife = 1;
    storage.insert(crc_hash, tmp);

    //For sanity's sake, let's unlock the mutex so we don't get stuck!
    pthread_mutex_unlock(&mutex);

    return tmp;
}

void TextureStore::DeleteUniqueTexture(TextureNode* tex)
{
    uint64_t crc_hash;
    uint64_t tex_life = 0;
    //For safety's sake, let's lock the mutex
    pthread_mutex_lock(&mutex);
    if(hasHash(tex))
    {
        crc_hash = tex->hash;
        tex_life = tex->textureLife;
        if(hasTexture(crc_hash) && tex_life == 0)
        {
            storage.remove(crc_hash);
        }
        else
            tex->textureLife--;//Decrement the life of the texture!
    }
    //For sanity's sake, let's unlock the mutex so we don't get stuck!
    pthread_mutex_unlock(&mutex);

    //Destroy the texture
    if(tex_life == 0)
    {
        SDL_FreeSurface(tex->tmp);
        SDL_DestroyTexture(tex->texture);
        delete tex;
    }
}

bool TextureStore::hasHash(TextureNode* tex)
{
    return tex->hash > 0;
}

void TextureStore::IncrementTextLife(TextureNode* tex)
{
    tex->textureLife++;
}

TextureNode* TextureStore::changeTexture(TextureNode* oldTex, TextureNode* newTex)
{
    DeleteUniqueTexture(oldTex);
    IncrementTextLife(newTex);
    return newTex;
}
