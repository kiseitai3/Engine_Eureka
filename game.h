#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "scriptwrap.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <stack>
#include <list>
#include "typedefs.h"
#include "info.h"
#include "ui.h"
#include "unit.h"
#include "plugin.h"
#include "Timer.h"

class ScriptWrap;
class Unit;

class Game : public GameInfo
{
public:
    Game();
    Game(cstr file);

    /*Init*/
    void LoadGameConstants(cstr file);
    bool init();
    /*Queues*/
    void QueueGlobalScript(const ScriptWrap& script);
    void QueueGlobalPlugin(const Plugin& plugin);
    /*Other setters*/
    void AddUI(const UI& ui);
    void SpawnUnit(cstr type, int BlitOrder, math_point loc, std::string file, bool hero, bool hasBars);
    /*Frame adjustment*/
    void FrameCapper();
private:
    /*Below are the store places for the objects that the game will use over and over during operation.*/
    std::map<size_t, std::stack<Unit*>> renderStack;
    std::stack<Unit*> soundStack;
    std::list<ScriptWrap*> scripts;
    std::list<Plugin*> plugins;
    std::vector<Unit*> gameObjects;
    std::vector<Unit*> gameUnits;
    std::vector<Unit*> gameProjectiles;
    std::vector<UI*> uis;

    //Timer and renderer
    Timer fps;
    SDL_Renderer *screen;
    SDL_Window *win;
};
//Global functions


#endif // GAME_H_INCLUDED
