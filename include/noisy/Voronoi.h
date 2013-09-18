#ifndef NOISY_VORONOI_H
#define NOISY_VORONOI_H

#include "noisy/Module.h"
#include "noisy/Simplex.h"

namespace noisy
{

class Voronoi : public Module
{
private:
    float m_seed;
    float m_scale;
    float m_displacement;

    Simplex simplex;
public:
    Voronoi(int seed);
    Voronoi(int seed, float scale, float displacement);

    virtual float getValue(float x, float y);
    virtual float getValue(float x, float y, float z);
    void setSeed(int s);
    void setScale(float s);
    void setDisplacement(float d);
};

} // namespace noisy

#endif