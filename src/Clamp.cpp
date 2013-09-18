#include "noisy/Clamp.h"
#include "noisy/Utils.h"

namespace noisy
{

Clamp::Clamp(Module *source, float low, float high, float oldLow=-1.0, float oldHigh=1.0)
{
    m_source = source;
    m_low = low;
    m_high = high;
    m_oldLow = oldLow;
    m_oldHigh = oldHigh;
}

void Clamp::setSource(Module *source)
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