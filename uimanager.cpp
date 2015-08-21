//#define EUREKA_EXPORT
#include "uimanager.h"
#include "eureka.h"
#include "input.h"

//Engine name space macro
//ENGINE_NAMESPACE



UIManager::UIManager(Game* owner)
{
    owner_ref = owner;
    //Create mutex
    mutex_ui_id = owner->SpawnMutex();
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
    size_t id = hasher();
    //Lock mutex
    owner_ref->LockMutex(mutex_ui_id);
    //Check for object existence and request a new hash if appropriate
    while(uiIDExists(id))
    {
        id = hasher();
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

size_t UIManager::FindUIByName(const std::string& name)
{
    size_t id = 0;
    //Lock mutex
    owner_ref->LockMutex(mutex_ui_id);
    std::vector<UI*> tmp = uis.getContents();
    for(size_t i = 0; i < tmp.size(); i++)
    {
        if(tmp[i]->GetName() == name)
        {
            id = tmp[i]->GetID();
            break;
        }
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_ui_id);
    return id;
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
        if(tmpObjs[i]->isVisible())
            tmpObjs[i]->Update();
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_ui_id);
}

void UIManager::UIProcessEvents()
{
    Button* bt = NULL;
    textbox* txt = NULL;
    raw_input in = owner_ref->GetRawInput();
    //Lock mutex
    owner_ref->LockMutex(mutex_ui_id);
    //Get array of contents
    std::vector<UI*> tmpObjs = uis.getContents();
    //Update each object
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        if(tmpObjs[i]->isVisible())
        {
            tmpObjs[i]->ProcessEvents(in.mx, in.my);
            if(tmpObjs[i]->isInside(in.mx, in.my))
            {
                bt = tmpObjs[i]->GetButtonByLoc(in.mx, in.my);
                txt = tmpObjs[i]->GetTextboxByLoc(in.mx, in.my);
            }
        }
    }
    //Let's run the events on selected object
    owner_ref->ProcessUIInput(bt, txt);
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
        if(tmpObjs[i]->isVisible())
            tmpObjs[i]->Draw();
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_ui_id);
}

void_ptr helperUIDraw(void_ptr game)
{
    Game* gameObj = (Game*)game;
    while(!gameObj->isEngineClosing())
    {
        gameObj->UIDraw();
    }
}

void_ptr helperUIProcessEvents(void_ptr game)
{
    Game* gameObj = (Game*)game;
    while(!gameObj->isEngineClosing())
    {
        gameObj->UIProcessEvents();
    }
}

void_ptr helperUIUpdate(void_ptr game)
{
    Game* gameObj = (Game*)game;
    while(!gameObj->isEngineClosing())
    {
        gameObj->UIUpdate();
    }
}

//End of namespace macro
//ENGINE_NAMESPACE_END
