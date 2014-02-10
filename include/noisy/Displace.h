#ifndef NOISY_DISPACE_H
#define NOISY_DISPACE_H

#include "noisy/Module.h"

namespace noisy
{

class Displace : public Module
{
private:
    float m_dx, m_dy, m_dz;
    Module *m_source;
public:
    Displace(Module *source, float x, float y, float z);

    virtual float getValue(float x, float y);
    virtual float getValue(float x, float y, float z);
    void setDisplacement(float dx, float dy, float dz);
    void setSource(Module *source);
};

} // namespace noisy

#endif