#pragma once

#include "Convex.hpp"

// Finite Convex class.
class FConvex : public Convex
{
public:
	explicit FConvex(const Point& p = Point(0, 0)) : Convex(p) {}
	virtual ~FConvex() = default;

	virtual real MaxX() const = 0;
	virtual real MinX() const = 0;
	virtual real MaxY() const = 0;
	virtual real MinY() const = 0;

	virtual real Width() const { return MaxX() - MinX(); }
	virtual real Height() const { return MaxY() - MinY(); }

	Point UpLeft() const { return Point(MinX(), MinY()); }
	Point UpRight() const { return Point(MaxX(), MinY()); }
	Point DownLeft() const { return Point(MinX(), MaxY()); }
	Point DownRight() const { return Point(MaxX(), MaxY()); }

	virtual real Area() const = 0;
	virtual real Perimeter() const = 0;
	// virtual shape Type() const = 0;

	// Bounding Radius.
	virtual real Radius() const = 0;
	virtual real RadiusSq() const { return Radius() * Radius(); }

	virtual Point FarthestPointAtAngle(real angle) const = 0;

	virtual Box BoundingBox() const;
	virtual Circle BoundingCircle() const;

	virtual bool Intersects(const Point& other, Point& overlap) const;

	using Convex::Intersects;
};
