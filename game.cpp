#define EUREKA_EXPORT
#include "eureka.h"
#include "level.h"

void_ptr helperDrawFunction(void_ptr game)
{
    Game* tmp = (Game*)game;
    while(!tmp->isEngineClosing())
    {
        tmp->drawWorld();
    }
    return NULL;
}

/*class EUREKA Game : public ParticleSystem, public ModuleSystem, public UnitManager, public IOManager,
    public UIManager, public NetworkManager, public TriggerManager, public LayerSystem, public TimerSystem,
    public ThreadSystem, public GameInfo
*/
Game::Game(cstr file): ParticleSystem(this), ModuleSystem(this), UnitManager(this), IOManager(this), UIManager(this),
    NetworkManager(this), TriggerManager(this), LayerSystem(this), TimerSystem(this), ThreadSystem(), GameInfo()
{
    //Save actual initial path
    std::string filePath = SDL_GetBasePath();
    filePath += file;
    //Create a timer
    mainTimer = CreateTimer();
    //First, load constants as they are important values for the bootloading process
    LoadGameConstants(filePath.c_str());
    //Second, initialize SDL and the extension libraries
    if(!this->init())
    {
        std::cout << "Error: Could not initialize subsystems! Maybe, the initial file is wrong or not present!" << std::endl;
    }
    //Third, load global modules
    LoadGlobalModules(filePath.c_str());
    //Fourth, load global UIs
    LoadUIs(filePath.c_str());
    //Fifth, load save database
    loadSaveData(filePath.c_str());
    //Sixth, load initial level (Title Screen!)
    if(loadLevel(filePath.c_str()))
    {
        std::cout << "Error: Could not load initial level! Maybe, the initial file is wrong or not present!" << std::endl;
    }
}

Game::Game(): ParticleSystem(this), ModuleSystem(this), UnitManager(this), IOManager(this), UIManager(this),
    NetworkManager(this), TriggerManager(this), LayerSystem(this), TimerSystem(this), ThreadSystem(), GameInfo()
{

}

void Game::LoadGameConstants(cstr file)
{
    //Load file
    data_base gameDOM(file);
    //Basic variables
    std::string rootDir, modLoc, saveLoc, gameName, icon, renderQuality;
    size_t fps, width, height, bpp, blitlvls, freq, chan, chunksize, displayIndex, displayCount;
    bool detectVid, detectAud, saveConstToFile;

    //Extract data
    saveConstToFile = false;
    char* tmp = SDL_GetBasePath();
    rootDir = tmp;
    SDL_free(tmp);
    rootDir += gameDOM.GetStrFromData("root");

    modLoc = gameDOM.GetStrFromData("selected_mod");
    gameName = gameDOM.GetStrFromData("game_name");
    icon = gameDOM.GetStrFromData("icon");
    displayIndex = gameDOM.GetIntFromData("current_display");
    renderQuality = gameDOM.GetStrFromData("render_quality");
    fps = gameDOM.GetIntFromData("frames_per_second");
    width = gameDOM.GetIntFromData("screen_width");
    height = gameDOM.GetIntFromData("screen_height");
    bpp = gameDOM.GetIntFromData("screen_bpp");
    blitlvls = gameDOM.GetIntFromData("blit_levels");
    freq = gameDOM.GetIntFromData("frequency");
    chan = gameDOM.GetIntFromData("channels");
    chunksize = gameDOM.GetIntFromData("chunk_size");
    detectVid = gameDOM.GetIntFromData("auto_video");
    multithreaded = gameDOM.GetIntFromData("multithreaded");

    displayCount = SDL_GetNumVideoDisplays();

    //Some final modifications
    if(detectVid)//Video auto detection
    {
        SDL_DisplayMode current;
        if(!SDL_GetCurrentDisplayMode(displayIndex, &current))
        {
            std::cout << SDL_GetError() << std::endl;
        }
        width = current.w;
        height = current.h;
        bpp = current.format;
        saveConstToFile = true;
    }

    //Save constants
    SetInfo(rootDir, modLoc, saveLoc, gameName, icon, renderQuality,
            displayCount, displayIndex, fps, width, height, bpp,
            blitlvls, freq, chan, chunksize);

    if(saveConstToFile)
    {
        gameDOM.CloseFile();
        gameDOM.OpenFile(file, false);
        gameDOM.WriteValue(intToStr(width), "screen_width");
        gameDOM.WriteValue(intToStr(height), "screen_height");
        gameDOM.WriteValue(intToStr(bpp), "screen_bpp");
    }
}

