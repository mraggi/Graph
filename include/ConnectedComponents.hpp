#pragma once

#include "Graph.hpp"

std::vector<int> connected_components(const Graph& G);

bool is_connected(const Graph& G);

int num_connected_components(const Graph& G);
