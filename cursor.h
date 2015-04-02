#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED
#include <istream>
#include "BST.h"
#include "typedefs.h"

class Game;
class draw_base;

struct CursorNode
{
    std::string name;
    std::string soundFile;
    size_t id;
    draw_base* cursor;
    CursorNode()
    {
        cursor = NULL;
    }
};

struct cursor_state : public math_point
{
    bool click;
};

class Cursor
{
public:
    //Ctors and dtor
    Cursor(Game* owner);
    ~Cursor();

    //Setters
    size_t LoadCursorScript(cstr file);
    size_t RegisterCursor(cstr file);
    void UpdateCursor(SDL_Event* e);
    void ChangeToCursor(size_t id);
    void ToggleMouseGrab();

    //Getters
    cursor_state GetCursorState() const;

    //Manipulation
    void DrawCursor();

    //vars
    enum CursorScriptResult
    {
        SUCCESS, ALREADY_HAS_SCRIPT, FAILED_TO_LOAD
    };

private:
    ScriptWrap* cursorScript;
    BinarySearchTree<size_t, CursorNode> cursors;
    CursorNode selected;
    cursor_state state;
    Game* owner_ref;
    size_t mutex_cursor_id;
    bool centered;

    //methods
    size_t generateID();
};


#endif // CURSOR_H_INCLUDED
