//#define EUREKA_EXPORT
#include "eureka.h"
#include "level.h"
#include <SDL_image.h>
#include "database.h"

//Engine name space macro
//ENGINE_NAMESPACE

//Threading entry points
void_ptr helperSoundFunction(void_ptr game)
{
    Game* tmp = (Game*)game;
    while(!tmp->isEngineClosing())
    {
        tmp->playSounds();
    }
    return NULL;
}

void_ptr helperPluginFunction(void_ptr game)
{
    Game* tmp = (Game*)game;
    while(!tmp->isEngineClosing())
    {
        tmp->RunAllFunctions();
    }
}

void_ptr helperEventsFunction(void_ptr game)
{
    Game* tmp = (Game*)game;
    while(!tmp->isEngineClosing() || SDL_WaitEvent(&tmp->GetEvents()))
    {
        tmp->UpdateInput(&tmp->GetEvents());
        tmp->UIProcessEvents();
        tmp->ProcessUnitEvents();
    }
    return NULL;
}

void_ptr helperPhysicsFunction(void_ptr game)
{
    Game* tmp = (Game*)game;
    while(!tmp->isEngineClosing())
    {
        tmp->RunPhysics();
    }
    return NULL;
}

void_ptr helperGCFunction(void_ptr game)
{
    Game* tmp = (Game*)game;
    while(!tmp->isEngineClosing())
    {
        tmp->mainGC();
        tmp->GC();
        tmp->GCSounds();
        sleep(randUniform(Range(0, 10000)));
    }
    return NULL;
}

void_ptr helperDrawFunction(void_ptr game)
{
    Game* tmp = (Game*)game;
    while(!tmp->isEngineClosing())
    {
        tmp->drawWorld();
    }
    return NULL;
}

void_ptr helperUpdateFunction(void_ptr game)
{
    Game* tmp = (Game*)game;
    while(!tmp->isEngineClosing())
    {
        tmp->UIUpdate();
        if(tmp->isPlayingVideo())
            tmp->UpdateVideo();
        else
           tmp->UpdateTriggers(tmp->GetHeroID());
    }
    return NULL;
}

const size_t Game::loadRate = 17;

/*class EUREKA Game : public ParticleSystem, public ModuleSystem, public UnitManager, public IOManager,
    public UIManager, public NetworkManager, public TriggerManager, public LayerSystem, public Cursor, public TimerSystem,
    public VideoPlayer, public ThreadSystem, public GameInfo
*/
Game::Game(cstr file, bool editor): SoundQueue(this), ParticleSystem(this), ModuleSystem(this), UnitManager(this), IOManager(this), UIManager(this),
    NetworkManager(this), TriggerManager(this), LayerSystem(this), Cursor(this), TimerSystem(this), VideoPlayer(this), Input(this), ThreadSystem(), GameInfo()
{
    LoadGame(file);
    closeEngine = false;
    loading = false;
    frameBuffer = NULL;
    requestFrame = editor;
    initSubSys();
}

Game::Game(bool editor): ThreadSystem(), GameInfo(), ModuleSystem(this), UnitManager(this), IOManager(this), UIManager(this),
    NetworkManager(this), TriggerManager(this), LayerSystem(this), Cursor(this), TimerSystem(this), VideoPlayer(this), Input(this),
    SoundQueue(this), ParticleSystem(this)
{
    closeEngine = false;
    loading = false;
    frameBuffer = NULL;
    requestFrame = editor;
    initSubSys();
}

void Game::initEditorFrameBuffer()
{
    frameSize = GetScreenWidth() * GetScreenHeight() * 4;//Size of the buffer that will be exposed to the game editor. 4 = 4 basic components of a pixel!
    frameBuffer = new char[frameSize];
}

void Game::initSubSys()
{
    initModSys();
    initLayerSys();
    initCursorSys();
    initUISys();
    initUnitSys();
    initNetSys();
    initParticleSys();
    initIOSys();
    initTimerSys();
    initVideoSys();
    initTriggerSys();
    initSoundSys();
}

void Game::LoadGame(cstr file)
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
    //some special ids
    hudID = FindUIByName("HUD");
    loadID = FindUIByName("LoadScreen");
    mainMenuID = FindUIByName("MainMenu");
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

    if(fps)
        frameCapped = true;
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

    //Initialize the buffer to be used by the game editor if engine is called with requestFrame == true!
    if(requestFrame)
        initEditorFrameBuffer();

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

