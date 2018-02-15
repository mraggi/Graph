#include "AllConvex.hpp"

Box FConvex::BoundingBox() const { return Box(UpLeft(), DownRight()); }

Circle FConvex::BoundingCircle() const { return Circle(Position(), Radius()); }

bool FConvex::Intersects(const Point& other, Point& overlap) const
{
	if (!Intersects(other))
		return false;

	real angle = (other - Position()).Angle();
	overlap = FarthestPointAtAngle(angle) - other;

	return true;
}
