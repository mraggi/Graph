#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "FConvex.hpp"
#include "Geometry.hpp"

// Always in COUNTER-CLOCKWISE ORDER!!!!!

class Polygon : public FConvex
{
private:
    VP    m_vPoints;
    Point GetPoint(unsigned index) const;

public:
    Polygon() : FConvex(Point()), m_vPoints(1) {}
    Polygon(const VP& SomePoints, bool alreadyconvex = false);
    explicit Polygon(const Box& box);
    explicit Polygon(const Segment& segment);
    explicit Polygon(const Point& point);
    explicit Polygon(const Circle& circle,
                     unsigned      num); // creates a regular polygon
    explicit Polygon(const FConvex& fconvex);

    real Radius() const;
    real Perimeter() const;
    real Area() const;
    real MinY() const;
    real MaxY() const;
    real MinX() const;
    real MaxX() const;
    void Scale(real Xamount, real Yamount);
    void Scale(real amount);
    void Rotate(real angle);

    void AddPoint(const Point& p);

    Point operator[](unsigned index) const { return GetPoint(index); }

    unsigned NumPoints() const { return m_vPoints.size(); }

    const VP& GetPoints() const;

    void CreateFromPoints(const VP& SomePoints);

    void CreateFromBox(const Box& box);
    void CreateFromSegment(const Segment& segment);
    void CreateFromPoint(const Point& point);
    void CreateFromCircle(const Circle& circle, unsigned numpoints = 20);

    Point FarthestPointAtAngle(real angle) const;

    shape Type() const { return shape_Polygon; }

    static shape ClassType() { return shape_Polygon; }

    static Polygon RegularPolygon(unsigned num, real radius = 1, Point pos = Point());

    using FConvex::Intersects;

    bool Intersects(const Convex& other) const { return other.Intersects(*this); }
    bool Intersects(const Convex& other, Point& overlap) const
    {
        return other.Intersects(*this, overlap);
    }

    bool Intersects(const Point& other) const;

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

#endif // POLYGON_HPP
