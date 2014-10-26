#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include <SDL.h>
#include <list>
#include <string>

//Forward declarations
class data_base;
class Trigger;
class ProgressBar;
class draw_base;
class textbox;
class sound_base;
class Timer;
class Pywrap;
class Game;

class Level
{
private:
    ProgressBar *loadingBar;
    textbox *loadingText;
    draw_base *lvlBackground;
    sound_base *lvlBackgroundMusic;
    data_base *lvlDOM;
    std::list<Unit*> gameObjects;
    std::list<Unit*> gameUnits;
    std::list<Unit*> gameProjectiles;
    std::list<Trigger*> gameTriggers;
    Timer* timer;
    Game* sys;
    bool backgroundFixed;
    std::string mapName;
public:
    //Constructors and Destructors
    Level(const char* file, const char *saveFile, SDL_Renderer& ren, Timer& t, const Game& sys, std::size_t loadRate = 20);
    ~Level();

    //Game logic functions
    void Update(Unit *hero);
    void Draw(const SDL_Renderer& ren);
    void ProcessEvents(const SDL_Event& event);
    void LoadingDraw(SDL_Renderer& ren);

    //Getters
    std::list<Unit*> GetObjectList(const std::string& listName) const;
    std::list<UI*> GetUIList() const;
    data_base GetDOM() const;

    //Setters
    size_t SpawnUnit(char type, math_point loc, cstr file, bool hero, bool hasBars);
    void removeUnit(const std::string& name);
    void removeUnit(size_t id);

    //Extra cleaning methods
    void ScreenClear();
};


#endif // LEVEL_H_INCLUDED
