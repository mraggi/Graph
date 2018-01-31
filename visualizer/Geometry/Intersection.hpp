#pragma once
/*
#include "Box.hpp"
#include "CPoint.hpp"
#include "Circle.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Ray.hpp"
#include "Segment.hpp"

bool Intersect(const Convex& A, const Convex& B, Polygon * poly = NULL);
bool Intersect(const Point& A, const Convex& B);


/// Intersect for POINT
bool Intersect(const Point& A, const Point& B);
bool Intersect(const Point& A, const Line& B);
bool Intersect(const Point& A, const Ray& B);
bool Intersect(const Point& A, const Segment& B);
bool Intersect(const Point& A, const Circle& B);
bool Intersect(const Point& A, const Box& B);
bool Intersect(const Point& A, const Polygon& B);

//Intersect for Line
bool Intersect(const Line& A, const Line& B, Point* intersection = NULL);
bool Intersect(const Line& A, const Ray& B, Point* intersection = NULL);
bool Intersect(const Line& A, const Segment& B, Point* intersection = NULL);
bool Intersect(const Line& A, const Circle& B, Segment* intersection = NULL);
bool Intersect(const Line& A, const Box& B,  Segment* intersection = NULL);
bool Intersect(const Line& A, const Polygon& B,  Segment* intersection = NULL);

//Intersect for Ray
bool Intersect(const Ray& A, const Ray& B, Point* intersection = NULL);
bool Intersect(const Ray& A, const Segment& B, Point* intersection = NULL);
bool Intersect(const Ray& A, const Circle& B, Segment* intersection = NULL);
bool Intersect(const Ray& A, const Box& B, Segment* intersection = NULL);
bool Intersect(const Ray& A, const Polygon& B, Segment* intersection = NULL);

//Intersect for Segment
bool Intersect(const Segment& A, const Segment& B, Point* intersection = NULL);
bool Intersect(const Segment& A, const Circle& B, Segment* intersection = NULL);
bool Intersect(const Segment& A, const Box& B, Segment* intersection = NULL);
bool Intersect(const Segment& A, const Polygon& B, Segment* intersection =
NULL);

//Intersect for Circle
bool Intersect(const Circle& A, const Circle& B, Segment* intersection = NULL);
bool Intersect(const Circle& A, const Box& B, Point* intersection = NULL);
bool Intersect(const Circle& A, const Polygon& B, Point* intersection = NULL);

//Intersect for Box
bool Intersect(const Box& A, const Box& B, Box* intersection = NULL);
bool Intersect(const Box& A, const Polygon& B, Polygon* intersection = NULL);

//Intersect for Polygon
bool Intersect(const Polygon& A, const Polygon& B, Polygon* intersection =
NULL);


//Viceversa!!!!

inline bool Intersect(const Line& A, const Point& B) { return Intersect(B,A); }
inline bool Intersect(const Ray& A, const Point& B) { return Intersect(B,A); }
inline bool Intersect(const Segment& A, const Point& B) { return Intersect(B,A);
} inline bool Intersect(const Circle& A, const Point& B) { return
Intersect(B,A); } inline bool Intersect(const Box& A, const Point& B) { return
Intersect(B,A); } inline bool Intersect(const Polygon& A, const Point& B) {
return Intersect(B,A); }

//Intersect for Line
inline bool Intersect(const Ray& A, const Line& B, Point* intersection = NULL) {
return Intersect(B,A, intersection); } inline bool Intersect(const Segment& A,
const Line& B, Point* intersection = NULL) { return Intersect(B,A,
intersection); } inline bool Intersect(const Circle& A, const Line& B, Segment*
intersection = NULL) { return Intersect(B,A, intersection); } inline bool
Intersect(const Box& A, const Line& B,  Segment* intersection = NULL) { return
Intersect(B,A, intersection); } inline bool Intersect(const Polygon& A, const
Line& B,  Segment* intersection = NULL) { return Intersect(B,A, intersection); }

//Intersect for Ray
inline bool Intersect(const Segment& A, const Ray& B, Point* intersection =
NULL) { return Intersect(B,A, intersection); } inline bool Intersect(const
Circle& A, const Ray& B, Segment* intersection = NULL) { return Intersect(B,A,
intersection); } inline bool Intersect(const Box& A, const Ray& B, Segment*
intersection = NULL) { return Intersect(B,A, intersection); } inline bool
Intersect(const Polygon& A, const Ray& B, Segment* intersection = NULL) { return
Intersect(B,A, intersection); }

//Intersect for Segment
inline bool Intersect(const Circle& A, const Segment& B, Segment* intersection =
NULL) { return Intersect(B,A, intersection); } inline bool Intersect(const Box&
A, const Segment& B, Segment* intersection = NULL) { return Intersect(B,A,
intersection); } inline bool Intersect(const Polygon& A, const Segment& B,
Segment* intersection = NULL) { return Intersect(B,A, intersection); }

//Intersect for Circle (intersection = some point in intersection, usually
around the middle) inline bool Intersect(const Box& A, const Circle& B, Point*
intersection = NULL) { return Intersect(B,A, intersection); } inline bool
Intersect(const Polygon& A, const Circle& B, Point* intersection = NULL) {
return Intersect(B,A, intersection); }

//Intersect for Box
inline bool Intersect(const Polygon& A, const Box& B, Polygon* intersection =
NULL) { return Intersect(B,A, intersection); }*/