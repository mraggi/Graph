#pragma once

#include "Convex.hpp"
#include "FConvex.hpp"

class Segment;

class Circle : public FConvex
{
private:
	real m_rRadius;

public:
	explicit Circle(const Point& p = Point(0, 0), real r = 0);
	void SetRadius(const real r) { m_rRadius = r; }

	real MinX() const { return Position().x - m_rRadius; }
	real MaxX() const { return Position().x + m_rRadius; }
	real MinY() const { return Position().y - m_rRadius; }
	real MaxY() const { return Position().y + m_rRadius; }

	real Width() const { return 2 * m_rRadius; }
	real Height() const { return 2 * m_rRadius; }

	real Radius() const { return m_rRadius; }

	Circle BoundingCircle() const { return (*this); }

	void Scale(real amount) { m_rRadius *= amount; }
	void Scale(real amountx, real amounty) { m_rRadius *= (amountx + amounty) / 2; }

	real Area() const { return pi * m_rRadius * m_rRadius; }
	real Perimeter() const { return 2 * pi * m_rRadius; }

	// Three Random circle functions. Probably better to do something else, but
	// whatever.
	static Circle Random(real maxDistanceToOrigin, real maxRadius);

	static Circle Random(real maxDistanceToOrigin, real minRadius, real maxRadius);

	static Circle
	Random(real minDistanceToOrigin, real maxDistanceToOrigin, real minRadius, real maxRadius);

	void Rotate(real angle) {}

	Point FarthestPointAtAngle(real angle) const;

	// If point inside of circle, sets perp to be a secant perpendicular to
	// origin--point through point.
	bool PerpendicularSegmentOfPoint(const Point& point, Segment* perp = NULL) const;

	shape Type() const { return shape_Circle; }
	static shape ClassType() { return shape_Circle; }

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