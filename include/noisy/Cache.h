#ifndef NOISY_CACHEMODULE_H
#define NOISY_CACHEMODULE_H

// this module takes the output for a given source module
// and saves it for a given position
// it only tracks one positon at a time though
// allows for quick access of the same value multiple times in a row

#include "noisy/Module.h"

namespace noisy
{
class Cache : public Module
{
    protected:
        Module *m_source;

        bool m_stored_2d;
        float m_storedX_2d;
        float m_storedY_2d;
        float m_storedValue_2d;

        bool m_stored_3d;
        float m_storedX_3d;
        float m_storedY_3d;
        float m_storedZ_3d;
        float m_storedValue_3d;

    public:
        Cache(Module *source);
        ~Cache();

        virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
};

} // end namespace Noise

#endif