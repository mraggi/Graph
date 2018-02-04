#pragma once

#include "FConvex.hpp"

class CPoint : public FConvex
{
public:
	CPoint() : FConvex(Point(0, 0)) {}
	explicit CPoint(const Point& point) : FConvex(point) {}
	Point		 FarthestPointAtAngle(real angle) const { return Position(); }
	real		 Radius() const { return 0; }
	real		 Perimeter() const { return 0; }
	real		 Area() const { return 0; }
	real		 MinY() const { return Position().y; }
	real		 MaxY() const { return Position().y; }
	real		 MinX() const { return Position().x; }
	real		 MaxX() const { return Position().x; }
	real		 Width() const { return 0; }
	real		 Height() const { return 0; }
	void		 Scale(real Xamount, real Yamount) {}
	void		 Scale(real amount) {}
	void		 Rotate(real angle) {}
	shape		 Type() const { return shape_Point; }
	static shape ClassType() { return shape_Point; }

	//	operator const Point&() const { return m_pPosition; }

	using FConvex::Intersects;

	bool Intersects(const Convex& other) const { return other.Intersects(Position()); }
	bool Intersects(const Convex& other, Point& overlap) const
	{
		return other.Intersects(Position(), overlap);
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
