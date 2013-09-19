#include "noisy/Select.h"
#include "noisy/Utils.h"

namespace noisy
{

    Select::Select()
    {
        m_control = 0;
        m_lowSource = 0;
        m_highSource = 0;

        m_threshold = 0.0;
        m_falloff = 0.0;
    }

    Select::Select(Module *c, Module *low, Module *high, float t, float f)
    {
        m_control = c;
        m_lowSource = low;
        m_highSource = high;

        m_threshold = t;
        m_falloff = f;
    }

    Select::~Select()
    {
    }

    void Select::setControlSource(Module *c)
    {
        m_control = c;
    }

    void Select::setLowSource(Module *low)
    {
        m_lowSource = low;
    }

    void Select::setHighSource(Module *high)
    {
        m_highSource = high;
    }

    void Select::setThreshold(float t)
    {
        m_threshold = t;
    }

    void Select::setFalloff(float f)
    {
        m_falloff = f;
    }
    // gets the value at the position based on the source
    // blend if in falloff area
    float Select::getValue(float x, float y)
    {
        float n = m_control->getValue(x, y);
        if(n > m_threshold + m_falloff)
            return m_highSource->getValue(x, y);
        else if(n < m_threshold - m_falloff)
            return m_lowSource->getValue(x, y);
        else
            return utils::lerp(m_highSource->getValue(x, y), 
                               m_lowSource->getValue(x, y),
                               0.5);
    }
    // gets the value at the position based on the source
    // blend if in falloff area
    float Select::getValue(float x, float y, float z)
    {
        // always use 2d noise for the control
        float n = m_control->getValue(x, z);
        if(n > m_threshold + m_falloff)
            return m_highSource->getValue(x, y, z);
        else if(n < m_threshold - m_falloff)
            return m_lowSource->getValue(x, y, z);
        else
        {
            float upper = m_threshold + m_falloff;
            float lower = m_threshold - m_falloff;
            float blend = utils::blend_quintic((n-lower)/(upper-lower));
            return utils::lerp(m_lowSource->getValue(x, y, z),
                               m_highSource->getValue(x, y, z),
                               blend);
        }
    }

} // end namespace Noise