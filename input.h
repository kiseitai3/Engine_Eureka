#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
#include <SDL.h>
#include <string>
#include <map>
#include "BST.h"
#include "typedefs.h"

class Game;
class Button;
class textbox;
class Unit;
class ScriptWrap;

typedef struct raw_input
{
    size_t eventType, type;
    size_t state;
    size_t mx, my, mx2, my2, mb, clicks;
    size_t txt_editing_len;
    size_t key;
    size_t winID;
    double pressure, tx, ty, tdx, tdy;
    std::string txtBuffer, txtEditing;
};

typedef struct KeyNode
{
    size_t key;
    std::string val;
    KeyNode(size_t id, const std::string& value)
    {
        key = id;
        val = value;
    }
    KeyNode()
    {
        key = 0;
        val = "";
    }
};

enum EurekaEventTypes
{
    TEXTINPUT, KEYBOARD, MOUSE, TOUCH, CONTROLLER, MOUSEMOTION
};

class InputMouse
{
private:
    math_point coordinates; //coordinates of mouse pointer

public:
    InputMouse();
    void ChangeCoordinates(int x, int y, int z = 0);
    math_point GetCoordinates();
};

class InputKeyboard
{
private:
    std::string text;
    bool textMode;// flag that will change the context of key presses in the game
    bool textReady;// flag to prevent string from getting erased prior to display. The getText method is the only method that can reset the text variable to "".

public:
    InputKeyboard();
    void feedBuffer(std::string& buffer);
    void toggleTextMode();
    const char* getText();//Get copy of string!
    bool GetTextMode() const;
    void StartTextInput();
    void StopTextInput();
};

class Input : public InputMouse, public InputKeyboard
{
public:
    //ctor and dtor
    Input(Game* owner);
    ~Input();

    //Load
    void LoadCursors(cstr file);
    void LoadKeyScript(cstr file);
    void LoadDefaultKeyBindings(cstr file);
    void LoadCurrentKeyBindings(size_t db_id);

    //Update status
    void UpdateInput(SDL_Event* pEvent);
    void ProcessUIInput(Button* bt, textbox* txt);
    void ProcessUnitInput(Unit* unit);

    //Setter
    void ChangeKeyBinding(size_t previousKey, size_t newKey);
    void SaveKeyBindings(size_t db_id);

    //Getter
    const raw_input& GetRawInput() const;
    std::string GetKeyName(size_t key) const;

private:
    ScriptWrap* script;
    Game* owner_ref;
    raw_input state;
    std::map<std::string, size_t> cursors;
    BinarySearchTree<size_t, KeyNode> keys;

    size_t db_id, keybindingsCount;

    void clearKeys();
    void deleteScript();
};

#endif // INPUT_H_INCLUDED
