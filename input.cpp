#include <SDL.h>
#include <string>
#include "physics.h"
#include "input.h"
#include "conversion.h"
#include "eureka.h"
#include "database.h"
#include "game.h"

//Engine name space macro
//ENGINE_NAMESPACE


InputMouse::InputMouse()
{
}

void InputMouse::ChangeCoordinates(int x, int y, int z)// This method will be useful in putting the mouse wherever we want when the user triggers a script
{
    coordinates.X = x;
    coordinates.Y = y;
    coordinates.Z = z;
}

math_point InputMouse::GetCoordinates()
{
    return coordinates;
}

InputKeyboard::InputKeyboard()//constructor
{
    text = "";
    textMode = false;
    textReady = false;
}

void InputKeyboard::feedBuffer(std::string& buffer)
{
    text += buffer;
}

void InputKeyboard::toggleTextMode()//Activates /deactivates text mode.
{
    if(textMode == false)
    {
        textMode = true;
        textReady = false;
    }
    else
    {
        textMode = false;
        textReady = true;
    }
}

const char* InputKeyboard::getText()//if textReady is ready, return the available text and set text = "". Else, simply return text but do not modify it!
{
    if(textMode)
    {
        return text.c_str();
    }
    return NULL;
}

bool InputKeyboard::GetTextMode() const
{
    return textMode;
}

void InputKeyboard::StartTextInput()
{
    SDL_StartTextInput();
}

void InputKeyboard::StopTextInput()
{
    SDL_StopTextInput();
}

Input::Input(Game* owner)
{
    owner_ref = owner;
    script = NULL;
}

void Input::LoadCursors(cstr file)
{
    data_base DOM(file);
    size_t cursorCount = DOM.GetIntFromData("cursor_count");
    std::string path = "";
    std::string name = "";

    for(size_t i = 0; i < cursorCount; i++)
    {
        name = DOM.GetStrFromData("cursor_" + intToStr(i) + "_name");
        path = DOM.GetStrFromData("cursor_" + intToStr(i) + "_file");
        cursors[name] = owner_ref->RegisterCursor(path.c_str());
    }
}

void Input::LoadKeyScript(cstr file)
{
    deleteScript();
    script = new ScriptWrap(file);
}

void Input::LoadCurrentKeyBindings(size_t db_id)
{
    DataBase* db = owner_ref->GetDataBase(db_id);
    int key;
    std::string fxn = "";

    db->query(db->prepareStatement("keybindings", "keys,function","","","",SELECT));
    for(size_t i = 0; i < keybindingsCount; i++)
    {
        db->GetResult(key);
        db->GetResult(fxn, 1);
        keys.insert(key, KeyNode(key, fxn));
    }
}

void Input::LoadDefaultKeyBindings(cstr file)
{
    data_base DOM(file);
    keybindingsCount = DOM.GetIntFromData("key_count");
    size_t key;
    std::string fxn = "";
    std::string name = "";

    for(size_t i = 0; i < keybindingsCount; i++)
    {
        name = "key_" + intToStr(i);
        key = DOM.GetIntFromData(name);
        name = "key_" + intToStr(i) + "_function";
        fxn = DOM.GetStrFromData(name);
        keys.insert(key, KeyNode(key, fxn));
    }
}

void Input::ChangeKeyBinding(size_t previousKey, size_t newkey)
{
    std::string val = keys[previousKey].val;
    keys.remove(previousKey);
    keys.insert(newkey, KeyNode(newkey, val));
}

void Input::SaveKeyBindings(size_t db_id)
{
    DataBase* db = owner_ref->GetDataBase(db_id);
    std::vector<KeyNode> tmpObjs = keys.getContents();
    std::string data = "";

    for(std::vector<KeyNode>::iterator itr = tmpObjs.begin(); itr != tmpObjs.end(); itr++)
    {
        data = intToStr(itr->key) + itr->val;
        db->query(db->prepareStatement("keybindings", data,std::string("keys=")+intToStr(itr->key),"","",UPDATE | WHERE));
    }
}

const raw_input& Input::GetRawInput() const
{
    return state;
}

void Input::ProcessUIInput(Button* bt, textbox* txt)
{
    script->ClearArgs(3);
    script->AddArgument((void_ptr)owner_ref);
    script->AddArgument((void_ptr)bt);
    script->AddArgument((void_ptr)txt);
    script->executeFunction("ProcessUIInput", script->NO_ARGS);
}

void Input::ProcessUnitInput(Unit* unit)
{
    script->ClearArgs(2);
    script->AddArgument((void_ptr)owner_ref);
    script->AddArgument((void_ptr)unit);
    script->executeFunction("ProcessUnitInput", script->NO_ARGS);
}

void Input::UpdateInput(SDL_Event* pEvent)
{
    switch(pEvent->type)
    {
    //Text input
    case SDL_TEXTINPUT:
        state.txtBuffer = pEvent->text.text;
        state.eventType = TEXTINPUT;
        break;
    case SDL_TEXTEDITING:
        state.txt_editing_len = pEvent->edit.length;
        state.txtBuffer = pEvent->edit.text;
        state.eventType = TEXTINPUT;
        break;
    //Keyboard
    case SDL_KEYDOWN:
    case SDL_KEYUP:
        state.key = pEvent->key.keysym.scancode;
        state.state = pEvent->key.state;
        state.type = pEvent->key.type;
        state.winID = pEvent->key.windowID;
        state.eventType = KEYBOARD;
        break;
    //Mouse
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        state.mb = pEvent->button.button;
        state.state = pEvent->button.state;
        state.type = pEvent->button.type;
        state.clicks = pEvent->button.clicks;
        state.mx = pEvent->button.x;
        state.my = pEvent->button.y;
        state.winID = pEvent->button.windowID;
        state.eventType = MOUSE;
        break;
    case SDL_MOUSEMOTION:
        state.state = pEvent->motion.state;
        state.type = pEvent->motion.type;
        state.mx = pEvent->motion.x;
        state.my = pEvent->motion.y;
        state.winID = pEvent->motion.windowID;
        state.eventType = MOUSEMOTION;
        break;
    //Touch
    case SDL_FINGERDOWN:
    case SDL_FINGERMOTION:
    case SDL_FINGERUP:
        state.type = pEvent->tfinger.type;
        state.tx = pEvent->tfinger.x;
        state.ty = pEvent->tfinger.y;
        state.tdx = pEvent->tfinger.dx;
        state.tdy = pEvent->tfinger.dy;
        state.winID = pEvent->tfinger.touchId;
        state.pressure = pEvent->tfinger.pressure;
        state.eventType = TOUCH;
        break;
    case SDL_CONTROLLERBUTTONUP:
    case SDL_CONTROLLERBUTTONDOWN:
        break;
    default:
        std::cout << "Unknown input type!" << std::endl;
    }

    script->ClearArgs(1);
    script->AddArgument((void_ptr)owner_ref);
    script->executeFunction("UpdateInput", ScriptWrap::NO_ARGS);
}

void Input::deleteScript()
{
    if(script)
        delete script;
}

Input::~Input()
{
    deleteScript();
}

//End of namespace macro
//ENGINE_NAMESPACE_END
