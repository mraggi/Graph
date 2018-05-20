#pragma once

#include "FConvex.hpp"

class Segment : public FConvex
{
protected:
    Point m_vDirection;

public:
    Segment();
    Segment(const Point& pointA, const Point& pointB);
    ~Segment() override = default;
    Segment(const Segment& B) = default;
    Segment(Segment&& B) = default;
    Segment& operator=(const Segment& B) = default;
    Segment& operator=(Segment&& B) = default;

    Point Direction() const { return m_vDirection; }

    Point Origin() const { return (m_pPosition - m_vDirection); }
    Point End() const { return (m_pPosition + m_vDirection); }

    // Swaps orientation
    void Swap() { m_vDirection *= -1; }

    real Length() const { return m_vDirection.Length()*2; }
    real LengthSq() const { return m_vDirection.LengthSq()*4; }

    real MinX() const override { return std::min(Origin().x, End().x); }
    real MaxX() const override { return std::max(Origin().x, End().x); }
    real MinY() const override { return std::min(Origin().y, End().y); }
    real MaxY() const override { return std::max(Origin().y, End().y); }

    // Fixes Ending
    void SetOrigin(const Point& newOrigin);
    void SetEnd(const Point& newEnd);
    void SetOriginAndEnd(const Point& newOrigin, const Point& newEnd);

    void SetDirection(const Point& newDirection)
    {
        m_vDirection = newDirection;
    }

    void Scale(real amount) override
    {
        m_pPosition += m_vDirection*(1.0 - amount)/2.0;
        m_vDirection *= amount;
    }

    void Scale(real amount, real u) override
    {
        m_pPosition += m_vDirection*(1 - amount)/2;
        m_vDirection.Scale(amount, u);
    }

    real Area() const override { return 0; }
    real Perimeter() const override { return Length(); }
    real Radius() const override { return Length()/2; }

    real Angle() const { return m_vDirection.Angle(); }

    void Rotate(real angle) override { m_vDirection.Rotate(angle); }

    shape Type() const override { return shape_Segment; }

    bool PointInLineIntersectsMe(const Point& point) const;

    bool SegmentInLineIntersectsMe(const Point& A,
                                   const Point& B,
                                   Segment* intersection = nullptr) const;
    bool SegmentInLineIntersectsMe(const Segment& A,
                                   Segment* intersection = nullptr) const;

    Point FarthestPointAtAngle(real angle) const override;

    static shape ClassType() { return shape_Segment; }

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
