<<<<<<< HEAD
#include "mysql.h"
#include <Python.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
=======
>>>>>>> TheIllusiveMan
#include <iostream>
#include "eureka.h"

<<<<<<< HEAD

using namespace std;
//constants
const char *ROOTDATA = "Data/";
const char *MOD = NULL;
const char *SAVELOC = NULL;
int FRAMES_PER_SECOND = 60;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int SCREEN_BPP = 32;
int BLITLEVELS = 20;
int FREQUENCY = 22050;
int CHANNELS = 2;
int CHUNKSIZE = 4096;
const char *NAME = "Eureka Engine!\0";
const char *ICON = NULL;
//Globals
Timer fps;
SDL_Renderer *screen;
SDL_Window *win;
vector<Unit*> gameObjects;
vector<Unit*> gameUnits;
vector<Unit*> gameProjectiles;
vector<UI*> gameUI;
///run
=======
>>>>>>> TheIllusiveMan
//Prototypes
void displayTest(const char* const input, int size);

int main(int argc, char* argv[]){
    //Call runing function or test function here
<<<<<<< HEAD
    MySQL db;
    db.connect("test", "t", "343249", "localhost");
=======
    Game g(argc, argv));
    g.LoadCursors();
>>>>>>> TheIllusiveMan
    return 0;
}
void displayTest(const char* const input, int size)
{
    std::cout<<"\n\r";
    for(int i = 0; i < size; i++)
    {
        std::cout << input[i];
    }
}

std::stack<fuzzy_obj> reverseOrderStack(const std::stack<fuzzy_obj>& in)
{
    std::stack<fuzzy_obj> out;
    std::stack<fuzzy_obj> In = in;
    while(!in.empty())
    {
        out.push(In.top());
        In.pop();
    }
    return out;
}

std::stack<fuzzy_obj> reverseOrderStack(const std::stack<fuzzy_obj>& in)
{
    std::stack<fuzzy_obj> out;
    std::stack<fuzzy_obj> In = in;
    while(!in.empty())
    {
        out.push(In.top());
        In.pop();
    }
    return out;
}
