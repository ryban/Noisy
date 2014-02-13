#include "noisy/Multiply.h"

namespace noisy
{
Multiply::Multiply()
{
}

void Multiply::addSource(pModule source)
{
    m_sources.push_back(source);
}

float Multiply::getValue(float x, float y)
{
    float result = 1.0;
    for(auto it = m_sources.begin(); it < m_sources.end(); it++)
        result *= (*it)->getValue(x, y);

    return result;
}

float Multiply::getValue(float x, float y, float z)
{
    float result = 1.0;
    for(auto it = m_sources.begin(); it < m_sources.end(); it++)
        result *= (*it)->getValue(x, y, z);

    return result;
}

}; // end namespace noisy
