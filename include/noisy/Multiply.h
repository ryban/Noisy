#ifndef NOISY_MULTIPLY_H
#define NOISY_MULTIPLY_H

#include "noisy/Module.h"
#include <vector>
namespace noisy
{

class Multiply : public Module
{
	public:
		Multiply();
		~Multiply();

		void addSource(Module *source);

		virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
	private:
		std::vector<Module *> m_sources;
};

}; // end namespace Noise

#endif