#pragma once

#include "FConvex.hpp"

class CPoint : public FConvex
{
public:
    CPoint() : FConvex(Point(0, 0)) {}
    explicit CPoint(const Point& point) : FConvex(point) {}
    ~CPoint() override = default;
    CPoint(const CPoint& B) = default;
    CPoint(CPoint&& B) = default;
    CPoint& operator=(const CPoint& B) = default;
    CPoint& operator=(CPoint&& B) = default;
    
    Point FarthestPointAtAngle(real angle) const override { return Position(); }

    real Radius() const override { return 0; }
    real Perimeter() const override { return 0; }
    real Area() const override { return 0; }

    real MinY() const override { return Position().y; }
    real MaxY() const override { return Position().y; }
    real MinX() const override { return Position().x; }
    real MaxX() const override { return Position().x; }

    real Width() const override { return 0; }
    real Height() const override { return 0; }

    void Scale(real Xamount, real Yamount) override {}
    void Scale(real amount) override {}

    void Rotate(real angle) override {}

    shape Type() const override { return shape_Point; }
    static shape ClassType() { return shape_Point; }

    //	operator const Point&() const { return m_pPosition; }

    using FConvex::Intersects;

    bool Intersects(const Convex& other) const override
    {
        return other.Intersects(Position());
    }
    bool Intersects(const Convex& other, Point& overlap) const override
    {
        return other.Intersects(Position(), overlap);
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
