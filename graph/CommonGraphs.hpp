#pragma once

#include "Graph.hpp"

namespace graphs
{
Graph Petersen();

Graph Path(int n);

Graph Cycle(int n);

Graph Complete(int n);

Graph CompleteBipartite(int n, int m);

Graph RandomGraph(int n, double p);


}; // namespace graphs
