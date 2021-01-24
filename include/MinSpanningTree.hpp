#pragma once

#include "Graph.hpp"

std::vector<Graph::Edge> prim(const Graph& G);

std::vector<Graph::Edge> kruskal(const Graph& G);
