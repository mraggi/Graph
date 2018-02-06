#pragma once

#include "Geometry/AllConvex.hpp"
#include <SFML/Graphics.hpp>

template <class T>
T interpolate(real t, const T& from, const T& to)
{
	return t * to + (1 - t) * from;
}

inline sf::Color interpolate(real t, const sf::Color& from, const sf::Color& to)
{
	real ra = from.r;
	real ga = from.g;
	real ba = from.b;
	real aa = from.a;
	real rb = to.r;
	real gb = to.g;
	real bb = to.b;
	real ab = to.a;

	real r = interpolate(t, ra, rb);
	real g = interpolate(t, ga, gb);
	real b = interpolate(t, ba, bb);
	real a = interpolate(t, aa, ab);

	return sf::Color(r, g, b, a);
}
