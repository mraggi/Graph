#pragma once

#include "Geometry/AllConvex.hpp"
#include <SFML/Graphics.hpp>

template <class T>
T interpolate(real t, const T& from, const T& to)
{
	return t * to + (1.0 - t) * from;
}

inline sf::Color interpolate(real t, const sf::Color& from, const sf::Color& to)
{
	real r1 = from.r;
	real g1 = from.g;
	real b1 = from.b;
	real a1 = from.a;

	real r2 = to.r;
	real g2 = to.g;
	real b2 = to.b;
	real a2 = to.a;

	real r = interpolate(t, r1, r2);
	real g = interpolate(t, g1, g2);
	real b = interpolate(t, b1, b2);
	real a = interpolate(t, a1, a2);

	auto clamp = [](real& t, real a, real b) {
		if (t < a)
			t = a;
		if (t > b)
			t = b;
	};

	clamp(r, 1, 254);
	clamp(g, 1, 254);
	clamp(b, 1, 254);
	clamp(a, 1, 254);

	sf::Uint8 ur = static_cast<unsigned char>(r);
	sf::Uint8 ug = static_cast<unsigned char>(g);
	sf::Uint8 ub = static_cast<unsigned char>(b);
	sf::Uint8 ua = static_cast<unsigned char>(a);

	return sf::Color(ur, ug, ub, ua);
}

template <class U, class T = U>
inline std::vector<T> interpolate(real t, const std::vector<U>& A, const std::vector<U>& B)
{
	assert(A.size() == B.size());
	std::vector<T> result(A.size());
	for (size_t i = 0; i < result.size(); ++i)
	{
		result[i] = interpolate(t, A[i], B[i]);
	}
	return result;
}
