#define EUREKA_EXPORT
#include "eureka.h"

//Engine name space macro
//ENGINE_NAMESPACE


SDL_Renderer& Game::GetRenderer(size_t& game_mutex)
{
    LockMutex(game_mutex_id);
    game_mutex = game_mutex_id;
    return *screen;
}

void Game::UnlockRenderer(size_t mutex_id)
{
    UnlockMutex(mutex_id);
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

bool Game::isGamePaused() const
{
    return gamePaused;
}

size_t Game::GetWinID() const
{
    return SDL_GetWindowID(win);
}

void Game::PauseGame()
{
    gamePaused = true;
}

void Game::ResumeGame()
{
    gamePaused = false;
}
//End of namespace macro
//ENGINE_NAMESPACE_END
