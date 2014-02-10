#include "noisy/FBM.h"
#include "noisy/Utils.h"

#include <cmath>

namespace noisy
{
FBM::FBM(int seed)
: simplex(seed)
{
    m_seed = seed;
    m_octaves = 1;
    m_scale = 1.0;
    m_persistence = 0.5;
    m_gain = 2.0;
    m_maxVal = 1.0;
    m_autoBound = true;
}

FBM::FBM(int seed, int oct, float scale, float pers, float gain, bool autoBound)
: simplex(seed)
{
    m_seed = seed;
    m_octaves = oct;
    m_scale = scale;
    m_persistence = pers;
    m_gain = gain;
    m_autoBound = autoBound;
    calcMaxValue();
}

void FBM::setSeed(int s)
{
    m_seed = s;
    simplex.setSeed(s);
}
void FBM::setOctaves(int o)
{
    m_octaves = o;
    calcMaxValue();
}
void FBM::setScale(float s)
{
    m_scale = s;
}
void FBM::setPersitence(float p)
{
    m_persistence = p;
    calcMaxValue();
}

void FBM::setGain(float g)
{
    m_gain = g;
}

void FBM::setAutoBound(bool b)
{
    m_autoBound = b;
}

void FBM::calcMaxValue()
{
    float a = 1.0;
    float n = 0.0;
    for(int i = 0; i < m_octaves; i++)
    {
        n += a;
        a *= m_persistence;
    }
    m_maxVal = n;
}

float FBM::getValue(float x, float y)
{
    x *= m_scale;
    y *= m_scale;

    float n = 0.0;
    float f = 1.0;
    float amp = 1.0;

    for(int i = 0; i < m_octaves; i++)
    {
        n += amp * simplex.getValue(x*f, y*f);
        f *= m_gain;
        amp *= m_persistence;
    }
    if(m_autoBound)
        return utils::bound(n, -1.0, 1.0, -m_maxVal, m_maxVal);
    else
        return n;
}

float FBM::getValue(float x, float y, float z)
{
    x *= m_scale;
    y *= m_scale;
    z *= m_scale;

    float n = 0.0;
    float f = 1.0;
    float amp = 1.0;

    for(int i = 0; i < m_octaves; i++)
    {
        n += amp * simplex.getValue(x*f, y*f, z*f);
        f *= m_gain;
        amp *= m_persistence;
    }
    if(m_autoBound)
        return utils::bound(n, -1.0, 1.0, -m_maxVal, m_maxVal);
    else
        return n;
}

} // end namespace noisy