#pragma once

#include "FConvex.hpp"

#ifdef USE_SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#endif

class Box : public FConvex
{
private:
    Point m_pLR;

public:
    explicit Box(const Point& pos = Point(0, 0), real w = 0, real h = 0);
    explicit Box(const Point& corner1, const Point& corner2);
    ~Box() override = default;
    Box(const Box& B) = default;
    Box(Box&& B) = default;
    Box& operator=(const Box& B) = default;
    Box& operator=(Box&& B) = default;

#ifdef USE_SFML
    explicit Box(const sf::FloatRect& F)
        : FConvex({F.left + F.width/2.0, F.top + F.height/2.0})
        , m_pLR(F.width, F.height)
    {}
#endif

    void SetWH(real w, real h)
    {
        m_pLR.x = w/2;
        m_pLR.y = h/2;
    }
    void SetWidth(const real w) { m_pLR.x = w/2; }
    void SetHeight(const real h) { m_pLR.y = h/2; }

    real MaxX() const override { return Position().x + m_pLR.x; }
    real MaxY() const override { return Position().y + m_pLR.y; }
    real MinX() const override { return Position().x - m_pLR.x; }
    real MinY() const override { return Position().y - m_pLR.y; }

    void Scale(real amount) override { m_pLR *= amount; }
    void Scale(real amountx, real amounty) override
    {
        m_pLR.x *= amountx;
        m_pLR.y *= amounty;
    }

    real Area() const override { return m_pLR.x*m_pLR.y*4; }
    real Perimeter() const override { return 4*(m_pLR.x + m_pLR.y); }
    real Radius() const override
    {
        return sqrt(m_pLR.x*m_pLR.x + m_pLR.y*m_pLR.y);
    }

    void Rotate(real angle) override {}

    shape Type() const override { return shape_Box; }
    static shape ClassType() { return shape_Box; }

    Point FarthestPointAtAngle(real angle) const override;

    using FConvex::Intersects;

    bool Intersects(const Convex& other) const override
    {
        return other.Intersects(*this);
    }
    bool Intersects(const Convex& other, Point& overlap) const override
    {
        return other.Intersects(*this, overlap);
    }

    bool Intersects(const Point& other) const override;

    bool Intersects(const Line& other) const override;
    bool Intersects(const Line& other, Point& intersection) const override;
    bool Intersects(const Line& other,
                    Point& intersection,
                    Point& normal) const override;
    bool Intersects(const Line& other, Segment& intersection) const override;

    bool Intersects(const Circle& other) const override;
    bool Intersects(const Circle& other, Point& overlap) const override;

    bool Intersects(const Box& other) const override;
    bool Intersects(const Box& other, Point& overlap) const override;

    bool Intersects(const Polygon& other) const override;
    bool Intersects(const Polygon& other, Point& overlap) const override;

    Point ClosestPoint(const Point& point) const override;
};
