#pragma once

#include "Convex.hpp"
#include "FConvex.hpp"

class Segment;

class Circle : public FConvex
{
private:
    real m_rRadius;

public:
    explicit Circle(const Point& p = Point(0, 0), real r = 0);
    ~Circle() override = default;

    void SetRadius(const real r) { m_rRadius = r; }

    real MinX() const override { return Position().x - m_rRadius; }
    real MaxX() const override { return Position().x + m_rRadius; }
    real MinY() const override { return Position().y - m_rRadius; }
    real MaxY() const override { return Position().y + m_rRadius; }

    real Width() const override { return 2*m_rRadius; }
    real Height() const override { return 2*m_rRadius; }

    real Radius() const override { return m_rRadius; }

    Circle BoundingCircle() const override { return (*this); }

    void Scale(real amount) override { m_rRadius *= amount; }
    void Scale(real amountx, real amounty) override
    {
        m_rRadius *= (amountx + amounty)/2;
    }

    real Area() const override { return pi*m_rRadius*m_rRadius; }
    real Perimeter() const override { return 2*pi*m_rRadius; }

    // Three Random circle functions. Probably better to do something else, but
    // whatever.
    static Circle Random(real maxDistanceToOrigin, real maxRadius);

    static Circle
    Random(real maxDistanceToOrigin, real minRadius, real maxRadius);

    static Circle Random(real minDistanceToOrigin,
                         real maxDistanceToOrigin,
                         real minRadius,
                         real maxRadius);

    void Rotate(real angle) override {}

    Point FarthestPointAtAngle(real angle) const override;

    // If point inside of circle, sets perp to be a secant perpendicular to
    // origin--point through point.
    bool PerpendicularSegmentOfPoint(const Point& point,
                                     Segment* perp = nullptr) const;

    shape Type() const override { return shape_Circle; }
    static shape ClassType() { return shape_Circle; }

    using FConvex::Intersects;

    bool Intersects(const Convex& other) const override
    {
        return other.Intersects(*this);
    }
    bool Intersects(const Convex& other, Point& overlap) const override
    {
        return other.Intersects(*this, overlap);
    }

    bool Intersects(const Point& other) const override;

    bool Intersects(const Line& other) const override;
    bool Intersects(const Line& other, Point& intersection) const override;
    bool Intersects(const Line& other,
                    Point& intersection,
                    Point& normal) const override;
    bool Intersects(const Line& other, Segment& intersection) const override;

    bool Intersects(const Circle& other) const override;
    bool Intersects(const Circle& other, Point& overlap) const override;

    bool Intersects(const Box& other) const override;
    bool Intersects(const Box& other, Point& overlap) const override;

    bool Intersects(const Polygon& other) const override;
    bool Intersects(const Polygon& other, Point& overlap) const override;

    Point ClosestPoint(const Point& point) const override;
};