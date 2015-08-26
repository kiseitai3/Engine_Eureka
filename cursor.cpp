#include "eureka.h"
#include "scriptwrap.h"

Cursor::Cursor(Game* owner)
{
    owner_ref = owner;
    mutex_cursor_id = owner->SpawnMutex();
    //Hide system cursor
    SDL_ShowCursor(SDL_DISABLE);
}

size_t Cursor::RegisterCursor(cstr file)
{
    size_t id;
    CursorNode tmp;
    data_base curDOM(file);
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    id = generateID();
    tmp.id = id;
    tmp.name = curDOM.GetStrFromData("cur_name");
    tmp.soundFile = curDOM.GetStrFromData("cur_sound_file");
    tmp.cursor = new draw_base();
    tmp.cursor->Load_Texture(curDOM.GetStrFromData("cur_texture").c_str(), owner_ref->GetRenderer(), curDOM.GetIntFromData("cur_fps"));
    if(!tmp.cursor)
        std::cout << "Cursor: error loading cursor!" << std::endl;
    cursors.insert(id, tmp);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_cursor_id);
    return id;
}

void Cursor::ToggleMouseGrab()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    centered = !centered;
    SDL_SetRelativeMouseMode((SDL_bool)centered);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_cursor_id);
}

void Cursor::DrawCursor()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    selected.cursor->apply_surface(owner_ref->GetRawInput().mx, owner_ref->GetRawInput().my, owner_ref->GetRenderer());
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_cursor_id);
}

void Cursor::ChangeToCursor(size_t id)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    cursors.search(id, selected);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_cursor_id);
}

size_t Cursor::generateID()
{
    size_t id = hasher();
    CursorNode tmp;
    while(cursors.search(id, tmp))
    {
        id = hasher();
    }

    return id;
}

Cursor::~Cursor()
{
    std::vector<CursorNode> tmpObjs;
    draw_base* tmp;
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    tmpObjs = cursors.getContents();
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        tmp = tmpObjs[i].cursor;
        if(tmp)
            delete tmp;
    }
    //Restore system cursor
    SDL_ShowCursor(SDL_ENABLE);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_cursor_id);
    owner_ref->DeleteMutex(mutex_cursor_id);
}