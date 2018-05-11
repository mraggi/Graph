#include "Clustering.hpp"
#include <unordered_set>

using Vertex = Graph::Vertex;

std::int64_t num_triangles_of_neighbors(const Graph& G, Graph::Vertex v)
{
    std::int64_t result = 0;

    std::vector<char> Neighbors(G.num_vertices(), 0);

    for (auto u : G.neighbors(v))
        Neighbors[u] = 1;

    for (auto u : G.neighbors(v))
    {
        for (auto w : G.neighbors(u))
        {
            if (w > u && Neighbors[w])
                ++result;
        }
    }
    return result;
}

std::int64_t num_triangles(const Graph& G)
{
    std::int64_t result = 0;
    for (auto v : G.vertices())
        result += num_triangles_of_neighbors(G, v);
    return result/3;
}

std::int64_t sum_degrees_in_two(const Graph& G)
{
    std::int64_t result = 0;
    for (auto v : G.vertices())
    {
        auto d = G.degree(v);
        result += (d*(d - 1))/2;
    }
    return result;
}

std::vector<double> clustering_local(const Graph& G)
{
    std::vector<double> result(G.num_vertices(), 0.0);

    for (auto v : G.vertices())
    {
        auto d = G.degree(v);
        if (d >= 2)
            result[v] =
              (2.0*num_triangles_of_neighbors(G, v))/(d*(d - 1));
    }

    return result;
}

double clustering_global(const Graph& G)
{
    double denominator = sum_degrees_in_two(G);
    if (denominator == 0)
        return 0;
    return (3.0*num_triangles(G))/denominator;
}
