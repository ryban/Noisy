#ifndef NOISY_UTILS_H
#define NOISY_UTILS_H

#include <cmath>

// utility functions for generating noise
// most are not used at the moment, but I found
// them in a lot of noise functions so I thought
// I would put them here, just in case.

namespace noisy
{
namespace utils
{
    float lerp(float x0, float x1, float t);

    float blend_hermite(float x);

    float blend_quintic(float x);

    float bias(float b, float x);

    float gain(float gain, float x);

    float easeCurve(float t);

    float bilerp(float x0y0, float x1y0, float x0y1, float x1y1, float x, float y);

    float trilerp(float v000, float v100, float v010, float v110,
                   float v001, float v101, float v011, float v111,
                   float x, float y, float z);

    float contour(float v);

    float bound(float n, float low, float high, float oldLow=-1.0, float oldHigh = 1.0);

	float clamp(float x, float low, float high);

} // end namespace utils
} // end namespace noisy

#endif