#ifndef NOISY_PERLIN_H
#define NOISY_PERLIN_H

#include "noisy/Module.h"
#include "noisy/Simplex.h"

// the basic perlin noise module

namespace noisy
{

class Perlin : public Module
{
    protected:
        Simplex *simplex;

        int m_seed;
        int m_octaves;
        float m_scale;
        float m_persitence;
        float m_lowBound;
        float m_highBound;
    public:
        Perlin(int s);
        Perlin(int seed, int oct, float scale, float pers, float low, float high);
        ~Perlin();

        virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
        void setSeed(int s);
        void setOctaves(int o);
        void setScale(float s);
        void setPersitence(float p);
        void setBounds(float low, float high);
};

} // end namespace Noise

#endif