#ifndef DRAW_BASE_H_INCLUDED
#define DRAW_BASE_H_INCLUDED

#include <SDL.h>
#include "data_base.h"
#include <string>

class draw_base
{
    public:
    void Load_Texture(const char* source, SDL_Renderer* ren);
    void apply_surface( int x, int y, SDL_Renderer* destination);
    int GetHeightOfMainRect();
    int GetWidthOfMainRect();
    int GetAnimCounter();
    data_base *GetDOM();
    bool isNoLoop();
    SDL_Texture *GetTexture();
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void ClearTexture();
    void SetTextureFromPointer(SDL_Texture *ptr);
    draw_base();
    ~draw_base();

    private:
    int frame;
    int frames;
    int height;
    int width;
    int animNum;//This variable is 0 indexed! That means that animation 1 in spritesheet is 0!
    int animCounter;//Contains total number of animations
    int timeBetweenFrames;//In cycles. This is the time each frame will spend on the screen. Useful when you have an animation with < FRAMEs_PER_SECOND and you want it to last more than or about a second.
    int timeSpentOnFrame; //Keeps track of how draw cycles have passed on the frame.
    SDL_Texture* SpriteSheet;
    SDL_Rect src, target;
    data_base *animDOM;
    int noLoop;

};

void apply_surface( int x, int y, SDL_Renderer* destination, SDL_Texture *SpriteSheet, int height = 40, int width = 40); //Non-animation drawing function
SDL_Texture *LoadTexture(const char* file, SDL_Renderer* ren);//Non-class loadingg function
#endif // DRAW_BASE_H_INCLUDED
