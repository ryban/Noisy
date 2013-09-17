#include "noisy/Utils.h"

namespace noisy
{
namespace utils
{
    // linear interpolation
	float lerp(float x0, float x1, float t)
    {
        return x0 + (x1-x0) * t;
    }
    // a blending function
    float blend_hermite(float x)
    {
        return (x*x*(3-2*x));
    }
    // another blending function
    float blend_quintic(float x)
    {
        return x*x*x*(x*(x*6-15)+10);
    }
    // bias a value x towards b
    float bias(float b, float x)
    {
        return pow(x, float(log(b)/log(0.5f)));
    }
    // apply a gain to x
    float gain(float gain, float x)
    {
        if(x < 0.5f)
            return bias(1.f-gain, 2.f*x)/2.f;
        else
            return 1.f - bias(1.f-gain, 2.f-2.f*x)/2.f;
    }
    // a blending function
    float easeCurve(float t)
    {
        return 6 * pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3);
    }
    // bilinear interpolation
    float bilerp(float x0y0, float x1y0, float x0y1, float x1y1, float x, float y)
    {
        float tx = easeCurve(x);
        float ty = easeCurve(y);

        float u = lerp(x0y0, x1y0, tx);
        float v = lerp(x0y1, x1y1, tx);

        return lerp(u, v, ty);
    }
    // trilinear interpolation
    float trilerp(float v000, float v100, float v010, float v110,
                   float v001, float v101, float v011, float v111,
                   float x, float y, float z)
    {
        float tx = x;
        float ty = y;
        float tz = z;

        return (
                v000*(1-tx)*(1-ty)*(1-tz) +
                v100*tx*(1-ty)*(1-tz) +
                v010*(1-tx)*ty*(1-tz) +
                v110*tx*ty*(1-tz) +
                v001*(1-tx)*(1-ty)*tz +
                v101*tx*(1-ty)*tz +
                v011*(1-tx)*ty*tz +
                v111*tx*ty*tz
                );
    }
    // blending function
    float contour(float v)
    {
        v = fabs(v);
        if(v >= 1.f)
            return 0.f;
        return 1.f - v;
    }
    // bounds an input value n (assumed to be originally bounded to -1 to 1)
    // to low to high.
    float bound(float low, float high, float n)
    {
        return (((n+1.f)/2.f)*(high-low)) + low;
    }

	float clamp(float x, float low, float high)
	{
		if(x < low)
			return low;
		else if(x > high)
			return high;
		else
			return x;
	}

} // endname space utils
} // end namespace noisy