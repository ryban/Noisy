#ifndef NOISY_AVERAGE_H
#define NOISY_AVERAGE_H

#include "noisy/Module.h"
#include <vector>

namespace noisy
{
class Average : public Module
{
	public:
		Average();
		~Average();

		void addSource(Module *source);

		virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
	private:
		std::vector<Module *> m_sources;
};

} // namespace noisy

#endif