#pragma once

#include "Graph.hpp"
#include <queue>

std::vector<Graph::sumweight_t> DijkstraCost(const Graph& G,
											 Graph::Vertex origin,
											 Graph::Vertex destination = Graph::INVALID_VERTEX);

using Path = std::deque<Graph::Neighbor>;

Path Dijkstra(const Graph& G, Graph::Vertex origin, Graph::Vertex destination);
