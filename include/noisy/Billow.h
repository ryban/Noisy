#ifndef NOISY_BILLOW_H
#define NOISY_BILLOW_H

#include "noisy/Module.h"
#include "noisy/Simplex.h"

namespace noisy
{

class Billow : public Module
{
private:
    int m_seed;
    float m_gain;
    float m_octaves;
    float m_persistence;
    float m_scale;

    Simplex simplex;

    // used to automatically bound the end result to [-1.0, 1.0]
    float m_maxVal;
    bool m_autoBound;

    void calcMaxValue();
public:
    Billow(int s);
    Billow(int seed, int oct, float scale, float pers, float m_gain, bool autoBound=true);

    virtual float getValue(float x, float y);
    virtual float getValue(float x, float y, float z);
    void setSeed(int s);
    void setOctaves(int o);
    void setScale(float s);
    void setPersitence(float p);
    void setGain(float g);
    void setAutoBound(bool b);
};

} // end noisy
#endif