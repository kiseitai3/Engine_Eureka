#include "eureka.h"
#include "scriptwrap.h"

Cursor::Cursor(Game* owner)
{
    owner_ref = owner;
    mutex_cursor_id = owner->SpawnMutex();
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

size_t Cursor::LoadCursorScript(cstr file)
{
    size_t res = SUCCESS;
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    if(cursorScript)
        res = ALREADY_HAS_SCRIPT;
    else
    {
        cursorScript = new ScriptWrap(file);
        if(!cursorScript)
            res = FAILED_TO_LOAD;
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_cursor_id);
    return res;
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

void Cursor::UpdateCursor(SDL_Event *e)
{
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    if(e->button.button == SDL_BUTTON_LEFT)
        state.click = true;
    else
        state.click = false;
    state.X = e->motion.x;
    state.Y = e->motion.y;
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_cursor_id);
}

cursor_state Cursor::GetCursorState() const
{
    return state;
}

void Cursor::DrawCursor()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_cursor_id);
    selected.cursor->apply_surface(state.X, state.Y, owner_ref->GetRenderer());
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
    if(cursorScript)
        delete cursorScript;
    tmpObjs = cursors.getContents();
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        tmp = tmpObjs[i].cursor;
        if(tmp)
            delete tmp;
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_cursor_id);
    owner_ref->DeleteMutex(mutex_cursor_id);
}
