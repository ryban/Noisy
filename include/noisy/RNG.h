#ifndef NOISY_RNG_H
#define NOISY_RNG_H

#include <ctime>
#include <cstdlib>

#define MY_RAND_MAX 0x7fffffff
//#define COINFLIP_MASK (1 << 15)
#define COINFLIP_MASK (1)
class RNG
{
    public:
        RNG(int seed);
        RNG();
        ~RNG();
        void setSeed(int seed);
        int getInt(int l=0, int h=MY_RAND_MAX);
        float getFloat(float l=0.0, float h=1.0);
        float getDouble(float l=0.0, float h=1.0);
        bool coinFlip();
    private:
        int m_lastValue;
        unsigned int getNextValue();


};

#endif