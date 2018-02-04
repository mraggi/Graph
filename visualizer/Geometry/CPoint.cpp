#include "AllConvex.hpp"

bool CPoint::Intersects(const Point& other) const { return Position() == other; }

bool CPoint::Intersects(const Line& other) const { return other.Intersects(Position()); }

bool CPoint::Intersects(const Circle& other) const { return other.Intersects(Position()); }

bool CPoint::Intersects(const Box& other) const { return other.Intersects(Position()); }

bool CPoint::Intersects(const Polygon& other) const { return other.Intersects(Position()); }

bool CPoint::Intersects(const Circle& other, Point& overlap) const
{
	if (!other.Intersects(Position(), overlap))
		return false;
	overlap *= -1;
	return true;
}

bool CPoint::Intersects(const Box& other, Point& overlap) const
{
	if (!other.Intersects(Position(), overlap))
		return false;
	overlap *= -1;
	return true;
}

bool CPoint::Intersects(const Polygon& other, Point& overlap) const
{
	if (!other.Intersects(Position(), overlap))
		return false;
	overlap *= -1;
	return true;
}

bool CPoint::Intersects(const Line& other, Point& intersection) const
{
	return other.Intersects(Position(), intersection);
}

bool CPoint::Intersects(const Line& other, Segment& intersection) const
{
	Point pi;

	if (!other.Intersects(Position(), pi))
		return false;

	intersection.SetOriginAndEnd(pi, pi);

	return true;
}

bool CPoint::Intersects(const Line& other, Point& intersection, Point& normal) const
{
	return other.Intersects(Position());
}

Point CPoint::ClosestPoint(const Point& point) const { return Position(); }
