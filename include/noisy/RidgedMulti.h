#ifndef NOISY_RIDGEMULTI_H
#define NOISY_RIDGEMULTI_H

#include "noisy/Simplex.h"
namespace noisy
{

class RidgedMulti : public Module
{
	public:
		RidgedMulti(int seed);
		RidgedMulti(int seed, int oct, float scale, float lac, float off, float H, float gain);
		~RidgedMulti();

		void setSeed(int s);
		void setGain(float gain);
		void setLacunarity(float l);
		void setOffset(float o);
		void setH(float h);
        void setScale(float s);
		void setOctaves(int o);

		virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
	private:
		int m_seed;
		float m_gain;
		float m_offset;
		float m_H;
		float m_lacunarity;
        int m_octaves;
        float m_scale;
		// pre calulated frequencies (saves some time)
		float *m_frequencies;
		void calculateFrequencies();
		float ridge(float n);

		Simplex *simplex;
};

} // end namespace noisy

#endif
