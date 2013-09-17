#ifndef NOISY_ADD_H
#define NOISY_ADD_H

#include "noisy/Module.h"
#include <vector>
namespace noisy
{

class Add : public Module
{
	public:
		Add();
		~Add();

		void addSource(Module *source);

		virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
	private:
		std::vector<Module *> m_sources;
};

}; // end namespace Noise

#endif