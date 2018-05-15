#pragma once
#include "Graph.hpp"

namespace centrality
{

std::vector<double> degree(const Graph& G);
std::vector<double> closeness(const Graph& G);
std::vector<double> betweenness(const Graph& G);

} // namespace centrality
