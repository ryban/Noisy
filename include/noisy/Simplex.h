#ifndef NOISY_SIMPLEX_H
#define NOISY_SIMPLEX_H

#include "noisy/Module.h"
#include "noisy/RNG.h"
namespace noisy
{

class Simplex : public Module
{
	public:
		Simplex(int seed);
		~Simplex();
		virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);

        void setSeed(int s);
	private:
		int m_seed;
		void initPerm();
		int perm[512];
};

}; // end noisy

#endif