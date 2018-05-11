#pragma once

#include "Graph.hpp"

class BipartiteGraph
{
public:
    /****** BEGIN using definitions *****/
    using size_type = Graph::size_type;

    using Vertex = Graph::Vertex;

    using weight_t = Graph::weight_t;

    // something larger than weight_t, for when you have that weight_t doesn't
    // properly hold a sum of weight_t (for example, if weight_t = char).
    using sumweight_t = Graph::sumweight_t;

    using Neighbor = Graph::Neighbor; // Represents a half-edge (vertex,weight)

    using Edge = Graph::Edge; // (from,to,weight)

    using neighbor_list = std::vector<Neighbor>;
    using neighbor_const_iterator = neighbor_list::const_iterator;
    using neighbor_iterator = neighbor_list::iterator;
    /****** END using definitions *****/

public:
    BipartiteGraph(size_type x, size_type y) : m_X(x), m_Y(y) {}
    BipartiteGraph(const Graph& G);

    size_type degreeX(Vertex x) const { return m_X[x].size(); }
    size_type degreeY(Vertex y) const { return m_Y[y].size(); }

    size_type num_verticesX() const { return m_X.size(); }
    size_type num_verticesY() const { return m_Y.size(); }

    size_type num_vertices() const { return num_verticesX() + num_verticesY(); }

    using all_vertices = basic_natural_number<Vertex>;
    auto verticesX() const { return all_vertices(num_verticesX()); }
    auto verticesY() const { return all_vertices(num_verticesY()); }

    const auto& X() const { return m_X; }
    const auto& Y() const { return m_Y; }

    const neighbor_list& neighborsX(Vertex a) const { return m_X[a]; }
    const neighbor_list& neighborsY(Vertex a) const { return m_Y[a]; }

    void add_edge(Vertex x, Vertex y, weight_t w = 1)
    {
        m_X[x].emplace_back(y, w);
        m_Y[y].emplace_back(x, w);
        ++m_numedges;
        m_neighbors_sorted = false;
    }

    void add_edge(const Edge& E) { add_edge(E.from, E.to, E.weight()); }

    template <class EdgeContainer>
    void add_edges(const EdgeContainer& edges)
    {
        for (auto& e : edges)
            add_edge(e);
    }

    void add_edges(const std::initializer_list<Edge>& edges)
    {
        for (auto& e : edges)
            add_edge(e);
    }

    void FlipXandY() { std::swap(m_X, m_Y); }

    void sort_neighbors();

    Graph GetGraph() const;

private:
    std::vector<neighbor_list> m_X{};
    std::vector<neighbor_list> m_Y{};
    size_type m_numedges{0};
    bool m_neighbors_sorted{false};
};
