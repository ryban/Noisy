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
        m_type = Keep;
    }

    Select::Select(Module *c, Module *low, Module *high, float t, float f, ControlType type)
    {
        m_control = c;
        m_lowSource = low;
        m_highSource = high;

        m_threshold = t;
        m_falloff = f;
        m_type = type;
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

    void Select::setControlType(ControlType type)
    {
        m_type = type;
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
        {
            float upper = m_threshold + m_falloff;
            float lower = m_threshold - m_falloff;
            float blend = utils::blend_quintic((n-lower)/(upper-lower));
            return utils::lerp(m_lowSource->getValue(x, y),
                               m_highSource->getValue(x, y),
                               blend);
        }
    }
    // gets the value at the position based on the source
    // blend if in falloff area
    float Select::getValue(float x, float y, float z)
    {
        float n;
        switch(m_type)
        {
            case Keep: n = m_control->getValue(x, y, z); break;
            case XY2D: n = m_control->getValue(x, y);    break;
            case XZ2D: n = m_control->getValue(x, z);    break;
            default:   n = m_control->getValue(x, y, z); break; // default, Keep
        }
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