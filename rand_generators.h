#ifndef RAND_GENERATORS_H_INCLUDED
#define RAND_GENERATORS_H_INCLUDED
#include <iostream>
#include "typedefs.h"

//static members
size_t hasher();//Spews out a random number as the key for an element using a bellshape distribution
size_t randUniform(Range limits = Range());//Generates random numbers that form a uniform distribution with a defined range.
size_t randBinomial(Range limits = Range());//Generates random numbers using the binomial distribution and a defined range.
size_t randNormal(Range limits = Range());//Generates random numbers using the bellshape distribution and a defined range.
size_t GetMaxValueSizeT();

#endif // RAND_GENERATORS_H_INCLUDED
