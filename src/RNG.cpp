#include "noisy/RNG.h"

#include <ctime>
#include <cstdlib>
#include <stdint.h>

RNG::RNG(int seed)
{
    setSeed(seed);
}

RNG::RNG()
{
    setSeed((int)time(0));
}

RNG::~RNG()
{
}

void RNG::setSeed(int seed)
{
    m_lastValue = seed;
}

unsigned int RNG::getNextValue()
{
    const unsigned int a = 1103515245;
    const unsigned int c = 12345;
    m_lastValue = (a * m_lastValue + c) & MY_RAND_MAX;
    return m_lastValue;
}

int RNG::getInt(int l, int h)
{
    return (getNextValue() % (h-l)) + l;
}
float RNG::getFloat(float l, float h)
{
    return ((float(getNextValue()) / float(MY_RAND_MAX)) * (h-l)) + l;
}
float RNG::getDouble(float l, float h)
{
    return ((float(getNextValue()) / float(MY_RAND_MAX)) * (h-l)) + l;
}
bool RNG::coinFlip()
{
    return (getNextValue() & COINFLIP_MASK) == 0;
}