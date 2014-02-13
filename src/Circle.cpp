#include "noisy/Circle.h"
#include "noisy/Utils.h"

namespace noisy
{

Circle::Circle()
{
    m_radiusSq = 1.0;
    m_inside = m_outside = 0;
}

Circle::Circle(float radius, pModule inside, pModule outside)
{
    m_radiusSq = radius*radius;
    m_inside = inside;
    m_outside = outside;
    // default threshold is 1/20th of the radius
    m_thresholdSq = m_radiusSq*0.05;
}

Circle::Circle(float radius, pModule inside, pModule outside, float threshold)
{
    m_radiusSq = radius*radius;
    m_inside = inside;
    m_outside = outside;
    m_thresholdSq = threshold*threshold;
}

void Circle::setRadius(float r)
{
    m_radiusSq = r*r;
}

void Circle::setSources(pModule inside, pModule outside)
{
    m_inside = inside;
    m_outside = outside;
}
void Circle::setThreshold(float threshold)
{
    m_thresholdSq = threshold*threshold;
}
float Circle::getValue(float x, float y)
{
    float r2 = x*x + y*y;
    if(r2 > m_radiusSq+m_thresholdSq)
        return m_outside->getValue(x, y);
    else if(r2 < m_radiusSq-m_thresholdSq)
        return m_inside->getValue(x, y);
    else
        return utils::lerp( m_outside->getValue(x, y),
                            m_inside->getValue(x, y),
                            ((m_radiusSq+m_thresholdSq)-r2)/(m_thresholdSq*2));
}

float Circle::getValue(float x, float y, float z)
{
    float r2 = x*x + y*y + z*z;
    if(r2 > m_radiusSq+m_thresholdSq)
        return m_outside->getValue(x, y, z);
    else if(r2 < m_radiusSq-m_thresholdSq)
        return m_inside->getValue(x, y, z);
    else
        return utils::lerp( m_outside->getValue(x, y, z),
                            m_inside->getValue(x, y, z),
                            ((m_radiusSq+m_thresholdSq)-r2)/(m_thresholdSq*2));
}

}; // namespace noisy