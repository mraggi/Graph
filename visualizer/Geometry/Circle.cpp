#include "AllConvex.hpp"
// DECLARACION DE Circle

Circle::Circle(const Point& p, real r) : FConvex(p), m_rRadius(r) {}

Point Circle::FarthestPointAtAngle(real angle) const
{
	return Position() + Point::Polar(Radius(), angle);
}

bool Circle::PerpendicularSegmentOfPoint(const Point& point, Segment* perp) const
{
	real lengthsq = RadiusSq() - Position().DistanceSq(point);
	if (lengthsq < 0)
		return false;

	Point vec = (point - Position()).Perp();
	perp->SetDirection(vec.WithLengthSq(lengthsq));
	perp->SetPosition(point);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool Circle::Intersects(const Line& other) const
{
	cout << "Circle vs Line" << endl;

	Point p = Position().ProjectionToLine(other.Position(), other.SecondPoint());
	return Intersects(p);
}

bool Circle::Intersects(const Point& other) const
{
	return (Position().DistanceSq(other) < RadiusSq());
}

bool Circle::Intersects(const Circle& other) const
{
	real distcenterssq = Position().DistanceSq(other.Position());
	real sumradius = Radius() + other.Radius();

	return (distcenterssq < sumradius * sumradius);
}

bool Circle::Intersects(const Circle& other, Point& overlap) const
{
	if (!Intersects(other))
		return false;

	overlap = other.Position() - Position();
	real longitud = -overlap.Length() + other.Radius() + Radius();
	overlap.SetLength(longitud);
	return true;
}

bool Circle::Intersects(const Box& other) const { return other.Intersects(*this); }

bool Circle::Intersects(const Box& other, Point& overlap) const
{
	if (!other.Intersects(*this, overlap))
		return false;

	overlap *= -1;

	return true;
}

bool Circle::Intersects(const Polygon& other) const { return other.Intersects(*this); }

bool Circle::Intersects(const Polygon& other, Point& overlap) const
{
	if (!other.Intersects(*this, overlap))
		return false;

	overlap *= -1;

	return true;
}

bool Circle::Intersects(const Line& other, Point& intersection) const
{
	if (Intersects(other.Position()))
	{
		intersection = other.Position();
		return true;
	}
	Segment si;
	if (!Intersects(other, si))
		return false;

	intersection = si.Origin();
	if (other.Position().IsCloserToFirstThanSecond(si.End(), si.Origin()))
		intersection = si.End();

	return true;
}

bool Circle::Intersects(const Line& other, Segment& intersection) const
{
	Point p1 = other.Position() - Position();
	Point p2 = other.SecondPoint() - Position();

	real dx = p2.x - p1.x;
	real dy = p2.y - p1.y;
	real dr2 = dx * dx + dy * dy;
	real D = p1.x * p2.y - p2.x * p1.y;
	real r2 = RadiusSq();

	real Delta = r2 * dr2 - D * D;

	if (Delta < 0)
		return false;

	real sqDelta = sqrt(Delta);

	real sgn = signof(dy);
	if (sgn == 0)
		sgn = 1;

	real ix1 = (D * dy + sgn * dx * sqDelta) / dr2;
	real iy1 = (-D * dx + abs(dy) * sqDelta) / dr2;

	real ix2 = (D * dy - sgn * dx * sqDelta) / dr2;
	real iy2 = (-D * dx - abs(dy) * sqDelta) / dr2;

	Point I1(ix1, iy1);
	I1 += Position();

	Point I2(ix2, iy2);
	I2 += Position();

	intersection.SetOriginAndEnd(Point(ix1, iy1) + Position(), Point(ix2, iy2) + Position());

	return true;
}

bool Circle::Intersects(const Line& other, Point& intersection, Point& normal) const
{
	if (!Intersects(other, intersection))
		return false;

	Point P = other.Position();
	Point Q = P.ProjectionToLine(Position(), intersection);
	normal = 2 * Q - P - intersection;

	return true;
}

Point Circle::ClosestPoint(const Point& point) const
{
	if (Intersects(point))
		return point;

	return Position() + (point - Position()).WithLength(Radius());
}
