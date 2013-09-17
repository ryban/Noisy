
#include "noisy/Add.h"

namespace noisy
{
Add::Add()
{
}


Add::~Add()
{
	m_sources.clear();
}

void Add::addSource(Module *source)
{
	m_sources.push_back(source);
}

float Add::getValue(float x, float y)
{
	float result = 0.0;
	std::vector<Module *>::iterator it;
	for(it = m_sources.begin(); it < m_sources.end(); it++)
		result += (*it)->getValue(x, y);

	return result;
}

float Add::getValue(float x, float y, float z)
{
	float result = 0.0;
	std::vector<Module *>::iterator it;
	for(it = m_sources.begin(); it < m_sources.end(); it++)
		result += (*it)->getValue(x, y, z);

	return result;
}

}; // end namespace noisy
