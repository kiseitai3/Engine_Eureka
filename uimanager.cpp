#include "uimanager.h"

UIManager::UIManager(Game* owner)
{
    owner_ref = owner;
    //Create mutex
    mutex_ui_id = owner.SpawnMutex();
}

UIManager::~UIManager()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_ui_id);
    //Get array of contents
    std::vector<UI*> tmpObjs = uis.getContents();
    //Update each object
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        if(tmpObjs[i])
            delete tmpObjs[i];
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_ui_id);
    //Unregister mutex
    owner_ref->DeleteMutex(mutex_ui_id);
}

size_t UIManager::RegisterUI(cstr file)
{
    size_t id = owner_ref->hasher();
    //Lock mutex
    owner_ref->LockMutex(mutex_ui_id);
    //Check for object existence and request a new hash if appropriate
    while(uiIDExists(id))
    {
        id = owner_ref->hasher();
    }
    //Create object
    uis.insert(id, new UI(file, owner_ref->GetRenderer()));
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_ui_id);
    return id;
}

UI& UIManager::GetUI(size_t ui_id)
{
    UI* tmp = NULL;
    //Lock mutex
    owner_ref->LockMutex(mutex_ui_id);
    //Grab object
    uis.search(ui_id, tmp);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_ui_id);
    return *tmp;
}

void UIManager::UnregisterUI(size_t ui_id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_ui_id);
    //Delete object
    uis.remove(ui_id);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_ui_id);
}

bool UIManager::uiIDExists(size_t id)
{
    UI* tmp = NULL;
    uis.search(id, tmp);
    if(tmp)
        return true;
    return false;
}

void UIManager::UIUpdate()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_ui_id);
    //Get array of contents
    std::vector<UI*> tmpObjs = uis.getContents();
    //Update each object
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        tmpObjs[i]->Update();
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_ui_id);
}

void UIManager::UIProcessEvents()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_ui_id);
    //Get array of contents
    std::vector<UI*> tmpObjs = uis.getContents();
    //Update each object
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        tmpObjs[i]->ProcessEvents(&owner_ref->GetEvents());
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_ui_id);
}

void UIManager::UIDraw()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_ui_id);
    //Get array of contents
    std::vector<UI*> tmpObjs = uis.getContents();
    //Update each object
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        tmpObjs[i]->Draw();
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_ui_id);
}

void_ptr helperUIDraw(void_ptr game)
{
    Game* gameObj = game;
    while(!gameObj->isEngineClosing())
    {
        gameObj->UIDraw();
    }
}

void_ptr helperUIProcessEvents(void_ptr game)
{
    Game* gameObj = game;
    while(!gameObj->isEngineClosing())
    {
        gameObj->UIProcessEvents();
    }
}

void_ptr helperUIUpdate(void_ptr game)
{
    Game* gameObj = game;
    while(!gameObj->isEngineClosing())
    {
        gameObj->UIUpdate();
    }
}
