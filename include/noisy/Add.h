#ifndef NOISY_ADD_H
#define NOISY_ADD_H

#include "noisy/Module.h"
#include <vector>
#include <memory>

namespace noisy
{

class Add : public Module
{
    public:
        Add();

        void addSource(pModule source);

        virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
    private:
        std::vector<pModule> m_sources;
};

typedef std::shared_ptr<Add> pAdd;

}; // end namespace Noise

#endif