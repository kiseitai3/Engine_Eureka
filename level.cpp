#include <SDL.h>
#include <list>
#include <string>
#include "globals.h"
#include "data_base.h"
#include "draw_base.h"
#include "sound_base.h"
#include "trigger.h"
#include "progressbar.h"
#include "textbox.h"
#include "Timer.h"
#include "level.h"
#include "pywrap.h"
#include "physics.h"
#include "ui.h"
#include <iostream>

//Methods
//Constructors and Destructor
Level::Level(Game* owner, cstr file)
{
    size_t status = 0;
    size_t objCount = 0;
    std::string nameString;
    data_base lvlDOM(file);

    //Stage 1
    /*Contents: Map name, background layers*/
    mapName = lvlDOM.GetStrFromData("lvl_name");
    layerList = owner->AddLayerSet(lvlDOM.GetStrFromData("lvl_layer_set"));
    status += loadRate;
    owner->UpdateLoadingStatus(status);

    //Stage 2
    /*Unit loading stage*/
    objCount = lvlDOM.GetIntFromData("lvl_blit_count");
    for(size_t i = 0; i < objCount; i++)
    {
        unitList = owner->SpawnUnitFromList(lvlDOM.GetStrFromData("lvl_unit_set_" + intToStr(i)), i);
    }
    status += loadRate;
    owner->UpdateLoadingStatus(status);

    //Stage 3
    /*UI stage*/
    nameString = "lvl_ui_";
    for(int i = 0; i < lvlDOM->GetIntFromData("lvl_ui_number"); i++)
    {
        nameString = "lvl_ui_";
        nameString += intToStr(i);
        uiList.push_back(owner->RegisterUI(nameString.c_str()));
    }
    status += loadRate;
    owner->UpdateLoadingStatus(status);

    //Stage 4
    lvlBackgroundMusic = new sound_base();
    if(!lvlBackgroundMusic)
    {
        std::cout<<"Error: Unable to load background music or no music is available in this level!\n\r";
    }
    else
    {
        lvlBackgroundMusic->Load_Sound(lvlDOM->GetStrFromData("lvl_music").c_str());
        if(!lvlBackgroundMusic->isPlaying())
        {
            lvlBackgroundMusic->Play(-1);
        }
        else
        {
            std::cout<<"Error: Unable to load background music or no music is available in this level!\n\r Error at lvl_music!\n\r";
        }
    }
    status += loadRate;
    owner->UpdateLoadingStatus(status);

    //Stage 5
    /*Now we load the triggers and the hero unit*/
    nameString = "lvl_trigger_";
    for(int i = 0; i < lvlDOM->GetIntFromData("lvl_trigger_number"); i++)
    {
        nameString += intToStr(i);
        triggerList.push_back(owner->RegisterTrigger(lvlDOM.GetStrFromData(nameString.c_str())))
        nameString = "lvl_trigger_";
    }

    //Hero portion
    heroID = owner->SpawnUnitFromFile(lvlDOM.GetStrFromData("lvl_hero"));
    status += loadRate;
    owner->UpdateLoadingStatus(status);

    //Stage 6
    /*Level modules!*/
    nameString = "lvl_module_";
    for(int i = 0; i < lvlDOM->GetIntFromData("lvl_module_number"); i++)
    {
        nameString += intToStr(i);
        moduleList.push_back(owner->RegisterModule(lvlDOM.GetStrFromData(nameString.c_str())))
        nameString = "lvl_module_";
    }
    status += loadRate;
    owner->UpdateLoadingStatus(status);

    sys = owner;
}

Level::~Level()
{

}

void Level::LoadingDraw(SDL_Renderer &ren)
{
    //Draw to screen the components that show the level is loading!
    SDL_SetRenderDrawColor((SDL_Renderer*)&ren, 0, 0, 0, 255);
    SDL_RenderClear((SDL_Renderer*)&ren);
    loadingBar->Draw(ren);
    loadingText->Draw(ren);
    SDL_RenderPresent((SDL_Renderer*)&ren);
}
