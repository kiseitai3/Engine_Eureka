#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
#include "typedefs.h"

<<<<<<< HEAD
enum FileTypes
{
    NONE, VAR, XML, LUA, PYTHON
};


class Game
{
public:

private:

};
//Global functions
=======
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <stack>
#include <list>
#include <cstdlib>
#include <pthread.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
>>>>>>> TheIllusiveMan

//Game includes
//#include <cmath>//Fixes ::hypot not declared error. Must be included before game.h. MySQL undefines ::hypot for some bizarre reason
#include "typedefs.h"


//Engine name space macro
//ENGINE_NAMESPACE


class ParticleSystem;
class ModuleSystem;
class IOManager;
class ThreadSystem;
class UnitManager;
class UIManager;
class NetworkManager;
class GameInfo;
class TimerSystem;
class LayerSystem;
class TriggerManager;
class Level;
class DataBase;
class SoundQueue;
class VideoPlayer;
class Cursor;
class Input;

class Game : public ThreadSystem, public GameInfo, public ModuleSystem, public UnitManager, public IOManager,
    public UIManager, public NetworkManager, public TriggerManager, public LayerSystem, public Cursor, public TimerSystem,
    public VideoPlayer, public Input, public SoundQueue, public ParticleSystem
{
public:
    /*Ctors and dtor*/
    Game(bool editor = false);
    Game(cstr file, bool editor = false);
    Game(int argc, char* argv[], bool editor = false);
    Game(cstr file, int argc, char* argv[], bool editor = false);
    ~Game();

    /*Init*/
    void LoadGame(cstr file);
    void LoadGameConstants(cstr file, bool hasdb = false);
    void LoadGlobalModules(cstr file);
    void LoadUIs(cstr file);
    void initEditorFrameBuffer();
    bool init();
    void initSubSys();

    //Level
    bool loadLevel(cstr file);
    Level* GetCurrentLevel();
    void SetHeroIDForCurrentLevel(size_t h_id);
    void SetHeroUnitAsLoaded();
    void UnsetHeroUnitAsLoaded();

    /*Getters*/
    SDL_Renderer& GetRenderer(size_t& game_mutex);
    SDL_Event& GetEvents();
    size_t GetMainTimer() const;
    size_t GetHeroID() const;
    bool isMultithreaded() const;
    bool isGamePaused() const;
    bool GetRelativity() const;
    bool isEngineClosing() const;
    bool noHero() const;
    char* GetFrameBuffer() const;
    size_t GetSizeOfFrameBuffer() const;
    size_t GetWinID() const;

    /*Setters*/
    void PauseGame();
    void ResumeGame();
    void SetWindowPosition(size_t x, size_t y);
    void SetWindowSize(size_t h, size_t w);
    void SetWindowBorderless(bool borderless);

    /*Save methods*/
    void LoadSaveData(const std::string& file);
    void SaveData(const std::string& query);//Done on a database so you must query
    void SaveGameSettings();
    DataBase* GetSaveDataHandle();

    /*Frame adjustment*/
    void FrameCapper();
    void ClearEditorFrameBuffer();
    void RestartRenderer();
    void RestartVideoAndSound();
    void RestartAudio();
    void RestartVideo();
    void UnlockRenderer(size_t mutex_id);

    /*Below are the methods that will be called by the main thread or independent threads (if in multithreaded mode).*/
    void drawWorld();
    void playSounds();
    void runPhysics();
    void run();//This method will run the game
    void stopGame();//This method will emit the exit command to the engine! Be careful!

    /*Let's remove ids for removed game objects*/
    void mainGC();

    /*UI quick methods*/
    void ShowLoadingScreen();
    void UpdateLoadingStatus(size_t value);
    void HideLoadingScreen();
    void ReplaceLoadingScreen(cstr file);
    void ShowMainMenu();
    void HideMainMenu();
    void ReplaceMainMenu(cstr file);
    void ShowHUD();
    void HideHUD();
    void ReplaceHUD(cstr file);
    void ShowVideoHUD();
    void HideVideoHUD();
    void ReplaceVideoHUD(cstr file);
    void ShowWindow(bool visible);

    static const size_t loadRate;
    static const size_t WINDOW_WIDTH = 640;
    static const size_t WINDOW_HEIGHT = 480;
    static const size_t FRAME_FORMAT_SIZE = 4;//4 = 4 basic components of a pixel! 8bits per channel for the 4 channels = 32bits
    static const std::string FRAME_FORMAT;//This is so outside programs can get some sort of hint as to what format to expect from the editor frame buffer
private:
    //Renderer
    SDL_Renderer *screen;
    SDL_Window *win;
    SDL_Event *event;//Where all the events will be stored.

    //Flags
    bool frameCapped;
    bool multithreaded;
    bool relativity;
    bool closeEngine;
    bool loading;
    bool heroLoaded;
    bool requestFrame;
    bool gamePaused;

    //IDs
    size_t mainTimer;//Timer
    size_t dbID;//Save database
    size_t drawThread, eventsThread, gcThread, soundThread, pluginThread, updateThread;
    size_t loadID, hudID, mainMenuID, videoHUD_ID;//Main ui ids
    size_t game_mutex_id;
    std::list<size_t> moduleList;
    std::list<size_t> uiList;

    //IO Streams
    std::streambuf *in, *out, *err;
    std::ofstream *g_out, *g_err;
    std::ifstream *g_in;
    std::string g_in_path, g_out_path, g_err_path, g_file_path;

    //Other variables
    Level *currentLvl;
    char* frameBuffer;
    size_t frameSize;
    std::string cmd_no_args;

    //methods
    void initCMD(int argc, char* argv[]);
    void initSTDStreams();
    void processCMD();
};
//Global functions
void_ptr helperDrawFunction(void_ptr game);
void_ptr helperSoundFunction(void_ptr game);
void_ptr helperPhysicsFunction(void_ptr game);
void_ptr helperEventsFunction(void_ptr game);
void_ptr helperGCFunction(void_ptr game);
void_ptr helperPluginFunction(void_ptr obj);
void_ptr helperUpdateFunction(void_ptr game);

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // GAME_H_INCLUDED
