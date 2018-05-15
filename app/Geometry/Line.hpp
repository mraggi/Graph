#pragma once

#include "Convex.hpp"

class Line : public Convex
{
private:
    real m_rAngle{0};

public:
    Line() : Convex(Point(0, 0)) {}
    Line(const Point& pointA, const Point& pointB)
        : Convex(pointA), m_rAngle((pointB - pointA).Angle())
    {
        if (pointA == pointB)
            m_rAngle = 0;
    }
    explicit Line(const Segment& segment);
    explicit Line(const Ray& ray);
    Line(const Point& origin, real angle)
        : Convex(origin), m_rAngle(MakeValidAngle(angle))
    {}

    ~Line() override = default;

    void Scale(real Xamount, real Yamount) override {}
    void Scale(real amount) override {}
    void Rotate(real angle) override { m_rAngle += angle; }
    shape Type() const override { return shape_Line; }
    static shape ClassType() { return shape_Line; }

    Point ClosestPointToPosition(const Segment& seg) const;

    Point Direction() const { return Point::Polar(1, Angle()); }
    Point SecondPoint() const { return Position() + Direction(); }

    real Angle() const { return m_rAngle; }
    void SetAngle(real angle) { m_rAngle = angle; }

    using Convex::Intersects;

    bool Intersects(const Convex& other) const override
    {
        return other.Intersects(*this);
    }
    bool Intersects(const Convex& other, Point& intersection) const override
    {
        return other.Intersects(*this, intersection);
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
