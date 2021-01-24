#pragma once

#include "Bipartite.hpp"
#include "Graph.hpp"

namespace graphs
{
Graph Petersen();

Graph Path(int n);

Graph Cycle(int n);

Graph Complete(int n);

Graph CompleteBipartite(int n, int m);

Graph BalancedBinaryTree(int n);

Graph Random(int n, double p);

Graph RandomWeighted(int n, double p);

Graph RandomWithSpecifiedNumEdges(int num_verts, int num_edges);

Graph RandomTree(int n);

Graph RandomBinaryTree(int n);

BipartiteGraph RandomBipartite(int n, int m, double p);

Graph Grid(int n, int m);

Graph WeightedGrid(int n, int m);

Graph AlbertBarabanasi(int n, int k);

} // namespace graphs
