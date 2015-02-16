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

//Game includes
#include <cmath>//Fixes ::hypot not declared error. Must be included before game.h. MySQL undefines ::hypot for some bizarre reason
#include "particlesystem.h"
#include "modules.h"
#include "threading.h"
#include "unitmanager.h"
#include "uimanager.h"
#include "networking.h"
#include "iomanager.h"
#include "info.h"
#include "Timer.h"
#include "level.h"
#include "rand_generators.h"
#include "typedefs.h"

class Game : public ParticleSystem, public ModuleSystem, public UnitManager, public IOManager,
    public UIManager, public NetworkManager, public GameInfo, public ThreadSystem
{
public:
    Game();
    Game(cstr file);

    /*Init*/
    void LoadGameConstants(cstr file);
    bool init();

    //Level
    bool loadLevel(cstr file);
    Level& GetCurrentLevel();
    Timer& GetTimer();

    /*Getters*/
    SDL_Renderer& GetRenderer();
    SDL_Event& GetEvents();
    bool isMultithreaded() const;
    bool GetRelativity() const;
    bool isEngineClosing() const;

    /*Save methods*/
    void loadData(const std::string& name);
    void saveData(const std::string& name);

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


private:
    //Timer and renderer
    Timer fps;
    SDL_Renderer *screen;
    SDL_Window *win;
    SDL_Event *event;//Where all the events will be stored.

    //Flags
    bool frameCapped;
    bool multithreaded;
    bool relativity;
    bool closeEngine;

    //Other variables
    Level *current;

    //Memory
    uint64_t currentMemory;
    uint64_t maxMemAllowed;
    uint64_t maxMem;

};
//Global functions


#endif // GAME_H_INCLUDED
