#ifndef PROGRESSBAR_H_INCLUDED
#define PROGRESSBAR_H_INCLUDED
#include "physics.h"
#include <SDL.h>

class ProgressBar
{
private:
    math_point location;
    int maxVal;
    int *currentVal;
    int blitOrder;
    SDL_Texture *bar;
    SDL_Rect src, target;

public:
    ProgressBar(const char *file, int *num, math_point loc, SDL_Renderer& ren, int blitOrderI = 10);
    void Update(int x, int y);
    void Draw(const SDL_Renderer& ren);
    void SetRectangleDimensions(int w, int h);
    int GetRectangleHeight() const;
    int GetRectangleWidth() const;
    ~ProgressBar();
};


#endif // PROGRESSBAR_H_INCLUDED
