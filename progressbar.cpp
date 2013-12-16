#include "progressbar.h"
#include "physics.h"
#include "draw_base.h"
#include <SDL.h>
#include <SDL_image.h>

ProgressBar::ProgressBar(const char *file, int *num, math_point loc, SDL_Renderer *ren, int blitOrderI)//file must be the texture path
{
    if(file > "")
    {
        bar = LoadTexture(file, ren);
    }
    src.x = loc.X;
    src.y = loc.Y;
    maxVal = *num;
    currentVal = num;
    blitOrder = blitOrderI;
    target.x = 0;
    target.y = 0;
}

void ProgressBar::Update(int x, int y)
{
    src.x = x;
    src.y = y;
    target.w = (int)((*currentVal / ((float)(maxVal))) * maxVal);
}

void ProgressBar::Draw(SDL_Renderer *ren)
{
    SDL_RenderCopy( ren, bar, &src, &target );
}

void ProgressBar::SetRectangleDimensions(int w, int h)
{
    src.w = w;
    src.h = h;
    target.w = w;
    target.h = h;
}

int ProgressBar::GetRectangleHeight()
{
    return target.h;
}

int ProgressBar::GetRectangleWidth()
{
    return target.w;
}

ProgressBar::~ProgressBar()
{
    if(bar > 0)
    {
        SDL_DestroyTexture(bar);
    }
}
