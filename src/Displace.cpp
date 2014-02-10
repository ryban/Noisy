#include "noisy/Displace.h"

namespace noisy
{

Displace::Displace(Module *source, float x, float y, float z)
{
    setSource(source);
    setDisplacement(x, y, z);
}

float Displace::getValue(float x, float y)
{
    return m_source->getValue(x+m_dx, y+m_dy);
}
float Displace::getValue(float x, float y, float z)
{
    return m_source->getValue(x+m_dx, y+m_dy, z+m_dz);
}
void Displace::setDisplacement(float dx, float dy, float dz)
{
    m_dx = dx;
    m_dy = dy;
    m_dz = dz;
}
void Displace::setSource(Module *source)
{
    m_source = source;
}

} // namespace noisy