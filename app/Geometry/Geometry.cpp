#include "Geometry.hpp"
#include "Probability.hpp"
using std::max;
using std::min;

bool DoLinesIntersect(
  Point p1, Point p2, Point p3, Point p4, Point* intersection)
{
    real x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    real y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

    real d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    // If d is zero, they are paralell and so there is no intersection
    if (d == 0)
        return false;

    // Get the x and y
    if (intersection != nullptr)
    {
        real pre = (x1*y2 - y1*x2);
        real post = (x3*y4 - y3*x4);
        real x = (pre*(x3 - x4) - (x1 - x2)*post)/d;
        real y = (pre*(y3 - y4) - (y1 - y2)*post)/d;
        intersection->x = x;
        intersection->y = y;
    }

    return true;
}

bool DoSegmentsIntersect(
  Point p1, Point p2, Point p3, Point p4, Point* intersection)
{
    real x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    real y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

    real d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    // If d is zero, they are paralell and so there is no intersection
    if (d == 0)
        return false;

    real pre = (x1*y2 - y1*x2);
    real post = (x3*y4 - y3*x4);
    real x = (pre*(x3 - x4) - (x1 - x2)*post)/d;
    real y = (pre*(y3 - y4) - (y1 - y2)*post)/d;

    // Get the x and y
    if (intersection != nullptr)
    {
        intersection->x = x;
        intersection->y = y;
    }

    // Check if the x and y coordinates are within both segments
    if (x < min(x1, x2) || x > max(x1, x2) || x < min(x3, x4) ||
        x > max(x3, x4))
        return false;
    if (y < min(y1, y2) || y > max(y1, y2) || y < min(y3, y4) ||
        y > max(y3, y4))
        return false;

    return true;
}

bool DoesSegmentIntersectLine(
  Point p1, Point p2, Point p3, Point p4, Point* intersection)
{
    real x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    real y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

    real d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    // If d is zero, they are paralell and so there is no intersection
    if (d == 0)
        return false;

    real pre = (x1*y2 - y1*x2);
    real post = (x3*y4 - y3*x4);
    real x = (pre*(x3 - x4) - (x1 - x2)*post)/d;
    real y = (pre*(y3 - y4) - (y1 - y2)*post)/d;

    // Get the x and y
    if (intersection != nullptr)
    {
        intersection->x = x;
        intersection->y = y;
    }

    // Check if the x and y coordinates are within the segment
    if (x < min(x1, x2) || x > max(x1, x2))
        return false;
    if (y < min(y1, y2) || y > max(y1, y2))
        return false;

    return true;
}

VP ConvexHull(const VP& SetOfPoints)
{
    // 	cout << "Inside Convex Fucking Hull" << endl;
    VP toReturn;

    if (SetOfPoints.empty())
        return toReturn;

    Point l(SetOfPoints[0]);
    Point h(SetOfPoints[0]);

    // 	cout << "Starting" << endl;

    for (unsigned i = 1; i < SetOfPoints.size(); ++i)
    {
        Point A = SetOfPoints[i];
        if (A.x < l.x)
            l = A;
        else if (A.x > h.x)
            h = A;
    }

    // 	cout << "Found high and low " << h << l << endl;

    VP top;
    VP bottom;

    // 	cout << "baaah" << endl;
    for (auto P : SetOfPoints)
    {
        if (P.IsToTheLeftOfLine(l, h))
            top.push_back(P);
        else if (P.IsToTheRightOfLine(l, h))
            bottom.push_back(P);
    }
    // 	cout << "finished loop... recursing..." << endl;

    // 	cout << "top = " << top << endl;
    // 	cout << "bottom = " << bottom << endl;
    // 	cout << "l = " << l << endl;
    // 	cout << "h = " << h << endl;
    VP convtop = ConvexHull(top, l, h);

    // 	cout << "bottom = " << bottom << endl;
    VP convbot = ConvexHull(bottom, h, l);

    convtop.insert(convtop.end(), convbot.begin(), convbot.end());
    // 	cout << "Finished with convex fucking hull" << endl;

    return convtop;
}