void Game::ClearEditorFrameBuffer()
{
    for(size_t i = 0; i < frameSize; i++)
    {
        frameBuffer[i] = 0;//Clear contents of buffer
    }
}

void Game::drawWorld()
{
    /*In this method, I will outline the way objects will be drawn in the game. Since, I was smart and took care of
    drawing objects at the UnitManager interface level, it is a matter of outlining whether layers are drawn first or last!
    Important Note: Based on the documentation, SDL_RenderPresent exposes a backbuffer for final drawing onto the screen.
    As a result, the simple call of RenderCopy only works on building the backbuffer, so the player only sees the final
    frame after RenderPresent is called. Call RenderPresent once after the frame is complete and call RenderClear before
    building any frames!

    **Update: This method will skip all drawing methods except the video and the UIManager if a video is playing.
    This will prevent potential issues with objects drawing on top of the video image!
    */
    SDL_RenderClear(screen);//Let's first clear and initialize the backbuffer
    //Let's begin building the frame
    if(!isPlayingVideo())
    {
        //Cursor
        DrawCursor();
        //Let's draw the layers
        DrawLayers();
        //Next let's draw everything else!
        DrawUnits();
        //Finally, draw the UIs that are marked as visible last so they are on top of the game world
        UIDraw();
        //Draw loading screen
        if(loading)
            GetUI(loadID).Draw();//Draw on top of whatever has been drawn!
    }
    else
    {
        DrawVideo();//Video frame
        UIDraw();//UI
    }

    //If the game is being run from a game editor, make sure the editor can obtain a copy of the pixels. Warning: this operation may be slow!
    if(requestFrame)
    {
        ClearEditorFrameBuffer();//clean the buffer
        if(SDL_RenderReadPixels(screen, NULL, 0, (void*)frameBuffer, 0) != 0)//Read the pixels
            std::cout << SDL_GetError() << std::endl;
    }
    //Present buffer
    SDL_RenderPresent(screen);
}

void Game::playSounds()
{
    /*This method will play the sounds*/
    //First, play the level music or atmosphere track
    PlayMusicSound();//Game music
    if(!isPlayingVideo())
        PlayUnitSounds();//Unit manager sounds
    PlayNextSound();//Other sound effects
}

void Game::runPhysics()
{
    //Since only units have physics...
    RunPhysics();
}

void Game::run()
{
    if(multithreaded)//First, check if the game is running in multithreaded mode
    {
        //Spawn thread objects
        //Spawning threads also autostart them!
        pluginThread = SpawnThread(helperPluginFunction, this);
        drawThread  = SpawnThread(helperDrawFunction, this);
        soundThread  = SpawnThread(helperSoundFunction, this);
        updateThread = SpawnThread(helperUpdateFunction, this);
        eventsThread  = SpawnThread(helperEventsFunction, this);
        gcThread  = SpawnThread(helperGCFunction, this);
        //block this thread until an exit command has been emitted
        while(!isEngineClosing())
        {

        }
    }
    else//If the engine is running in single thread mode
    {
        //Run through every method call once per frame until exit command is issued from within the game
        while(!isEngineClosing())
        {
            //Update
            UpdateTriggers(currentLvl->GetHeroID());
            UIUpdate();
            if(isPlayingVideo())
                UpdateVideo();
            //Process events
            SDL_WaitEvent(&GetEvents());
            if(!isPlayingVideo())
                ProcessUnitEvents();
            UpdateInput(&GetEvents());
            UIProcessEvents();
            //Run physics
            if(!isPlayingVideo())
                runPhysics();
            //Run plugins
            RunAllFunctions();
            //Play sounds
            playSounds();
            //Draw world
            drawWorld();
            //Run GarbageCollector
            GC();
            mainGC();
            GCSounds();
        }
    }
}

void Game::stopGame()
{
    closeEngine = true;
}

void Game::ShowLoadingScreen()
{
    if(!GetUI(loadID).isVisible())
    {
        GetUI(loadID).toggleVisibility();
    }
    loading = true;
}

void Game::HideLoadingScreen()
{
    if(GetUI(loadID).isVisible())
    {
        GetUI(loadID).toggleVisibility();
    }
    loading = false;
}

void Game::UpdateLoadingStatus(size_t value)
{
    GetUI(loadID).AddNumToPBar(value, "LoadBar");
}

void Game::ReplaceLoadingScreen(cstr file)
{
    loading = false;
    UnregisterUI(loadID);
    loadID = RegisterUI(file);
}

