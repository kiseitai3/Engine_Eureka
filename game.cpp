#include "game.h"

size_t Game::hasher()
{
    size_t max_t = 0;
    max_t--;
    std::mt19937 engine(time(NULL));
    std::normal_distribution<size_t> distribution(0, max_t);
    return normal_distribution(engine);
}
