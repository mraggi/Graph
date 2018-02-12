#pragma once

#include "Point.hpp"

const real tolerance = 0.00000001;

class FConvex;
class CPoint;
class Line;
class Ray;
class Segment;
class Circle;
class Box;
class Polygon;

enum shape
{
	shape_Point = 0,
	shape_Line,
	shape_Ray,
	shape_Segment,
	shape_Circle,
	shape_Box,
	shape_Polygon
};

class Convex
{
protected:
	Point m_pPosition; // This is ALWAYS the center of mass, and the ORIGIN of
					   // the coordinate system.

public:
	explicit Convex(const Point& p = Point(0, 0)) : m_pPosition(p) {}
	Convex() {}
	virtual ~Convex() = default;

	virtual shape Type() const = 0;

	// Center of mass in inherited classes
	Point Position() const { return m_pPosition; }
	void  SetPosition(Point newpos) { m_pPosition = newpos; }

	void		 Translate(const Point& T) { m_pPosition += T; }
	virtual void Rotate(real angle) = 0;

	// Scale equally x and y
	virtual void Scale(real amount)				   = 0;
	virtual void Scale(real Xamount, real Yamount) = 0;

	virtual bool Intersects(const Convex& other) const		   = 0;
	virtual bool Intersects(const Convex& other, Point&) const = 0;

	virtual bool Intersects(const Point& other) const				  = 0;
	virtual bool Intersects(const Point& other, Point& overlap) const = 0;

	virtual bool Intersects(const CPoint& other);
	virtual bool Intersects(const CPoint& other, Point& overlap);

	virtual bool Intersects(const Line& other) const									 = 0;
	virtual bool Intersects(const Line& other, Point& intersection) const				 = 0;
	virtual bool Intersects(const Line& other, Segment& intersection) const				 = 0;
	virtual bool Intersects(const Line& other, Point& intersection, Point& normal) const = 0;

	virtual bool Intersects(const Ray& other) const;
	virtual bool Intersects(const Ray& other, Point& intersection) const;
	virtual bool Intersects(const Ray& other, Segment& intersection) const;
	virtual bool Intersects(const Ray& other, Point& intersection, Point& normal) const;

	virtual bool Intersects(const Segment& other) const;
	virtual bool Intersects(const Segment& other, Point& intersection) const;
	virtual bool Intersects(const Segment& other, Segment& intersection) const;
	virtual bool Intersects(const Segment& other, Point& intersection, Point& normal) const;

	virtual bool Intersects(const Circle& other) const				   = 0;
	virtual bool Intersects(const Circle& other, Point& overlap) const = 0;

	virtual bool Intersects(const Box& other) const					= 0;
	virtual bool Intersects(const Box& other, Point& overlap) const = 0;

	virtual bool Intersects(const Polygon& other) const					= 0;
	virtual bool Intersects(const Polygon& other, Point& overlap) const = 0;

	virtual Point ClosestPoint(const Point& point) const = 0;
};
