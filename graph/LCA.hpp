#pragma once

#include "Graph.hpp"
#include "RangeMinQuery.hpp"
#include "TreeAlgorithms.hpp"

Graph::Vertex lowest_common_ancestor_naive(
  const std::vector<Graph::Vertex>& parents, Graph::Vertex u, Graph::Vertex v);

class LCAWithPowersOfTwo
{
public:
    using Vertex = Graph::Vertex;

    LCAWithPowersOfTwo(const Graph& G, Vertex root);

    Vertex FindLCA(Vertex u, Vertex v) const;

    const std::vector<std::vector<Vertex>>& Ancestors() const { return A; }
    const auto& Levels() const { return L; }

    std::vector<Vertex> GetParents() const;

private:
    // L[v] is the level (distance to root) of vertex v
    std::vector<int> L;

    // A[v][i] is the 2^i ancestor of vertex v
    std::vector<std::vector<Vertex>> A;

    int log_height() const { return A[0].size(); }

    Vertex AncestorAtLevel(Vertex u, int lvl) const;
};

class LCAWithRMQ
{
public:
    using Vertex = Graph::Vertex;
    using index_t = std::make_signed_t<size_t>;

    LCAWithRMQ(const Graph& G, Vertex root);

    Vertex FindLCA(Vertex u, Vertex v) const;

    auto& get_euler_tour() const { return m_euler_tour; }
    auto& get_height_map() const { return m_height_map; }

    auto& get_first_and_last_occurrences() const
    {
        return m_first_and_last_index;
    }

private:
    struct MyFirstMyLastMyEverything
    {
        index_t first_occurrence;
        index_t last_occurrence;
    };

    void dfs_helper(const Graph& G,
                    Vertex parent,
                    Vertex current,
                    int current_height);

    bool initialize(const Graph& G, Vertex root);

    std::vector<MyFirstMyLastMyEverything> m_first_and_last_index;
    std::vector<Vertex> m_euler_tour;
    std::vector<int> m_height_map;
    bool m_initialized;
    range_min_query<decltype(m_height_map)> m_RMQ;
};
