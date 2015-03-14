//#define EUREKA_EXPORT
#include <SDL.h>
#include <list>
#include <string>
#include "eureka.h"

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

//Engine name space macro
//ENGINE_NAMESPACE


//Methods
//Constructors and Destructor
Level::Level(Game* owner, cstr file)
{
    size_t status = 0;
    size_t objCount = 0;
    std::vector<size_t> tmp;
    std::string nameString;
    data_base lvlDOM(file);

    owner->ShowLoadingScreen();
    //Stage 1
    /*Contents: Map name, background layers*/
    mapName = lvlDOM.GetStrFromData("lvl_name");
    tmp = owner->AddLayerSet(lvlDOM.GetStrFromData("lvl_layer_set").c_str());
    layerList.assign(tmp.begin(), tmp.end());
    status += owner->loadRate;
    owner->UpdateLoadingStatus(status);

    //Stage 2
    /*Unit loading stage*/
    objCount = lvlDOM.GetIntFromData("lvl_blit_count");
    for(size_t i = 0; i < objCount; i++)
    {
        tmp = owner->SpawnUnitFromList(lvlDOM.GetStrFromData("lvl_unit_set_" + intToStr(i)).c_str(), i);
        unitList.assign(tmp.begin(), tmp.end());
    }
    status += owner->loadRate;
    owner->UpdateLoadingStatus(status);

    //Stage 3
    /*UI stage*/
    nameString = "lvl_ui_";
    for(int i = 0; i < lvlDOM.GetIntFromData("lvl_ui_number"); i++)
    {
        nameString += intToStr(i);
        uiList.push_back(owner->RegisterUI(nameString.c_str()));
        nameString = "lvl_ui_";
    }
    status += owner->loadRate;
    owner->UpdateLoadingStatus(status);

    //Stage 4
    lvlBackgroundMusic = new sound_base();
    if(!lvlBackgroundMusic)
    {
        std::cout<<"Error: Unable to load background music or no music is available in this level!\n\r";
    }
    else
    {
        lvlBackgroundMusic->Load_Sound(lvlDOM.GetStrFromData("lvl_music").c_str());
        if(!lvlBackgroundMusic->isPlaying())
        {
            lvlBackgroundMusic->Play(-1);
        }
        else
        {
            std::cout<<"Error: Unable to load background music or no music is available in this level!\n\r Error at lvl_music!\n\r";
        }
    }
    status += owner->loadRate;
    owner->UpdateLoadingStatus(status);

    //Stage 5
    /*Now we load the triggers and the hero unit*/
    nameString = "lvl_trigger_";
    for(int i = 0; i < lvlDOM.GetIntFromData("lvl_trigger_number"); i++)
    {
        nameString += intToStr(i);
        triggerList.push_back(owner->RegisterTrigger(lvlDOM.GetStrFromData(nameString.c_str()).c_str()));
        nameString = "lvl_trigger_";
    }

    //Hero portion
    if(owner->noHero() && lvlDOM.GetIntFromData("lvl_has_hero"))
        heroID = owner->SpawnUnitFromFile(lvlDOM.GetStrFromData("lvl_hero").c_str(), lvlDOM.GetIntFromData("lvl_hero_blitorder"));
    owner->SetHeroUnitAsLoaded();
    status += owner->loadRate;
    owner->UpdateLoadingStatus(status);

    //Stage 6
    /*Level modules!*/
    nameString = "lvl_module_";
    for(int i = 0; i < lvlDOM.GetIntFromData("lvl_module_number"); i++)
    {
        nameString += intToStr(i);
        moduleList.push_back(owner->RegisterModule(lvlDOM.GetStrFromData(nameString.c_str()).c_str()));
        nameString = "lvl_module_";
    }
    status += owner->loadRate;
    owner->UpdateLoadingStatus(status);

    //Last part
    //Create mutexes
    mutex_modlist_id = sys->SpawnMutex();
    mutex_unitlist_id = sys->SpawnMutex();
    mutex_layerlist_id = sys->SpawnMutex();
    mutex_uilist_id = sys->SpawnMutex();
    mutex_triggerlist_id = sys->SpawnMutex();
    sys = owner;
    music_status = false;

    owner->HideLoadingScreen();
}

Level::~Level()
{
    //Lock mutexes
    sys->LockMutex(mutex_modlist_id);
    sys->LockMutex(mutex_unitlist_id);
    sys->LockMutex(mutex_layerlist_id);
    sys->LockMutex(mutex_uilist_id);
    sys->LockMutex(mutex_triggerlist_id);
    //Unloading resources
    //Unloading modules
    for(std::list<size_t>::iterator itr = moduleList.begin(); itr != moduleList.end(); itr++)
    {
        sys->UnregisterModule(*itr);
    }
    //Unloading units
    if(sys->isEngineClosing())
        sys->DeleteAll();
    else
        for(std::list<size_t>::iterator itr = unitList.begin(); itr != unitList.end(); itr++)
        {
            sys->DeleteUnitByID(*itr);
        }
    //Unloading layers
    sys->DeleteAllLayers();
    //Unloading triggers
    for(std::list<size_t>::iterator itr = triggerList.begin(); itr != triggerList.end(); itr++)
    {
        sys->UnRegisterTrigger(*itr);
    }
    //Unloading UIs
    for(std::list<size_t>::iterator itr = uiList.begin(); itr != uiList.end(); itr++)
    {
        sys->UnregisterUI(*itr);
    }
    //Unlock mutexes
    sys->UnlockMutex(mutex_modlist_id);
    sys->UnlockMutex(mutex_unitlist_id);
    sys->UnlockMutex(mutex_layerlist_id);
    sys->UnlockMutex(mutex_uilist_id);
    sys->UnlockMutex(mutex_triggerlist_id);
    //Delete mutexes
    sys->DeleteMutex(mutex_modlist_id);
    sys->DeleteMutex(mutex_unitlist_id);
    sys->DeleteMutex(mutex_layerlist_id);
    sys->DeleteMutex(mutex_uilist_id);
    sys->DeleteMutex(mutex_triggerlist_id);
}

std::string Level::GetMapName() const
{
    return mapName;
}

std::list<size_t>* Level::GetLayerIDs()
{
    return &layerList;
}

std::list<size_t>* Level::GetUnitIDs()
{
    return &unitList;
}

std::list<size_t>* Level::GetTriggerIDs()
{
    return &triggerList;
}

std::list<size_t>* Level::GetUIIDs()
{
    return &uiList;
}

std::list<size_t>* Level::GetModuleIDs()
{
    return &moduleList;
}

size_t Level::GetHeroID() const
{
    return heroID;
}

bool Level::isMusicPlaying() const
{
    return music_status;
}

void Level::playBackgroundMusic()
{
    if(!music_status)
        lvlBackgroundMusic->Play(-1);
    music_status = true;
}

void Level::killBackgrounMusic()
{
    if(music_status)
        lvlBackgroundMusic->Stop();
    music_status = false;
}

void Level::fadeBackgroundMusic(int ms)
{
    if(music_status)
        lvlBackgroundMusic->FadeOut(ms);
}

void Level::SetHeroID(size_t h_id)
{
    heroID = h_id;
}

//End of namespace macro
//ENGINE_NAMESPACE_END
