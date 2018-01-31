#pragma once

#include "Point.hpp"

using VP = std::vector<Point>;

VP GenerateRandomPoints(unsigned n, real mincoord = -1.0, real maxcoord = 1.0);

bool DoSegmentsIntersect(Point a, Point b, Point c, Point d, Point* intersection = NULL);
bool DoSegmentsIntersectStairConvexity(Point a, Point b, Point c, Point d);
bool DoSegmentsIntersectStairConvexityH(Point a, Point b, Point c, Point d);
bool DoesSegmentIntersectLine(Point a, Point b, Point c, Point d, Point* intersection = NULL);
bool DoLinesIntersect(Point a, Point b, Point c, Point d, Point* intersection = NULL);

VP ConvexHull(const VP& SetOfPoints);

// Assuming every point on the set of points is on the LEFT side of the ray
// pointA--->pointB. Returns something that starts at pointA (inclusive) and
// ends at pointB (non inclusive)
VP ConvexHull(const VP& SetOfPoints, Point pointA, Point pointB);

// Should return true if the path intersects the INTERIOR of the convex, false
// otherwise.
bool DoesConvexIntersectSegment(const VP& convex, Point A, Point B);

bool IsPointInsideConvex(Point A, const VP& convex);
