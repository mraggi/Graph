#pragma once

#include "Graph.hpp"

inline std::ostream& operator<<(std::ostream& os, const Graph::Neighbor& N)
{
	os << '(' << N.vertex << ',' << N.weight() << ')';
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const Graph::Edge& E)
{
	os << '{' << E.from << '-' << E.to << ',' << E.weight() << '}';
	return os;
}

inline std::string to_string(const Graph::Neighbor& N)
{
	std::stringstream ss;
	ss << N;
	return ss.str();
}

inline std::string to_string(const Graph::Edge& E)
{
	std::stringstream ss;
	ss << E;
	return ss.str();
}
