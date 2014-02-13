
#include "noisy/Add.h"

namespace noisy
{

Add::Add()
{
}

void Add::addSource(pModule source)
{
    m_sources.push_back(source);
}

float Add::getValue(float x, float y)
{
    float result = 0.0;
    for(auto it = m_sources.begin(); it < m_sources.end(); it++)
        result += (*it)->getValue(x, y);

    return result;
}

float Add::getValue(float x, float y, float z)
{
    float result = 0.0;
    for(auto it = m_sources.begin(); it < m_sources.end(); it++)
        result += (*it)->getValue(x, y, z);

    return result;
}

}; // end namespace noisy
