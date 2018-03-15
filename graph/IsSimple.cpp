#include "IsSimple.hpp"
#include <unordered_set>
bool is_simple(const Graph& G)
{
	for (auto v : G.vertices())
	{
		std::unordered_set<Graph::Vertex> US;
		for (auto u : G.neighbors(v))
		{
			if (!US.emplace(u).second)
				return false;
		}
	}
	return true;
}
