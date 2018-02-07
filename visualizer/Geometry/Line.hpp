#pragma once

#include "Convex.hpp"

class Line : public Convex
{
private:
	real m_rAngle;

public:
	Line() : Convex(Point(0, 0)), m_rAngle(0) {}
	Line(const Point& pointA, const Point& pointB)
		: Convex(pointA), m_rAngle((pointB - pointA).Angle())
	{
		if (pointA == pointB)
			m_rAngle = 0;
	}
	explicit Line(const Segment& segment);
	explicit Line(const Ray& segment);
	Line(const Point& origin, real angle) : Convex(origin), m_rAngle(MakeValidAngle(angle)) {}
	~Line() {}

	void		 Scale(real Xamount, real Yamount) {}
	void		 Scale(real amount) {}
	void		 Rotate(real angle) { m_rAngle += angle; }
	shape		 Type() const { return shape_Line; }
	static shape ClassType() { return shape_Line; }

	Point ClosestPointToPosition(const Segment& seg) const;

	Point Direction() const { return Point::Polar(1, Angle()); }
	Point SecondPoint() const { return Position() + Direction(); }

	real Angle() const { return m_rAngle; }
	void SetAngle(real angle) { m_rAngle = angle; }

	using Convex::Intersects;

	bool Intersects(const Convex& other) const { return other.Intersects(*this); }
	bool Intersects(const Convex& other, Point& intersection) const
	{
		return other.Intersects(*this, intersection);
	}

	bool Intersects(const Point& other) const;
	bool Intersects(const Point& other, Point& intersection) const;

	bool Intersects(const Line& other) const;
	bool Intersects(const Line& other, Point& intersection) const;
	bool Intersects(const Line& other, Point& intersection, Point& normal) const;
	bool Intersects(const Line& other, Segment& intersection) const;

	bool Intersects(const Circle& other) const;
	bool Intersects(const Circle& other, Point& intersection) const;

	bool Intersects(const Box& other) const;
	bool Intersects(const Box& other, Point& intersection) const;

	bool Intersects(const Polygon& other) const;
	bool Intersects(const Polygon& other, Point& intersection) const;

	Point ClosestPoint(const Point& point) const;
};