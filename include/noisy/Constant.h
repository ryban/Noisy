#ifndef NOISY_CONST_H
#define NOISY_CONST_H

#include "noisy/Module.h"
#include <memory>

namespace noisy
{

class Constant : public Module
{
public:
    Constant(float c);

    void setValue(float c);
    virtual float getValue(float x, float y);
    virtual float getValue(float x, float y, float z);
private:
    float m_value;
};

typedef std::shared_ptr<Constant> pConstant;

}; // name space Noise
#endif