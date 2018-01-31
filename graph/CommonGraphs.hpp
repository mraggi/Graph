#pragma once

#include "Graph.hpp"

namespace graphs
{
Graph Petersen();

Graph Path(int n);

Graph Cycle(int n);

Graph Complete(int n);

Graph CompleteBipartite(int n, int m);
}; // namespace graphs
