#include "AllConvex.hpp"

Line::Line(const Segment& segment)
    : Convex(segment.Origin()), m_rAngle(segment.Angle())
{}

Line::Line(const Ray& ray) : Convex(ray.Position()), m_rAngle(ray.Angle()) {}

Point Line::ClosestPointToPosition(const Segment& seg) const
{
    Point toReturn = Position();

    if (!seg.PointInLineIntersectsMe(Position()))
    {
        if (toReturn.IsCloserToFirstThanSecond(seg.Origin(), seg.End()))
            toReturn = seg.Origin();
        else
            toReturn = seg.End();
    }

    return toReturn;
}

bool Line::Intersects(const Point& other) const
{
    return (other.IsOnLine(Position(), SecondPoint()));
}

bool Line::Intersects(const Line& other) const
{
    if (Angle() == other.Angle())
        return Intersects(other.Position());

    return true;
}

bool Line::Intersects(const Circle& other) const
{
    return other.Intersects(*this);
}

bool Line::Intersects(const Box& other) const
{
    return other.Intersects(*this);
}

bool Line::Intersects(const Polygon& other) const
{
    return other.Intersects(*this);
}

bool Line::Intersects(const Line& other, Point& intersection) const
{
    if (Angle() == other.Angle())
        return Intersects(other.Position());

    Point p1 = Position();
    Point p2 = SecondPoint();

    Point p3 = other.Position();
    Point p4 = other.SecondPoint();

    real x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    real y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

    real d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);

    real pre = (x1*y2 - y1*x2);
    real post = (x3*y4 - y3*x4);

    intersection.x = (pre*(x3 - x4) - (x1 - x2)*post)/d;
    intersection.y = (pre*(y3 - y4) - (y1 - y2)*post)/d;

    return true;
}

bool Line::Intersects(const Point& other, Point& intersection) const
{
    if (!Intersects(other))
        return false;

    intersection = other;

    return true;
}

bool Line::Intersects(const Circle& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Line::Intersects(const Box& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Line::Intersects(const Polygon& other, Point& intersection) const
{
    return other.Intersects(*this, intersection);
}

bool Line::Intersects(const Line& other,
                      Point& intersection,
                      Point& normal) const
{
    if (!Intersects(other, intersection))
        return false;

    Point P = Position();
    Point X = P.ProjectionToLine(other.Position(), intersection);

    normal = P + intersection - 2*X;

    return true;
}

bool Line::Intersects(const Line& other, Segment& intersection) const
{
    Point A;
    if (!Intersects(other, A))
        return false;
    intersection.SetOriginAndEnd(A, A);
    return true;
}

Point Line::ClosestPoint(const Point& point) const
{
    return point.ProjectionToLine(Position(), SecondPoint());
}