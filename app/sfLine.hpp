#include <Geometry/Point.hpp>
#include <SFML/Graphics.hpp>

class sfLine : public sf::Drawable
{
public:
    sfLine(const Point& point1,
           const Point& point2,
           const sf::Color& color = sf::Color::White,
           real thickness = 1.0)
        : P(point1), Q(point2)
    {
        setFillColor(color);
        setThickness(thickness);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(
          static_cast<sf::Vertex const*>(vertices), 4, sf::Quads, states);
    }

    void setFillColor(const sf::Color& color)
    {
        for (auto& v : vertices)
            v.color = color;
    }

    void setOutlineColor(const sf::Color& color) { setFillColor(color); }

    void setThickness(real t)
    {
        Point unitDirection = (P - Q).Normalized();
        Point unitPerpendicular = unitDirection.Perp();

        Point offset = (t/2.0)*unitPerpendicular;

        vertices[0].position = Q + offset;
        vertices[1].position = P + offset;
        vertices[2].position = P - offset;
        vertices[3].position = Q - offset;
    }

private:
    sf::Vertex vertices[4];
    Point P;
    Point Q;
};
