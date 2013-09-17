#include "noisy/Constant.h"

namespace noisy
{

Constant::Constant(float c)
{
    m_value = c;
}

Constant::~Constant()
{
}

void Constant::setValue(float c)
{
    m_value = c;
}

float Constant::getValue(float x, float y)
{
    return m_value;
}

float Constant::getValue(float x, float y, float z)
{
    return m_value;
}

}; // namespace Noise