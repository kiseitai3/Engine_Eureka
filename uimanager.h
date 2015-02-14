#ifndef UIMANAGER_H_INCLUDED
#define UIMANAGER_H_INCLUDED
#include <iostream>
#include <string>
#include "ui.h"
#include "BST.h"

class UIManager
{
public:
    //ctors and dtor
    UIManager(Game* owner);
    ~UIManager();

    //Setter
    size_t RegisterUI(cstr file);
    void UnregisterUI(size_t ui_id);

    //Getter
    UI& GetUI(size_t ui_id);

    //Execution
    void UIUpdate();
    void UIProcessEvents();
    void UIDraw();

private:
    BinarySearchTree<size_t, UI*> uis;
    Game* owner_ref;
    size_t mutex_ui_id;

    //Methods
    bool uiIDExists(size_t id);//Checks if there's a UI resgistered under the specified id
};

//Helper functions
void_ptr helperUIUpdate(void_ptr game);
void_ptr helperUIProcessEvents(void_ptr game);
void_ptr helperUIDraw(void_ptr game);

#endif // UIMANAGER_H_INCLUDED
