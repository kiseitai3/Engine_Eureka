//#define EUREKA_EXPORT
#include "eureka.h"
#include "level.h"
#include <SDL_image.h>
#include "database.h"
#include <cmd_utils.h>

#include <windows.h>

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
const std::string Game::FRAME_FORMAT = "RGBA8888";

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
    gamePaused = false;
    frameBuffer = NULL;
    requestFrame = editor;
    initSTDStreams();
    initSubSys();
}

Game::Game(bool editor): ThreadSystem(), GameInfo(), ModuleSystem(this), UnitManager(this), IOManager(this), UIManager(this),
    NetworkManager(this), TriggerManager(this), LayerSystem(this), Cursor(this), TimerSystem(this), VideoPlayer(this), Input(this),
    SoundQueue(this), ParticleSystem(this)
{
    closeEngine = false;
    loading = false;
    gamePaused = false;
    frameBuffer = NULL;
    requestFrame = editor;
    initSubSys();
}

Game::Game(int argc, char* argv[], bool editor): ThreadSystem(), GameInfo(), ModuleSystem(this), UnitManager(this), IOManager(this), UIManager(this),
    NetworkManager(this), TriggerManager(this), LayerSystem(this), Cursor(this), TimerSystem(this), VideoPlayer(this), Input(this),
    SoundQueue(this), ParticleSystem(this)
{
    closeEngine = false;
    loading = false;
    gamePaused = false;
    frameBuffer = NULL;
    requestFrame = editor;
    initCMD(argc, argv);

    //Process cmd
    processCMD();

    if(g_file_path.size() > 0)
        LoadGame(g_file_path.c_str());
    //Replace standard streams with ours
    initSTDStreams();


    initSubSys();
}

Game::Game(cstr file, int argc, char* argv[], bool editor): ThreadSystem(), GameInfo(), ModuleSystem(this), UnitManager(this), IOManager(this), UIManager(this),
    NetworkManager(this), TriggerManager(this), LayerSystem(this), Cursor(this), TimerSystem(this), VideoPlayer(this), Input(this),
    SoundQueue(this), ParticleSystem(this)
{
    closeEngine = false;
    loading = false;
    gamePaused = false;
    frameBuffer = NULL;
    requestFrame = editor;
    initCMD(argc, argv);
    //Process cmd
    processCMD();
    LoadGame(file);
    //Replace standard streams with ours
    initSTDStreams();
    initSubSys();
}

void Game::initEditorFrameBuffer()
{
    frameSize = GetScreenWidth() * GetScreenHeight() * FRAME_FORMAT_SIZE;//Size of the buffer that will be exposed to the game editor.
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
    game_mutex_id = SpawnMutex();
}

