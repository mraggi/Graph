#pragma once

#include "Graph.hpp"

namespace graphs
{
Graph Petersen();

Graph Path(int n);

Graph Cycle(int n);

Graph Complete(int n);

Graph CompleteBipartite(int n, int m);

Graph Random(int n, double p);

Graph RandomWeighted(int n, double p);

Graph RandomWithSpecifiedNumEdges(int num_verts, int num_edges);

Graph RandomTree(int n);

Graph Grid(int n, int m);

Graph WeightedGrid(int n, int m);

Graph RandomBinaryTree(int n);

Graph AlbertBarabanasi(int n, int k);

}; // namespace graphs
