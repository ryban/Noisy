#include "noisy/Average.h"

namespace noisy
{
Average::Average()
{
}

void Average::addSource(pModule source)
{
    m_sources.push_back(source);
}

float Average::getValue(float x, float y)
{
    float result = 0.0;
    for(auto it = m_sources.begin(); it < m_sources.end(); it++)
        result += (*it)->getValue(x, y);
    result /= m_sources.size();
    return result;
}

float Average::getValue(float x, float y, float z)
{
    float result = 0.0;
    for(auto it = m_sources.begin(); it < m_sources.end(); it++)
        result += (*it)->getValue(x, y, z);
    result /= m_sources.size();
    return result;
}

}; // end namespace Noise
