#ifndef NOISY_MODULE_H
#define NOISY_MODULE_H

// pure virtual class that all modules derive from

namespace noisy
{

class Module
{
    public:
        Module();
        ~Module();

        virtual float getValue(float x, float y) = 0;
        virtual float getValue(float x, float y, float z) = 0;
};

} // end namespace noisy

#endif