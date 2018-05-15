#include "LCA.hpp"
#include "ConnectedComponents.hpp"
#include "TreeAlgorithms.hpp"
#include "VectorHelpers.hpp"
#include <cmath>
#include <set>
#include <stack>

using Vertex = Graph::Vertex;

Vertex lowest_common_ancestor_naive(const std::vector<Vertex>& parents,
                                    Vertex u,
                                    Vertex v)
{
    std::vector<bool> explored(parents.size(), false);

    Vertex root = find(parents.begin(), parents.end(), -1) - parents.begin();

    while (u != root)
    {
        explored[u] = true;
        u = parents[u];
    }

    while (v != root)
    {
        if (explored[v])
            return v;
        v = parents[v];
    }
    return root;
}

LCAWithPowersOfTwo::LCAWithPowersOfTwo(const Graph& G, Vertex root)
    : L(height_map(G, root))
    , A(G.num_vertices(),
        std::vector<Vertex>(
          std::log2(*std::max_element(L.begin(), L.end()) + 1) + 1, -1))
{
    auto parents = set_root(G, root);

    // The 2^0-th ancestor of v is simply the parent of v
    for (auto v : G.vertices())
        A[v][0] = parents[v];

    for (int i = 1; i < log_height(); ++i)
    {
        for (auto v : G.vertices())
        {
            // My 2^i-th ancestor is the 2^{i-1} ancestor of my 2^{i-1}
            // ancestor!
            if (A[v][i - 1] != -1)
                A[v][i] = A[A[v][i - 1]][i - 1];
        }
    }
}

Vertex LCAWithPowersOfTwo::AncestorAtLevel(Vertex u, int lvl) const
{
    int d = L[u] - lvl;
    assert(d >= 0);

    while (d > 0)
    {
        int h = std::log2(d);
        u = A[u][h];
        d -= (1 << h);
    }

    return u;
}

Vertex LCAWithPowersOfTwo::FindLCA(Vertex u, Vertex v) const
{
    if (L[u] < L[v])
        std::swap(u, v);

    u = AncestorAtLevel(u, L[v]);

    if (u == v)
        return u;

    for (int i = std::log2(L[u]); i >= 0; --i)
    {
        if (A[u][i] != -1 && A[u][i] != A[v][i])
        {
            u = A[u][i];
            v = A[v][i];
        }
    }

    return A[u][0]; // which is = A[v][0]
}

std::vector<Vertex> LCAWithPowersOfTwo::GetParents() const
{
    std::vector<Vertex> parents(A.size());
    for (size_t v = 0; v < parents.size(); ++v)
        parents[v] = A[v][0];
    return parents;
}

void LCAWithRMQ::dfs_helper(const Graph& G,
                            Vertex parent,
                            Vertex current,
                            int current_height)
{
    m_first_and_last_index[current].first_occurrence = m_euler_tour.size();
    m_euler_tour.push_back(current);
    m_height_map.push_back(current_height);
    for (auto v : G.neighbors(current))
    {
        if (v != parent)
        {
            dfs_helper(G, current, v, current_height + 1);
            m_euler_tour.push_back(current);
            m_height_map.push_back(current_height);
        }
    }
    m_first_and_last_index[current].last_occurrence = m_euler_tour.size() - 1;
}

LCAWithRMQ::LCAWithRMQ(const Graph& G, Vertex root)
    : m_first_and_last_index(G.num_vertices())
    , m_initialized(initialize(G, root))
    , m_RMQ(m_height_map)
{}

bool LCAWithRMQ::initialize(const Graph& G, Vertex root)
{
    auto n = G.num_vertices();
    m_euler_tour.reserve(2*n + 1);
    m_height_map.reserve(2*n + 1);

    dfs_helper(G, Graph::INVALID_VERTEX, root, 0);

    return true;
}

Vertex LCAWithRMQ::FindLCA(Vertex u, Vertex v) const
{
    if (u == v)
        return u;

    auto FLU = m_first_and_last_index[u];
    auto FLV = m_first_and_last_index[v];

    if (FLU.first_occurrence > FLV.first_occurrence)
    {
        std::swap(u, v);
        std::swap(FLU, FLV);
    }

    // Now u appears before v

    // If u is an ancestor of v:
    if (FLU.last_occurrence > FLV.last_occurrence)
        return u;

    // else
    auto best_index =
      m_RMQ.GetMinIndex(FLU.last_occurrence, FLV.first_occurrence);
    return m_euler_tour[best_index];
}
