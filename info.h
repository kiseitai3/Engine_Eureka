#ifndef INFO_H_INCLUDED
#define INFO_H_INCLUDED
#include <SDL.h>
#include <iostream>
#include <string>
#include <list>
#include "BST.h"
#include "typedefs.h"
#undef LocaleInfo
#undef GetLocaleInfo

//Engine name space macro
//ENGINE_NAMESPACE
class DataBase;

struct ExpansionItem
{
    size_t id;
    std::string name;
    std::string path;
    std::string description;
    ExpansionItem(size_t id, const std::string& name, const std::string& path, const std::string& descrip);
    ExpansionItem(const ExpansionItem& item);
    ExpansionItem();
};

struct LocaleItem
{
    std::string name;
    std::string path;
};

class ExpansionInfo
{
public:
    //dtor
    ~ExpansionInfo();
    //Loading methods
    void LoadExpansionInfo(cstr file);
    void LoadExpansionInfo(DataBase* db);
    //Getters
    std::string GetExpansionName(size_t id) const;
    std::string GetExpansionPath(size_t id) const;
    std::string GetExpansionDescription(size_t id) const;
    size_t GenerateExpansionID(const std::string& name) const;
    size_t GetExpansionCount() const;

    static const std::string INVALID;

private:
    BinarySearchTree<size_t, ExpansionItem*> mods;
};

class LocaleInfo
{
public:
    void LoadLocaleListFromLoc(const std::string& dir);
    void LoadLocaleListFromDB(DataBase* db);
    void AddLocaleToList(const std::string& name, const std::string& path);
    LocaleItem GetLocaleInfo(const std::string& name) const;
    LocaleItem GetLocaleInfo(size_t id) const;
    LocaleItem GetSelectedLocale() const;
    size_t GetLocaleItemCount() const;

private:
    LocaleItem selected;
    std::list<LocaleItem> locales;
};

class ScreenInfo
{
 public:
     ScreenInfo();
     /*Setter*/
     void SetScreenInfo(size_t displayCount = 1, size_t display = 0, size_t frames_per_second = 60,
                        size_t screenWidth = 640, size_t screenHeight = 480, size_t screenBPP = 32, const std::string& driver = ScreenInfo::OPENGL,
                        size_t screenmode = ScreenInfo::FULLSCREEN);
     void SetScreenLoc(int x = 0, int y = 0);
     void SetScreenDeviceStr(const std::string& gfx_card);
     void AutoDetectVideoCard();
     /*Getters*/
     size_t GetMaxFramesPerSec() const;
     size_t GetScreenWidth() const;
     size_t GetScreenHeight() const;
     math_point& GetScreenLoc();
     size_t GetScreenBPP() const;
     size_t GetDisplayIndex() const;
     size_t GetDisplayCount() const;
     size_t GetScreenMode() const;
     std::string GetRenderDriver() const;
     std::string GetGraphicsDeviceName() const;


     //globals
     const static size_t FULLSCREEN;
     const static size_t RESIZABLE;
     const static size_t MAXIMIZED;
     const static std::string OPENGL;
     const static std::string DIRECT3D;
     const static std::string SOFTWARE;
 private:
    size_t m_frames_per_second, m_screen_width, m_screen_height, m_screen_bpp, m_display, m_display_count, m_screenmode;
    std::string video_driver, video_card;
    math_point screenLoc;
};

class SoundInfo
{
  public:
      SoundInfo();
      /*Setter*/
      void SetSoundInfo(size_t frequency = 22050, size_t channels = 2, size_t chunksize = 4096)  ;
      void SetSoundVolume(size_t vol);
      void SetSoundDeviceStr(const std::string& sound_card);
      void AutoDetectSoundCard();
      /*Getter*/
      size_t GetSoundFrequency() const;
      size_t GetSoundChannels() const;
      size_t GetSoundChunkSize() const;
      size_t GetMasterVolume() const;
      std::string GetSoundDeviceName() const;
  private:
    size_t m_frequency, m_channels, m_chunksize, m_volume;
    std::string card;
};

class GameInfo : public ScreenInfo, public SoundInfo, public ExpansionInfo, public LocaleInfo, public SDL_RendererInfo
{
public:
    GameInfo();
    /*Setter*/
    void SetInfo(const std::string& rootdata = EMPTY, const std::string& mod = EMPTY, const std::string& saveloc = EMPTY,
            const std::string& name = EMPTY, const std::string& icon = EMPTY, const std::string& renderQuality = EMPTY,
            size_t displayCount = 1, size_t display = 0, size_t frames_per_second = 60, size_t screenWidth = 640, size_t screenHeight = 480, size_t screenBPP = 32,
            size_t blitlevels = 50, size_t screenmode = ScreenInfo::FULLSCREEN, const std::string& driver = ScreenInfo::OPENGL,
            size_t frequency = 22050, size_t channels = 2, size_t chunksize = 4096);
    /*Getters*/
    std::string GetRootDirectory() const;
    std::string GetModName() const;
    std::string GetGameName() const;
    std::string GetIconLoc() const;
    size_t GetBlitLevels() const;
    std::string GetRenderQuality() const;

private:
    /*These are the key variables of the game*/
    static const std::string EMPTY;
    std::string m_rootdata, m_mod, m_saveloc, m_name, m_icon, m_render_quality;
    size_t m_blitlevels;
};

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // INFO_H_INCLUDED
