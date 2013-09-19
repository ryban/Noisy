#include "noisy/Cache.h"

namespace noisy
{
Cache::Cache(Module *source)
{
    m_source = source;
    m_stored_2d = m_stored_3d = false;
}

Cache::~Cache()
{
}
// checks if xy are the same as teh stored values and returns the stored one if they are
// other wise get a new one
float Cache::getValue(float x, float y)
{
    if(m_stored_2d && m_storedX_2d == x && m_storedY_2d == y)
        return m_storedValue_2d;
    else
    {
        m_storedX_2d = x;
        m_storedY_2d = y;
        m_storedValue_2d = m_source->getValue(x, y);
        m_stored_2d = true;
        return m_storedValue_2d;
    }
}
// same as 2d
float Cache::getValue(float x, float y, float z)
{
    if(m_stored_3d && m_storedX_3d == x && m_storedY_3d == y && m_storedZ_3d == z)
        return m_storedValue_3d;
    else
    {
        m_storedX_3d = x;
        m_storedY_3d = y;
        m_storedZ_3d = z;
        m_storedValue_3d = m_source->getValue(x, y, z);
        m_stored_3d = true;
        return m_storedValue_3d;
    }
}

} // namespace noisy