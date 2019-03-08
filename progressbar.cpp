//#define EUREKA_EXPORT
#include "progressbar.h"
#include "physics.h"
#include "draw_base.h"
#include <SDL.h>
#include <SDL_image.h>

//Engine name space macro
//ENGINE_NAMESPACE


ProgressBar::ProgressBar(const char *file, int *num, math_point loc, SDL_Renderer& ren, int blitOrderI)//file must be the texture path
{
    if(file != "")
    {
        bar = LoadTexture(file, (SDL_Renderer&)ren);
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

void ProgressBar::Draw(const SDL_Renderer& ren)
{
    SDL_RenderCopy( (SDL_Renderer*)&ren, getTextureFromNode(bar), &src, &target );
}

void ProgressBar::SetRectangleDimensions(int w, int h)
{
    src.w = w;
    src.h = h;
    target.w = w;
    target.h = h;
}

int ProgressBar::GetRectangleHeight() const
{
    return target.h;
}

int ProgressBar::GetRectangleWidth() const
{
    return target.w;
}

ProgressBar::~ProgressBar()
{
    if(bar > 0)
    {
        draw_base::textures.DeleteUniqueTexture(bar);
    }
}

//End of namespace macro
//ENGINE_NAMESPACE_END
