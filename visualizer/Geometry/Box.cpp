#include "AllConvex.hpp"

// DECLARACION DE Box

Box::Box(const Point& pos, real w, real h) : FConvex(pos), m_pLR(w, h) {}

Box::Box(const Point& corner1, const Point& corner2)
    : FConvex((corner1 + corner2)/2.0)
    , m_pLR(std::abs(corner1.x - corner2.x)/2.0,
            std::abs(corner1.y - corner2.y)/2.0)
{}

Point Box::FarthestPointAtAngle(real angle) const
{
    angle = MakeValidAngle(angle);
    real theta = MakeValidAngle(m_pLR.Angle());
    real w = m_pLR.x;
    real h = m_pLR.y;

    if (std::abs(angle) <= theta)
        return Position() + Point(w, w*tan(angle));

    if (pi - std::abs(angle) <= theta)
        return Position() + Point(-w, w*tan(pi - angle));

    if (angle > 0)
        return Position() + Point(h*tan(pi/2 - angle), h);

    if (angle < 0)
        return Position() + Point(-h*tan(pi/2 - angle), -h);

    return {0, 0};
}

bool Box::Intersects(const Point& other) const
{
    if (other.x < MinX() || other.x > MaxX())
        return false;
    if (other.y < MinY() || other.y > MaxY())
        return false;
    return true;
}

bool Box::Intersects(const Line& other) const
{
    Polygon A(*this);

    return A.Intersects(other);
}

bool Box::Intersects(const Line& other, Point& intersection) const
{
    Polygon A(*this);

    return A.Intersects(other, intersection);
}

bool Box::Intersects(const Line& other,
                     Point& intersection,
                     Point& normal) const
{
    Polygon A(*this);

    return A.Intersects(other, intersection, normal);
}

bool Box::Intersects(const Line& other, Segment& intersection) const
{
    Polygon A(*this);

    return A.Intersects(other, intersection);
}

bool Box::Intersects(const Circle& other) const
{
    Point overlap = Point();
    real x = 0;
    real y = 0;
    real aux;
    aux = MinX() - other.Position().x;
    if (aux > 0)
        x = aux;
    else
    {
        aux = MaxX() - other.Position().x;
        if (aux < 0)
            x = aux;
    }
    aux = MinY() - other.Position().y;
    if (aux > 0)
        y = aux;
    else
    {
        aux = MaxY() - other.Position().y;
        if (aux < 0)
            y = aux;
    }
    overlap = -Point(x, y);
    aux = other.Radius()*other.Radius();
    return overlap.LengthSq() <= aux;
}

bool Box::Intersects(const Circle& other, Point& overlap) const
{
    overlap = Point();
    real x = 0;
    real y = 0;
    real xInterior = 0; // Estos son para el caso en que el centro del circulo
                        // esta dentro del cuadro.
    real yInterior = 0; // No sirven para determinar colision, pero si para
                        // determinar el desplazamiento en ese caso.
    real aux;
    aux = MinX() - other.Position().x;
    if (aux > 0)
        x = aux;
    else
    {
        xInterior = aux;
        aux = MaxX() - other.Position().x;
        if (aux < 0)
            x = aux;
        else if (-xInterior > aux)
            xInterior = aux;
    }
    aux = MinY() - other.Position().y;
    if (aux > 0)
        y = aux;
    else
    {
        yInterior = aux;
        aux = MaxY() - other.Position().y;
        if (aux < 0)
            y = aux;
        else if (-yInterior > aux)
            yInterior = aux;
    }
    if (std::abs(x) > tolerance || std::abs(y) > tolerance)
    {
        overlap = Point(x, y);
        aux = other.Radius()*other.Radius();
        if (overlap.LengthSq() > aux)
            return false;

        aux = overlap.Length();
        overlap.Normalize();
        overlap.Scale(aux - other.Radius());
        return true;
    }
    if (std::abs(xInterior) < std::abs(yInterior))
        overlap = Point(xInterior, 0);
    else
        overlap = Point(0, yInterior);
    aux = overlap.Length();
    if (std::abs(aux) > tolerance)
    {
        aux = (other.Radius() + aux)/aux;
        overlap.Scale(aux);
    }
    else // CASO DEGENERADO: El centro del circulo es alguna esquina.
    {
        if (std::abs(other.Position().x - MinX()) < tolerance)
            overlap = Point(-other.Radius(), 0);
        else
            overlap = Point(other.Radius(), 0);
    }
    return true;
}

bool Box::Intersects(const Box& other) const
{
    if (other.MaxX() < MinX() || MaxX() < other.MinX())
        return false;
    if (other.MaxY() < MinY() || MaxY() < other.MinY())
        return false;
    return true;
}

bool Box::Intersects(const Box& other, Point& overlap) const
{
    overlap = Point();
    real x1 = other.MaxX() - MinX();
    real x2 = other.MinX() - MaxX();
    if (x1 < 0 || x2 > 0)
        return false;
    real y1 = other.MaxY() - MinY();
    real y2 = other.MinY() - MaxY();
    if (y1 < 0 || y2 > 0)
        return false;
    real x = 0;
    real y = 0;
    real aux1 = MaxX() - other.MaxX();
    real aux2 = MinX() - other.MinX();
    if (aux1 > 0 && aux2 > 0)
        x = x1;
    else if (aux1 < 0 && aux2 < 0)
        x = x2;
    aux1 = MaxY() - other.MaxY();
    aux2 = MinY() - other.MinY();
    if (aux1 > 0 && aux2 > 0)
        y = y1;
    else if (aux1 < 0 && aux2 < 0)
        y = y2;
    if (std::abs(x) < tolerance && std::abs(y) < tolerance)
    {
        if (x1 < -x2)
            x = x1;
        else
            x = x2;
        if (y1 < -y2)
            y = y1;
        else
            y = y2;
    }
    if (std::abs(x) > tolerance && std::abs(y) > tolerance)
    {
        if (std::abs(x) < std::abs(y))
            overlap = Point(-x, 0);
        else
            overlap = Point(0, -y);
    }
    else
        overlap = Point(-x, -y);

    return true;
}

bool Box::Intersects(const Polygon& other) const
{
    return other.Intersects(Polygon(*this));
}

bool Box::Intersects(const Polygon& other, Point& overlap) const
{
    Polygon A(*this);

    return A.Intersects(other, overlap);
}

Point Box::ClosestPoint(const Point& point) const
{
    Polygon A(*this);
    return A.ClosestPoint(point);
}
