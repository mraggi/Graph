#pragma once
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using real = double;

const double pi = 3.1415926535897932384626433832795028841971694;

inline real RadiansToDegrees(real angle) { return angle*180/pi; }

// Returns an angle that is between -pi and pi.
inline real MakeValidAngle(real theta)
{
    while (theta > pi)
        theta -= 2*pi;
    while (theta < -pi)
        theta += 2*pi;
    return theta;
}

inline bool isAngleBetweenAngles(real a, real b1, real b2)
{
    real c = MakeValidAngle(a - b1 + pi);
    real c2 = MakeValidAngle(b2 - b1 + pi);

    return c2 <= c;
}

template <class T>
int signof(const T& a)
{
    if (a > 0)
        return 1;
    if (a < 0)
        return -1;
    return 0;
}