void Game::LoadGame(cstr file)
{
    //Save actual initial path
    std::string filePath = SDL_GetBasePath();
    filePath += file;
    //First, load save database
    LoadSaveData(filePath.c_str());
    //Second, load constants as they are important values for the bootloading process
    LoadGameConstants(filePath.c_str());
    //Third, initialize SDL and the extension libraries
    if(!this->init())
    {
        std::cout << "Error: Could not initialize subsystems! Maybe, the initial file is wrong or not present!" << std::endl;
    }
    //Fourth, load global modules
    LoadGlobalModules(filePath.c_str());
    //Fifth, load global UIs
    LoadUIs(filePath.c_str());
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

void Game::LoadGameConstants(cstr file, bool hasdb)
{
    //Load file
    data_base gameDOM(file);
    DataBase* tmpDB = NULL;
    tmpDB = GetDataBase(dbID);
    //Basic variables
    std::string rootDir, modLoc, saveLoc, gameName, icon, renderQuality, driver;
    size_t fps, width, height, bpp, blitlvls, freq, chan, chunksize, displayIndex, displayCount, screenmode, vol;
    bool detectVid, detectAud, saveConstToFile;

    //Since we have setting data in a file and also in the save file (custom settings), we have to give priority to the user's settings!
    if(hasdb || (tmpDB && tmpDB->isConnected()))
    {
        //Extract data
        std::string tmpStr;
        saveConstToFile = false;
        char* tmp = SDL_GetBasePath();
        rootDir = tmp;
        SDL_free(tmp);
        tmpDB->query(tmpDB->prepareStatement("settings", "root", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(tmpStr);
        rootDir += tmpStr;

        //Mod
        tmpDB->query(tmpDB->prepareStatement("settings", "current_mod", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(modLoc);
        //Game Name
        tmpDB->query(tmpDB->prepareStatement("settings", "game_name", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(gameName);
        //Icon
        tmpDB->query(tmpDB->prepareStatement("settings", "icon", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(icon);
        //Current display
        tmpDB->query(tmpDB->prepareStatement("settings", "current_display", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(displayIndex);
        //The rendering quality
        tmpDB->query(tmpDB->prepareStatement("settings", "render_quality", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(renderQuality);
        //fps limit
        tmpDB->query(tmpDB->prepareStatement("settings", "frames_per_second", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(fps);
        //Screen variables
        tmpDB->query(tmpDB->prepareStatement("settings", "screen_width", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(width);
        tmpDB->query(tmpDB->prepareStatement("settings", "screen_height", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(height);
        tmpDB->query(tmpDB->prepareStatement("settings", "screen_bp", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(bpp);
        tmpDB->query(tmpDB->prepareStatement("settings", "blit_levels", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(blitlvls);
        tmpDB->query(tmpDB->prepareStatement("settings", "screen_mode", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(screenmode);
        tmpDB->query(tmpDB->prepareStatement("settings", "renderer", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(driver);
        //Sound settings
        tmpDB->query(tmpDB->prepareStatement("settings", "frequency", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(freq);
        tmpDB->query(tmpDB->prepareStatement("settings", "channels", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(chan);
        tmpDB->query(tmpDB->prepareStatement("settings", "chunk_size", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(chunksize);
        //Auto detect video settings?
        tmpDB->query(tmpDB->prepareStatement("settings", "auto_video", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(detectVid);
        //Run the game in multithreading mode?
        tmpDB->query(tmpDB->prepareStatement("settings", "multithreaded", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(multithreaded);
        //Sound volume
        tmpDB->query(tmpDB->prepareStatement("settings", "sound_volume", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(vol);
        //Save destination
        tmpDB->query(tmpDB->prepareStatement("settings", "save_destination", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(saveLoc);

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
                blitlvls, screenmode, driver, freq, chan, chunksize);
        SetSoundVolume(vol);
        SetSoundDeviceStr(SDL_GetAudioDeviceName(0, 0));
        SetScreenDeviceStr(SDL_GetDisplayName(0));

        //Load all of the expansion basic data!
        LoadExpansionInfo(tmpDB);

        //First, we load the default keybindings
        LoadDefaultKeyBindings((GetModName() + gameDOM.GetStrFromData("keybindings_file")).c_str());

        /*The save file (sqlite) database will contain tables with save data, but also the input settings for the game!*/
        LoadCurrentKeyBindings(dbID);

        /*Load locale data from database*/
        LoadLocaleListFromDB(tmpDB);
        SetLocale(GetSelectedLocale().path.c_str());

        //Get logging path
        tmpDB->query(tmpDB->prepareStatement("Log_Settings", "in", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(g_in_path);
        tmpDB->query(tmpDB->prepareStatement("Log_Settings", "out", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(g_out_path);
        tmpDB->query(tmpDB->prepareStatement("Log_Settings", "err", "id=1","","",SELECT|WHERE));
        tmpDB->GetResult(g_err_path);

        if(saveConstToFile)
        {
            //Game Name
            tmpDB->query(tmpDB->prepareStatement("settings", intToStr(width), "variable=screen_width","","",UPDATE));
            tmpDB->query(tmpDB->prepareStatement("settings", intToStr(height), "variable=screen_height","","",UPDATE));
            tmpDB->query(tmpDB->prepareStatement("settings", intToStr(bpp), "variable=screen_bpp","","",UPDATE));
        }
    }
    else
    {
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
        screenmode = gameDOM.GetIntFromData("screen_mode");
        driver = gameDOM.GetStrFromData("video_driver");
        freq = gameDOM.GetIntFromData("frequency");
        chan = gameDOM.GetIntFromData("channels");
        chunksize = gameDOM.GetIntFromData("chunk_size");
        detectVid = gameDOM.GetIntFromData("auto_video");
        multithreaded = gameDOM.GetIntFromData("multithreaded");
        vol = gameDOM.GetIntFromData("sound_volume");
        saveLoc = gameDOM.GetStrFromData("save_destination");

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
                blitlvls, screenmode, driver, freq, chan, chunksize);
        SetSoundVolume(vol);
        SetSoundDeviceStr(SDL_GetAudioDeviceName(0,0));
        SetScreenDeviceStr(SDL_GetDisplayName(0));

        //We load the default keybindings
        LoadDefaultKeyBindings((modLoc + gameDOM.GetStrFromData("keybindings_file")).c_str());

        //Load all of the expansion basic data!
        LoadExpansionInfo(file);

        //Locale data
        LoadLocaleListFromLoc(rootDir + "/locales");
        SetLocale(GetSelectedLocale().path.c_str());

        //Get logging path
        g_in_path = gameDOM.GetStrFromData("in");
        g_out_path = gameDOM.GetStrFromData("out");
        g_err_path = gameDOM.GetStrFromData("err");
    }
    //Now we load the script file that will handle input for the chosen mod!
    LoadKeyScript((modLoc + gameDOM.GetStrFromData("key_script")).c_str());
    /*Finally, we load the main cursor set! Although the game scripts and plugins can load additional cursors, it is important to
    load an initial set of cursors for the game. If the cursor set file is empty, then no cursors should be loaded or errors issued!
    */
    LoadCursors((modLoc + gameDOM.GetStrFromData("cursor_set")).c_str());
    if(fps)
        frameCapped = true;
    changeProgramWorkingDirectory(rootDir.c_str());
    sleep(1000);
}

void Game::SaveGameSettings()
{
    DataBase* tmpDB = GetSaveDataHandle();
    tmpDB->query(tmpDB->prepareStatement("settings", GetRootDirectory(), "variable=root","","",UPDATE));

    //Mod
    tmpDB->query(tmpDB->prepareStatement("settings", GetModName(), "variable=current_mod","","",UPDATE));
    //Game Name
    tmpDB->query(tmpDB->prepareStatement("settings", GetGameName(), "variable=game_name","","",UPDATE));
    //Icon
    tmpDB->query(tmpDB->prepareStatement("settings", GetIconLoc(), "variable=icon","","",UPDATE));
    //Current display
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetDisplayIndex()), "variable=current_display","","",UPDATE));
    //The rendering quality
    tmpDB->query(tmpDB->prepareStatement("settings", GetRenderQuality(), "variable=render_quality","","",UPDATE));
    //fps limit
    tmpDB->query(tmpDB->prepareStatement("settings",  intToStr(GetMaxFramesPerSec()), "variable=frames_per_second","","",UPDATE));
    //Screen variables
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetScreenWidth()), "variable=screen_width","","",UPDATE));
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetScreenHeight()), "variable=screen_height","","",UPDATE));
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetScreenBPP()), "variable=screen_bpp","","",UPDATE));
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetBlitLevels()), "variable=blit_levels","","",UPDATE));
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetScreenMode()), "variable=screen_mode","","",UPDATE));
    tmpDB->query(tmpDB->prepareStatement("settings", GetRenderDriver(), "variable=renderer","","",UPDATE));
    //Sound settings
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetSoundFrequency()), "variable=frequency","","",UPDATE));
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetSoundChannels()), "variable=channels","","",UPDATE));
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetSoundChunkSize()), "variable=chunk_size","","",UPDATE));
    //Auto detect video settings?
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(0), "variable=auto_video","","",UPDATE));
    //Run the game in multithreading mode?
    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(multithreaded), "variable=multithreaded","","",UPDATE));

    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetDisplayCount()), "variable=display_count","","",UPDATE));

    tmpDB->query(tmpDB->prepareStatement("settings", intToStr(GetMasterVolume()), "variable=sound_volume","","",UPDATE));
}

void Game::LoadGlobalModules(cstr file)
{
    data_base gameDOM(file);
    data_base tmp;
    std::string modPath = gameDOM.GetStrFromData("plugins");
    std::string path;
    gameDOM.CloseFile();
    gameDOM.OpenFile(modPath.c_str());
    size_t mod_id;

    /*Game modules!*/
    std::string nameString = "module_";
    for(int i = 0; i < gameDOM.GetIntFromData("module_number"); i++)
    {
        path = gameDOM.GetStrFromData(nameString).c_str();
        nameString += intToStr(i);
        mod_id = RegisterModule(path.c_str());
        moduleList.push_back(mod_id);
        nameString = "module_";
        //Check for possible descriptor files
        tmp.OpenFile(path.c_str());
        if(tmp.GetStateOfInternalBuffer())
            RegisterFunctionFromFile((path + ".txt").c_str(), mod_id);
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

void Game::LoadSaveData(const std::string& saveData)
{
    data_base gameDOM(saveData.c_str());
    DataBase* tmpDB;
    //Load Database!
    dbID = RegisterDataBase(gameDOM.GetStrFromData("save_destination").c_str());
    tmpDB = GetDataBase(dbID);
    if(!tmpDB->isConnected())
    {
        /*If the database does not exist, it is probably because this is the "first" time the game is ran.
        As a result, the file must be copied to the target location!*/
        std::cout << "Warning: Save file missing! Copying default copy! Ignore if this is the first time you run the game!" << std::endl;
        std::string data;
        data_base dst;
        data_base src(gameDOM.GetStrFromData("save").c_str());
        dst.OpenBinFileForQuickWrite(gameDOM.GetStrFromData("save_destination").c_str());
        data = src.GetStrBuffer();
        dst.WriteValueAndFlush(data);//copy data
        tmpDB->connect(gameDOM.GetStrFromData("save_destination").c_str());//attempt to connect again
    }
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
    win = SDL_CreateWindow(GetGameName().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, GetScreenMode());

    //If there was an error in setting up the screen
    if( win == NULL )
    {
        std::cout<<"Error: Could not create the window!\n\r";
        return false;
    }
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, GetRenderDriver().c_str());
        screen = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, GetRenderQuality().c_str());  // make the scaled rendering look smoother.
        SDL_RenderSetLogicalSize(screen, GetScreenWidth(), GetScreenHeight());
        SDL_GetRendererInfo(screen, this);
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
    //Create a timer
    mainTimer = CreateTimer();
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

void Game::initCMD(int argc, char* argv[])
{
    cmd_no_args = "help,h,app_name;";
    cmd_init(cmd_no_args.c_str(), cmd_no_args.size());
    cmd_process(argc, argv);
    /*Example of cmd usage*/
    /*
    for(size_t i = 0; i < cmd_get_argc(); i++)
    {
        size_t hash = cmd_get_option();
        if(hash == cmd_generate_hash("-t", 2))
            printf("%s \n", cmd_get_argument());
        else
            printf("%s", "Unknown argument!");
        cmd_next_arg();
    }*/

}

void Game::initSTDStreams()
{
    //Init our streams
    g_in =  new std::ifstream(g_in_path.c_str());
    g_out =  new std::ofstream(g_out_path.c_str());
    g_err =  new std::ofstream(g_err_path.c_str());
    //Grab stream buffers
    in = std::cin.rdbuf();
    out = std::cout.rdbuf();
    err = std::cerr.rdbuf();
    //Replace stream buffers with our own
    std::cin.rdbuf(g_in->rdbuf());
    std::cout.rdbuf(g_out->rdbuf());
    std::cerr.rdbuf(g_err->rdbuf());
}

void Game::processCMD()
{
    for(size_t i = 0; i < cmd_get_argc(); i++)
    {
        size_t hash = cmd_get_option();
        if(hash == cmd_generate_hash("-o", 2))
        {
            g_out_path = cmd_get_argument();
        }
        if(hash == cmd_generate_hash("-i", 2))
        {
            g_in_path = cmd_get_argument();
        }
        if(hash == cmd_generate_hash("-e", 2))
        {
            g_err_path = cmd_get_argument();
        }
        if(hash == cmd_generate_hash("-file", 5))
        {
            g_file_path = cmd_get_argument();
        }
        cmd_next_arg();
    }
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

void Game::RestartRenderer()
{
    LockMutex(game_mutex_id);
    //Free the previous renderer
    SDL_DestroyRenderer(screen);
    screen = NULL;
    //Build new renderer
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, GetRenderDriver().c_str());
    screen = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, GetRenderQuality().c_str());  // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(screen, GetScreenWidth(), GetScreenHeight());
    UnlockMutex(game_mutex_id);
}

void Game::RestartVideoAndSound()
{
    //Restart video
    RestartVideo();
    //Restart audio
    RestartAudio();
}

void Game::RestartAudio()
{
    LockMutex(game_mutex_id);
    //Close audio
    Mix_CloseAudio();
    //Open audio
    if( Mix_OpenAudio( GetSoundFrequency(), MIX_DEFAULT_FORMAT, GetSoundChannels(), GetSoundChunkSize() ) == -1 )
        std::cerr << "Engine error: Could not restart audio system!" << std::endl;
    UnlockMutex(game_mutex_id);
}

void Game::RestartVideo()
{
    LockMutex(game_mutex_id);
    //Free the previous renderer and screen
    SDL_DestroyRenderer(screen);
    SDL_DestroyWindow(win);
    screen = NULL;
    win = NULL;
    //Create new window
    win = SDL_CreateWindow(GetGameName().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, GetScreenMode());
    //Create new renderer
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, GetRenderDriver().c_str());
    screen = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, GetRenderQuality().c_str());  // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(screen, GetScreenWidth(), GetScreenHeight());
    UnlockMutex(game_mutex_id);
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
        //ClearEditorFrameBuffer();//clean the buffer
        if(SDL_RenderReadPixels(screen, NULL, SDL_PIXELFORMAT_RGBA8888, (void*)frameBuffer, max_texture_width) != 0)//Read the pixels
        {
            std::cout << SDL_GetError() << std::endl;
        }
    }/**/ //Causes memory leak for some bizzarre reason
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

    PlayCursorSound();
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
            if(!isPlayingVideo())
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

void Game::ShowWindow(bool visible)
{
    if(visible)
        SDL_ShowWindow(win);
    else
        SDL_HideWindow(win);
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

void Game::SetWindowPosition(size_t x, size_t y)
{
    SDL_SetWindowPosition(win, x, y);
}

void Game::SetWindowSize(size_t h, size_t w)
{
    SDL_SetWindowSize(win, w, h);
}

void Game::SetWindowBorderless(bool borderless)
{
    SDL_SetWindowBordered(win, (SDL_bool)!borderless);
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

    //Restore the standard streams and clean up the custom buffers
    std::cout.rdbuf(out);
    std::cin.rdbuf(in);
    std::cerr.rdbuf(err);
    delete g_in;
    delete g_out;
    delete g_err;

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
