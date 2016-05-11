#include "eureka.h"
#include "scriptwrap.h"

Cursor::Cursor(Game* owner)
{
    owner_ref = owner;
    //Hide system cursor
    SDL_ShowCursor(SDL_DISABLE);
}

void Cursor::initCursorSys()
{
    mutex_cursor_id = owner_ref->SpawnMutex();
}

size_t Cursor::RegisterCursor(cstr file)
{
    size_t id, r_id;
    CursorNode tmp;
    data_base curDOM(file);
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    id = generateID();
    tmp.id = id;
    tmp.name = curDOM.GetStrFromData("cur_name");
    tmp.soundFile = curDOM.GetStrFromData("cur_sound_file");
    tmp.cursor = new draw_base();
    tmp.cursor->Load_Texture(curDOM.GetStrFromData("cur_texture").c_str(), owner_ref->GetRenderer(r_id), curDOM.GetIntFromData("cur_fps"));
    owner_ref->UnlockRenderer(r_id);
    if(!tmp.cursor)
        std::cout << "Cursor: error loading cursor!" << std::endl;
    cursors.insert(id, tmp);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_cursor_id);
    return id;
}

std::vector<size_t> Cursor::LoadCursors(cstr file)
{
    data_base DOM(file);
    std::vector<size_t> ids;
    size_t cursorCount = DOM.GetIntFromData("cursor_count");
    std::string path = "";
    std::string name = "";

    for(size_t i = 0; i < cursorCount; i++)
    {
        ids.push_back(owner_ref->RegisterCursor(path.c_str()));
    }

    return ids;
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
    size_t id;
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    selected.cursor->apply_surface(owner_ref->GetRawInput().mx, owner_ref->GetRawInput().my, owner_ref->GetRenderer(id));
    owner_ref->UnlockRenderer(id);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_cursor_id);
}

void Cursor::PlayCursorSound()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    owner_ref->AddSoundToQueue(selected.soundFile.c_str());
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

bool Cursor::RemoveCursor(size_t id)
{
    owner_ref->LockMutex(mutex_cursor_id);
    CursorNode tmp;
    cursors.search(id, tmp);
    if(tmp.name != selected.name)
    {
        delete tmp.cursor;
        cursors.remove(id);
        owner_ref->UnlockMutex(mutex_cursor_id);
        return true;
    }

    owner_ref->UnlockMutex(mutex_cursor_id);
    return false;
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
