#pragma once

#include "Utility.hpp"

#ifdef USE_SFML
#include <SFML/System.hpp>
#endif

struct Point
{
public:
    real x{0};
    real y{0};

    Point() : x(0), y(0) {}

    Point(real X, real Y) : x(X), y(Y) {}

    void Zero()
    {
        x = 0.0;
        y = 0.0;
    }

    bool isZero() const { return (LengthSq() == 0); }

    inline real LengthSq() const { return x*x + y*y; }
    inline real Length() const { return std::sqrt(LengthSq()); }

    inline real Distance(const Point& vec) const
    {
        return std::sqrt(DistanceSq(vec));
    }

    inline real DistanceSq(const Point& vec) const
    {
        real disX = (vec.x - x);
        real disY = (vec.y - y);
        return disX*disX + disY*disY;
    }

    inline real Angle() const { return atan2(y, x); }
    inline real AngleTo(const Point& vec) const
    {
        return MakeValidAngle(vec.Angle() - Angle());
    }

    inline bool IsCloserToFirstThanSecond(const Point& A, const Point& B) const
    {
        return DistanceSq(A) < DistanceSq(B);
    }

    Point
    VectorWithAngle(real t) const; // std::vector of same length and angle t
    void SetAngle(real t);

    void Rotate(real t);
    Point Rotated(real t) const;

    void Rotate(real SIN,
                real COS); // so that you don't calculate sin and cos again.
    Point
    Rotated(real sint,
            real cost) const; // so that you don't calculate sin and cos again.

    inline void Normalize()
    {
        if (x != 0 || y != 0)
        {
            real length = Length();

            x /= length;
            y /= length;
        }
    }

    inline Point Normalized() const
    {
        Point normalized(x, y);

        normalized.Normalize();

        return normalized;
    }

    inline void Scale(real factor)
    {
        x *= factor;
        y *= factor;
    }

    inline void Scale(real xfactor, real yfactor)
    {
        x *= xfactor;
        y *= yfactor;
    }

    void SetLength(real r);
    void SetLengthSq(real r2);
    void SetPolar(real r, real t);

    Point WithLength(real r) const;
    Point WithLengthSq(real r2) const;

    Point Projection(const Point& H) const;
    Point ProjectionToLine(const Point& A, const Point& B) const;

    bool IsToTheLeftOfLine(const Point& A, const Point& B) const; // strictly
    bool IsOnLine(const Point& A, const Point& B) const;
    bool IsToTheRightOfLine(const Point& A, const Point& B) const; // strictly

    // This returns the projection if it's "positive" (wrt H) and returns 0 if
    // it's negative
    Point ForwardProjection(const Point& H) const;

    void Truncate(real r);
    Point Truncated(real r) const;

    // Returns a point with same length that is rotated pi/2 counter-clockwise
    inline Point Perp() const { return {-y, x}; }

    /* start Operator definitions */

    inline void operator+=(const Point& vec)
    {
        x += vec.x;
        y += vec.y;
    }
    inline void operator-=(const Point& vec)
    {
        x -= vec.x;
        y -= vec.y;
    }
    inline void operator*=(real num)
    {
        x *= num;
        y *= num;
    }
    inline void operator/=(real num)
    {
        x /= num;
        y /= num;
    }
    inline Point operator-() const { return {-x, -y}; }

    bool operator!=(const Point& vec) const;
    bool operator==(const Point& vec) const;

    ///////////////////////////////////////////////////////////////
    ///\brief Convert from Local Coordinates to Global Coordinates
    ///
    /// Assume *this is written in the basis U, V with origin at origin.
    /// This function writes it in the canonical basis (with origin at 0).
    ///
    ///\param origin is the origin
    ///\param U is first basis std::vector
    ///\param V is second basis std::vector
    ///\return The local std::vector
    ///////////////////////////////////////////////////////////////
    Point
    LocalToGlobal(const Point& origin, const Point& U, const Point& V) const;

    ///////////////////////////////////////////////////////////////
    ///\brief Convert from Global Coordinates to Local Coordinates
    ///
    /// Assume *this is written in the basis e_1, e_1. This function
    /// writes it in basis U, V (with origin origin).
    ///
    ///\param origin is the origin
    ///\param U is first basis std::vector
    ///\param V is second basis std::vector
    ///\return The global std::vector
    ///////////////////////////////////////////////////////////////
    Point
    GlobalToLocal(const Point& origin, const Point& U, const Point& V) const;

    // Get the std::vector with length r, angle theta
    static Point Polar(real r, real theta);
    static Point RandomPoint(real maxLength);
    static Point RandomPoint(real minLength, real maxLength);

#ifdef USE_SFML
    // cppcheck-suppress noExplicitConstructor
    Point(const sf::Vector2f& p) : x(p.x), y(p.y) {} // NOLINT
    // cppcheck-suppress noExplicitConstructor
    Point(const sf::Vector2i& p) : x(p.x), y(p.y) {} // NOLINT
    // cppcheck-suppress noExplicitConstructor
    Point(const sf::Vector2u& p) : x(p.x), y(p.y) {} // NOLINT

    operator sf::Vector2f() const { return sf::Vector2f(x, y); } // NOLINT
    operator sf::Vector2i() const { return sf::Vector2i(x, y); } // NOLINT
    operator sf::Vector2u() const { return sf::Vector2u(x, y); } // NOLINT

    Point& operator=(const sf::Vector2f& vec)
    {
        x = vec.x;
        y = vec.y;
        return *this;
    }

    Point& operator=(const sf::Vector2i& vec)
    {
        x = vec.x;
        y = vec.y;
        return *this;
    }
#endif
};

// Add and Substract
inline Point operator+(const Point& A, const Point& B)
{
    return {A.x + B.x, A.y + B.y};
}

inline Point operator-(const Point& A, const Point& B)
{
    return {A.x - B.x, A.y - B.y};
}

// Multiply and divide by scalars on both sides;
inline Point operator*(real num, const Point& vec)
{
    return {num*vec.x, num*vec.y};
}

inline Point operator/(real num, const Point& vec)
{
    return {num/vec.x, num/vec.y};
}

inline Point operator*(const Point& vec, real num)
{
    return {num*vec.x, num*vec.y};
}

inline Point operator/(const Point& vec, real num)
{
    return {vec.x/num, vec.y/num};
}

// dot product
inline real operator*(const Point& A, const Point& B)
{
    return (A.x*B.x + A.y*B.y);
}

inline real distancesq(const Point& A, const Point& B)
{
    real dx = A.x - B.x;
    real dy = A.y - B.y;
    return dx*dx + dy*dy;
}

inline real distance(const Point& A, const Point& B)
{
    return sqrt(distancesq(A, B));
}

std::ostream& operator<<(std::ostream& os, const Point& rhs);

inline Point Sum(const std::vector<Point>& SomePoints)
{
    return std::accumulate(SomePoints.begin(), SomePoints.end(), Point(0, 0));
}

bool operator<(const Point& A, const Point& B);
