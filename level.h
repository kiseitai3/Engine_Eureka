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
    BinarySearchTree<size_t, size_t> unitList;
    Timer* timer;
    Game* sys;
    bool backgroundFixed;
    std::string mapName;
public:
    //Constructors and Destructors
    Level();
    ~Level();

    //Getters
    std::string& GetMapName() const;

    //Extra cleaning methods
    void ScreenClear();
};


#endif // LEVEL_H_INCLUDED
