#define EUREKA_EXPORT
#include "eureka.h"

//Engine name space macro
//ENGINE_NAMESPACE


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

size_t Game::GetMainTimer() const
{
    return mainTimer;
}

SDL_Event& Game::GetEvents()
{
    return *event;
}

bool Game::isMultithreaded() const
{
    return multithreaded;
}

size_t Game::GetWinID() const
{
    return SDL_GetWindowID(win);
}
//End of namespace macro
//ENGINE_NAMESPACE_END
