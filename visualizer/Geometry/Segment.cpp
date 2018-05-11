#include "AllConvex.hpp"
#include <algorithm>
Segment::Segment(const Point& pointA, const Point& pointB)
    : FConvex((pointA + pointB)/2), m_vDirection((pointB - pointA)/2)
{}

Segment::Segment() : FConvex(Point(0, 0)), m_vDirection(Point(1, 0)) {}

void Segment::SetOrigin(const Point& newOrigin)
{
    SetPosition((End() + newOrigin)/2);
    m_vDirection = Position() - newOrigin;
}

void Segment::SetEnd(const Point& newEnd)
{
    SetPosition((Origin() + newEnd)/2);
    m_vDirection = newEnd - Position();
}

void Segment::SetOriginAndEnd(const Point& newOrigin, const Point& newEnd)
{
    SetPosition((newOrigin + newEnd)/2);
    SetDirection(newEnd - Position());
}

bool Segment::PointInLineIntersectsMe(const Point& point) const
{
    Point V = point - Origin();
    Point U = point - End();

    return V*U < 0;

    /*
    if ( point.x < MinX()-tolerance || point.x > MaxX()+tolerance || point.y <
    MinY()-tolerance || point.y > MaxY()+tolerance) return false;

    return true;*/
}

Point Segment::FarthestPointAtAngle(real angle) const
{
    if (angle == m_vDirection.Angle())
        return End();
    if (angle == -m_vDirection.Angle())
        return Origin();

    return Position();
}

bool Segment::SegmentInLineIntersectsMe(const Point& A,
                                        const Point& B,
                                        Segment* intersection) const
{
    std::vector<Point> p(4);
    p[0] = A;
    p[1] = B;
    p[2] = Origin();
    p[3] = End();
    std::sort(p.begin(), p.end());

    if (PointInLineIntersectsMe((p[1] + p[2])/2))
    {
        if (intersection != nullptr)
            intersection->SetOriginAndEnd(p[1], p[2]);

        return true;
    }

    return false;
}

bool Segment::SegmentInLineIntersectsMe(const Segment& A,
                                        Segment* intersection) const
{
    return SegmentInLineIntersectsMe(A.Origin(), A.End(), intersection);
}

bool Segment::Intersects(const Point& other) const
{
    return CPoint(other).Intersects(*this);
}

bool Segment::Intersects(const Line& other) const
{
    return other.Intersects(*this);
}

bool Segment::Intersects(const Circle& other) const
{
    return other.Intersects(*this);
}

bool Segment::Intersects(const Box& other) const
{
    return other.Intersects(*this);
}

bool Segment::Intersects(const Polygon& other) const
{
    return other.Intersects(*this);
}

bool Segment::Intersects(const Point& other, Point& intersection) const
{
    return CPoint(other).Intersects(*this, intersection);
}

bool Segment::Intersects(const Circle& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Segment::Intersects(const Box& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Segment::Intersects(const Polygon& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Segment::Intersects(const Line& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Segment::Intersects(const Line& other, Segment& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Segment::Intersects(const Line& other,
                         Point& intersection,
                         Point& normal) const
{
    return other.Intersects(*this, intersection, normal);
}

Point Segment::ClosestPoint(const Point& point) const
{
    Point proj = point.ProjectionToLine(Origin(), End());

    if (PointInLineIntersectsMe(proj))
        return proj;

    if (proj.IsCloserToFirstThanSecond(Origin(), End()))
        return Origin();

    return End();
}
