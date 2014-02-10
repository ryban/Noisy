#include "noisy/Circle.h"

namespace noisy
{

Circle::Circle()
{
    m_radiusSq = 1.0;
    m_inside = m_outside = 0;
}

Circle::Circle(float radius, Module *inside, Module *outside)
{
    m_radiusSq = radius*radius;
    m_inside = inside;
    m_outside = outside;
}

void Circle::setRadius(float r)
{
    m_radiusSq = r*r;
}

void Circle::setSources(Module *inside, Module *outside)
{
    m_inside = inside;
    m_outside = outside;
}

float Circle::getValue(float x, float y)
{
    float r2 = x*x + y*y;
    if(r2 > m_radiusSq)
        return m_outside->getValue(x, y);
    else
        return m_inside->getValue(x, y);
}

float Circle::getValue(float x, float y, float z)
{
    float r2 = x*x + y*y + z*z;
    if(r2 > m_radiusSq)
        return m_outside->getValue(x, y, z);
    else
        return m_inside->getValue(x, y, z);
}

}; // namespace noisy