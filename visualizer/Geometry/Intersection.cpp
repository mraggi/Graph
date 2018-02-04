#include "Intersection.hpp"
/*

bool Intersect(const Convex& A, const Convex& B, Polygon* intersection)
{
	shape Atype = A.Type();
	shape Btype = B.Type();

	Point pointinter;
	Segment segmentinter;
	Box boxinter;

	bool toReturn;

	switch (Atype)
	{
		case (shape_Line):
			switch (Btype)
			{
				case (shape_Line):
					toReturn = Intersect(static_cast<const Line&>(A), static_cast<const Line&>(B),
&pointinter); if (intersection != NULL) intersection->CreateFromPoint(pointinter); return toReturn;
					return toReturn;
					break;
				case (shape_Segment):
					toReturn = Intersect(static_cast<const Line&>(A), static_cast<const
Segment&>(B), &pointinter); if (intersection != NULL) intersection->CreateFromPoint(pointinter);
					return toReturn;
					return toReturn;
					break;
				case (shape_Ray):
					toReturn = Intersect(static_cast<const Line&>(A), static_cast<const Ray&>(B),
&pointinter); if(intersection != NULL) intersection->CreateFromPoint(pointinter); return toReturn;
					break;
				case (shape_Circle):
					toReturn = Intersect(static_cast<const Line&>(A), static_cast<const Circle&>(B),
&segmentinter); if(intersection != NULL) intersection->CreateFromSegment(segmentinter); return
toReturn; break; case (shape_Box): toReturn = Intersect(static_cast<const Line&>(A),
static_cast<const Box&>(B), &segmentinter); if(intersection != NULL)
intersection->CreateFromSegment(segmentinter); return toReturn; break; case (shape_Polygon):
					toReturn = Intersect(static_cast<const Line&>(A), static_cast<const
Polygon&>(B), &segmentinter); if(intersection != NULL)
intersection->CreateFromSegment(segmentinter); return toReturn; break;
			};
			return toReturn;
					break;
		case (shape_Segment):
			switch (Btype)
			{
				case (shape_Line):
					toReturn = Intersect(static_cast<const Segment&>(A), static_cast<const
Line&>(B), &pointinter); if(intersection != NULL) intersection->CreateFromPoint(pointinter); return
toReturn; break; case (shape_Segment): toReturn = Intersect(static_cast<const Segment&>(A),
static_cast<const Segment&>(B), &pointinter); if(intersection != NULL)
intersection->CreateFromPoint(pointinter); return toReturn; break; case (shape_Ray): toReturn =
Intersect(static_cast<const Segment&>(A), static_cast<const Ray&>(B), &pointinter); if(intersection
!= NULL) intersection->CreateFromPoint(pointinter); return toReturn; break; case (shape_Circle):
					toReturn = Intersect(static_cast<const Segment&>(A), static_cast<const
Circle&>(B), &segmentinter); if(intersection != NULL) intersection->CreateFromSegment(segmentinter);
					return toReturn;
					break;
				case (shape_Box):
					toReturn = Intersect(static_cast<const Segment&>(A), static_cast<const Box&>(B),
&segmentinter); if(intersection != NULL) intersection->CreateFromSegment(segmentinter); return
toReturn; break; case (shape_Polygon): toReturn = Intersect(static_cast<const Segment&>(A),
static_cast<const Polygon&>(B), &segmentinter); if(intersection != NULL)
intersection->CreateFromSegment(segmentinter); return toReturn; break;
			};
			return toReturn;
					break;
		case (shape_Ray):
			switch (Btype)
			{
				case (shape_Line):
					toReturn = Intersect(static_cast<const Ray&>(A), static_cast<const Line&>(B),
&pointinter); if(intersection != NULL) intersection->CreateFromPoint(pointinter); return toReturn;
					return toReturn;
					return toReturn;
					break;
				case (shape_Segment):
					toReturn = Intersect(static_cast<const Ray&>(A), static_cast<const Segment&>(B),
&pointinter); if(intersection != NULL) intersection->CreateFromPoint(pointinter); return toReturn;
					break;
				case (shape_Ray):
					toReturn = Intersect(static_cast<const Ray&>(A), static_cast<const Ray&>(B),
&pointinter); if(intersection != NULL) intersection->CreateFromPoint(pointinter); return toReturn;
					break;
				case (shape_Circle):
					toReturn = Intersect(static_cast<const Ray&>(A), static_cast<const Circle&>(B),
&segmentinter); if(intersection != NULL) intersection->CreateFromSegment(segmentinter); return
toReturn; break; case (shape_Box): toReturn = Intersect(static_cast<const Ray&>(A),
static_cast<const Box&>(B), &segmentinter); if(intersection != NULL)
intersection->CreateFromSegment(segmentinter); return toReturn; break; case (shape_Polygon):
					toReturn = Intersect(static_cast<const Ray&>(A), static_cast<const Polygon&>(B),
&segmentinter); if(intersection != NULL) intersection->CreateFromSegment(segmentinter); return
toReturn; break;
			};
			break;
		case (shape_Circle):
			switch (Btype)
			{
				case (shape_Line):
					cout << "Intersecting line and circle..." << endl;
					toReturn = Intersect(static_cast<const Circle&>(A), static_cast<const Line&>(B),
&segmentinter); if(intersection != NULL) intersection->CreateFromSegment(segmentinter); return
toReturn; break; case (shape_Segment): toReturn = Intersect(static_cast<const Circle&>(A),
static_cast<const Segment&>(B), &segmentinter); if(intersection != NULL)
intersection->CreateFromSegment(segmentinter); return toReturn; break; case (shape_Ray): toReturn =
Intersect(static_cast<const Circle&>(A), static_cast<const Ray&>(B), &segmentinter); if(intersection
!= NULL) intersection->CreateFromSegment(segmentinter); return toReturn; break; case (shape_Circle):
					toReturn = Intersect(static_cast<const Circle&>(A), static_cast<const
Circle&>(B), &segmentinter); if(intersection != NULL) intersection->CreateFromSegment(segmentinter);
					return toReturn;
					break;
				case (shape_Box):
					toReturn = Intersect(static_cast<const Circle&>(A), static_cast<const Box&>(B));
					return toReturn;
					break;
				case (shape_Polygon):
					toReturn = Intersect(static_cast<const Circle&>(A), static_cast<const
Polygon&>(B)); return toReturn; break;
			};
			break;
		case (shape_Box):
			switch (Btype)
			{
				case (shape_Line):
					toReturn = Intersect(static_cast<const Box&>(A), static_cast<const Line&>(B),
&segmentinter); if(intersection != NULL) intersection->CreateFromSegment(segmentinter); return
toReturn; break; case (shape_Segment): toReturn = Intersect(static_cast<const Box&>(A),
static_cast<const Segment&>(B), &segmentinter); if(intersection != NULL)
intersection->CreateFromSegment(segmentinter); return toReturn; break; case (shape_Ray): toReturn =
Intersect(static_cast<const Box&>(A), static_cast<const Ray&>(B), &segmentinter); if(intersection !=
NULL) intersection->CreateFromSegment(segmentinter); return toReturn; break; case (shape_Circle):
					toReturn = Intersect(static_cast<const Box&>(A), static_cast<const Circle&>(B));
					return toReturn;
					break;
				case (shape_Box):
					toReturn = Intersect(static_cast<const Box&>(A), static_cast<const Box&>(B),
&boxinter); if(intersection != NULL) intersection->CreateFromBox(boxinter); return toReturn; break;
				case (shape_Polygon):
					toReturn = Intersect(static_cast<const Box&>(A), static_cast<const
Polygon&>(B)); return toReturn; break;
			};
			break;
		case (shape_Polygon):
			switch (Btype)
			{
				case (shape_Line):
					toReturn = Intersect(static_cast<const Polygon&>(A), static_cast<const
Line&>(B), &segmentinter); if(intersection != NULL) intersection->CreateFromSegment(segmentinter);
					return toReturn;
					break;
				case (shape_Segment):
					toReturn = Intersect(static_cast<const Polygon&>(A), static_cast<const
Segment&>(B), &segmentinter); if(intersection != NULL)
intersection->CreateFromSegment(segmentinter); return toReturn; break; case (shape_Ray): toReturn =
Intersect(static_cast<const Polygon&>(A), static_cast<const Ray&>(B), &segmentinter);
					if(intersection != NULL) intersection->CreateFromSegment(segmentinter);
					return toReturn;
					break;
				case (shape_Circle):
					toReturn = Intersect(static_cast<const Polygon&>(A), static_cast<const
Circle&>(B)); return toReturn; break; case (shape_Box): toReturn = Intersect(static_cast<const
Polygon&>(A), static_cast<const Box&>(B)); return toReturn; break; case (shape_Polygon): toReturn =
Intersect(static_cast<const Polygon&>(A), static_cast<const Polygon&>(B)); return toReturn; break;
			};
			break;
	};

	cout << "ERROR in bool Intersect(const Convex& A, const Convex& B)" << endl;
	return false;
}

bool Intersect(const Point& A, const Convex& B)
{
	shape Btype = B.Type();
	switch (Btype)
			{
				case (shape_Line):
					return Intersect(A, static_cast<const Line&>(B));
					break;
				case (shape_Segment):
					return Intersect(A, static_cast<const Segment&>(B));
					break;
				case (shape_Ray):
					return Intersect(A, static_cast<const Ray&>(B));
					break;
				case (shape_Circle):
					return Intersect(A, static_cast<const Circle&>(B));
					break;
				case (shape_Box):
					return Intersect(A, static_cast<const Box&>(B));
					break;
				case (shape_Polygon):
					return Intersect(A, static_cast<const Polygon&>(B));
					break;
			};
	cout << "ERROR in bool Intersect(const Point& A, const Convex& B)" << endl;
	return false;
}

/// Intersect for POINTC
bool Intersect(const Point& A, const Point& B)
{
	return (A == B);
}

bool Intersect(const Point& A, const Line& B)
{
	return A.IsOnLine(B.Position(), B.SecondPoint()); //Tolerance?
}

bool Intersect(const Point& A, const Ray& B)
{
	if (Intersect(A,Line(B.Position(), B.SecondPoint())))
		return B.PointInLineIntersectsMe(A);
}

bool Intersect(const Point& A, const Segment& B)
{
	if (A.x > B.MaxX() || A.x < B.MinX() || A.y > B.MaxY() || A.y < B.MinY())
		return false;

	return A.IsOnLine(B.Origin(), B.End());

 }

bool Intersect(const Point& A, const Circle& B)
{
	return (A.DistanceSq(B.Position()) <= B.Radius()*B.Radius());
}

bool Intersect(const Point& A, const Box& B)
{
	return (A.x < B.MaxX() && A.x > B.MinX() && A.y < B.MaxY() && A.y > B.MinY());
}

bool Intersect(const Point& A, const Polygon& B)
{
	nuint n = B.NumPoints();
	if (n <= 2) return false;
	for (nuint i = 0; i < n; ++i)
	{
		Point X = B[i];
		Point Y = B[(i+1)%n];

		if (A.IsToTheLeftOfLine(X,Y) || X == Y)
			return false;
	}
	return true;
 }


//Intersect for Line
bool Intersect(const Line& A, const Line& B, Point* intersection)
{
	if (A.Angle() == B.Angle())
		return Intersect(A.Position(), B);

	if (intersection == NULL)
		return true;

	Point p1 = A.Position();
	Point p2 = A.SecondPoint();

	Point p3 = B.Position();
	Point p4 = B.SecondPoint();

	real x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	real y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	real d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	real pre = (x1*y2 - y1*x2);
   real post = (x3*y4 - y3*x4);

   intersection->x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
   intersection->y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

	return true;
 }

bool Intersect(const Line& A, const Ray& B, Point* intersection)
{
	Point tmp;
	if (intersection == NULL) intersection = &tmp;

	Line Bl(B.Position(), B.Angle());

	if (!Intersect(A,Bl,intersection)) return false;

	if (!B.PointInLineIntersectsMe(*intersection)) return false;

	return true;
}

bool Intersect(const Line& A, const Segment& B, Point* intersection)
{
	Point tmp;
	if (intersection == NULL) intersection = &tmp;

	Line Bl(B.Origin(), B.End());

	if (!Intersect(A, Bl, intersection)) return false;

	if (!B.PointInLineIntersectsMe(*intersection)) return false;

	return true;

}

bool Intersect(const Line& A, const Circle& B, Segment* intersection)
{
	if (intersection == NULL)
	{
		Point p = B.Position().ProjectionToLine(A.Position(), A.SecondPoint());
		return (B.Position().DistanceSq(p) <= B.RadiusSq());
	}

	Point p1 = A.Position() - B.Position();
	Point p2 = A.SecondPoint() - B.Position();

	real dx = p2.x - p1.x;
	real dy = p2.y - p1.y;
	real dr2 = dx*dx+dy*dy;
	real D = p1.x*p2.y - p2.x*p1.y;
	real r2 = B.Radius()*B.Radius();

	real Delta = r2*dr2-D*D;

	if (Delta < 0)
		return false;

	if (intersection == NULL)
		return true;

	real sqDelta = sqrt(Delta);

	real sgn = signof(dy);
	if (sgn == 0) sgn = 1;

	real ix1 = (D*dy+sgn*dx*sqDelta)/dr2;
	real iy1 = (-D*dx+abs(dy)*sqDelta)/dr2;

	real ix2 = (D*dy-sgn*dx*sqDelta)/dr2;
	real iy2 = (-D*dx-abs(dy)*sqDelta)/dr2;

	intersection->SetOriginAndEnd(Point(ix1,iy1)+B.Position(), Point(ix2,iy2)+B.Position());

	return true;
}

bool Intersect(const Line& A, const Box& B, Segment* intersection)
{
	VP p(4, Point());
	if (!Intersect(A, Line(B.UpLeft(), B.DownLeft()), &p[0]))
	{
		real x = A.Position().x;
		if (x > B.MaxX() || x < B.MinX())
			return false;
		if (intersection == NULL)
			return true;
		intersection->SetOriginAndEnd(Point(x,B.MinY()), Point(x,B.MaxY()));
		return true;
	}

	Intersect(A, Line(B.UpRight(), B.DownRight()), &p[1]);
	Intersect(A, Line(B.UpRight(), B.UpLeft()), &p[2]);
	Intersect(A, Line(B.DownRight(), B.DownLeft()), &p[3]);

	std::sort(p.begin(), p.end());

	if (!Intersect((p[1]+p[2])/2, B))
		return false;
	if (intersection == NULL)
		return true;

	intersection->SetOriginAndEnd(p[1], p[2]);

	return true;

}

bool Intersect(const Line& A, const Polygon& B, Segment* intersection)
{
	Point p = A.Position();
	Point q = A.SecondPoint();
	if (intersection == NULL)
	{
		bool left = B[0].IsToTheLeftOfLine(p,q);

		for (nuint i = 1; i < B.NumPoints(); ++i)
		{
			if (B[i].IsToTheLeftOfLine(p,q) != left)
				return true;
		}

		return false;
	}

	bool left = B[0].IsToTheLeftOfLine(p,q);

	bool foundFirstIntersection = false;

	for (nuint i = 0; i < B.NumPoints()+1; ++i)
	{
		if (B[i].IsToTheLeftOfLine(p,q) != left)
		{
			Point point;
			if (!Intersect(A, Line(B[i-1], B[i]), &point))
			{
				cout << "ERROR IN Intersect(const Line& A, const Polygon& B, Segment* intersection)"
<< endl;
			}
			if (!foundFirstIntersection)
			{
				intersection->SetOrigin(point);
			} else
			{
				intersection->SetEnd(point);
				return true;
			}

			left = !left;
			foundFirstIntersection = true;
		}
	}

	return false;


}


//Intersect for Ray
bool Intersect(const Ray& A, const Ray& B, Point* intersection)
{
	Point tmp;
	if (intersection == NULL) intersection = &tmp;

	Line Al(A.Position(), A.Angle());
	Line Bl(B.Position(), B.Angle());

	if (!Intersect(Al, Bl, intersection))
		return false;

	if (!A.PointInLineIntersectsMe(*intersection)) return false;
	if (!B.PointInLineIntersectsMe(*intersection)) return false;

	return true;

}

bool Intersect(const Ray& A, const Segment& B, Point* intersection)
{
	Point tmp;
	if (intersection == NULL) intersection = &tmp;

	Line Al(A.Position(), A.Angle());
	Line Bl(B.Origin(), B.End());

	if (!Intersect(Al, Bl, intersection)) return false;

	if (!A.PointInLineIntersectsMe(*intersection)) return false;
	if (!B.PointInLineIntersectsMe(*intersection)) return false;

	return true;
}

bool Intersect(const Ray& A, const Circle& B, Segment* intersection)
{
	Segment tmp;
	if (intersection == NULL)	intersection = &tmp;

	if (!Intersect(Line(A.Position(), A.Angle()), B, intersection)) return false;

	if (!A.SegmentInLineIntersectsMe(intersection->Origin(), intersection->End(), intersection))
return false;

	return true;
}

bool Intersect(const Ray& A, const Box& B, Segment* intersection)
{
	Segment tmp;
	if (intersection == NULL)	intersection = &tmp;

	if (!Intersect(Line(A.Position(), A.Angle()), B, intersection)) return false;

	if (!A.SegmentInLineIntersectsMe(intersection->Origin(), intersection->End(), intersection))
return false;

	return true;
}

bool Intersect(const Ray& A, const Polygon& B, Segment* intersection)
{
	Segment tmp;
	if (intersection == NULL)	intersection = &tmp;

	if (!Intersect(Line(A.Position(), A.Angle()), B, intersection)) return false;

	if (!A.SegmentInLineIntersectsMe(intersection->Origin(), intersection->End(), intersection))
return false;

	return true;
}


//Intersect for Segment
bool Intersect(const Segment& A, const Segment& B, Point* intersection)
{
	Point tmp;
	if (intersection == NULL) intersection = &tmp;

	Line Al(A.Origin(), A.End());
	Line Bl(B.Origin(), B.End());

	if (!Intersect(Al, Bl, intersection)) return false;

	if (!A.PointInLineIntersectsMe(*intersection) ) return false;
	if (!B.PointInLineIntersectsMe(*intersection) ) return false;

	return true;

}

bool Intersect(const Segment& A, const Circle& B, Segment* intersection)
{
	Segment tmp;
	if (intersection == NULL)	intersection = &tmp;

	if (!Intersect(Line(A.Origin(), A.End()), B, intersection)) return false;

	if (!A.SegmentInLineIntersectsMe(intersection->Origin(), intersection->End(), intersection))
return false;

	return true;
}

bool Intersect(const Segment& A, const Box& B, Segment* intersection)
{
	Segment tmp;
	if (intersection == NULL)	intersection = &tmp;

	if (!Intersect(Line(A.Origin(), A.End()), B, intersection)) return false;

	if (!A.SegmentInLineIntersectsMe(intersection->Origin(), intersection->End(), intersection))
return false;

	return true;
}

bool Intersect(const Segment& A, const Polygon& B, Segment* intersection)
{
	Segment tmp;
	if (intersection == NULL)	intersection = &tmp;

	if (!Intersect(Line(A.Origin(), A.End()), B, intersection)) return false;

	if (!A.SegmentInLineIntersectsMe(intersection->Origin(), intersection->End(), intersection))
return false;

	return true;
}


//Intersect for Circle
bool Intersect(const Circle& A, const Circle& B, Segment* intersection)
{
	real distcenterssq = A.Position().DistanceSq(B.Position());
	real sumradius = A.Radius() + B.Radius();

	if (sumradius*sumradius < distcenterssq)
		return false;

	if (intersection != NULL)
	{
		//Check if one circle is inside the other

		real r = A.Radius();
		real R = B.Radius();
		real d = A.Position().Distance(B.Position());

		if (d+min(r,R) < max(r,R))
		{
			intersection->SetDirection(Point(0,0));
			if (r < R)
			{
				intersection->SetPosition(B.Position() + (A.Position()-B.Position())*(d+r)/d);
			} else
			{
				intersection->SetPosition(A.Position() + (B.Position()-A.Position())*(d+R)/d);

			}

			return true;
		}
		real a = (r*r-R*R+d*d)/(2*d);
		real b = d-a;

		Point p = (b*A.Position() + a*B.Position())/d;

		B.PerpendicularSegmentOfPoint(p, intersection);
	}

	return true;
}

bool Intersect(const Circle& A, const Box& B, Point* intersection)
{
	return Intersect(A, Polygon(B), intersection);
}

bool Intersect(const Circle& A, const Polygon& B, Point* intersection)
{
	if (Intersect(A.Position(), B)) return true;

	for (nuint i = 0; i < B.NumPoints(); ++i)
	{
		if (Intersect(Segment(B[i], B[i+1]), A))
		{
			return true;
		}
	}

	return false;
}


//Intersect for Box
bool Intersect(const Box& A, const Box& B, Box* intersection)
{
	if( A.MaxX() < B.MinX() || B.MaxX() < A.MinX())
		return false;
	if( A.MaxY() < B.MinY() || B.MaxY() < A.MinY())
		return false;

	if (intersection == NULL)
		return true;

	real minx = max(A.MinX(), B.MinX());
	real miny = max(A.MinY(), B.MinY());

	real maxx = min(A.MaxX(), B.MaxX());
	real maxy = min(A.MaxY(), B.MaxY());

	*intersection = Box(Point(minx,miny), Point(maxx,maxy));

	return true;
}

bool Intersect(const Box& A, const Polygon& B, Polygon* intersection)
{
	if (Intersect(A.Position(), B)) return true;

	for (nuint i = 0; i < B.NumPoints()+1; ++i)
	{
		if (Intersect(Segment(B[i], B[i+1]), A)) return true;
	}

	return false;
}


//Intersect for Polygon
bool Intersect(const Polygon& A, const Polygon& B, Polygon* intersection)
{
	if (Intersect(A.Position(), B)) return true;

	for (nuint i = 0; i < B.NumPoints()+1; ++i)
	{
		if (Intersect(Segment(B[i], B[i+1]), A)) return true;
	}

	return false;
}
*/