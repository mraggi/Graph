#include "Bipartite.hpp"
#include "BipartiteMatching.hpp"
#include "CommonGraphs.hpp"
#include "Probability.hpp"
#include "TimeHelpers.hpp"
#include "VectorHelpers.hpp"
#include "external/bipartite_matching.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <unordered_set>

using Vertex = BipartiteGraph::Vertex;

void CheckMatching(const BipartiteGraph& G, int expected_size)
{
    BipartiteMatcher M(G);

    ASSERT_EQ(M.size(), expected_size);

    std::set<Vertex> matches;

    for (auto x : G.verticesX())
    {
        auto y = M.MatchX(x);
        if (y != -1)
        {
            ASSERT_EQ(M.MatchY(y), x);
            matches.insert(y);
        }
    }
    ASSERT_EQ(matches.size(), expected_size);

    auto edges = M.Edges();
    auto order = [](const Graph::Edge& A, const Graph::Edge& B) {
        if (A.weight() != B.weight())
            return A.weight() < B.weight();
        if (A.from != B.from)
            return A.from < B.from;
        return A.to < B.to;
    };

    std::set<Graph::Edge, decltype(order)> S(edges.begin(), edges.end(), order);

    ASSERT_EQ(S.size(), matches.size());
}

TEST(BipartiteMatching, Small22)
{
    BipartiteGraph B(2, 2);
    B.add_edges({{0, 0}, {0, 1}, {1, 0}});
    CheckMatching(B, 2);
}

TEST(BipartiteMatching, Small13)
{
    BipartiteGraph B(1, 3);
    B.add_edges({{0, 0}, {0, 1}, {0, 2}});
    CheckMatching(B, 1);
}

TEST(BipartiteMatching, Small24)
{
    BipartiteGraph B(2, 4);
    B.add_edges({{0, 0}, {0, 1}, {1, 0}, {1, 3}});
    CheckMatching(B, 2);
}

TEST(BipartiteMatching, Small55)
{
    BipartiteGraph B(5, 5);
    B.add_edges({{0, 0},
                 {0, 1},
                 {1, 0},
                 {1, 1},
                 {2, 0},
                 {2, 1},
                 {3, 2},
                 {3, 3},
                 {3, 4},
                 {4, 2},
                 {4, 3},
                 {4, 4}});
    CheckMatching(B, 4);
}

TEST(BipartiteMatching, Complete)
{
    for (int i = 0; i < 10; ++i)
    {
        int n = random_int(1, 20);
        int m = random_int(1, 20);
        BipartiteGraph G = graphs::CompleteBipartite(n, m);

        BipartiteMatcher M(G);

        CheckMatching(G, std::min(n, m));
    }
}

TEST(BipartiteMatching, PermutationGraph)
{
    double total_time = 0.0;
    long num = 10;
    for (int i = 0; i < num; ++i)
    {
        int n = random_int(1, 20);
        int m = random_int(1, 20);
        int degreeX = random_int(1, m + 1);

        if (n > m)
            std::swap(n, m);

        BipartiteGraph B(n, m);

        std::vector<Vertex> Y = random_order(B.verticesY());

        // 		std::cout << "Y = " << Y << std::endl;
        for (int x = 0; x < n; ++x)
        {
            auto neighbors_of_x =
              random_sample(std::vector<Vertex>(B.verticesY()), degreeX);

            if (std::count(
                  neighbors_of_x.begin(), neighbors_of_x.end(), Y[x]) == 0)
                neighbors_of_x.push_back(Y[x]);

            for (auto y : neighbors_of_x)
                B.add_edge(x, y);
        }

        Chronometer C;
        CheckMatching(B, n);
        total_time += C.Peek();
    }
    // 	std::cout << "AVG TIME: " << total_time/num << "s" << std::endl;
}

TEST(BipartiteMatching, vsJaheup)
{
    for (int n = 1; n < 20; ++n)
    {
        for (int m = 1; m < 20; ++m)
        {
            auto B = graphs::RandomBipartite(n, m, 1.1/m);
            BipartiteMatcher BM(B);
            VI mr, mc;
            auto size = BipartiteMatching(AdjacencyMatrix(B), mr, mc);
            ASSERT_EQ(size, BM.size());
        }
    }
}
