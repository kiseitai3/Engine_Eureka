#include "../eureka.h"

int main(int argc, char** argv)
{
    //Basic variables
    Game* g = new Game(true);

    //Set video settings
    g->SetInfo(".", "demo", "save/save", "Test", ".", "best",
                    1, 0, 60, 640, 480, 32,
                    50, 32, "opengl", 22050, 2, 4096);
    g->SetSoundVolume(100);
    g->initSubSys();
    g->init();

    //Test drawWorld for any memory leaks
    for(size_t i = 0; i < 30; i++)
    {
        g->drawWorld();
    }

    delete g;
}
