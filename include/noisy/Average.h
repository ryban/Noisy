#ifndef NOISY_AVERAGE_H
#define NOISY_AVERAGE_H

#include "noisy/Module.h"
#include <vector>
#include <memory>

namespace noisy
{
class Average : public Module
{
    public:
        Average();

        void addSource(pModule source);

        virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
    private:
        std::vector<pModule> m_sources;
};

typedef std::shared_ptr<Average> pAverage;

} // namespace noisy

#endif