#include "info.h"
#include "database.h"
#include "data_base.h"
#include <GL/gl.h>
#undef LocaleInfo
#undef GetLocaleInfo
//Engine name space macro
//ENGINE_NAMESPACE

/*ScreenInfo*/

const std::string ScreenInfo::OPENGL = "opengl";
const std::string ScreenInfo::DIRECT3D = "direct3d";
const std::string ScreenInfo::SOFTWARE = "software";
const size_t ScreenInfo::FULLSCREEN = SDL_WINDOW_FULLSCREEN;
const size_t ScreenInfo::RESIZABLE = SDL_WINDOW_RESIZABLE;
const size_t ScreenInfo::MAXIMIZED = SDL_WINDOW_MAXIMIZED;

ScreenInfo::ScreenInfo()
{
    m_frames_per_second = 0;
    m_screen_width = 0;
    m_screen_height = 0;
    m_screen_bpp = 0;
}

void ScreenInfo::SetScreenInfo(size_t displayCount, size_t display, size_t frames_per_second, size_t screenWidth,
                               size_t screenHeight, size_t screenBPP, const std::string& driver, size_t screenmode)
{
    m_display_count = displayCount;
    m_display = display;
    m_frames_per_second = frames_per_second;
    m_screen_width = screenWidth;
    m_screen_height = screenHeight;
    m_screen_bpp = screenBPP;
    m_screenmode = screenmode;
    video_driver = driver;
}

void ScreenInfo::SetScreenLoc(int x, int y)
{
    screenLoc.X = x;
    screenLoc.Y = y;
}

void ScreenInfo::SetScreenDeviceStr(const std::string& gfx_card)
{
    video_card = gfx_card;
}

void ScreenInfo::AutoDetectVideoCard()
{
    std::string gfx_str;
    gfx_str = (char*)glGetString(GL_VENDOR);
    gfx_str += " ";
    gfx_str += (char*)glGetString(GL_RENDERER);
    SetScreenDeviceStr(gfx_str);
}

math_point& ScreenInfo::GetScreenLoc()
{
    return screenLoc;
}

size_t ScreenInfo::GetMaxFramesPerSec() const
{
    return m_frames_per_second;
}

size_t ScreenInfo::GetScreenBPP() const
{
    return m_screen_bpp;
}

size_t ScreenInfo::GetScreenHeight() const
{
    return m_screen_height;
}

size_t ScreenInfo::GetScreenWidth() const
{
    return m_screen_width;
}

size_t ScreenInfo::GetDisplayIndex() const
{
    return m_display;
}

size_t ScreenInfo::GetDisplayCount() const
{
    return m_display_count;
}

size_t ScreenInfo::GetScreenMode() const
{
    return m_screenmode;
}

std::string ScreenInfo::GetRenderDriver() const
{
    return video_driver;
}

std::string ScreenInfo::GetGraphicsDeviceName() const
{
    return video_card;
}
/*End of ScreenInfo*/

/*SoundInfo*/
SoundInfo::SoundInfo()
{
    m_frequency =0;
    m_channels = 0;
    m_chunksize = 0;
}

void SoundInfo::SetSoundInfo(size_t frequency, size_t channels, size_t chunksize)
{
    m_frequency = frequency;
    m_channels = channels;
    m_chunksize = chunksize;
}

void SoundInfo::SetSoundVolume(size_t vol)
{
    m_volume = vol;
}

void SoundInfo::SetSoundDeviceStr(const std::string& sound_card)
{
    card = sound_card;
}

void SoundInfo::AutoDetectSoundCard()
{
    SetSoundDeviceStr(SDL_GetAudioDeviceName(0,0));
}

size_t SoundInfo::GetSoundFrequency() const
{
    return m_frequency;
}

size_t SoundInfo::GetSoundChannels() const
{
    return m_channels;
}

size_t SoundInfo::GetSoundChunkSize() const
{
    return m_chunksize;
}

size_t SoundInfo::GetMasterVolume() const
{
    return m_volume;
}

std::string SoundInfo::GetSoundDeviceName() const
{
    return card;
}

/*End of SoundInfo*/

/*GameInfo*/
const std::string GameInfo::EMPTY = "";

GameInfo::GameInfo():ScreenInfo(), SoundInfo(), ExpansionInfo(), LocaleInfo(), SDL_RendererInfo()
{
    m_rootdata = "";
    m_mod = "";
    m_saveloc = "";
    m_name = "";
    m_icon = "";
    m_render_quality = "";
    m_blitlevels = 0;
}

void GameInfo::SetInfo(const std::string& rootdata, const std::string& mod, const std::string& saveloc,
            const std::string& name, const std::string& icon, const std::string& renderQuality,
            size_t displayCount, size_t display, size_t frames_per_second, size_t screenWidth, size_t screenHeight, size_t screenBPP,
            size_t blitlevels, size_t screenmode, const std::string& driver, size_t frequency, size_t channels, size_t chunksize)
{
    SetScreenInfo(displayCount, display, frames_per_second, screenWidth, screenHeight, screenBPP, driver, screenmode);
    SetSoundInfo(frequency, channels, chunksize);
    m_rootdata = rootdata;
    m_mod = mod;
    m_saveloc = saveloc;
    m_name = name;
    m_icon = icon;
    m_render_quality = renderQuality;
    m_blitlevels = blitlevels;
}
std::string GameInfo::GetRootDirectory() const
{
    return m_rootdata;
}

std::string GameInfo::GetModName() const
{
    return m_mod;
}

std::string GameInfo::GetGameName() const
{
    return m_name;
}

std::string GameInfo::GetIconLoc() const
{
    return m_icon;
}

