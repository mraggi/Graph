#include "ShortestPaths.hpp"

// Dijkstra and Astar are now templates :)

using Matrix = std::vector<std::vector<Distance>>;
Matrix AllPairsShortestPaths(const Graph& G)
{
    constexpr Distance oo = INF/2-1;
    auto n = G.num_vertices();
    Matrix D(n,Row(n,oo));
    
    for (auto u : G.vertices())
    {
        D[u][u] = 0;
        for (auto v : G.neighbors(u))
            D[u][v] = v.weight();
    }
    
    for (auto u : G.vertices())
    {
        for (auto v : G.vertices())
        {
            for (auto w : G.vertices())
            {
                auto dvuw = D[v][u] + D[u][w];
                if (D[v][w] > dvuw)
                    D[v][w] = dvuw;
            }
        }
    }
    
    return D;
}
