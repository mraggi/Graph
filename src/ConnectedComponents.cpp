#include "ConnectedComponents.hpp"
#include <stack>

using Vertex = Graph::Vertex;

std::vector<int> connected_components(const Graph& G)
{
    auto n = G.num_vertices();
    std::vector<int> components(n, -1);
    int current_component = 0;

    for (auto v : G.vertices())
    {
        if (components[v] != -1)
            continue;

        std::stack<Vertex> frontier;
        frontier.emplace(v);
        while (!frontier.empty())
        {
            auto p = frontier.top();
            frontier.pop();
            if (components[p] != -1)
                continue;
            components[p] = current_component;
            for (auto u : G.neighbors(p))
            {
                if (components[u] == -1)
                    frontier.emplace(u);
            }
        }
        ++current_component;
    }

    return components;
}

bool is_connected(const Graph& G)
{
    auto n = G.num_vertices();
    if (n < 2)
        return true;

    using Bool = char;
    std::vector<Bool> seen(n, false);
    int num_seen = 0;

    std::stack<Vertex> frontier;
    frontier.emplace(0);

    while (!frontier.empty())
    {
        auto p = frontier.top();
        frontier.pop();
        if (seen[p])
            continue;
        seen[p] = true;
        ++num_seen;
        for (auto u : G.neighbors(p))
        {
            if (!seen[u])
                frontier.emplace(u);
        }
    }

    return num_seen == n;
}

int num_connected_components(const Graph& G)
{
    if (G.num_vertices() == 0)
        return 0;

    auto components = connected_components(G);

    return (*std::max_element(components.begin(), components.end())) + 1;
}
