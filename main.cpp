#include <Python.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "physics.h"
#include "pywrap.h"
#include "draw_base.h"
#include "Timer.h"
#include "conversion.h"
#include "unit.h"
#include "input.h"
#include <vector>
#include <stdlib.h>
#include "globals.h"
#include "ui.h"
#include "data_base.h"

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
//Prototypes
void displayTest(const char* const input, int size);
int mainGame(int argc, char* argv[]);

int main(int argc, char* argv[]){
    //Call runing function or test function here

    return 0;
}
void displayTest(const char* const input, int size)
{
    cout<<"\n\r";
    for(int i = 0; i < size; i++)
    {
        cout << input[i];
    }
}

int mainGame(int argc, char* argv[]) {
    //Initialization
    bool end = false;
    loadGameConstants();
	init();

    //Load image

    //Game Loop
    do
    {
       //Check input

      //execute game logic

      //Draw everything to the screen
      //SDL_BlitSurface(hello, NULL, screen, NULL );
      SDL_RenderPresent( screen );
        }while(end==false);
      //Free everything
      //SDL_FreeSurface( hello );
	return 0;
}

bool init()
{
    //Set screen pointer to null in case.
    screen = NULL;
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);

    //If there was an error in setting up the screen
    if( win == NULL )
    {
        cout<<"Error: Could not create the window!\n\r";
        return false;
    }
    else
    {
        screen = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
        SDL_RenderSetLogicalSize(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNKSIZE ) == -1 )
    {
        return false;
    }
    //Start timer(s)
    fps.start();

    //If everything initialized fine
    return true;
}

void FrameCapper()
{
    if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)//1000 ms = 1 second such that if FRAMES_PER_SECOND is bigger then the game is running at a higher rate than the cap!
    {
        //Sleep the remaining frame time
        SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
    }
}

void SpawnUnit(const char type, int BlitOrder, math_point loc, std::string file, bool hero, bool hasBars)
{
    if(type == 'u')//it's a game unit!
    {
        Unit *pUnit = new Unit(BlitOrder, file, loc, screen, &fps, hero, hasBars);
        gameUnits.push_back(pUnit);
    }

    if(type == 'p')//it's a game projectile!
    {
        Unit *pUnit = new Unit(BlitOrder, file, loc, screen, &fps);
        gameProjectiles.push_back(pUnit);
    }

    if(type == 'o')//it's a game environment object!
    {
        Unit *pUnit = new Unit(BlitOrder, file, loc, screen, &fps);
        gameObjects.push_back(pUnit);
    }
}

PyObject *FindNearbyUnit(PyObject *unit)
{
    if(PyCObject_Check(unit))
    {
        Unit *pUnit = (Unit *)PyCObject_AsVoidPtr(unit);
        Unit *tmp = 0;
        Unit *old = 0;
        for(int i = 0; i < gameUnits.size(); i++)
        {
            tmp = gameUnits[i];
            int d = pUnit->GetPhysics()->GetDistance(tmp->GetPhysics()->GetLoc());
            if(abs(d) < (pUnit->GetVRange() * 2))
            {
                if(!old)
                {
                    old = tmp;
                }
                else
                {
                    int d2 = pUnit->GetPhysics()->GetDistance(old->GetPhysics()->GetLoc());
                    if(d < d2)
                    {
                        old = tmp;
                    }
                }
            }
        }
        return PyCObject_FromVoidPtr((void *)old, NULL);
    }
}

Unit *FindNearbyUnit(Unit *pUnit)
{
    Unit *tmp = 0;
        Unit *old = 0;
        for(int i = 0; i < gameUnits.size(); i++)
        {
            tmp = gameUnits[i];
            int d = pUnit->GetPhysics()->GetDistance(tmp->GetPhysics()->GetLoc());
            if(abs(d) < (pUnit->GetVRange() * 2))
            {
                if(!old)
                {
                    old = tmp;
                }
                else
                {
                    int d2 = pUnit->GetPhysics()->GetDistance(old->GetPhysics()->GetLoc());
                    if(d < d2)
                    {
                        old = tmp;
                    }
                }
            }
        }
        return old;
}

Unit *FindUnitByName(std::string name)
{
    Unit *tmp = NULL;
    for(int i = 0; i < gameUnits.size(); i++)
    {
        tmp = gameUnits[i];
        if(tmp->GetName() == name)
        {
            return tmp;
        }
    }
}

void loadGameConstants()
{
    std::string modPath = fuseStrs(ROOTDATA, "mod.txt");
    data_base *mod, *info = NULL;
    mod = new data_base(modPath.c_str());
    if(mod > 0)//Load constants before initialization of the SDL systems
    {
        MOD = (mod->GetStrFromData("selected_mod") + "/\0").c_str();
        info = new data_base(mod->GetStrFromData("selected_mod").c_str());
        if(info > 0)
        {
            NAME = info->GetStrFromData("name").c_str();
            ICON = info->GetStrFromData("icon").c_str();
            delete(info);
            info = NULL;
        }
        SCREEN_WIDTH = (const int)mod->GetIntFromData("screen_width");
        SCREEN_HEIGHT = (const int)mod->GetIntFromData("screen_height");
        SCREEN_BPP = (const int)mod->GetIntFromData("screen_bpp");
        FRAMES_PER_SECOND = (const int)mod->GetIntFromData("frames_per_second");
        BLITLEVELS = (const int)mod->GetIntFromData("blit_levels");
        FREQUENCY = (const int)mod->GetIntFromData("frequency");
        CHANNELS = (const int)mod->GetIntFromData("channels");
        CHUNKSIZE = (const int)mod->GetIntFromData("chunk_size");
        SAVELOC = mod->GetStrFromData("save_loc").c_str();
        delete(mod);
        mod = NULL;
    }
}

SDL_Renderer *GetRenderer()
{
    return screen;
}

void saveToFile(std::string file, std::string value, std::string searchTerm)
{
    data_base save((SAVELOC + file).c_str(), false);
    if(searchTerm != "" && save.SearchTermExists(searchTerm))
    {
        save.WriteValue(value, searchTerm);
    }
    else
    {
        save.CloseFile();
        save.OpenFileForQuickWrite((SAVELOC + file).c_str());
        save.WriteValueAndFlush(value);
    }
    save.CloseFile();
}

void gameSave()
{
    /*This function will call the python script for saving stuff in the game.*/
    Pywrap saveScript = Pywrap((std::string(ROOTDATA) + std::string(MOD) + "Scripts/save\0").c_str());
}

data_base *loadFile(const char* fileName)
{
    data_base *tmp = new data_base((std::string(SAVELOC) + std::string(fileName)).c_str());
    if(!tmp)
    {
        std::cout<<"Error: Could not load Load file!\n\r";
        return NULL;
    }
    else
    {
        return tmp;
    }
}
