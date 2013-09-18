#ifndef NOISY_BOUND_H
#define NOISY_BOUND_H

#include "noisy/Module.h"

namespace noisy
{

class Bound : public Module
{
private:
    float m_low;
    float m_high;
    float m_oldLow;
    float oldHigh;

    Module *m_source;
public:
    Bound(Module *source, float low, float high, float oldLow=-1.0, float oldHigh=1.0);

    void setSource(Module *source);
    void setBounds(float low, float high);
    void setOldBounds(float low, float high);

    virtual float getValue(float x, float y);
    virtual float getValue(float x, float y, float z);
};

} // namespace noisy
#endif