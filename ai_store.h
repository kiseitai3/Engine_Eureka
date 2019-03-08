#ifndef AI_STORE_H_INCLUDED
#define AI_STORE_H_INCLUDED
#include <iostream>
#include <string>
#include <pthread.h>
#include "scriptwrap.h"
#include "BST.h"
#include "typedefs.h"

class AIStore
{
public:
    AIStore();

    ScriptWrap* LoadUniqueAI(cstr file);
    void DeleteUniqueAI(ScriptWrap* tex);
    bool hasAI(uint64_t hash);
    bool hasHash(ScriptWrap* tex);
    void IncrementTextLife(ScriptWrap* tex);

private:
    BinarySearchTree<uint64_t, ScriptWrap*> storage;//Storage of unmodified textures
    BinarySearchTree<ScriptWrap*, uint64_t> hashCache;//Cache of hashes that can be accessed when we get the texture pointer
    BinarySearchTree<ScriptWrap*, uint64_t> AILife;//Storage of lifetime of texture!
    pthread_mutex_t mutex;

    //Methods

    ScriptWrap* createAI(cstr file);
};
#endif // AI_STORE_H_INCLUDED