size_t GameInfo::GetBlitLevels() const
{
    return m_blitlevels;
}

std::string GameInfo::GetRenderQuality() const
{
    return m_render_quality;
}
/*End of GameInfo*/

/*ExpansionItem*/
ExpansionItem::ExpansionItem(const ExpansionItem& item)
{
    id = item.id;
    name = item.name;
    path = item.path;
    description = item.description;
}

ExpansionItem::ExpansionItem(size_t ID, const std::string& n, const std::string& p, const std::string& descrip)
{
    id = ID;
    name = n;
    path = p;
    description = descrip;
}

ExpansionItem::ExpansionItem()
{
    id = 0;
    name = "";
    path = "";
}

/*ExpansionInfo*/

const std::string ExpansionInfo::INVALID = "<invalid>";

ExpansionInfo::~ExpansionInfo()
{
    //delete all expansion items
    std::vector<ExpansionItem*> tmpObjs = mods.getContents();
    for(size_t i = 0; i < tmpObjs.size(); i++)
    {
        if(tmpObjs[i])
            delete tmpObjs[i];
    }
}

size_t ExpansionInfo::GenerateExpansionID(const std::string& name) const
{
    size_t val = 0;
    for(size_t i = 0; i < name.size(); i++)
    {
        val += name[i];
    }
    return val;
}

std::string ExpansionInfo::GetExpansionName(size_t id) const
{
    ExpansionItem* tmp = NULL;
    mods.search(id, tmp);
    if(tmp)
        return tmp->name;
    return INVALID;
}

std::string ExpansionInfo::GetExpansionPath(size_t id) const
{
    ExpansionItem* tmp = NULL;
    mods.search(id, tmp);
    if(tmp)
        return tmp->path;
    return INVALID;
}

std::string ExpansionInfo::GetExpansionDescription(size_t id) const
{
    ExpansionItem* tmp = NULL;
    mods.search(id, tmp);
    if(tmp)
        return tmp->description;
    return INVALID;
}

size_t ExpansionInfo::GetExpansionCount() const
{
    return mods.size();
}

void ExpansionInfo::LoadExpansionInfo(cstr file)
{
    data_base data(file);
    std::string name;
    ExpansionItem tmp;
    int modCount = 0;

    modCount = data.GetIntFromData("mod_number");
    for(int i = 0; i < modCount; i++)
    {
        name = "mod_" + intToStr(i);
        tmp.name = data.GetStrFromData(name + "_name");
        tmp.path = data.GetStrFromData(name + "_path");
        tmp.id = GenerateExpansionID(tmp.name);
        mods.insert(tmp.id, new ExpansionItem(tmp));
    }
}

void ExpansionInfo::LoadExpansionInfo(DataBase* db)
{
    int rowCount = 0;
    ExpansionItem tmp;

    //First, we get the number of records in the database!
    db->query(db->prepareStatement("modifications", "id","","","",SELECT));
    db->GetResult(rowCount);
    //Now we go through every record until the end
    for(int i = 0; i < rowCount; i++)
    {
        db->query(db->prepareStatement("modifications", "name,path","id=" + intToStr(i),"","",SELECT));
        //extract record data
        db->GetResult(tmp.name);
        db->GetResult(tmp.path, 1);
        //Generate an actual id from the name field
        tmp.id = GenerateExpansionID(tmp.name);
        //copy this item into the heap and BST!
        mods.insert(tmp.id, new ExpansionItem(tmp));
    }
}

/*Locales*/
void LocaleInfo::LoadLocaleListFromLoc(const std::string& dir)
{
    data_base DOM;
    std::string path = dir + "/localelist.txt";
    DOM.OpenFile(path.c_str());

    for(size_t i = 0; i < DOM.GetIntFromData("locale_count"); i++)
    {
        path = dir + DOM.GetStrFromData("locale_" + intToStr(i));
        data_base localeF(path.c_str());
        AddLocaleToList(localeF.GetStrFromData("name"), path);
    }

}

void LocaleInfo::LoadLocaleListFromDB(DataBase* db)
{
    int rowCount = 0;
    int selectedItem = 0;
    LocaleItem tmp;

    //First, we get the number of records in the database!
    db->query(db->prepareStatement("locales", "id","","","",SELECT));
    db->GetResult(rowCount);
    //Now we go through every record until the end
    for(int i = 0; i < rowCount; i++)
    {
        db->query(db->prepareStatement("locales", "name,path,selected","id=" + intToStr(i),"","",SELECT));
        //extract record data
        db->GetResult(tmp.name);
        db->GetResult(tmp.path, 1);
        db->GetResult(selectedItem, 2);
        //copy this item into the list!
        locales.push_back(tmp);

        if(selectedItem)
            selected = tmp;
    }
}

void LocaleInfo::AddLocaleToList(const std::string& name, const std::string& path)
{
    LocaleItem i;
    i.name = name;
    i.path = path;
    locales.push_back(i);
}

LocaleItem LocaleInfo::GetLocaleInfo(const std::string& name) const
{
    for(std::list<LocaleItem>::const_iterator itr = locales.begin(); itr != locales.end(); itr++)
    {
        if(itr->name == name)
        {
            return *itr;
        }
    }
}

LocaleItem LocaleInfo::GetLocaleInfo(size_t id) const
{
    std::list<LocaleItem>::const_iterator itr = locales.begin();
    for(size_t i = 0; i != id || itr != locales.end(); i++)
    {
        itr++;
    }
    return *itr;
}

LocaleItem LocaleInfo::GetSelectedLocale() const
{
    return selected;
}

size_t LocaleInfo::GetLocaleItemCount() const
{
    return locales.size();
}

//End of namespace macro
//ENGINE_NAMESPACE_END
