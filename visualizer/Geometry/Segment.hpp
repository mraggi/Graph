#pragma once

#include "FConvex.hpp"
using namespace std;

class Segment : public FConvex
{
protected:
    Point m_vDirection;

public:
    Segment();
    Segment(const Point& pointA, const Point& pointB);
    virtual ~Segment() {}

    Point Direction() const { return m_vDirection; }

    Point Origin() const { return (m_pPosition - m_vDirection); }
    Point End() const { return (m_pPosition + m_vDirection); }

    // Swaps orientation
    void Swap() { m_vDirection *= -1; }

    real Length() const { return m_vDirection.Length() * 2; }
    real LengthSq() const { return m_vDirection.LengthSq() * 4; }

    real MinX() const { return min(Origin().x, End().x); }
    real MaxX() const { return max(Origin().x, End().x); }
    real MinY() const { return min(Origin().y, End().y); }
    real MaxY() const { return max(Origin().y, End().y); }

    // Fixes Ending
    void SetOrigin(const Point& newOrigin);
    void SetEnd(const Point& newEnd);
    void SetOriginAndEnd(const Point& newOrigin, const Point& newEnd);

    void SetDirection(const Point& newDirection) { m_vDirection = newDirection; }

    void Scale(real amount)
    {
        m_pPosition += m_vDirection * (1 - amount) / 2;
        m_vDirection *= amount;
    }

    void Scale(real amount, real u)
    {
        m_pPosition += m_vDirection * (1 - amount) / 2;
        m_vDirection *= amount;
    }

    real Area() const { return 0; }
    real Perimeter() const { return Length(); }
    real Radius() const { return Length() / 2; }

    real Angle() const { return m_vDirection.Angle(); }

    void Rotate(real angle) { m_vDirection.Rotate(angle); }

    shape Type() const { return shape_Segment; }

    bool PointInLineIntersectsMe(const Point& point) const;

    bool
         SegmentInLineIntersectsMe(const Point& A, const Point& B, Segment* intersection = NULL) const;
    bool SegmentInLineIntersectsMe(const Segment& A, Segment* intersection = NULL) const;

    Point FarthestPointAtAngle(real angle) const;

    static shape ClassType() { return shape_Segment; }

    using FConvex::Intersects;

    bool Intersects(const Convex& other) const { return other.Intersects(*this); }
    bool Intersects(const Convex& other, Point& overlap) const
    {
        return other.Intersects(*this, overlap);
    }

    bool Intersects(const Point& other) const;
    bool Intersects(const Point& other, Point& overlap) const;

    bool Intersects(const Line& other) const;
    bool Intersects(const Line& other, Point& intersection) const;
    bool Intersects(const Line& other, Point& intersection, Point& normal) const;
    bool Intersects(const Line& other, Segment& intersection) const;

    bool Intersects(const Circle& other) const;
    bool Intersects(const Circle& other, Point& overlap) const;

    bool Intersects(const Box& other) const;
    bool Intersects(const Box& other, Point& overlap) const;

    bool Intersects(const Polygon& other) const;
    bool Intersects(const Polygon& other, Point& overlap) const;

    Point ClosestPoint(const Point& point) const;
};