void Game::ShowHUD()
{
    if(!GetUI(hudID).isVisible())
    {
        GetUI(hudID).toggleVisibility();
    }
}

void Game::HideHUD()
{
    if(GetUI(hudID).isVisible())
    {
        GetUI(hudID).toggleVisibility();
    }
}

void Game::ReplaceHUD(cstr file)
{
    UnregisterUI(hudID);
    hudID = RegisterUI(file);
}

void Game::ShowMainMenu()
{
    if(!GetUI(mainMenuID).isVisible())
    {
        GetUI(mainMenuID).toggleVisibility();
    }
}

void Game::HideMainMenu()
{
    if(GetUI(mainMenuID).isVisible())
    {
        GetUI(mainMenuID).toggleVisibility();
    }
}

void Game::ReplaceMainMenu(cstr file)
{
    UnregisterUI(mainMenuID);
    mainMenuID = RegisterUI(file);
}

void Game::ShowVideoHUD()
{
    if(!GetUI(videoHUD_ID).isVisible())
    {
        GetUI(videoHUD_ID).toggleVisibility();
    }
}

void Game::HideVideoHUD()
{
    if(GetUI(videoHUD_ID).isVisible())
    {
        GetUI(videoHUD_ID).toggleVisibility();
    }
}

void Game::ReplaceVideoHUD(cstr file)
{
    UnregisterUI(videoHUD_ID);
    videoHUD_ID = RegisterUI(file);
}

void Game::mainGC()
{
    //check ui ids
    for(std::list<size_t>::iterator itr = uiList.begin(); itr != uiList.end(); itr++)
    {
        if(!uiIDExists(*itr))
            uiList.erase(itr);
    }

    //check unit ids
    for(std::list<size_t>::iterator itr = moduleList.begin(); itr != moduleList.end(); itr++)
    {
        if(!hasUnit(*itr))
            moduleList.erase(itr);
    }
}

void Game::SaveData(const std::string& query)
{
    GetDataBase(dbID)->query(query);
}

DataBase* Game::GetSaveDataHandle()
{
    return GetDataBase(dbID);
}

size_t Game::GetHeroID() const
{
    return currentLvl->GetHeroID();
}

Level* Game::GetCurrentLevel()
{
    return currentLvl;
}

char* Game::GetFrameBuffer() const
{
    return frameBuffer;
}

size_t Game::GetSizeOfFrameBuffer() const
{
    return frameSize;
}

Game::~Game()
{
    //Emit engine exit command
    stopGame();
    //Close threads
    if(multithreaded)
    {
        CloseThread(pluginThread);
        CloseThread(drawThread);
        CloseThread(eventsThread);
        CloseThread(soundThread);
        CloseThread(updateThread);
        CloseThread(gcThread);
    }
    //Delay a bit so threads can begin exiting
    SDL_Delay(5000);

    //Begin deleting global objects
    for(std::list<size_t>::iterator itr = moduleList.begin(); itr != moduleList.end(); itr++)
    {
        UnregisterModule(*itr);
    }

    for(std::list<size_t>::iterator itr = uiList.begin(); itr != uiList.end(); itr++)
    {
        UnregisterUI(*itr);
    }

    //Delete level
    if(currentLvl)
        delete currentLvl;

    //Close save file
    CloseDBConnection(dbID);

    //Stop timer
    std::cout << "Engine closing after about " << GetTicks(mainTimer) << " ms!" << std::endl;
    DeleteTimer(mainTimer);

    //Delete the editor frame buffer if initialized
    if(frameBuffer)
        delete[] frameBuffer;

    //Delete SDL things
    SDL_DestroyRenderer(screen);
    SDL_DestroyWindow(win);
    SDL_free(event);

    //Let's shutdown the SDL subsystems
    SDLNet_Quit();//Network lib
    TTF_Quit();//Font lib
    Mix_Quit();//Audio lib
    IMG_Quit();//Image loading lib
    SDL_Quit();//SDL core subsystem
}

void Game::SetHeroIDForCurrentLevel(size_t h_id)
{
    currentLvl->SetHeroID(h_id);
}

bool Game::noHero() const
{
    return heroLoaded;
}

void Game::SetHeroUnitAsLoaded()
{
    heroLoaded = true;
}

void Game::UnsetHeroUnitAsLoaded()
{
    heroLoaded = false;
}

//End of namespace macro
//ENGINE_NAMESPACE_END
