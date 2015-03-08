#ifndef UIMANAGER_H_INCLUDED
#define UIMANAGER_H_INCLUDED
#include <iostream>
#include <string>
#include "ui.h"
#include "BST.h"
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


class Game;

class EUREKA UIManager
{
public:
    //ctors and dtorp
    UIManager(Game* owner);
    ~UIManager();

    //Setter
    size_t RegisterUI(cstr file);
    void UnregisterUI(size_t ui_id);

    //Getter
    UI& GetUI(size_t ui_id);
    size_t FindUIByName(const std::string& name);
    bool uiIDExists(size_t id);//Checks if there's a UI resgistered under the specified id

    //Execution
    void UIUpdate();
    void UIProcessEvents();
    void UIDraw();

private:
    BinarySearchTree<size_t, UI*> uis;
    Game* owner_ref;
    size_t mutex_ui_id;

    //Methods

};

//Helper functions
void_ptr helperUIUpdate(void_ptr game);
void_ptr helperUIProcessEvents(void_ptr game);
void_ptr helperUIDraw(void_ptr game);

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // UIMANAGER_H_INCLUDED
