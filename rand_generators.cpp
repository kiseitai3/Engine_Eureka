#include <random>
#include <ctime>
#include "rand_generators.h"
#include "conversion.h"

//Engine name space macro
//ENGINE_NAMESPACE


size_t hasher()
{
    size_t val;
    size_t max_t = 0;
    max_t--;
    std::mt19937 engine(time(NULL));
    std::normal_distribution<double> distribution(0, max_t);
    val = static_cast<size_t>(numToInt(distribution(engine)));
    return val;
}

size_t randNormal(Range limits)
{
    size_t val;
    std::mt19937 engine(time(NULL));
    std::normal_distribution<double> distribution(limits.i, limits.f);
    val = static_cast<size_t>(numToInt(distribution(engine)));
    return val;
}

size_t randUniform(Range limits)
{
    size_t val;
    std::mt19937 engine(time(NULL));
    std::uniform_int_distribution<size_t> distribution(limits.i, limits.f);
    val = distribution(engine);
    return val;
}

size_t randBinomial(Range limits)
{
    size_t val;
    std::mt19937 engine(time(NULL));
    std::binomial_distribution<size_t> distribution(limits.i, limits.f);
    val = distribution(engine);
    return val;
}

size_t GetMaxValueSizeT()
{
    return 0-1;
}

void printHello()
{
    std::cout << "Hello World!" << std::endl;
}

//End of namespace macro
//ENGINE_NAMESPACE_END
