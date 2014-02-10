#include "noisy/Voronoi.h"
#include <cmath>

namespace noisy
{

Voronoi::Voronoi(int seed)
: simplex(seed)
{
    m_seed = seed;
}
Voronoi::Voronoi(int seed, float scale, float displacement)
: simplex(seed)
{
    m_seed = seed;
    m_scale = scale;
    m_displacement = displacement;
}

void Voronoi::setSeed(int s)
{
    m_seed = s;
    simplex.setSeed(s);
}
void Voronoi::setScale(float s)
{
    m_scale = s;
}
void Voronoi::setDisplacement(float d)
{
    m_displacement = d;
}

float Voronoi::getValue(float x, float y)
{
    x *= m_scale;
    y *= m_scale;

    int X = (x > 0.0? (int)x: (int)x - 1);
    int Y = (y > 0.0? (int)y: (int)y - 1);

    float minDist = 2147483647.0; // 2^31
    float xCandidate = 0;
    float yCandidate = 0;

    // Inside each unit cube, there is a seed point at a random position.  Go
    // through each of the nearby cubes until we find a cube with a seed point
    // that is closest to the specified position.
    for(int curY = Y - 2; curY <= Y + 2; curY++)
    {
        for(int curX = X - 2; curX <= X + 2; curX++)
        {

            // Calculate the position and distance to the seed point inside of
            // this unit cube.
            float n = simplex.getValue(curX, curY);
            float xPos = curX + n;
            float yPos = curY + n;
            float xDist = xPos - x;
            float yDist = yPos - y;
            float dist = xDist * xDist + yDist * yDist;

            if(dist < minDist)
            {
                // This seed point is closer to any others found so far, so record
                // this seed point.
                minDist = dist;
                xCandidate = xPos;
                yCandidate = yPos;
            }
        }
    }
    return m_displacement * simplex.getValue(floor(xCandidate), floor(yCandidate));
}

float Voronoi::getValue(float x, float y, float z)
{
    x *= m_scale;
    y *= m_scale;
    z *= m_scale;

    int X = (x > 0.0? (int)x: (int)x - 1);
    int Y = (y > 0.0? (int)y: (int)y - 1);
    int Z = (z > 0.0? (int)z: (int)z - 1);

    float minDist = 2147483647.0;
    float xCandidate = 0;
    float yCandidate = 0;
    float zCandidate = 0;

    // Inside each unit cube, there is a seed point at a random position.  Go
    // through each of the nearby cubes until we find a cube with a seed point
    // that is closest to the specified position.
    for (int curZ = Z - 2; curZ <= Z + 2; curZ++)
    {
        for (int curY = Y - 2; curY <= Y + 2; curY++)
        {
            for (int curX = X - 2; curX <= X + 2; curX++)
            {

                // Calculate the position and distance to the seed point inside of
                // this unit cube.
                float n = simplex.getValue(curX, curY, curZ);
                float xPos = curX + n;
                float yPos = curY + n;
                float zPos = curZ + n;
                float xDist = xPos - x;
                float yDist = yPos - y;
                float zDist = zPos - z;
                float dist = xDist * xDist + yDist * yDist + zDist * zDist;

                if (dist < minDist)
                {
                    // This seed point is closer to any others found so far, so record
                    // this seed point.
                    minDist = dist;
                    xCandidate = xPos;
                    yCandidate = yPos;
                    zCandidate = zPos;
                }
            }
        }
    }

    return (m_displacement * simplex.getValue(floor(xCandidate),
                                              floor(yCandidate),
                                              floor(zCandidate)));
}

} // namespace noisy