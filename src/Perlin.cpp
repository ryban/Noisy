#include "noisy/Perlin.h"
#include "noisy/Utils.h"

#include <cmath>

namespace noisy
{
Perlin::Perlin(int seed)
{
    m_seed = seed;
    m_octaves = 1;
    m_scale = 1.0;
    m_persitence = 0.5;
    m_gain = 2.0;

    simplex.setSeed(seed);
}

Perlin::Perlin(int seed, int oct, float scale, float pers, float gain)
{
    m_seed = seed;
    m_octaves = oct;
    m_scale = scale;
    m_persitence = pers;
    m_gain = gain;

    simplex.setSeed(seed);
}

void Perlin::setSeed(int s)
{
    m_seed = s;
    simplex.setSeed(s);
}
void Perlin::setOctaves(int o)
{
    m_octaves = o;
}
void Perlin::setScale(float s)
{
    m_scale = s;
}
void Perlin::setPersitence(float p)
{
    m_persitence = p;
}

void Perlin::setGain(float g)
{
    m_gain = g;
}

float Perlin::getValue(float x, float y)
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
        amp *= m_persitence;
    }
    return n;
}

float Perlin::getValue(float x, float y, float z)
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
        amp *= m_persitence;
    }
    return n;
}

} // end namespace noisy