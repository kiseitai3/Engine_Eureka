#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "iomanager.h"
#include "scriptwrap.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <stack>
#include <list>
#include <cstdlib>
#include <random>
#include <pthread.h>
#include "info.h"
#include "Timer.h"
#include "modules.h"
#include "threading.h"
#include "unitmanager.h"
#include "uimanager.h"
#include "networking.h"
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

    //static members
    static size_t hasher();//Spews out a random number as the key for an element using a bellshape distribution
    static size_t randUniform(Range limits = Range());//Generates random numbers that form a uniform distribution with a defined range.
    static size_t randBinomial(Range limits = Range());//Generates random numbers using the binomial distribution and a defined range.
    static size_t randNormal(Range limits = Range());//Generates random numbers using the bellshape distribution and a defined range.
    static bool GetMaxValueSizeT();

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
