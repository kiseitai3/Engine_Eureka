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

class Cursor
{
public:
    //Ctors and dtor
    Cursor(Game* owner);
    ~Cursor();
    void initCursorSys();

    //Setters
    size_t RegisterCursor(cstr file);
    void ChangeToCursor(size_t id);
    void ToggleMouseGrab();

    //Manipulation
    void DrawCursor();
    void PlayCursorSound();

private:
    BinarySearchTree<size_t, CursorNode> cursors;
    CursorNode selected;
    Game* owner_ref;
    size_t mutex_cursor_id;
    bool centered;

    //methods
    size_t generateID();
};


#endif // CURSOR_H_INCLUDED
