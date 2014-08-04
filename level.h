#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include <SDL.h>
#include <list>
#include <string>
#include "globals.h"

//Forward declarations
class data_base;
class Trigger;
class ProgressBar;
class draw_base;
class textbox;
class sound_base;
class Timer;
class Pywrap;

class Level
{
private:
    ProgressBar *loadingBar;
    textbox *loadingText;
    draw_base *lvlBackground;
    sound_base *lvlBackgroundMusic;
    data_base *lvlDOM, *saveFileDOM;
    Unit *hero;
    std::list<Unit*> gameObjects;
    std::list<Unit*> gameUnits;
    std::list<Unit*> gameProjectiles;
    std::list<UI*> gameUI;
    std::list<Trigger*> gameTriggers;
    Timer* timer;
    bool backgroundFixed;
    std::string mapName;
public:
    //Constructors and Destructors
    Level(const char* file, const char *saveFile, SDL_Renderer& ren, Timer& t, std::size_t loadRate = 20);
    ~Level();

    //Game logic functions
    void Update(Unit *hero);
    void Draw(const SDL_Renderer& ren);
    void ProcessEvents(const SDL_Event& event);
    void LoadingDraw(SDL_Renderer& ren);

    //Getters
    std::list<Unit*>* GetObjectList(std::string listName) const;
    std::list<UI*>* GetUIList() const;
    data_base *GetDOM() const;

    //Extra cleaning methods
    void ScreenClear();
};


#endif // LEVEL_H_INCLUDED
