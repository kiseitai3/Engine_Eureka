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
//Constructors and Destructors
Level::Level(const char* file, const char *saveFile, SDL_Renderer *ren, Timer* t, std::size_t loadRate)
{
    int status = 1;
    lvlDOM, saveFileDOM, lvlBackground, lvlBackgroundMusic, loadingText, loadingBar = NULL;//Set all critical pointersto NULL in case they fail to be set properly!
    timer = t;
    lvlDOM = new data_base(file);
    saveFileDOM = new data_base(saveFile);
    if(!lvlDOM || !saveFileDOM)
    {
        std::cout<<"Error: could not create DOM object for this level! This is a sad day for all of us! D:<<<<\n\r";
    }
    else
    {
        math_point loc;
        loc.X = lvlDOM->GetIntFromData("lvl_progressbar_x");
        loc.Y = lvlDOM->GetIntFromData("lvl_progressbar_y");
        loadingBar = new ProgressBar(lvlDOM->GetStrFromData("lvl_progressbar").c_str(), &status, loc, ren);
        loadingBar->SetRectangleDimensions(1, lvlDOM->GetIntFromData("lvl_progressbar_w"));
        loadingText = new textbox(lvlDOM->GetStrFromData("lvl_textbox_msg"),lvlDOM->GetStrFromData("lvl_textbox").c_str(), ren);
        LoadingDraw(ren);

        //Stage 1
        mapName = lvlDOM->GetStrFromData("lvl_name");
        lvlBackground = new draw_base();
        lvlBackground->Load_Texture(lvlDOM->GetStrFromData("lvl_background").c_str(),ren);
        if(!lvlBackground || !lvlBackground->GetTexture())
        {
            std::cout<<"Error: Failed to load background texture for this level. Stage 1 failure! \n\r";
        }
        status += loadRate;
        loadingBar->Update(loc.X, loc.Y);
        LoadingDraw(ren);

        //Stage 2
        std::string nameString = "lvl_unit_";
        math_point unitLoc;
        for(int i = 0; i < lvlDOM->GetIntFromData("lvl_unit_number"); i++)
        {
            nameString += intToStr(i);
            unitLoc.X = lvlDOM->GetIntFromData(nameString + "_x");
            unitLoc.Y = lvlDOM->GetIntFromData(nameString + "_y");
            Unit *pUnit = new Unit(lvlDOM->GetIntFromData(nameString + "_blitorder"), lvlDOM->GetStrFromData(nameString), unitLoc, ren, timer, lvlDOM->GetIntFromData(nameString + "_hero"), lvlDOM->GetIntFromData(nameString + "_bars"));
            if(!pUnit)
            {
                std::cout<<"Error: Failed to load unit type object during stage 2. Error at "<<nameString<<"!\n\r";
            }
            else
            {
                pUnit->SetID(i);
                bool objectNotDeleted = !saveFileDOM->SearchTermExists(mapName + "_unit_" + intToStr(i));
                if(pUnit->GetType() == "object" && objectNotDeleted)
                {
                    gameObjects.push_back(pUnit);
                }
                else if(pUnit->GetType() == "unit" && objectNotDeleted)
                {
                    gameUnits.push_back(pUnit);
                }
                else if(pUnit->GetType() == "projectile" && objectNotDeleted)
                {
                    gameProjectiles.push_back(pUnit);
                }
            }
        }
        status += loadRate;
        loadingBar->Update(loc.X, loc.Y);
        LoadingDraw(ren);

        //Stage 3
        nameString = "lvl_ui_";
        for(int i = 0; i < lvlDOM->GetIntFromData("lvl_ui_number"); i++)
        {
            nameString += intToStr(i);
            UI *pUi = new UI(lvlDOM->GetStrFromData(nameString).c_str(), ren);
            if(!pUi)
            {
                std::cout<<"Error: Failed to load UI to the UI list for this level! :( Curse the number 3? Error occurred in stage 3 at "<<nameString<<"\n\r";
            }
            else
            {
                gameUI.push_back(pUi);
            }
        }
        status += loadRate;
        loadingBar->Update(loc.X, loc.Y);
        LoadingDraw(ren);

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
        loadingBar->Update(loc.X, loc.Y);
        LoadingDraw(ren);

        //Stage 5
        nameString = "lvl_trigger_";
        for(int i = 0; i < lvlDOM->GetIntFromData("lvl_trigger_number"); i++)
        {
            nameString += intToStr(i);
            Trigger *pTrig = new Trigger(lvlDOM->GetStrFromData(nameString).c_str());
            if(!pTrig)
            {
                std::cout<<"Error: Unable to load a trigger in this level! Error at "<<nameString<<" \n\r";
            }
            else
            {
                pTrig->SetID(i);
                bool objectNotDeleted = !saveFileDOM->SearchTermExists(mapName + "_trigger_" + intToStr(i));
                if(objectNotDeleted)
                {
                    gameTriggers.push_back(pTrig);
                }
            }
        }
        loc.X = saveFileDOM->GetIntFromData("hero_x");
        loc.Y = saveFileDOM->GetIntFromData("hero_y");
        hero = new Unit(saveFileDOM->GetIntFromData("hero_blitorder"), saveFileDOM->GetStrFromData(saveFileDOM->GetStrFromData("current_hero")), loc, ren, t, true, true);
        if(!hero)
        {
            std::cout<<"Error: the hero could not be loaded at stage 5! Really? This thing could not be loading? You gotta be shitting me!\n\r";
        }
        else
        {
            //Overwrite values of the default hero file with the values from the safe file!
            hero->SetAD(saveFileDOM->GetIntFromData("hero_ad"));
            hero->SetHP(saveFileDOM->GetIntFromData("hero_hp"));
            hero->SetMovementSpeed(saveFileDOM->GetValueFromData("hero_mSpeed"));
            hero->SetAP(saveFileDOM->GetIntFromData("hero_ap"));
            hero->SetAttackSpeed(saveFileDOM->GetIntFromData("hero_aSpeed"));
            hero->SetRange(saveFileDOM->GetIntFromData("hero_range"));
            hero->SetVisionRange(saveFileDOM->GetIntFromData("hero_vRange"));
        }
        status += loadRate;
        loadingBar->Update(loc.X, loc.Y);
        LoadingDraw(ren);
    }
}

Level::~Level()
{

}

void Level::LoadingDraw(SDL_Renderer *ren)
{
    //Draw to screen the components that show the level is loading!
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    loadingBar->Draw(ren);
    loadingText->Draw(ren);
    SDL_RenderPresent(ren);
}
