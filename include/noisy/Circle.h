#ifndef NOISY_CIRCLE_H
#define NOISY_CIRCLE_H

#include "noisy/Module.h"

namespace noisy
{

// Class that selects between two sources whether the input values lie
// within a given radius of the origin or not. Is a circle in 2D, sphere in 3D.
// Does not blend the sources together
class Circle : public Module
{
    public:
        Circle();
        // Sets the thrshold to radius*0.05
        Circle(float radius, Module *inside, Module *outside);
        Circle(float radius, Module *inside, Module *outside, float threshold);

        void setRadius(float r);
        void setSources(Module *inside, Module *outside);
        void setThreshold(float threshold);

        virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
    private:
        // the radius sqaured. sqrt is slow, so we avoid it
        float m_radiusSq;
        float m_thresholdSq;
        Module *m_inside;
        Module *m_outside;
};

}; // end namespace Noise

#endif