#pragma once

#include "FConvex.hpp"

#ifdef USE_SFML
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#endif

class Box : public FConvex
{
private:
    Point m_pLR;

public:
    explicit Box(const Point& pos = Point(0, 0), real w = 0, real h = 0);
    explicit Box(const Point& corner1, const Point& corner2);
	
#ifdef USE_SFML
	explicit Box(const sf::FloatRect& F) : FConvex({F.left+F.width/2.0, F.top+F.height/2.0}), m_pLR(F.width,F.height) {}
#endif
	
    Box(const Box& box);
    virtual ~Box(){};

    void SetWH(real w, real h)
    {
        m_pLR.x = w / 2;
        m_pLR.y = h / 2;
    }
    void SetWidth(const real w) { m_pLR.x = w / 2; }
    void SetHeight(const real h) { m_pLR.y = h / 2; }

    real MaxX() const { return Position().x + m_pLR.x; }
    real MaxY() const { return Position().y + m_pLR.y; }
    real MinX() const { return Position().x - m_pLR.x; }
    real MinY() const { return Position().y - m_pLR.y; }

    void Scale(real amount) { m_pLR *= amount; }
    void Scale(real amountx, real amounty)
    {
        m_pLR.x *= amountx;
        m_pLR.y *= amounty;
    }

    real Area() const { return m_pLR.x * m_pLR.y * 4; }
    real Perimeter() const { return 4 * (m_pLR.x + m_pLR.y); }
    real Radius() const { return sqrt(m_pLR.x * m_pLR.x + m_pLR.y * m_pLR.y); }

    void Rotate(real angle) {}

    shape        Type() const { return shape_Box; }
    static shape ClassType() { return shape_Box; }

    Point FarthestPointAtAngle(real angle) const;

    using FConvex::Intersects;

    bool Intersects(const Convex& other) const { return other.Intersects(*this); }
    bool Intersects(const Convex& other, Point& overlap) const
    {
        return other.Intersects(*this, overlap);
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
