
#include "noisy/Simplex.h"
#include <cmath>
namespace noisy
{

Simplex::Simplex(int seed)
{
    setSeed(seed);
}

void Simplex::setSeed(int s)
{
    m_seed = s;
    initPerm();
}

// initialize the permuations to generate 
void Simplex::initPerm()
{
    RNG rng;
    rng.setSeed(m_seed);
    // each element from 0-255 inside the permutations, no duplicates
    for(int i = 0; i < 256; i++)
        perm[i] = i;
    // shuffle the array
    for(int i = 255; i > 0; i--)
    {
        int j = rng.getInt(0, i+1); // i+1 since the rng.getInt is not inclusive
        int hold = perm[i];
        perm[i] = perm[j];
        perm[j] = hold;
    }

    // copy the array to the top half
    // uses more memory but makes things easier
    for(int i = 256; i < 512; i++)
        perm[i] = perm[i&255];
}

/*  
    Everything below here sourced from Stefan Gustavson
    http://webstaff.itn.liu.se/~stegu/simplexnoise/SimplexNoise.java
*/
const float F2 = 0.5*(sqrt(3.0)-1.0);
const float G2 = (3.0-sqrt(3.0))/6.0;
const float F3 = 1.0/3.0;
const float G3 = 1.0/6.0;
// These are for 4D noise
//const float F4 = (sqrt(5.0)-1.0)/4.0;
//const float G4 = (5.0-sqrt(5.0))/20.0;

int fastfloor(float x)
{
    return x>0 ? int(x) : int(x-1);
}
float dot(const int g[], float x, float y, float z)
{
    return g[0]*x + g[1]*y + g[2]*z;
}
float dot(const int g[], float x, float y)
{
    return g[0]*x + g[1]*y;
}
float mix(float a, float b, float t)
{
    return (1-t)*a + t*b;
}
float fade(float t)
{
    return t*t*t*(t*(t*6-15)+10);
}

const int grad3[][3] = {{1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0},
                        {1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1},
                        {0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1}};

// 3D
float Simplex::getValue(float x, float y, float z)
{
    
    float n0, n1, n2, n3; // Noise contributions from the four corners
    // Skew the input space to determine which simplex cell we're in
    //float F3 = 1.f/3.f;
    float s = (x+y+z)*F3; // Very nice and simple skew factor for 3D
    int i = fastfloor(x+s);
    int j = fastfloor(y+s);
    int k = fastfloor(z+s);
    //float G3 = 1.f/6.f; // Very nice and simple unskew factor, too
    float t = (i+j+k)*G3; 
    float X0 = i-t; // Unskew the cell origin back to (x,y,z) space
    float Y0 = j-t;
    float Z0 = k-t;
    float x0 = x-X0; // The x,y,z distances from the cell origin
    float y0 = y-Y0;
    float z0 = z-Z0;
    // For the 3D case, the simplex shape is a slightly irregular tetrahedron.
    // Determine which simplex we are in.
    int i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
    int i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords
    if(x0>=y0)
    {
        if(y0>=z0)
        {
            i1=1; j1=0; k1=0; i2=1; j2=1; k2=0;
        } // X Y Z order
        else if(x0>=z0)
        {
            i1=1; j1=0; k1=0; i2=1; j2=0; k2=1;
        } // X Z Y order
        else
        {
            i1=0; j1=0; k1=1; i2=1; j2=0; k2=1;
        } // Z X Y order
    }
    else
    { // x0<y0
        if(y0<z0)
        {
            i1=0; j1=0; k1=1; i2=0; j2=1; k2=1;
        } // Z Y X order
        else if(x0<z0)
        {
            i1=0; j1=1; k1=0; i2=0; j2=1; k2=1;
        } // Y Z X order
        else
        {
            i1=0; j1=1; k1=0; i2=1; j2=1; k2=0;
        } // Y X Z order
    }
    // A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
    // a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
    // a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
    // c = 1/6.    float x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
    float x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
    float y1 = y0 - j1 + G3;
    float z1 = z0 - k1 + G3;
    float x2 = x0 - i2 + 2.f*G3; // Offsets for third corner in (x,y,z) coords
    float y2 = y0 - j2 + 2.f*G3;
    float z2 = z0 - k2 + 2.f*G3;
    float x3 = x0 - 1.f + 3.f*G3; // Offsets for last corner in (x,y,z) coords
    float y3 = y0 - 1.f + 3.f*G3;
    float z3 = z0 - 1.f + 3.f*G3;
    // Work out the hashed gradient indices of the four simplex corners
    int ii = i & 255;
    int jj = j & 255;
    int kk = k & 255;
    int gi0 = perm[ii+perm[jj+perm[kk]]] % 12;
    int gi1 = perm[ii+i1+perm[jj+j1+perm[kk+k1]]] % 12;
    int gi2 = perm[ii+i2+perm[jj+j2+perm[kk+k2]]] % 12;
    int gi3 = perm[ii+1+perm[jj+1+perm[kk+1]]] % 12;
    // Calculate the contribution from the four corners
    float t0 = 0.6f - x0*x0 - y0*y0 - z0*z0;
    if(t0<0) n0 = 0.f;
    else
    {
      t0 *= t0;
      n0 = t0 * t0 * dot(grad3[gi0], x0, y0, z0);
    }
    float t1 = 0.6f - x1*x1 - y1*y1 - z1*z1;
    if(t1<0) n1 = 0.f;
    else
    {
      t1 *= t1;
      n1 = t1 * t1 * dot(grad3[gi1], x1, y1, z1);
    }
    float t2 = 0.6f - x2*x2 - y2*y2 - z2*z2;
    if(t2<0) n2 = 0.f;
    else
    {
      t2 *= t2;
      n2 = t2 * t2 * dot(grad3[gi2], x2, y2, z2);
    }
    float t3 = 0.6f - x3*x3 - y3*y3 - z3*z3;
    if(t3<0) n3 = 0.f;
    else
    {
      t3 *= t3;
      n3 = t3 * t3 * dot(grad3[gi3], x3, y3, z3);
    }
    // Add contributions from each corner to get the final noise value.
    // The result is scaled to stay just inside [-1,1]
    return 32.f*(n0 + n1 + n2 + n3);
}

// 2D
float Simplex::getValue(float x, float y)
{
    float n0, n1, n2; // Noise contributions from the three corners
    // Skew the input space to determine which simplex cell we're in
    //float F2 = 0.5f*(sqrt(3.f)-1.f);
    float s = (x+y)*F2; // Hairy factor for 2D
    int i = fastfloor(x+s);
    int j = fastfloor(y+s);
    //float G2 = (3.f-sqrt(3.f))/6.f;
    float t = (i+j)*G2;
    float X0 = i-t; // Unskew the cell origin back to (x,y) space
    float Y0 = j-t;
    float x0 = x-X0; // The x,y distances from the cell origin
    float y0 = y-Y0;
    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
    if(x0>y0) {i1=1; j1=0;} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    else {i1=0; j1=1;}      // upper triangle, YX order: (0,0)->(0,1)->(1,1)
    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6
    float x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
    float y1 = y0 - j1 + G2;
    float x2 = x0 - 1.f + 2.f * G2; // Offsets for last corner in (x,y) unskewed coords
    float y2 = y0 - 1.f + 2.f * G2;
    // Work out the hashed gradient indices of the three simplex corners
    int ii = i & 255;
    int jj = j & 255;
    int gi0 = perm[ii+perm[jj]] % 12;
    int gi1 = perm[ii+i1+perm[jj+j1]] % 12;
    int gi2 = perm[ii+1+perm[jj+1]] % 12;
    // Calculate the contribution from the three corners
    float t0 = 0.5f - x0*x0-y0*y0;
    if(t0<0) n0 = 0.f;
    else {
      t0 *= t0;
      n0 = t0 * t0 * dot(grad3[gi0], x0, y0);  // (x,y) of grad3 used for 2D gradient
    }
    float t1 = 0.5f - x1*x1-y1*y1;
    if(t1<0) n1 = 0.f;
    else {
      t1 *= t1;
      n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
    }
    float t2 = 0.5f - x2*x2-y2*y2;
    if(t2<0) n2 = 0.f;
    else {
      t2 *= t2;
      n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
    }
    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 70.f * (n0 + n1 + n2);
}

}; // end Noise
