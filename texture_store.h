#ifndef TEXTURE_STORE_H_INCLUDED
#define TEXTURE_STORE_H_INCLUDED
#include <iostream>
#include <string>
#include <SDL.h>
#include <pthread.h>
#include "BST.h"
#include "typedefs.h"

typedef struct TexturePacket TextureNode;

class TextureStore
{
public:
    TextureStore();

    TextureNode* LoadUniqueTexture(const std::string& file, SDL_Renderer& ren);
    void DeleteUniqueTexture(TextureNode* tex);
    bool hasTexture(uint64_t hash);
    bool hasHash(TextureNode* tex);
    void IncrementTextLife(TextureNode* tex);
    TextureNode* changeTexture(TextureNode* oldTex, TextureNode* newTex);

private:
    BinarySearchTree<uint64_t, TextureNode*> storage;//Storage of unmodified textures
    pthread_mutex_t mutex;

    //Methods

    TextureNode createTexture(const std::string& file, SDL_Renderer& ren);
};

SDL_Texture* getTextureFromNode(TextureNode* tex);
uint64_t getTextureHash(TextureNode* tex);


#endif // TEXTURE_STORE_H_INCLUDED
