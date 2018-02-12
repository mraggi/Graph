#include "Point.hpp"
#include "Probability.hpp"

void Point::Normalize(void)
{
	if (x != 0 || y != 0)
	{
		real length = Length();

		x /= length;
		y /= length;
	}
}

Point Point::Normalized() const
{
	Point normalized(x, y);

	normalized.Normalize();

	return normalized;
}

real Point::Distance(const Point& vec) const
{
	real disX = vec.x - x;
	real disY = vec.y - y;
	return sqrt(disX * disX + disY * disY);
}

real Point::DistanceSq(const Point& vec) const
{
	real disX = (vec.x - x);
	real disY = (vec.y - y);
	return disX * disX + disY * disY;
}

Point Point::VectorWithAngle(real t) const
{
	Point withAngle;
	real  r = Length();
	return Polar(r, t);
}

void Point::SetAngle(real t)
{
	real r = Length();
	x	  = r * cos(t);
	y	  = r * sin(t);
}

Point Point::Rotated(real t) const
{
	real SIN = sin(t);
	real COS = cos(t);

	real xprime = COS * x - SIN * y;
	real yprime = SIN * x + COS * y;
	return Point(xprime, yprime);
}

void Point::Rotate(real t)
{
	real SIN = sin(t);
	real COS = cos(t);

	real xprime = COS * x - SIN * y;

	y = SIN * x + COS * y;
	x = xprime;
}

void Point::Rotate(real SIN, real COS)
{
	real xprime = COS * x - SIN * y;

	y = SIN * x + COS * y;
	x = xprime;
}

Point Point::Rotated(real sint, real cost) const
{
	Point a = *this;
	a.Rotate(sint, cost);
	return a;
}

void Point::SetLength(real r)
{
	Normalize();
	x *= r;
	y *= r;
}

void Point::SetLengthSq(real r2)
{
	real m = sqrt(r2 / LengthSq());
	x *= m;
	y *= m;
}

void Point::SetPolar(real r, real t)
{
	x = 1;
	y = 1;
	SetAngle(t);
	SetLength(r);
}

Point Point::WithLength(real r) const { return r * Normalized(); }

Point Point::WithLengthSq(real r2) const
{
	Point copy = *this;
	copy.SetLengthSq(r2);
	return copy;
}

Point Point::Projection(const Point& H) const
{
	Point T(x, y);
	real  t	= (T * H) / (H * H);
	Point proj = t * H;
	return proj;
}

Point Point::ProjectionToLine(const Point& A, const Point& B) const
{
	Point me = *this;
	
    Point meMinusA = me - A;
	Point BMinusA  = B - A;

    Point temp = meMinusA.Projection(BMinusA);
	
    return temp + A;
}

Point Point::ForwardProjection(const Point& H) const
{
	if (std::abs(AngleTo(H)) > pi / 2)
		return Point(0, 0);
	return Projection(H);
}

bool Point::IsToTheLeftOfLine(const Point& A, const Point& B) const
{
	Point H = B - A;
	Point P = (*this) - A;
	if (H.x * P.y > H.y * P.x)
		return true;
	return false;
}

bool Point::IsOnLine(const Point& A, const Point& B) const
{
	Point H = B - A;
	Point P = (*this) - A;
	return (H.x * P.y == H.y * P.x);
}

bool Point::IsToTheRightOfLine(const Point& A, const Point& B) const
{
	Point H = B - A;
	Point P = (*this) - A;
	if (H.x * P.y < H.y * P.x)
		return true;
	return false;
}

bool Point::operator!=(const Point& vec) const { return ((x != vec.x) || (y != vec.y)); }

bool Point::operator==(const Point& vec) const { return ((x == vec.x) && (y == vec.y)); }

void Point::Truncate(real r)
{
	if (LengthSq() > r * r)
		SetLength(r);
}

Point Point::Truncated(real r) const
{
	if (LengthSq() > r * r)
		return WithLength(r);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Point& rhs)
{
	os << "(" << rhs.x << ", " << rhs.y << ")";

	return os;
}

Point Point::Polar(real r, real theta) { return Point(r * cos(theta), r * sin(theta)); }

Point Point::RandomPoint(real maxLength)
{
	real r	 = random_real(0.0, maxLength);
	real theta = random_real(-pi, pi);
	return Polar(r, theta);
}

Point Point::RandomPoint(real minLength, real maxLength)
{
	real r	 = random_real((minLength), (maxLength));
	real theta = random_real((-pi), (pi));
	return Polar(r, theta);
}

Point Point::LocalToGlobal(const Point& origin, const Point& U, const Point& V) const
{
	return origin + x * U + y * V;
}

Point Point::GlobalToLocal(const Point& origin, const Point& U, const Point& V) const
{
	Point L			  = *this - origin;
	real  determinant = (U.x * V.y - U.y * V.x);

	// check to see if they U and V are linearly dependent
	if (std::abs(determinant) != 0)
		return L.Projection(U);

	real locx = (L.x * V.y - L.y * V.x) / determinant;
	real locy = -(L.x * U.y - L.y * U.x) / determinant;
	return Point(locx, locy);
}

bool operator<(const Point& A, const Point& B)
{
	if (A.x > B.x)
		return true;
	if (A.x < B.x)
		return false;
	return (A.y >= B.y);
}
