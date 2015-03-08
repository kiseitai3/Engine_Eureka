#include <random>
#include <ctime>
#include "rand_generators.h"
#include "conversion.h"

//Engine name space macro
//ENGINE_NAMESPACE


size_t hasher()
{
    size_t max_t = 0;
    max_t--;
    std::mt19937 engine(time(NULL));
    std::normal_distribution<double> distribution(0, max_t);
    return static_cast<size_t>(numToInt(distribution(engine)));
}

size_t randNormal(Range limits)
{
    std::mt19937 engine(time(NULL));
    std::normal_distribution<double> distribution(limits.i, limits.f);
    return static_cast<size_t>(numToInt(distribution(engine)));
}

size_t randUniform(Range limits)
{
    std::mt19937 engine(time(NULL));
    std::uniform_int_distribution<size_t> distribution(limits.i, limits.f);
    return distribution(engine);
}

size_t randBinomial(Range limits)
{
    std::mt19937 engine(time(NULL));
    std::binomial_distribution<size_t> distribution(limits.i, limits.f);
    return distribution(engine);
}

size_t GetMaxValueSizeT()
{
    return 0-1;
}

//End of namespace macro
//ENGINE_NAMESPACE_END
