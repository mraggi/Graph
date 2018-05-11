#pragma once

#include "Graph.hpp"

inline bool check_graph(const Graph& G)
{
    long E = 0;
    for (auto v : G.vertices())
    {
        E += G.degree(v);
    }
    return (E == 2*G.num_edges());
}