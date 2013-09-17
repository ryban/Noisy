#ifndef NOISY_CONST_H
#define NOISY_CONST_H

#include "noisy/Module.h"

namespace noisy
{

class Constant : public Module
{
public:
    Constant(float c);
    ~Constant();
    void setValue(float c);
    virtual float getValue(float x, float y);
    virtual float getValue(float x, float y, float z);
private:
    float m_value;
};

}; // name space Noise
#endif