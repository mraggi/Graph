#include "MinSpanningTree.hpp"
#include "utils/disjoint_sets.hpp"
#include <queue>

using Edge = Graph::Edge;
using Vertex = Graph::Vertex;

struct by_reverse_weight
{
    template <class T>
    bool operator()(const T& a, const T& b)
    {
        return a.weight() > b.weight();
    }
};

std::vector<Graph::Edge> prim(const Graph& G)
{
    auto n = G.num_vertices();

    std::vector<Edge> T;
    if (n < 2)
        return T;

    Vertex num_tree_edges = n - 1;

    T.reserve(num_tree_edges);

    std::vector<char> explored(n, false);

    std::priority_queue<Edge, std::vector<Edge>, by_reverse_weight>
      EdgesToExplore;

    explored[0] = true;
    for (auto v : G.neighbors(0))
    {
        EdgesToExplore.emplace(0, v, v.weight());
    }

    while (!EdgesToExplore.empty())
    {
        Edge s = EdgesToExplore.top();
        EdgesToExplore.pop();

        if (explored[s.to])
            continue;

        T.emplace_back(s);

        --num_tree_edges;
        if (num_tree_edges == 0)
            return T;

        explored[s.to] = true;
        for (auto v : G.neighbors(s.to))
        {
            if (!explored[v])
                EdgesToExplore.emplace(s.to, v, v.weight());
        }
    }
    return T;
}

std::vector<Graph::Edge> kruskal(const Graph& G)
{
    auto n = G.num_vertices();
    Vertex num_tree_edges = n - 1;

    std::vector<Graph::Edge> T;
    T.reserve(num_tree_edges);

    auto E = G.edges();

    std::sort(E.begin(), E.end(), [](const Edge& a, const Edge& b) {
        if (a.weight() != b.weight())
            return a.weight() < b.weight();
        if (a.from != b.from)
            return a.from < b.from;
        return a.to < b.to;
    });

    disjoint_sets D(G.num_vertices());

    for (auto& e : E)
    {
        Vertex a = e.from;
        Vertex b = e.to;

        if (!D.are_in_same_connected_component(a, b))
        {
            D.merge(a, b);
            T.emplace_back(e);
            --num_tree_edges;
            if (num_tree_edges == 0)
                return T;
        }
    }

    return T;
}
