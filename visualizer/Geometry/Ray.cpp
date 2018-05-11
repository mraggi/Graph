#include "AllConvex.hpp"

Ray::Ray(const Segment& segment)
    : Convex(segment.Origin()), m_rAngle(segment.Angle())
{}

bool Ray::PointInLineIntersectsMe(const Point& point) const
{
    return (point - Position())*(Direction()) < 0;
}

bool Ray::SegmentInLineIntersectsMe(const Point& A,
                                    const Point& B,
                                    Segment* intersection) const
{
    bool Aint = PointInLineIntersectsMe(A);
    bool Bint = PointInLineIntersectsMe(B);

    if (intersection == nullptr)
    {
        return Aint || Bint;
    }

    if (!Aint && !Bint)
        return false;

    if (Aint && Bint)
        intersection->SetOriginAndEnd(A, B);

    if (Aint && !Bint)
        intersection->SetOriginAndEnd(A, Position());

    if (!Aint && Bint)
        intersection->SetOriginAndEnd(Position(), B);

    return true;
}

bool Ray::Intersects(const Point& other) const
{
    return CPoint(other).Intersects(*this);
}

bool Ray::Intersects(const Line& other) const
{
    return other.Intersects(*this);
}

bool Ray::Intersects(const Line& other, Segment& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Ray::Intersects(const Circle& other) const
{
    return other.Intersects(*this);
}

bool Ray::Intersects(const Box& other) const { return other.Intersects(*this); }

bool Ray::Intersects(const Polygon& other) const
{
    return other.Intersects(*this);
}

bool Ray::Intersects(const Point& other, Point& intersection) const
{
    return CPoint(other).Intersects(*this, intersection);
}

bool Ray::Intersects(const Circle& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Ray::Intersects(const Box& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Ray::Intersects(const Polygon& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Ray::Intersects(const Line& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Ray::Intersects(const Line& other,
                     Point& intersection,
                     Point& normal) const
{
    return other.Intersects(*this, intersection, normal);
}

Point Ray::ClosestPoint(const Point& point) const
{
    Point proj = point.ProjectionToLine(Position(), SecondPoint());

    if (PointInLineIntersectsMe(proj))
        return proj;
    return Position();
}
