#include "noisy/RidgedMulti.h"
#include "noisy/Utils.h"
#include <cmath>

// WHY IS NULL NOT DEFINED?!?
#ifndef NULL
#define NULL 0
#endif

namespace noisy
{

RidgedMulti::RidgedMulti(int seed)
{
	m_frequencies = NULL;
	simplex.setSeed(seed);
}

RidgedMulti::RidgedMulti(int seed, int oct, float scale, float lac, float off, float H, float gain)
{
	m_seed = seed;
	m_frequencies = NULL;
	m_gain = gain;
	m_lacunarity = lac;
	m_offset = off;
	m_H = H;
	m_octaves = oct;
	m_scale = scale;
	calculateFrequencies();
	simplex.setSeed(seed);
}


RidgedMulti::~RidgedMulti()
{
	delete [] m_frequencies;
}

void RidgedMulti::setSeed(int s)
{
	m_seed = s;
	simplex.setSeed(seed);
}

void RidgedMulti::setScale(float s)
{
	m_scale = s;
}

void RidgedMulti::setOctaves(int o)
{
	m_octaves = o;
	calculateFrequencies();
}

void RidgedMulti::setGain(float gain)
{
	m_gain = gain;
}

void RidgedMulti::setLacunarity(float l)
{
	m_lacunarity = l;
	calculateFrequencies();
}

void RidgedMulti::setOffset(float o)
{
	m_offset = o;
}

void RidgedMulti::setH(float h)
{
	m_H = h;
	calculateFrequencies();
}

void RidgedMulti::calculateFrequencies()
{
	delete [] m_frequencies;
	m_frequencies = new float[m_octaves];
	for(int i = 0; i < m_octaves; i++)
	{
		m_frequencies[i] = pow(m_lacunarity, -i * m_H);
	}
}

float RidgedMulti::ridge(float n)
{
	n = m_offset - fabs(n);
	return n * n;
}

float RidgedMulti::getValue(float x, float y)
{
	x *= m_scale; y *= m_scale;
	float signal = ridge(simplex->getValue(x, y));
	float sum = signal;
	float weight = 1.0;
	for(int i = 1; weight > 0.001 && i < m_octaves-1; i++)
	{
		x *= m_lacunarity; y *= m_lacunarity;
		weight = signal * m_gain;
		weight = utils::clamp(weight, 0.0, 1.0);
		signal = ridge(simplex->getValue(x, y));
		signal *= weight;
		sum += signal * m_frequencies[i];
	}
	return sum;
}
float RidgedMulti::getValue(float x, float y, float z)
{
	x *= m_scale; y *= m_scale; z *= m_scale;
	float signal = ridge(simplex->getValue(x, y, z));
	float sum = signal;
	float weight = 1.0;
	for(int i = 1; weight > 0.001 && i < m_octaves-1; i++)
	{
		x *= m_lacunarity; y *= m_lacunarity; z *= m_lacunarity;
		weight = signal * m_gain;
		weight = utils::clamp(weight, 0.0, 1.0);
		signal = ridge(simplex->getValue(x, y, z));
		signal *= weight;
		sum += signal * m_frequencies[i];
	}
	return sum;
}

}; // end namespace Noise