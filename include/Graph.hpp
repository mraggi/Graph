#pragma once

#include "Misc.hpp"
#include "NaturalNumber.hpp"
#include <algorithm>
#include <unordered_map>

// simple undirected graph
class Graph
{
public:
    using size_type = long long; // NOLINT

    using Vertex = std::int64_t;

    enum WORKAROUND_UNTIL_CPP17
    {
        INVALID_VERTEX = -1
    };
    // 	inline static constexpr Vertex INVALID_VERTEX = -1; // Uncomment with
    // c++17

    using weight_t = std::int64_t;

    // something larger than weight_t, for when you have that weight_t doesn't
    // properly hold a sum of weight_t (for example, if weight_t = char).
    using sumweight_t = std::int64_t;

    struct Neighbor; // Represents a half-edge (vertex,weight)

    struct Edge; // (from,to,weight)

    using neighbor_list = std::vector<Neighbor>;
    using neighbor_const_iterator = neighbor_list::const_iterator;
    using neighbor_iterator = neighbor_list::iterator;

    // Constructor
    explicit Graph(Vertex numberOfVertices = 0);

    size_type degree(Vertex a) const { return m_graph[a].size(); }

    // Graph modification functions
    Vertex add_vertex();
    void add_edge(Vertex from, Vertex to, weight_t w = 1);
    void add_edge(const Edge& e);

    template <class EdgeContainer>
    void add_edges(const EdgeContainer& edges)
    {
        for (auto& e : edges)
            add_edge(e);
    }

    void add_edges(const std::initializer_list<Edge>& edges);

    bool add_edge_no_repeat(Vertex from, Vertex to, weight_t w = 1);

    void sort_neighbors();

    void remove_vertex(Vertex v);
    void remove_edge(Vertex v, Vertex u);

    void delete_loops();
    void delete_repeated_edges();
    void make_simple();

    // Get Graph Info
    Vertex num_vertices() const { return m_numvertices; }
    size_type num_edges() const { return m_numedges; }

    inline const neighbor_list& neighbors(Vertex n) const { return m_graph[n]; }
    inline const neighbor_list& outneighbors(Vertex n) const
    {
        return m_graph[n];
    }
    inline const neighbor_list& inneighbors(Vertex n) const
    {
        return m_graph[n];
    }

    using all_vertices = basic_natural_number<Vertex>;
    auto vertices() const { return all_vertices{num_vertices()}; }

    std::vector<Edge> edges() const; // TODO(mraggi): make*this lazy

    bool is_neighbor(Vertex from, Vertex to) const;

    weight_t edge_value(Vertex from, Vertex to) const;

    neighbor_const_iterator get_neighbor(Vertex from, Vertex to) const;
    neighbor_iterator get_neighbor(Vertex from, Vertex to);

    // Start class definitions
    struct Neighbor
    {
        explicit Neighbor() : vertex(INVALID_VERTEX), m_weight(0) {}

        explicit Neighbor(Vertex v, weight_t w = 1) : vertex(v), m_weight(w) {}

        inline operator Vertex() const { return vertex; }

        weight_t weight() const { return m_weight; }

        void set_weight(weight_t w) { m_weight = w; }

        Vertex vertex{INVALID_VERTEX};

    private:
        // comment out if not needed, and make set_weight do nothing, and make
        // weight() return 1
        weight_t m_weight{1};
    };

    struct Edge
    {
        Vertex from{INVALID_VERTEX};
        Vertex to{INVALID_VERTEX};

        Edge() : m_weight(0) {}
        Edge(Vertex f, Vertex t, weight_t w = 1) : from(f), to(t), m_weight(w)
        {}

        Vertex operator[](bool i) const { return i ? to : from; }

        // replace by "return 1" if weight doesn't exist
        weight_t weight() const { return m_weight; }
        void change_weight(weight_t w) { m_weight = w; }

        bool operator==(const Edge& E) const
        {
            return ((from == E.from && to == E.to) ||
                    (from == E.to && to == E.from)) &&
              m_weight == E.m_weight;
        }

    private:
        weight_t m_weight{1};
    };

private:
    // Graph member variables
    size_type m_numvertices;
    size_type m_numedges{0};

    std::vector<neighbor_list> m_graph;
    bool m_neighbors_sorted{false};
};
