#ifndef NOISY_SELECTMODULE_H
#define NOISY_SELECTMODULE_H

#include "noisy/Module.h"

// a module that selects between two other modules based on the source module
// the threshold is the dividing line between the high and low sources
// the fall off is the area where the teo sources are blended together
// to create a smooth transition between them

namespace noisy
{

class Select : public Module
{
    protected:
        Module *m_control;
        Module *m_lowSource;
        Module *m_highSource;

        float m_threshold;
        float m_falloff;
    public:
        Select();
        Select(Module *c, Module *low, Module *high, float t, float f);
        ~Select();

        void setControlSource(Module *c);
        void setLowSource(Module *low);
        void setHighSource(Module *high);
        void setThreshold(float t);
        void setFalloff(float f);

        virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
};

} // end namespace Noise

#endif