#pragma once

#include "Graph.hpp"
#include "RangeMinQuery.hpp"

bool is_tree(const Graph& G);

// calculate its parent (for each vertex)
std::vector<Graph::Vertex> set_root(const Graph& G, Graph::Vertex root);
std::vector<int> height_map(const Graph& G, Graph::Vertex root);
