#include "game.h"

size_t Game::hasher()
{
    size_t max_t = 0;
    max_t--;
    std::mt19937 engine(time(NULL));
    std::normal_distribution<size_t> distribution(0, max_t);
    return distribution(engine);
}

size_t Game::randNormal(Range limits)
{
    std::mt19937 engine(time(NULL));
    std::normal_distribution<size_t> distribution(limits.i, limits.f);
    return distribution(engine);
}

size_t Game::randUniform(Range limits)
{
    std::mt19937 engine(time(NULL));
    std::uniform_int_distribution<size_t> distribution(limits.i, limits.f);
    return distribution(engine);
}

size_t Game::randBinomial(Range limits)
{
    std::mt19937 engine(time(NULL));
    std::binomial_distribution<size_t> distribution(limits.i, limits.f);
    return distribution(engine);
}
