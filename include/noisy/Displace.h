#ifndef NOISY_DISPACE_H
#define NOISY_DISPACE_H

#include "noisy/Module.h"
#include <memory>

namespace noisy
{

class Displace : public Module
{
private:
    float m_dx, m_dy, m_dz;
    pModule m_source;
public:
    Displace(pModule source, float x, float y, float z);

    virtual float getValue(float x, float y);
    virtual float getValue(float x, float y, float z);
    void setDisplacement(float dx, float dy, float dz);
    void setSource(pModule source);
};

typedef std::shared_ptr<Displace> pDisplace;

} // namespace noisy

#endif