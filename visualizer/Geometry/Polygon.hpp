#pragma once

#include "FConvex.hpp"
#include "Geometry.hpp"

// Always in COUNTER-CLOCKWISE ORDER!!!!!

class Polygon : public FConvex
{
private:
    VP m_vPoints{};
    Point GetPoint(int index) const;

public:
    Polygon() : FConvex(Point()), m_vPoints(1) {}
    Polygon(const VP& SomePoints, bool alreadyconvex = false);
    explicit Polygon(const Box& box);
    explicit Polygon(const Segment& segment);
    explicit Polygon(const Point& point);
    explicit Polygon(const Circle& circle, int num); // regular polygon
    ~Polygon() override = default;

    real Radius() const override;
    real Perimeter() const override;
    real Area() const override;
    real MinY() const override;
    real MaxY() const override;
    real MinX() const override;
    real MaxX() const override;
    void Scale(real Xamount, real Yamount) override;
    void Scale(real amount) override;
    void Rotate(real angle) override;

    void AddPoint(const Point& p);

    Point operator[](int index) const { return GetPoint(index); }

    int NumPoints() const { return m_vPoints.size(); }

    const VP& GetPoints() const;

    void CreateFromPoints(const VP& SomePoints);

    void CreateFromBox(const Box& box);
    void CreateFromSegment(const Segment& segment);
    void CreateFromPoint(const Point& point);
    void CreateFromCircle(const Circle& circle, int numpoints = 20);

    Point FarthestPointAtAngle(real angle) const override;

    shape Type() const override { return shape_Polygon; }

    static shape ClassType() { return shape_Polygon; }

    static Polygon
    RegularPolygon(int num, real radius = 1, Point pos = Point());

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
