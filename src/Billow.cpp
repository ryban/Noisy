#include "noisy/Billow.h"
#include <cmath>

namespace noisy
{
Billow::Billow(int seed)
: simplex(seed)
{
    m_seed = seed;
    m_octaves = 1;
    m_scale = 1.0;
    m_persistence = 0.5;
    m_gain = 2.0;
}
Billow::Billow(int seed, int oct, float scale, float pers, float gain)
: simplex(seed)
{
    m_seed = seed;
    m_octaves = oct;
    m_scale = scale;
    m_persistence = pers;
    m_gain = gain;
}

void Billow::setSeed(int s)
{
    m_seed = s;
    simplex.setSeed(m_seed);
}
void Billow::setOctaves(int o)
{
    m_octaves = o;
}
void Billow::setScale(float s)
{
    m_scale = s;
}
void Billow::setPersitence(float p)
{
    m_persistence = p;
}
void Billow::setGain(float g)
{
    m_gain = g;
}

float Billow::getValue(float x, float y)
{
    x *= m_scale;
    y *= m_scale;

    float n = 0.0;
    float signal = 0.0;
    float f = 1.0;
    float amp = 1.0;

    for(int i = 0; i < m_octaves; i++)
    {
        signal = simplex.getValue(x*f, y*f);
        signal = 2.0 * fabs(signal) - 1.0;
        n += signal * amp;
        f *= m_gain;
        amp *= m_persistence;
    }
    return n + 0.5f;
}
float Billow::getValue(float x, float y, float z)
{
    x *= m_scale;
    y *= m_scale;
    z *= m_scale;

    float n = 0.0;
    float signal = 0.0;
    float f = 1.0;
    float amp = 1.0;

    for(int i = 0; i < m_octaves; i++)
    {
        signal = simplex.getValue(x*f, y*f, z*f);
        signal = 2.0 * fabs(signal) - 1.0;
        n += signal * amp;
        f *= m_gain;
        amp *= m_persistence;
    }
    return n + 0.5f;
}


} // namespace noisy