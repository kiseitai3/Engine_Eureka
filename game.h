#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "scriptwrap.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <stack>
#include <list>
#include <pthread.h>
#include "typedefs.h"
#include "info.h"
#include "ui.h"
#include "unit.h"
#include "plugin.h"
#include "Timer.h"
#include "modadapter.h"

class ScriptWrap;
class Unit;

class Game : public GameInfo
{
public:
    typedef (void*)(*func)(void* data) thread_func;
    typedef (void) (*func)(void* data) func;

    Game();
    Game(cstr file);

    /*Init*/
    void LoadGameConstants(cstr file);
    bool init();
    /*Queues*/
    void QueueGlobalScript(const ScriptWrap& script);
    void QueueGlobalModule(const ModAdapter& plugin);
    /*Other setters*/
    size_t AddUI(const UI& ui);
    size_t SpawnUnit(char type, math_point loc, cstr file, bool hero, bool hasBars);
    size_t SpawnThread(thread_func target);
    size_t SpawnThread(func target);//This one uses the reentrant helperMethod()

    //Level
    bool loadLevel(cstr file);
    void endTopLevel();
    Level& GetCurrentLevel();

    void removeUnit(const std::string& name);
    void removeUnit(size_t id);
    /*Save methods*/
    void loadData();
    void saveData();
    /*Frame adjustment*/
    void FrameCapper();
    /*Below are the methods that will be called by the main thread or independent threads (if in multithreaded mode).*/
    void drawWorld();
    void playSounds();
    void executePlugins();
    void executeScripts();
    void run();
    void stop();//This method will halt all of the threads
    /*Let's remove game objects*/


private:
    /*Below are the store places for the objects that the game will use over and over during operation.*/
    std::map<size_t, std::stack<Unit*>> renderStack;
    std::stack<Unit*> soundStack;
    std::stack<Level*> levelStack;
    std::list<ScriptWrap*> scripts;
    std::list<ModAdapter*> modules;
    std::list<pthread_t*> threads;
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

    //Methods
    void* helperMethod_r(func target);//Feed it a void function for execution in a pthread!
};
//Global functions


#endif // GAME_H_INCLUDED
