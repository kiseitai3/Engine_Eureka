#include <iostream>
#include <string>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_net.h>

#include "../data_base.h"
#include "../draw_base.h"
#include "../sound_base.h"
#include "../threading.h"
#include "../textbox.h"
#include "../trigger.h"
#include "../button.h"
#include "../physics.h"
#include "../timersystem.h"
#include "../Dependencies/CRC/crc.h"

#include <windows.h>

bool stop = false;
size_t mutex_id;
std::string msg3;
bool world = false;

//SDL values
int FRAMES_PER_SECOND = 60;
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int SCREEN_BPP = 32;
int BLITLEVELS = 50;
int FREQUENCY = 22050;
int CHANNELS = 2;
int CHUNKSIZE = 4096;
const char *NAME = "Eureka Engine!\0";
const char *ICON = NULL;
//Globals
SDL_Renderer* screen = NULL;
SDL_Window* win = NULL;
SDL_Event e;
Timer fps;


draw_base texture, texture2, texture3;
textbox* txt_input = NULL;

void_ptr myThread(void* data)
{
    char* d = (char*) data;
    while(!stop)
    {
        sleep(10000);
        std::cout << d << std::endl;
    }
}

void_ptr myThread2(void* data)
{
    ThreadSystem* d = (ThreadSystem*) data;
    while(msg3.size() < 400)
    {
        d->LockMutex(mutex_id);
        if(!world)
            msg3 += "Hello ";
        else
            msg3 += "World! ";
        world = !world;
        std::cout << msg3 << std::endl;
        d->UnlockMutex(mutex_id);
    }
}

void_ptr myDrawThread(void_ptr obj)
{
    while(!stop)
    {
        SDL_RenderClear(screen);
        ((draw_base*)obj)->apply_surface(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, *screen);
        texture2.apply_surface(SCREEN_WIDTH/4, SCREEN_HEIGHT/4, *screen);
        if(txt_input)
            txt_input->Draw(*screen);
        SDL_RenderPresent(screen);
        SDL_Delay(5);
    }
}

void_ptr mySoundThread(void_ptr sound)
{
    sound_base* tmp = (sound_base*)sound;
    tmp->Play(-1);
}

//Prototypes
bool init();

int main(int argc, char** argv)
{
    size_t res;
    //Let's build a thread manager object and call 3 threads
    /*This section is for testing threads!*/
    ThreadSystem ts;
    char* msg1 = "Hello World from thread 1.\0";
    char* msg2 = "Hello World from thread 2.\0";
    size_t thread1 = ts.SpawnThread(myThread, (void*)msg1);
    size_t thread2 = ts.SpawnThread(myThread, (void*)msg2);
    sleep(90000);
    stop = true;

    mutex_id = ts.SpawnMutex();
    size_t thread3 = ts.SpawnThread(myThread2, (void*)&ts);
    ts.LockMutex(mutex_id);
    ts.UnlockMutex(mutex_id);
    sleep(500000);

    /*Now, we move on to testing draw_base!
    However, for the following objects I will have to initialize SDL!*/

    //Init
    init();

    //Create draw_base object
    texture.Load_Texture("test_hero.txt\0", *screen, 30);
    texture2.Load_Texture("test_hero.txt\0", *screen, 30);
    size_t thread4 = ts.SpawnThread(myDrawThread, (void*)&texture);
    const byte* keystates;
    stop = false;

    //Create sound_base object
    size_t t = 0;
    unsigned char* buff = get_bin_buffer("Crickets.wav", t);
    sound_base sound;
    //sound.Load_Sound("sound_test.txt");
    sound.Load_SoundFromBuffer(buff, t, false);
    size_t thread5 = ts.SpawnThread(mySoundThread, (void*)&sound);

    //CRC test
    std::cout << "CRC of Crickets: " << std::hex << crc64_on_file_fast("Crickets.wav") << std::endl;
    std::cout << "CRC of Animation: " <<  std::hex << crc64_on_file_fast("Fireb.png") << std::endl;
    std::cout << "CRC of Save Database: " <<  std::hex << crc64_on_file_fast("save") << std::endl;
    std::cout << "CRC of Python Script: " <<  std::hex << crc64_on_file_fast("pyMod.py") << std::endl;

    //Create textbox
    txt_input = new textbox("Hello World!\0", "textbox_test.txt", *screen);

    //Event handling for the tests
    while(SDL_WaitEvent(&e))
    {
        math_point loc = txt_input->GetLoc();
        keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_Q])
            break;
        else if(keystates[SDL_SCANCODE_A])
            texture.setAlpha(255);
        else if(keystates[SDL_SCANCODE_Z])
            texture.setAlpha(0);
        else if(keystates[SDL_SCANCODE_R])
            texture.rotate(10);
        else if(keystates[SDL_SCANCODE_L])
            texture.rotate(-10);
        else if(keystates[SDL_SCANCODE_B])
            texture.setColor(255,255,255);
        else if(keystates[SDL_SCANCODE_T])
            //Print ticks
            std::cout << fps.get_ticks() << std::endl;
        else if(keystates[SDL_SCANCODE_LEFT])
        {
            loc.X -= 5;
            txt_input->SetLoc(loc.X, loc.Y);
        }
        else if(keystates[SDL_SCANCODE_RIGHT])
        {
            loc.X += 5;
            txt_input->SetLoc(loc.X, loc.Y);
        }

    }
    stop = true;
    SDL_Delay(500);
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
    win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    //If there was an error in setting up the screen
    if( win == NULL )
    {
        std::cout<<"Error: Could not create the window!\n\r";
        return false;
    }
    else
    {
        screen = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
        SDL_RenderSetLogicalSize(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_SetRenderDrawColor(screen, 255,255,255,255);
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

