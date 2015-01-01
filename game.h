#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
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
#include "typedefs.h"
#include "info.h"
#include "ui.h"
#include "unit.h"
#include "plugin.h"
#include "Timer.h"
#include "modules.h"
#include "threading.h"

class ScriptWrap;
class Unit;

class Game : public GameInfo, public ThreadSystem, public ParticleSystem, public ModuleSystem
{
public:
    Game();
    Game(cstr file);

    /*Init*/
    void LoadGameConstants(cstr file);
    bool init();

    /*Queues*/
    void QueueGlobalScript(const ScriptWrap& script);

    /*Other setters*/
    size_t AddUI(const UI& ui);

    //Level
    bool loadLevel(cstr file);
    void endTopLevel();
    Level& GetCurrentLevel();
    Timer& GetTimer();

    /*Getters*/
    SDL_Renderer& GetRenderer() const;
    bool isMultithreaded() const;
    size_t GetDefaultUnitCount() const;

    //Delete
    void removeUnit(const std::string& name);
    void removeUnit(size_t id);

    /*Save methods*/
    void loadData(const std::string& name);
    void saveData(const std::string& name);

    //static members
    static size_t hasher();//Spews out a random number as the key for an element

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
    /*Below are the store places for the objects that the game will use over and over during operation.*/
    std::map<size_t, std::stack<Unit*>> renderStack;
    std::stack<Unit*> soundStack;
    std::stack<Level*> levelStack;
    std::list<ScriptWrap*> scripts;
    std::vector<UI*> uis;

    //Timer and renderer
    Timer fps;
    SDL_Renderer *screen;
    SDL_Window *win;
    SDL_Event *event;//Where all the events will be stored.

    //Flags
    bool frameCapped;
    bool multithreaded;

    //Other variables
    Level *current;

    //Memory
    uint64_t currentMemory;
    uint64_t maxMemAllowed;
    uint64_t maxMem;

    //Global Unit Allocation Count
    size_t defaultUnitCount;
};
//Global functions


#endif // GAME_H_INCLUDED
