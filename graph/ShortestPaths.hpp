#pragma once

#include "Graph.hpp"
#include <queue>

using Distance = Graph::sumweight_t;
using Vertex = Graph::Vertex;

const auto INF = std::numeric_limits<Distance>::max();

struct DistanceAndParent
{
	DistanceAndParent(Graph::size_type n) : distance(n, INF), parent(n, Graph::INVALID_VERTEX) {}
	std::vector<Distance> distance;
	std::vector<Vertex> parent;
};

DistanceAndParent
DijkstraDistance(const Graph& G, Vertex origin, Vertex destination = Graph::INVALID_VERTEX);

using Path = std::deque<Graph::Neighbor>;

Path Dijkstra(const Graph& G, Vertex origin, Vertex destination);
