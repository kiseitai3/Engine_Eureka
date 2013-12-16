#include "physics.h"
#include "sound_base.h"
#include "draw_base.h"
#include "xml_base.h"
#include <SDL.h>
#include <string>



class Env_obj
{
    /*This class will be the template for all environment objects. The idea is to use external data to differentiate i.e. a tree from a rock,
but still have one underlying data structure so that I can "guess the type" of the environment objects in a list/ vector/ array. The same
strategy will be used for characters, animals, spells and usable items. */

    public:
    Env_obj(int BlitOrder, std::string name, char soundName, math_point *screenPoint, math_point loc, SDL_Surface *screen, SDL_Surface *sharedTexture = NULL)
    {
        //blitOrder will be used to prioritize what objects to draw first.
        phys.Load_Physics((char *)name.c_str());

        //Since this is an environment object, it is possible for it to use the texture of a previously initiated object. i. e. a second
        //tree in the map.
        std::string a = "Data\\Animation\\Anim_"; //Apparently, C++ has some issues with mixing string literals with char variables.
        std::string b = ".xml";                   //As a result, I split the literals into a and b pieces.
        std::string animPath = a + name + b;
        if(sharedTexture != NULL)
        {
            draw.Load_Texture_Shared((const char *)(animPath.c_str()), (char *)name.c_str(), sharedTexture);
        }
        else
        {
            draw.Load_Texture((const char *)(animPath.c_str()), (char *)name.c_str());
        }

        //This part is tricky. The sound won't be in every object, but not all objects are soundless, so I have to load a sound even if
        //it is a dummy sound (empty wave data)
        a = "Data\\Audio\\env_Obj_";
        std::string sndPath = a + name + b;
        sound.Load_Sound((const char *)(sndPath.c_str()), (char *)soundName);
        blitOrder = BlitOrder;
        pScreenPoint = screenPoint;
        mapPoint = loc;
        destination = screen;
    }

    int getBlitOrder()
    {
        return blitOrder;
    }

    math_point getLoc()
    {
        return mapPoint;
    }

    void Draw()
    {
        draw.apply_surface((int *)mapPoint.X, (int *)mapPoint.Y, destination);
    }



    private:
    Physics phys;
    xml_base xml;
    draw_base draw;
    sound_base sound;
    int blitOrder;
    math_point mapPoint;
    math_point *pScreenPoint;
    SDL_Surface *destination;
};
