#define EUREKA_EXPORT
#include "eureka.h"

SDL_Renderer& Game::GetRenderer()
{
    return *screen;
}

bool Game::isEngineClosing() const
{
    return closeEngine;
}

bool Game::GetRelativity() const
{
    return relativity;
}

size_t Game::GetMainTimer()
{
    return mainTimer;
}

