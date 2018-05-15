#include "TreeAlgorithms.hpp"
#include "ConnectedComponents.hpp"
#include "VectorHelpers.hpp"

#include <cmath>
#include <set>
#include <stack>

using Vertex = Graph::Vertex;

bool is_tree(const Graph& G)
{
    return G.num_edges() + 1 == G.num_vertices() && is_connected(G);
}

std::vector<Vertex> set_root(const Graph& G, Vertex root)
{
    std::vector<Vertex> parent(G.num_vertices());

    parent[root] = Graph::INVALID_VERTEX;

    std::stack<Vertex> frontier;
    frontier.emplace(root);

    while (!frontier.empty())
    {
        auto p = frontier.top();
        frontier.pop();

        for (auto u : G.neighbors(p))
        {
            if (parent[p] == u)
                continue;
            parent[u] = p;
            frontier.emplace(u);
        }
    }
    return parent;
}

std::vector<int> height_map(const Graph& G, Vertex root)
{
    std::vector<int> level(G.num_vertices(), -1);

    level[root] = 0;

    std::stack<Vertex> frontier;
    frontier.emplace(root);

    while (!frontier.empty())
    {
        auto p = frontier.top();
        frontier.pop();
        int current_level = level[p];

        for (auto u : G.neighbors(p))
        {
            if (level[u] != -1)
                continue;
            level[u] = current_level + 1;
            frontier.emplace(u);
        }
    }

    return level;
}
