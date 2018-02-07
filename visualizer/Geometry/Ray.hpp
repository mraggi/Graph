#pragma once

#include "Convex.hpp"

class Segment;

class Ray : public Convex
{
private:
	real m_rAngle;

public:
	Ray(const Point& pointA, const Point& pointB)
		: Convex(pointA), m_rAngle((pointB - pointA).Angle())
	{}
	Ray(const Segment& segment);
	Ray(const Point& origin, real angle) : Convex(origin), m_rAngle(MakeValidAngle(angle)) {}
	~Ray() {}

	void  Scale(real Xamount, real Yamount) {}
	void  Scale(real amount) {}
	void  Rotate(real angle) { m_rAngle += angle; }
	shape Type() const { return shape_Ray; }

	static shape ClassType() { return shape_Ray; }

	Point Direction() const { return Point::Polar(1, Angle()); }
	Point SecondPoint() const { return Position() + Direction(); }

	real Angle() const { return m_rAngle; }
	void SetAngle(real angle) { m_rAngle = angle; }

	bool
	SegmentInLineIntersectsMe(const Point& A, const Point& B, Segment* intersection = NULL) const;

	bool PointInLineIntersectsMe(const Point& point) const;

	using Convex::Intersects;

	bool Intersects(const Convex& other) const { return other.Intersects(*this); }
	bool Intersects(const Convex& other, Point& overlap) const
	{
		return other.Intersects(*this, overlap);
	}

	bool Intersects(const Point& other) const;
	bool Intersects(const Point& other, Point& overlap) const;

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
