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

class EUREKA Game : public ParticleSystem, public ModuleSystem, public UnitManager, public IOManager,
    public UIManager, public NetworkManager, public TriggerManager, public LayerSystem, public TimerSystem,
     public ThreadSystem, public GameInfo
{
public:
    Game();
    Game(cstr file);

    /*Init*/
    void LoadGameConstants(cstr file);
    void LoadGlobalModules(cstr file);
    void LoadUIs(cstr file);
    bool init();

    //Level
    bool loadLevel(cstr file);
    Level* GetCurrentLevel();

    /*Getters*/
    SDL_Renderer& GetRenderer();
    SDL_Event& GetEvents();
    size_t GetMainTimer();
    bool isMultithreaded() const;
    bool GetRelativity() const;
    bool isEngineClosing() const;

    /*Save methods*/
    void loadSaveData(const std::string& file);
    void SaveData(const std::string& query);//Done on a database so you must query
    DataBase* GetSaveDataHandle();

    /*Frame adjustment*/
    void FrameCapper();

    /*Below are the methods that will be called by the main thread or independent threads (if in multithreaded mode).*/
    void drawWorld();
    void playSounds();
    void executePlugins();
    void executeScripts();
    void runPhysics();
    void run(int id = -1);//This method will run all of the threads unless an specific thread id is specified
    void stop(int id = -1);//This method will halt all of the threads unless an specific thread id is specified

    /*Let's remove game objects*/

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


private:
    //Renderer
    SDL_Renderer *screen, *outputFrame;
    SDL_Window *win;
    SDL_Event *event;//Where all the events will be stored.

    //Flags
    bool frameCapped;
    bool multithreaded;
    bool relativity;
    bool closeEngine;

    //IDs
    size_t mainTimer;//Timer
    size_t dataID;//ID for save data
    size_t dbID;//Save database
    std::list<size_t> moduleList;
    std::list<size_t> uiList;

    //Other variables
    Level *currentLvl;
};
//Global functions
void_ptr helperDrawFunction(void_ptr game);

#endif // GAME_H_INCLUDED
