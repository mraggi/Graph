#include "Centrality.hpp"
#include "ShortestPaths.hpp"
#include "VectorHelpers.hpp"

namespace centrality
{

std::vector<double> degree(const Graph& G)
{
    auto n = G.num_vertices();
    double e = n - 1.0;
    std::vector<double> C(n);

    for (auto v : G.vertices())
        C[v] = G.degree(v)/e;

    return C;
}
std::vector<double> closeness(const Graph& G)
{
    auto n = G.num_vertices();

    std::vector<double> C(n, n - 1);

    auto D = AllPairsShortestPaths(G);

    for (auto u : G.vertices())
    {
        auto d = std::accumulate(D[u].begin(), D[u].end(), 0.0);
        C[u] /= d;
    }

    return C;
}

void betweenness_normalize(std::vector<double>& B, Vertex n)
{
    double L = 2*n - 1;
    double R = n*n - n + 1;

    // Convert to nice, natural format
    for (auto& x : B)
    {
        x = (x - L)/(R - L);
    }
}

std::vector<double> betweenness_contrib(const Graph& G, Vertex s)
{
    auto n = G.num_vertices();
    std::vector<Vertex> ordered_vertices(1, s);
    std::vector<Distance> D(n, -1);
    std::vector<Distance> W(n, 0);
    std::vector<double> X(n, 1.0);

    D[s] = 0;
    W[s] = 1;

    std::queue<Vertex> frontier;
    frontier.emplace(s);

    // Step X
    while (!frontier.empty())
    {
        auto lastnode = frontier.front();
        frontier.pop();

        int d = D[lastnode];

        for (auto v : G.neighbors(lastnode))
        {
            if (D[v] == -1)
            {
                D[v] = d + 1;
                W[v] = W[lastnode];

                frontier.emplace(v);
                ordered_vertices.emplace_back(v);
            }
            else if (D[v] == D[lastnode] + 1)
            {
                W[v] += W[lastnode];
            }
        }
    }

    // Step W
    for (auto vit = ordered_vertices.rbegin(); vit != ordered_vertices.rend();
         ++vit)
    {
        auto v = *vit;
        for (auto u : G.neighbors(v))
        {
            if (D[u] == D[v] + 1)
            {
                X[v] += (X[u]*W[v])/W[u];
            }
        }
    }

    return X;
}

std::vector<double> betweenness(const Graph& G)
{
    auto n = G.num_vertices();
    std::vector<double> B(n, 0.0);

    for (auto s : G.vertices())
    {
        auto X = betweenness_contrib(G, s);
        for (auto i : G.vertices())
            B[i] += X[i];
    }

    betweenness_normalize(B, n);

    return B;
}

} // namespace centrality
