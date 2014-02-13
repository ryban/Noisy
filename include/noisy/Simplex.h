#ifndef NOISY_SIMPLEX_H
#define NOISY_SIMPLEX_H

#include "noisy/Module.h"
#include "noisy/RNG.h"
#include <memory>

namespace noisy
{

class Simplex : public Module
{
    public:
        Simplex(int seed);
        virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);

        void setSeed(int s);
    private:
        int m_seed;
        void initPerm();
        int perm[512];
};

typedef std::shared_ptr<Simplex> pSimplex;

}; // end noisy

#endif