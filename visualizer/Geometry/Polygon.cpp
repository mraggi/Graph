#include <cassert>

#include "AllConvex.hpp"
#include "Geometry.hpp"

Polygon::Polygon(const VP& SomePoints, bool alreadyconvex)
{
	assert(!SomePoints.empty());

	// 	cout << "Polygon::cctor" << endl;
	if (alreadyconvex)
	{
		m_vPoints = SomePoints;
	}
	else
	{
		m_vPoints = ConvexHull(SomePoints);
	}
	// 	cout << "getting center of mass" << endl;

	m_pPosition = Sum(m_vPoints) / m_vPoints.size();

	// 	cout << "substracting" << endl;
	for (auto& m_vPoint : m_vPoints)
	{
		m_vPoint -= m_pPosition;
	}
	// 	cout << "done" << endl;
}

Polygon::Polygon(const Box& box) : FConvex(box.Position()), m_vPoints(4)
{
	m_vPoints[0] = box.DownRight() - Position();
	m_vPoints[1] = box.UpRight() - Position();
	m_vPoints[2] = box.UpLeft() - Position();
	m_vPoints[3] = box.DownLeft() - Position();
}

Polygon::Polygon(const Segment& segment) : FConvex(segment.Position()), m_vPoints(2)
{
	m_vPoints[0] = segment.Direction();
	m_vPoints[1] = -segment.Direction();
}

Polygon::Polygon(const Point& point) : FConvex(point), m_vPoints(1) { m_vPoints[0] = Point(0, 0); }

Polygon::Polygon(const Circle& circle, unsigned num) : FConvex(circle.Position()), m_vPoints(num)
{
	real angle = -2 * pi / num;

	real sint = sin(angle);
	real cost = cos(angle);

	Point current(-circle.Radius(), 0);

	for (unsigned i = 0; i < num; ++i)
	{
		m_vPoints[i] = current;
		current.Rotate(sint, cost);
	}
}

Polygon::Polygon(const FConvex& fconvex) : FConvex(fconvex), m_vPoints(1)
{
	switch (fconvex.Type())
	{
	case (shape_Circle):
	{
		CreateFromCircle(*(dynamic_cast<const Circle* const>(&fconvex)));
		break;
	}
	case (shape_Box):
	{
		CreateFromBox(*(dynamic_cast<const Box* const>(&fconvex)));
		break;
	}
	case (shape_Segment):
	{
		CreateFromSegment(*(dynamic_cast<const Segment* const>(&fconvex)));
		break;
	}
	case (shape_Point):
	{
		CreateFromPoint(fconvex.Position());
		break;
	}
	default:
		break;
	}
}

void Polygon::CreateFromBox(const Box& box) { *this = Polygon(box); }

void Polygon::CreateFromSegment(const Segment& segment) { *this = Polygon(segment); }

void Polygon::CreateFromPoint(const Point& point) { *this = Polygon(point); }

void Polygon::CreateFromCircle(const Circle& circle, unsigned numpoints)
{
	*this = Polygon(circle, numpoints);
}

real Polygon::Radius() const
{
	real maxsofar = 0;
	for (auto m_vPoint : m_vPoints)
	{
		real length = m_vPoint.Length();
		if (maxsofar < length)
		{
			maxsofar = length;
		}
	}
	return maxsofar;
}

real Polygon::Perimeter() const
{
	real perimeter = (m_vPoints[0] - m_vPoints[m_vPoints.size() - 1]).Length();
	for (unsigned i = 0; i < m_vPoints.size() - 1; ++i)
	{
		perimeter += (m_vPoints[i] - m_vPoints[i + 1]).Length();
	}

	return perimeter;
}

real Polygon::Area() const
{
	cout << "Not yet implemented! Damnit!" << endl;
	return 0;
}

real Polygon::MinY() const
{
	real bestsofar = Position().y + m_vPoints[0].y;

	for (unsigned i = 1; i < m_vPoints.size(); ++i)
	{
		real current = m_vPoints[i].y;
		if (current < bestsofar)
		{
			bestsofar = current;
		}
	}

	return bestsofar + Position().y;
}

real Polygon::MaxY() const
{
	real bestsofar = Position().y + m_vPoints[0].y;

	for (unsigned i = 1; i < m_vPoints.size(); ++i)
	{
		real current = m_vPoints[i].y;
		if (current > bestsofar)
		{
			bestsofar = current;
		}
	}

	return bestsofar + Position().y;
}

real Polygon::MinX() const
{
	real bestsofar = Position().x + m_vPoints[0].x;

	for (unsigned i = 1; i < m_vPoints.size(); ++i)
	{
		real current = m_vPoints[i].x;
		if (current < bestsofar)
		{
			bestsofar = current;
		}
	}

	return bestsofar + Position().x;
}

real Polygon::MaxX() const
{
	real bestsofar = Position().x + m_vPoints[0].x;

	for (unsigned i = 1; i < m_vPoints.size(); ++i)
	{
		real current = m_vPoints[i].x;
		if (current > bestsofar)
		{
			bestsofar = current;
		}
	}

	return bestsofar + Position().x;
}

void Polygon::Scale(real /*Xamount*/, real /*Yamount*/) { cout << "Not implemented" << endl; }

void Polygon::Scale(real amount)
{
	for (auto& m_vPoint : m_vPoints)
	{
		m_vPoint *= amount;
	}
}

void Polygon::Rotate(real angle)
{
	for (auto& m_vPoint : m_vPoints)
	{
		m_vPoint.Rotate(angle);
	}
}

Point Polygon::GetPoint(unsigned index) const
{
	return Position() + m_vPoints[index % NumPoints()];
}

const VP& Polygon::GetPoints() const { return m_vPoints; }

