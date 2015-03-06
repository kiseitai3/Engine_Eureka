#ifndef INFO_H_INCLUDED
#define INFO_H_INCLUDED
#include <iostream>
#include <string>
#include "typedefs.h"

class ScreenInfo
{
 public:
     ScreenInfo();
     /*Setter*/
     void SetScreenInfo(size_t displayCount = 1, size_t display = 0, size_t frames_per_second = 60, size_t screenWidth = 640, size_t screenHeight = 480, size_t screenBPP = 32);
     /*Getters*/
     size_t GetMaxFramesPerSec() const;
     size_t GetScreenWidth() const;
     size_t GetScreenHeight() const;
     math_point& GetScreenLoc();
     size_t GetScreenBPP() const;
     size_t GetDisplayIndex() const;
     size_t GetDisplayCount() const;
 private:
    size_t m_frames_per_second, m_screen_width, m_screen_height, m_screen_bpp, m_display, m_display_count;
    math_point screenLoc;
};

class SoundInfo
{
  public:
      SoundInfo();
      /*Setter*/
      void SetSoundInfo(size_t frequency = 22050, size_t channels = 2, size_t chunksize = 4096)  ;
      /*Getter*/
      size_t GetSoundFrequency() const;
      size_t GetSoundChannels() const;
      size_t GetSoundChunkSize() const;
  private:
    size_t m_frequency, m_channels, m_chunksize;
};

class GameInfo : public ScreenInfo, public SoundInfo
{
public:
    GameInfo();
    /*Setter*/
    void SetInfo(const std::string& rootdata = EMPTY, const std::string& mod = EMPTY, const std::string& saveloc = EMPTY,
            const std::string& name = EMPTY, const std::string& icon = EMPTY, const std::string& renderQuality = EMPTY,
            size_t displayCount = 1, size_t display = 0, size_t frames_per_second = 60, size_t screenWidth = 640, size_t screenHeight = 480, size_t screenBPP = 32,
            size_t blitlevels = 50, size_t frequency = 22050, size_t channels = 2, size_t chunksize = 4096);
    void SetScreenLoc(int x = 0, int y = 0);
    /*Getters*/
    std::string GetRootDirectory() const;
    std::string GetModName() const;
    std::string GetGameName() const;
    size_t GetBlitLevels() const;
    std::string GetRenderQuality() const;

private:
    /*These are the key variables of the game*/
    const static std::string EMPTY;
    std::string m_rootdata, m_mod, m_saveloc, m_name, m_icon, m_render_quality;
    size_t m_blitlevels;
};

#endif // INFO_H_INCLUDED