VP ConvexHull(const VP& SetOfPoints, Point A, Point B)
{
    // 	cout << "StartingConvexHull (ver b) with A = " << A << " and B = " << B
    // << endl;
    if (SetOfPoints.empty()) // no more points
    {
        VP finally;
        finally.push_back(A);
        return finally;
    }

    // 	cout << "Not empty!!! Size = " << SetOfPoints.size() << endl;

    real maxdistancesq = 0;
    Point farthest;
    for (auto P : SetOfPoints)
    {
        // 		cout << "i = " << i << endl;
        // 		cout << "P = " << P << endl;
        real dist = P.DistanceSq(P.ProjectionToLine(A, B));
        // 		cout << "dist = " << dist << endl;
        if (dist > maxdistancesq)
        {
            farthest = P;
            maxdistancesq = dist;
        }
        // 		cout << "farthest = " << farthest << endl;
    }
    // 	cout << "Found farthest! = " << farthest << endl;

    VP izquierda;
    VP derecha;
    for (auto P : SetOfPoints)
    {
        bool uno = P.IsToTheLeftOfLine(farthest, A);
        bool dos = P.IsToTheLeftOfLine(B, farthest);

        if (uno && dos)
            continue;

        if (dos)
        {
            izquierda.push_back(P);
        }
        else if (uno)
        {
            derecha.push_back(P);
        }
    }
    // 	cout << "Found that there are " << izquierda.size() << " points on
    // izquierda and " << endl; 	cout << "Found that there are " <<
    // derecha.size() << " points on derecha and " << endl;
    VP convIzq = ConvexHull(izquierda, A, farthest);
    VP convDer = ConvexHull(derecha, farthest, B);

    convIzq.insert(convIzq.end(), convDer.begin(), convDer.end());

    // 	cout << "Well, returning this many points: " << convIzq.size() << endl;

    return convIzq;
}

bool IsPointInsideConvex(Point A, const VP& convex)
{
    // First check if either A or B are inside the convex
    unsigned whichsideA = 0;
    if (A.IsToTheLeftOfLine(convex[0], convex[1]))
    {
        whichsideA = 1;
    }
    else if (A.IsToTheRightOfLine(convex[0], convex[1]))
    {
        whichsideA = 2;
    }

    if (whichsideA == 0)
        return false;

    unsigned n = convex.size();

    for (unsigned i = 1; i < n; ++i)
    {
        Point X = convex[i];
        Point Y = convex[(i + 1)%n];

        if (whichsideA == 2 && A.IsToTheLeftOfLine(X, Y))
        {
            return false;
        }

        if (whichsideA == 1 && A.IsToTheRightOfLine(X, Y))
        {
            return false;
        }

        if (A.IsOnLine(X, Y))
            return false;
    }
    return true;
}

bool DoesConvexIntersectSegment(const VP& convex, Point A, Point B)
{
    // cout << "Does Convex Intersect Segment?? " << endl;
    if (IsPointInsideConvex(A, convex))
    {
        // cout << "Yes, because A is inside the convex" << endl;
        return true;
    }
    if (IsPointInsideConvex(B, convex))
    {
        // cout << "Yes, because B is inside the convex" << endl;
        return true;
    }

    unsigned n = convex.size();
    // cout << "Well, no point is inside the convex!" << endl;
    for (unsigned i = 0; i < n; ++i)
    {
        Point X = convex[i];
        Point Y = convex[(i + 1)%n];
        Point intersection;
        if (DoSegmentsIntersect(A, B, X, Y, &intersection) &&
            intersection != A && intersection != B && intersection != X &&
            intersection != Y)
        {
            // cout << "Yes, because the segment " << A << "---" << B << "
            // intersects the " << i << "th segment of the convex,  which goes
            // from " << X << " to " << Y << " at " << intersection << endl;
            return true;
        }
    }
    // cout << "Nope!" << endl;
    return false;
}

VP GenerateRandomPoints(unsigned n, real mincoord, real maxcoord)
{
    VP hola;
    hola.reserve(n);
    for (unsigned i = 0; i < n; ++i)
    {
        Point a(random_real(mincoord, maxcoord),
                random_real(mincoord, maxcoord));
        hola.push_back(a);
    }
    return hola;
}
