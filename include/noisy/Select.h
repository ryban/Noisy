#ifndef NOISY_SELECTMODULE_H
#define NOISY_SELECTMODULE_H

#include "noisy/Module.h"

// a module that selects between two other modules based on the source module
// the threshold is the dividing line between the high and low sources
// the fall off is the area where the teo sources are blended together
// to create a smooth transition between them

namespace noisy
{

class Select : public Module
{
    // The control type only affects 3D noise.
    // When the module gets noise from the control it will either
    // use the xyz coords passed in on the 3D function of the control,
    // the XY on the 2D control function, or the XZ on the 2D control.
    // Default is Keep
    enum ControlType
    {
        Keep, // 3D uses 3D coords for the control input
        XY2D, // 3D uses the 3D XY as the 2D XY control input
        XZ2D  // 3D uses the 3D XZ as the 2D XY control input 
    };

    protected:
        Module *m_control;
        Module *m_lowSource;
        Module *m_highSource;

        float m_threshold;
        float m_falloff;
        ControlType m_type;
    public:
        Select();
        Select(Module *c, Module *low, Module *high, float t, float f, ControlType type=Keep);
        ~Select();

        void setControlSource(Module *c);
        void setLowSource(Module *low);
        void setHighSource(Module *high);
        void setThreshold(float t);
        void setFalloff(float f);
        void setControlType(ControlType t);

        virtual float getValue(float x, float y);
        virtual float getValue(float x, float y, float z);
};

} // end namespace Noise

#endif