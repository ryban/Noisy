#ifndef NOISY_PERLIN_H
#define NOISY_PERLIN_H

#include "noisy/Module.h"
#include "noisy/Simplex.h"

// the basic Fractal Browning Motion noise module

namespace noisy
{

class FBM : public Module
{
    protected:
        Simplex simplex;

        int m_seed;
        int m_octaves;
        float m_scale;
        float m_persistence;
        float m_gain;

        // used to automatically bound the end result to [-1.0, 1.0]
        float m_maxVal;
        bool m_autoBound;

        void calcMaxValue();
    public:
        FBM(int s);
        FBM(int seed, int oct, float scale, float pers, float gain, bool autoBound=true);

        virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
        void setSeed(int s);
        void setOctaves(int o);
        void setScale(float s);
        void setPersitence(float p);
        void setGain(float g);
        void setAutoBound(bool b);
};

} // end namespace Noise

#endif