void Polygon::CreateFromPoints(const VP& SomePoints)
{
	m_pPosition = Sum(SomePoints) / SomePoints.size();

	m_vPoints = ConvexHull(SomePoints);

	for (auto& m_vPoint : m_vPoints)
	{
		m_vPoint -= m_pPosition;
	}
}

Point Polygon::FarthestPointAtAngle(real angle) const
{
	// TODO(mraggi): Replace with Binary search implementation
	unsigned n = NumPoints();

	for (unsigned i = 0; i < n; ++i)
	{
		Point p1 = m_vPoints[i];
		Point p2 = m_vPoints[(i + 1) % n];
		real a1 = p1.Angle();
		real a2 = p2.Angle();

		if (isAngleBetweenAngles(angle, a1, a2))
		{
			Point hola;
			Ray ray(Ray(Point(0, 0), angle));
			ray.Intersects(Segment(p1, p2), hola);
			return hola + Position();
		}
	}
	if (NumPoints() > 2)
		cout << "ERROR IN Polygon::FarthestPointAtAngle" << endl;
	return {0, 0};
}

Polygon Polygon::RegularPolygon(unsigned num, real radius, Point pos)
{
	Circle circ(pos, radius);
	return Polygon(circ, num);
}

bool Polygon::Intersects(const Point& other) const
{
	const Polygon& B = *this;
	unsigned n = NumPoints();
	if (n <= 2)
		return false;
	for (unsigned i = 0; i < n; ++i)
	{
		Point X = B[i];
		Point Y = B[(i + 1) % n];

		if (other.IsToTheLeftOfLine(X, Y) || X == Y)
			return false;
	}
	return true;
}

bool Polygon::Intersects(const Line& other) const
{
	const Polygon& B = *this;

	Point p = other.Position();
	Point q = other.SecondPoint();

	bool left = B[0].IsToTheLeftOfLine(p, q);

	for (unsigned i = 1; i < B.NumPoints(); ++i)
	{
		if (B[i].IsToTheLeftOfLine(p, q) != left)
			return true;
	}

	return false;
}

bool Polygon::Intersects(const Line& other, Point& intersection) const
{
	Segment si;
	if (!Intersects(other, si))
		return false;

	intersection = other.ClosestPointToPosition(si);
	return true;
}

bool Polygon::Intersects(const Line& other, Point& intersection, Point& /*normal*/) const
{
	// TODO(mraggi): Normal

	return Intersects(other, intersection);
}

bool Polygon::Intersects(const Line& other, Segment& intersection) const
{
	const Polygon& B = *this;

	Point p = other.Position();
	Point q = other.SecondPoint();

	bool left = B[0].IsToTheLeftOfLine(p, q);

	bool foundFirstIntersection = false;

	for (unsigned i = 0; i < B.NumPoints() + 1; ++i)
	{
		if (B[i].IsToTheLeftOfLine(p, q) != left)
		{
			Point point;
			if (!other.Intersects(Line(B[i - 1], B[i]), point))
			{
				cout << "ERROR IN Intersect(const Line& A, const Polygon& B, Segment* intersection)"
					 << endl;
			}
			if (!foundFirstIntersection)
			{
				intersection.SetOrigin(point);
			}
			else
			{
				intersection.SetEnd(point);
				return true;
			}

			left = !left;
			foundFirstIntersection = true;
		}
	}

	return false;
}

bool Polygon::Intersects(const Circle& other) const
{
	const Polygon& B = *this;

	if (Intersects(other.Position()))
		return true; // If the center of the circle is inside the polygon

	for (unsigned i = 0; i < B.NumPoints(); ++i)
	{
		if (other.Intersects(Segment(B[i], B[i + 1])))
			return true;
	}

	return false;
}

bool Polygon::Intersects(const Circle& other, Point& /*overlap*/) const
{
	// TODO(mraggi): Implement overlap!

	return Intersects(other);
}

bool Polygon::Intersects(const Box& other) const { return Intersects(Polygon(other)); }

bool Polygon::Intersects(const Box& other, Point& overlap) const
{
	return Intersects(Polygon(other), overlap);
}

bool Polygon::Intersects(const Polygon& other) const
{
	if (other.Intersects(Position()))
	{
		// 		cout << "Polygon " << this << " inside " << &other << endl;
		return true; // If I'm inside the other guy
	}

	if (Intersects(other.Position()))
	{
		// 		cout << "Polygon " << &other << " inside " << this << endl;
		return true; // If I'm inside the other guy
	} // If the other guy is inside me

	// 	cout << "baaah" << endl;
	for (unsigned i = 0; i < other.NumPoints() + 1; ++i)
	{
		// 		cout << "i = " << i << endl;
		// 		cout << "other[i] = " << other[i] << endl;
		// 		cout << "other[i+1] = " << other[i+1] << endl;
		Segment seg(other[i], other[i + 1]);

		if (Intersects(seg))
		{
			return true;
		}
	}

	// 	cout << "Returning false!" << endl;

	return false;
}

bool Polygon::Intersects(const Polygon& other, Point& /*overlap*/) const
{
	// TODO(mraggi): Implement overlap!

	return Intersects(other);
}

Point Polygon::ClosestPoint(const Point& point) const
{
	if (Intersects(point))
		return point;

	Point closestSoFar = GetPoint(0);

	for (unsigned i = 0; i < NumPoints(); ++i)
	{
		Segment seg(GetPoint(i), GetPoint(i + 1));
		Point closestNow = seg.ClosestPoint(point);
		if (point.IsCloserToFirstThanSecond(closestNow, closestSoFar))
			closestSoFar = closestNow;
	}

	return closestSoFar;
}
