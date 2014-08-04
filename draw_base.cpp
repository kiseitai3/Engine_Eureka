#include <SDL.h>
#include <SDL_image.h>
#include "data_base.h"
#include <string>
#include <iostream>
#include "draw_base.h"
#include "conversion.h"

void draw_base::Load_Texture(const char* source, SDL_Renderer& ren, int fps)// animName is the variable that will contain the name of the animation tag name in the xml file containing the animation details of especific objects (i.e. The hero's animation would have an animation name <hero>).
{
    animDOM = new data_base(source);
    if(animDOM)
    {
        SDL_Surface* tmp = IMG_Load(animDOM->GetStrFromData("tex_texture").c_str());
        if(!tmp)
        {
            std::cout << "Failed to load the surface!\n\r";
        }
        else
        {
            SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB( tmp->format, 0x0, 0xFF, 0xFF ));
            SpriteSheet = SDL_CreateTextureFromSurface(&ren, tmp);
            SDL_FreeSurface(tmp);
        }
        frames = animDOM->GetIntFromData("tex_frames");
        height = animDOM->GetIntFromData("tex_height");//Size of placeholding rectangle
        width = animDOM->GetIntFromData("tex_width");
        animNum = animDOM->GetIntFromData("tex_anim_num");
        animCounter = animDOM->GetIntFromData("tex_anim_counter");
        noLoop = animDOM->GetIntFromData("tex_noloop");
        timeBetweenFrames = animDOM->GetIntFromData("tex_time_on_frames");
        if(timeBetweenFrames == 0)
        {
            timeBetweenFrames = (int)(round(1.0 / (frames / (double)(fps)), 0)); //get the number of cycles the frame will be visible by targetting the current frame cap
        }
        src.h = height;
        src.w = width;
        target.h = height;
        target.w = width;
    }
    else
    {
        std::cout<<"ERROR:Failed to load this draw_base object's Document Object Model\n\r";
    }
}

bool draw_base::isNoLoop() const
{
    return noLoop;
}

void draw_base::apply_surface( int x, int y, SDL_Renderer& destination)
{
    //Holds the clip rectangle that will cycle through the spritesheet!
    src.x = width * frame;
    src.y = height * animNum;

    //Get offsets
    target.x = x;
    target.y = y;

    //Blit
    SDL_RenderCopy(&destination, SpriteSheet, &src, &target);
    if(frame != frames && !noLoop)
    {
        if(timeSpentOnFrame == timeBetweenFrames)
        {
            frame++;
            timeSpentOnFrame = 0;
        }
        else
        {
            timeSpentOnFrame++;
        }
    }
    else
    {
        frame = 0;
    }
}
int draw_base::GetHeightOfMainRect() const//This function is here in case I need some data for pixel detection in my physics class (coming up next! :))
{
    return height;
}
int draw_base::GetWidthOfMainRect() const//This function is here in case I need some data for pixel detection in my physics class (coming up next! :))
{
    return width;
}

int draw_base::GetAnimCounter() const
{
    return animCounter;
}

data_base *draw_base::GetDOM() const
{
    return animDOM;
}

SDL_Texture& draw_base::GetTexture() const
{
    return *SpriteSheet;
}

void draw_base::ClearTexture()
{
    SDL_DestroyTexture(SpriteSheet);
    SpriteSheet = 0;
}

void draw_base::SetTextureFromPointer(SDL_Texture *ptr)
{
    SpriteSheet = ptr;
}

void draw_base::SetTextureFromRef(SDL_Texture& tex)
{
    SpriteSheet = &tex;
}

void draw_base::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( SpriteSheet, red, green, blue );
}

void draw_base::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( SpriteSheet, blending );
}

void draw_base::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( SpriteSheet, alpha );
}

draw_base::draw_base()
{
    frame =0;
    frames=1;
    height =0;
    width =0;
    noLoop = 0;
}

draw_base::~draw_base()
{
    ClearTexture();
    if(animDOM > 0)
    {
        delete(animDOM);
    }
}


void apply_surface( int x, int y, SDL_Renderer& destination, SDL_Texture& SpriteSheet, int height, int width)
{
//Holds the clip rectangle that will cycle through the spritesheet!
    SDL_Rect clip;
    clip.h = height;
    clip.w = width;
    clip.x = 0;
    clip.y = 0;

    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;
    offset.h = height;
    offset.w = width;

    //Blit
    SDL_RenderCopy( &destination, &SpriteSheet, &clip, &offset );

 }

SDL_Texture *LoadTexture(const char* file, SDL_Renderer& ren)
{
    SDL_Texture* SpriteSheet;
    SDL_Surface* tmp = IMG_Load(file);
    if(!tmp)
    {
        std::cout << "Failed to load the surface!\n\r";
    }
    else
    {
        SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB( tmp->format, 0x0, 0xFF, 0xFF ));
        SpriteSheet = SDL_CreateTextureFromSurface(&ren, tmp);
        SDL_FreeSurface(tmp);
    }
    if(!SpriteSheet)
    {
        std::cout<< "Error: Unable to build texture from the surface!\n\r";
        return NULL;
    }
    else
    {
        return SpriteSheet;
    }
}

