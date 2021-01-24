#pragma once
#include "Graph.hpp"

std::vector<double> clustering_local(const Graph& G);
double clustering_global(const Graph& G);

std::int64_t num_triangles(const Graph& G);
std::int64_t num_triangles_of_neighbors(const Graph& G, Graph::Vertex v);
