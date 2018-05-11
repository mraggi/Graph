#pragma once

#include "Bipartite.hpp"

class BipartiteMatcher
{
public:
    using Vertex = BipartiteGraph::Vertex;
    using Edge = Graph::Edge;

    BipartiteMatcher(const BipartiteGraph& G);

    Vertex MatchX(Vertex x) const { return m_Xmatches[x]; }
    Vertex MatchY(Vertex y) const { return m_Ymatches[y]; }

    int size() const { return m_size; }
    std::vector<Edge> Edges() const;

private:
    void CreateInitialMatching(const BipartiteGraph& G);

    // returns false if no augmenting path was found
    void Augment(const BipartiteGraph& G);
    bool FindAugmentingPath(const BipartiteGraph& G, Vertex x);

    void ApplyAugmentingPath(Vertex y, const std::vector<Vertex>& parent);

    int m_size{0};
    std::vector<Vertex> m_Xmatches{}; // -1 if not matched
    std::vector<Vertex> m_Ymatches{}; // -1 if not matched

    std::vector<Vertex> m_unmatched_in_X{};
};
