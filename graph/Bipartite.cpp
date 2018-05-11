#include "Bipartite.hpp"
#include <stack>
using Vertex = BipartiteGraph::Vertex;

void BipartiteGraph::sort_neighbors()
{
    if (m_neighbors_sorted)
        return;

    for (auto& x : m_X)
        std::sort(std::begin(x), std::end(x));

    for (auto& y : m_Y)
        std::sort(std::begin(y), std::end(y));

    m_neighbors_sorted = true;
}

BipartiteGraph::BipartiteGraph(const Graph& G)
{
    // -1 means not set. 0 and 1 are the colors.
    std::vector<char> coloring(G.num_vertices(), -1);

    // map from vertices in G to vertices in (X,Y).
    std::vector<Vertex> map(G.num_vertices(), -1);

    for (auto v : G.vertices())
    {
        if (coloring[v] != -1)
            continue;
        std::stack<Vertex> frontier;
        frontier.emplace(v);
        coloring[v] = 0;
        map[v] = m_X.size();
        m_X.emplace_back();

        while (!frontier.empty())
        {
            auto u = frontier.top();
            frontier.pop();

            bool color = coloring[u];

            for (auto w : G.neighbors(u))
            {
                if (coloring[w] == -1)
                {
                    coloring[w] = !color;
                    if (coloring[w])
                    {
                        map[w] = m_Y.size();
                        m_Y.emplace_back();
                    }
                    else
                    {
                        map[w] = m_X.size();
                        m_X.emplace_back();
                    }
                    frontier.emplace(w);
                }
            }
        }

        for (auto v : G.vertices())
        {
            for (auto u : G.neighbors(v))
            {
                if (u < v)
                    continue;
                if (!coloring[u])
                    add_edge(map[u], map[v]);
                else
                    add_edge(map[v], map[u]);
            }
        }
    }
}

Graph BipartiteGraph::GetGraph() const
{
    Graph G(num_vertices());

    for (Vertex v = 0; v < num_verticesX(); ++v)
    {
        for (auto u : neighborsX(v))
        {
            G.add_edge(v, u + num_verticesX(), u.weight());
        }
    }

    return G;
}