void Game::LoadGlobalModules(cstr file)
{
    data_base gameDOM(file);
    std::string modPath = gameDOM.GetStrFromData("plugins");
    gameDOM.CloseFile();
    gameDOM.OpenFile(modPath.c_str());

    /*Game modules!*/
    std::string nameString = "module_";
    for(int i = 0; i < gameDOM.GetIntFromData("module_number"); i++)
    {
        nameString += intToStr(i);
        moduleList.push_back(RegisterModule(gameDOM.GetStrFromData(nameString).c_str()));
        nameString = "module_";
    }
}

void Game::LoadUIs(cstr file)
{
    data_base gameDOM(file);
    std::string uiPath = gameDOM.GetStrFromData("ui");
    uiPath = GetModName() + "/" + uiPath;
    gameDOM.CloseFile();
    gameDOM.OpenFile(uiPath.c_str());

    /*UI stage*/
    std::string nameString = "ui_";
    for(int i = 0; i < gameDOM.GetIntFromData("ui_number"); i++)
    {
        nameString += intToStr(i);
        uiList.push_back(RegisterUI(nameString.c_str()));
        nameString = "ui_";
    }
}

void Game::loadSaveData(const std::string& saveData)
{
    data_base gameDOM(saveData.c_str());
    //Load Database!
    dbID = RegisterDataBase(gameDOM.GetStrFromData("save").c_str());
}

bool Game::loadLevel(cstr file)
{
    data_base gameDOM(file);
    std::string lvlFile = gameDOM.GetStrFromData("initial_lvl");

    if(currentLvl)
    {
        delete currentLvl;//Delete previous lvl
        currentLvl = new Level(this, lvlFile.c_str());//create new lvl
        if(!currentLvl)
        {
            std::cout << "Error: Failed to load new level!" << std::endl;
            return false;
        }
    }
    return true;
}

bool Game::init()
{
//Set screen pointer to null in case.
    screen = NULL;
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    if(SDLNet_Init()==-1)
    {
        return false;
    }

    //Set up the screen
    win = SDL_CreateWindow(GetGameName().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GetScreenWidth(), GetScreenHeight(), SDL_WINDOW_FULLSCREEN);

    //If there was an error in setting up the screen
    if( win == NULL )
    {
        std::cout<<"Error: Could not create the window!\n\r";
        return false;
    }
    else
    {
        screen = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetHint(GetRenderQuality().c_str(), "linear");  // make the scaled rendering look smoother.
        SDL_RenderSetLogicalSize(screen, GetScreenWidth(), GetScreenHeight());
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( GetSoundFrequency(), MIX_DEFAULT_FORMAT, GetSoundChannels(), GetSoundChunkSize() ) == -1 )
    {
        return false;
    }
    //Start timer(s)
    StartTimer(mainTimer);

    //Change dir
    SDL_strdup(GetRootDirectory().c_str());

    //If everything initialized fine
    return true;
}

void Game::FrameCapper()
{
    if(GetTicks(mainTimer) < 1000 / GetMaxFramesPerSec())//1000 ms = 1 second
    {
        //Sleep the remaining frame time
        SDL_Delay( ( 1000 / GetMaxFramesPerSec() ) - GetTicks(mainTimer) );
    }
}

void Game::drawWorld()
{

}
