#ifndef NOISY_CLAMP_H
#define NOISY_CLAMP_H

#include "noisy/Module.h"

namespace noisy
{

class Clamp : public Module
{
private:
    float m_low;
    float m_high;

    Module *m_source;
public:
    Clamp(Module *source, float low, float high);
    ~Clamp();

    void setSource(Module *source);
    void setBounds(float low, float high);

    virtual float getValue(float x, float y);
    virtual float getValue(float x, float y, float z);
};

} // namespace noisy
#endif