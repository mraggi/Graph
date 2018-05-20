#pragma once

#include "Convex.hpp"

// Finite Convex class.
class FConvex : public Convex
{
public:
    explicit FConvex(const Point& p = Point(0, 0)) : Convex(p) {}
    ~FConvex() override = default;
    FConvex(const FConvex& B) = default;
    FConvex(FConvex&& B) = default;
    FConvex& operator=(const FConvex& B) = default;
    FConvex& operator=(FConvex&& B) = default;

    virtual real MaxX() const = 0;
    virtual real MinX() const = 0;
    virtual real MaxY() const = 0;
    virtual real MinY() const = 0;

    virtual real Width() const { return MaxX() - MinX(); }
    virtual real Height() const { return MaxY() - MinY(); }

    Point UpLeft() const { return {MinX(), MinY()}; }
    Point UpRight() const { return {MaxX(), MinY()}; }
    Point DownLeft() const { return {MinX(), MaxY()}; }
    Point DownRight() const { return {MaxX(), MaxY()}; }

    virtual real Area() const = 0;
    virtual real Perimeter() const = 0;
    // virtual shape Type() const = 0;

    // Bounding Radius.
    virtual real Radius() const = 0;
    virtual real RadiusSq() const { return Radius()*Radius(); }

    virtual Point FarthestPointAtAngle(real angle) const = 0;

    virtual Box BoundingBox() const;
    virtual Circle BoundingCircle() const;

    bool Intersects(const Point& other, Point& overlap) const override;

    using Convex::Intersects;
};
