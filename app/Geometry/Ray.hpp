#pragma once

#include "Convex.hpp"

class Segment;

class Ray : public Convex
{
private:
    real m_rAngle;

public:
    Ray(const Point& pointA, const Point& pointB)
        : Convex(pointA), m_rAngle((pointB - pointA).Angle())
    {}
    explicit Ray(const Segment& segment);
    Ray(const Point& origin, real angle)
        : Convex(origin), m_rAngle(MakeValidAngle(angle))
    {}
    ~Ray() override = default;
    Ray(const Ray& B) = default;
    Ray(Ray&& B) = default;
    Ray& operator=(const Ray& B) = default;
    Ray& operator=(Ray&& B) = default;
    
    void Scale(real Xamount, real Yamount) override {}
    void Scale(real amount) override {}
    void Rotate(real angle) override { m_rAngle += angle; }
    shape Type() const override { return shape_Ray; }

    static shape ClassType() { return shape_Ray; }

    Point Direction() const { return Point::Polar(1, Angle()); }
    Point SecondPoint() const { return Position() + Direction(); }

    real Angle() const { return m_rAngle; }
    void SetAngle(real angle) { m_rAngle = angle; }

    bool SegmentInLineIntersectsMe(const Point& A,
                                   const Point& B,
                                   Segment* intersection = nullptr) const;

    bool PointInLineIntersectsMe(const Point& point) const;

    using Convex::Intersects;

    bool Intersects(const Convex& other) const override
    {
        return other.Intersects(*this);
    }
    bool Intersects(const Convex& other, Point& overlap) const override
    {
        return other.Intersects(*this, overlap);
    }

    bool Intersects(const Point& other) const override;
    bool Intersects(const Point& other, Point& intersection) const override;

    bool Intersects(const Line& other) const override;
    bool Intersects(const Line& other, Point& intersection) const override;
    bool Intersects(const Line& other,
                    Point& intersection,
                    Point& normal) const override;
    bool Intersects(const Line& other, Segment& intersection) const override;

    bool Intersects(const Circle& other) const override;
    bool Intersects(const Circle& other, Point& intersection) const override;

    bool Intersects(const Box& other) const override;
    bool Intersects(const Box& other, Point& intersection) const override;

    bool Intersects(const Polygon& other) const override;
    bool Intersects(const Polygon& other, Point& intersection) const override;

    Point ClosestPoint(const Point& point) const override;
};
