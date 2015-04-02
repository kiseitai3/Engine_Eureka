#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

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

class Game : public SoundQueue, public ParticleSystem, public ModuleSystem, public UnitManager, public IOManager,
    public UIManager, public NetworkManager, public TriggerManager, public LayerSystem, public Cursor, public TimerSystem,
     public VideoPlayer, public ThreadSystem, public GameInfo
{
public:
    /*Ctors and dtor*/
    Game(bool editor = false);
    Game(cstr file, bool editor = false);
    ~Game();

    /*Init*/
    void LoadGame(cstr file);
    void LoadGameConstants(cstr file);
    void LoadGlobalModules(cstr file);
    void LoadUIs(cstr file);
    void initEditorFrameBuffer();
    bool init();

    //Level
    bool loadLevel(cstr file);
    Level* GetCurrentLevel();
    void SetHeroIDForCurrentLevel(size_t h_id);
    void SetHeroUnitAsLoaded();
    void UnsetHeroUnitAsLoaded();

    /*Getters*/
    SDL_Renderer& GetRenderer();
    SDL_Event& GetEvents();
    size_t GetMainTimer() const;
    size_t GetHeroID() const;
    bool isMultithreaded() const;
    bool GetRelativity() const;
    bool isEngineClosing() const;
    bool noHero() const;
    char* GetFrameBuffer() const;
    size_t GetSizeOfFrameBuffer() const;

    /*Save methods*/
    void loadSaveData(const std::string& file);
    void SaveData(const std::string& query);//Done on a database so you must query
    DataBase* GetSaveDataHandle();

    /*Frame adjustment*/
    void FrameCapper();
    void ClearEditorFrameBuffer();

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

    static const size_t loadRate;

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

    //IDs
    size_t mainTimer;//Timer
    size_t dbID;//Save database
    size_t drawThread, eventsThread, gcThread, soundThread, pluginThread, updateThread;
    size_t loadID, hudID, mainMenuID, videoHUD_ID;//Main ui ids
    std::list<size_t> moduleList;
    std::list<size_t> uiList;

    //Other variables
    Level *currentLvl;
    char* frameBuffer;
    size_t frameSize;
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
