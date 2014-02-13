#include "noisy/Clamp.h"
#include "noisy/Utils.h"

namespace noisy
{

Clamp::Clamp(pModule source, float low, float high)
{
    m_source = source;
    m_low = low;
    m_high = high;
}

void Clamp::setSource(pModule source)
{
    m_source = source;
}
void Clamp::setBounds(float low, float high)
{
    m_low = low;
    m_high = high;
}

float Clamp::getValue(float x, float y)
{
    return utils::clamp(m_source->getValue(x, y), m_low, m_high);
}
float Clamp::getValue(float x, float y, float z)
{
    return utils::clamp(m_source->getValue(x, y, z), m_low, m_high);
}

} // namespace noisy