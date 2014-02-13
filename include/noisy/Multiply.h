#ifndef NOISY_MULTIPLY_H
#define NOISY_MULTIPLY_H

#include "noisy/Module.h"
#include <vector>
#include <memory>

namespace noisy
{

class Multiply : public Module
{
    public:
        Multiply();

        void addSource(pModule source);

        virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
    private:
        std::vector<pModule> m_sources;
};

typedef std::shared_ptr<Multiply> pMultiply;

}; // end namespace Noise

#endif