#ifndef DRAW_BASE_H_INCLUDED
#define DRAW_BASE_H_INCLUDED

#include <SDL.h>

#include <string>
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


class draw_base
{
    public:
    void Load_Texture(const char* source, SDL_Renderer& ren, int fps = 30);
    void apply_surface( int x, int y, SDL_Renderer& destination);
    int GetHeightOfMainRect() const;
    int GetWidthOfMainRect() const;
    int GetAnimCounter() const;
    bool isNoLoop() const;
    SDL_Texture& GetTexture() const;
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void setRotationPivot(math_point p);
    void flip(size_t direction = NOFLIP);
    void rotate(double degrees);
    void resetRotation();
    void ClearTexture();
    void SetTextureFromPointer(SDL_Texture* ptr);
    void SetTextureFromRef(SDL_Texture& tex);
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
    SDL_RendererFlip flipDir;//The direction to flip
    SDL_Texture* SpriteSheet;
    SDL_Rect src, target;
    SDL_Point pivot;
    int noLoop;
    double rotationDeg;//Degrees around which the texture should be rotated!

};

void apply_surface( int x, int y, SDL_Renderer& destination, SDL_Texture& SpriteSheet, int height = 40, int width = 40); //Non-animation drawing function
SDL_Texture *LoadTexture(const char* file, SDL_Renderer& ren);//Non-class loading function

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // DRAW_BASE_H_INCLUDED
