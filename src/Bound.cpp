#include "noisy/Bound.h"
#include "noisy/Utils.h"

namespace noisy
{

Bound::Bound(Module *source, float low, float high, float oldLow=-1.0, float oldHigh=1.0)
{
    m_source = source;
    m_low = low;
    m_high = high;
    m_oldLow = oldLow;
    m_oldHigh = oldHigh;
}

void Bound::setSource(Module *source)
{
    m_source = source;
}
void Bound::setBounds(float low, float high)
{
    m_low = low;
    m_high = high;
}
void Bound::setOldBounds(float low, float high)
{
    m_oldLow = low;
    m_oldHigh = high;
}

float Bound::getValue(float x, float y)
{
    return utils::bound(m_source->getValue(x, y), m_low, m_high, m_oldLow, m_oldHigh);
}
float Bound::getValue(float x, float y, float z)
{
    return utils::bound(m_source->getValue(x, y, z), m_low, m_high, m_oldLow, m_oldHigh);
}

} // namespace noisy