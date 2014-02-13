#ifndef NOISY_BOUND_H
#define NOISY_BOUND_H

#include "noisy/Module.h"
#include <memory>

namespace noisy
{

class Bound : public Module
{
private:
    float m_low;
    float m_high;
    float m_oldLow;
    float m_oldHigh;

    pModule m_source;
public:
    Bound(pModule source, float low, float high, float oldLow=-1.0, float oldHigh=1.0);

    void setSource(pModule source);
    void setBounds(float low, float high);
    void setOldBounds(float low, float high);

    virtual float getValue(float x, float y);
    virtual float getValue(float x, float y, float z);
};

typedef std::shared_ptr<Bound> pBound;

} // namespace noisy
#endif