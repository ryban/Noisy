#ifndef NOISY_CLAMP_H
#define NOISY_CLAMP_H

#include "noisy/Module.h"
#include <memory>

namespace noisy
{

class Clamp : public Module
{
private:
    float m_low;
    float m_high;

    pModule m_source;
public:
    Clamp(pModule source, float low, float high);

    void setSource(pModule source);
    void setBounds(float low, float high);

    virtual float getValue(float x, float y);
    virtual float getValue(float x, float y, float z);
};

typedef std::shared_ptr<Clamp> pClamp;

} // namespace noisy
#endif