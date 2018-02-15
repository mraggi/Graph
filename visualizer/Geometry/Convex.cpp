#include "AllConvex.hpp"

bool Convex::Intersects(const Segment& other) const
{
	Point intersection;
	if (!Intersects(Line(other), intersection))
		return false;

	if (!other.PointInLineIntersectsMe(intersection))
		return false;

	return true;
}

bool Convex::Intersects(const Segment& other, Point& intersection) const
{
	if (!Intersects(Line(other), intersection))
		return false;

	if (!other.PointInLineIntersectsMe(intersection))
		return false;

	return true;

	/*
	Segment ConvIntLine;

	if ( !Intersects(Line(other), ConvIntLine) )
		return false;

	Segment si;

	if ( !other.SegmentInLineIntersectsMe(ConvIntLine, &si) )
		return false;

	intersection = other.Origin();

	if (intersection.IsCloserToFirstThanSecond(si.End(), si.Origin()))
		intersection = si.End();

	return true;*/
}

bool Convex::Intersects(const Segment& other, Point& intersection, Point& normal) const
{
	if (!Intersects(Line(other), intersection, normal))
		return false;

	if (!other.PointInLineIntersectsMe(intersection))
		return false;

	return true;
}

bool Convex::Intersects(const Ray& other) const
{
	Point intersection;
	if (!Intersects(Line(other), intersection))
		return false;
	if (!other.PointInLineIntersectsMe(intersection))
		return false;

	return true;
}

bool Convex::Intersects(const Ray& other, Point& intersection) const
{
	return Intersects(Line(other), intersection) && other.PointInLineIntersectsMe(intersection);
}

bool Convex::Intersects(const Ray& other, Point& intersection, Point& normal) const
{
	return Intersects(Line(other), intersection, normal)
	  && other.PointInLineIntersectsMe(intersection);
}

bool Convex::Intersects(const Segment& other, Segment& intersection) const
{
	if (!Intersects(Line(other), intersection))
		return false;

	Point A = intersection.Origin();
	Point B = intersection.End();
	return !!other.SegmentInLineIntersectsMe(
	  intersection.Origin(), intersection.End(), &intersection);
}

bool Convex::Intersects(const Ray& other, Segment& intersection) const
{
	if (!Intersects(Line(other), intersection))
		return false;

	Point A = intersection.Origin();
	Point B = intersection.End();
	return !!other.SegmentInLineIntersectsMe(
	  intersection.Origin(), intersection.End(), &intersection);
}

bool Convex::Intersects(const CPoint& other) { return Intersects(other.Position()); }

bool Convex::Intersects(const CPoint& other, Point& overlap)
{
	return Intersects(other.Position(), overlap);
}