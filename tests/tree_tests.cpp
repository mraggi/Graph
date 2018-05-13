#include "CommonGraphs.hpp"
#include "LCA.hpp"
#include "PrintUtils.hpp"
#include "Probability.hpp"
#include "TreeAlgorithms.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(TreeAlgorithms, is_tree)
{
    for (int i = 0; i < 10; ++i)
    {
        Graph P = graphs::Path(random_int(1, 100));
        Graph C = graphs::Cycle(random_int(3, 100));
        Graph T = graphs::RandomTree(random_int(1, 100));
        Graph B = graphs::RandomBinaryTree(random_int(1, 10));

        ASSERT_TRUE(is_tree(P));
        ASSERT_FALSE(is_tree(C));
        ASSERT_TRUE(is_tree(T));
        ASSERT_TRUE(is_tree(B));
    }
}

TEST(TreeAlgorithms, SetRootPath)
{
    Graph P = graphs::Path(random_int(1, 100));

    auto parents = set_root(P, 0);

    for (auto v : P.vertices())
    {
        if (v == 0)
            continue;
        ASSERT_EQ(parents[v], v - 1);
    }
}

TEST(TreeAlgorithms, SetRootStar)
{
    Graph G(10);
    for (int i = 0; i < 10; ++i)
    {
        if (i != 4)
            G.add_edge(i, 4);
    }

    auto parents = set_root(G, 4);

    for (auto v : G.vertices())
    {
        if (v == 4)
            continue;
        ASSERT_EQ(parents[v], 4);
    }
}

TEST(TreeAlgorithms, HeightMapPath)
{
    Graph P = graphs::Path(random_int(1, 100));

    auto levels = height_map(P, 0);

    for (auto v : P.vertices())
    {
        ASSERT_EQ(levels[v], v);
    }
}

TEST(TreeAlgorithms, HeightMapStar)
{
    Graph G(10);
    for (int i = 0; i < 10; ++i)
    {
        if (i != 4)
            G.add_edge(i, 4);
    }

    auto level = height_map(G, 4);

    for (auto v : G.vertices())
    {
        if (v == 4)
        {
            ASSERT_EQ(level[v], 0);
            continue;
        }
        ASSERT_EQ(level[v], 1);
    }
}

TEST(TreeAlgorithms, LCASparseStar)
{
    Graph G(10);
    for (int i = 0; i < 10; ++i)
    {
        if (i != 4)
            G.add_edge(i, 4);
    }

    LCAWithPowersOfTwo LCA(G, 4);

    ASSERT_EQ(LCA.FindLCA(0, 1), 4);
    ASSERT_EQ(LCA.FindLCA(3, 4), 4);
    ASSERT_EQ(LCA.FindLCA(6, 6), 6);
}

TEST(TreeAlgorithms, LCASparsePath)
{
    using Vertex = Graph::Vertex;
    for (int i = 0; i < 10; ++i)
    {
        Graph G = graphs::Path(random_int(1, 100));
        auto root = random_int<Vertex>(0, G.num_vertices());

        LCAWithPowersOfTwo LCA(G, root);

        for (auto u : G.vertices())
        {
            for (auto v = u + 1; v < G.num_vertices(); ++v)
            {
                if (v <= root)
                    ASSERT_EQ(LCA.FindLCA(u, v), v);
                else if (u <= root)
                    ASSERT_EQ(LCA.FindLCA(u, v), root);
                else
                    ASSERT_EQ(LCA.FindLCA(u, v), u);
            }
        }
    }
}

TEST(TreeAlgorithms, LCABalancedBinary)
{
    Graph G = graphs::BalancedBinaryTree(32);

    LCAWithPowersOfTwo LCA(G, 0);

    ASSERT_EQ(LCA.FindLCA(1, 2), 0);
    ASSERT_EQ(LCA.FindLCA(1, 8), 1);
    ASSERT_EQ(LCA.FindLCA(1, 6), 0);
    ASSERT_EQ(LCA.FindLCA(7, 8), 3);
    ASSERT_EQ(LCA.FindLCA(8, 9), 1);
}

#include "VectorHelpers.hpp"

TEST(TreeAlgorithms, LCAComparisonWithBF)
{
    for (int i = 0; i < 100; ++i)
    {
        int n = random_int(1, 35);
        auto G = graphs::RandomTree(n);
        int root = random_int(0, n);

        LCAWithPowersOfTwo LCA(G, root);
        auto parents = LCA.GetParents();
        ASSERT_EQ(parents, set_root(G, root));

        for (int w = 0; w < 100; ++w)
        {
            int u = random_int(0, n);
            int v = random_int(0, n);
            auto fast_lca = LCA.FindLCA(u, v);
            auto slow_lca = lowest_common_ancestor_naive(parents, u, v);

            ASSERT_EQ(fast_lca, slow_lca);
        }
    }
}

TEST(TreeAlgorithms, EulerTour)
{
    Graph G(12);
    G.add_edge(0, 1);
    G.add_edge(1, 2);
    G.add_edge(2, 4);
    G.add_edge(2, 5);
    G.add_edge(5, 8);
    G.add_edge(5, 9);
    G.add_edge(5, 10);
    G.add_edge(1, 3);
    G.add_edge(3, 6);
    G.add_edge(6, 11);
    G.add_edge(3, 7);
    G.sort_neighbors();
    LCAWithRMQ L(G, 0);

    // 	std::cout << std::vector<int>(natural_number(L.get_euler_tour().size()))
    // << std::endl; 	std::cout << L.get_euler_tour() << std::endl; 	std::cout
    // << L.get_height_map() << std::endl; 	int i = 0; 	for (auto t :
    // L.get_first_and_last_occurrences())
    // 	{
    // 		std::cout << i << ": " << t.first_occurrence << " " <<
    // t.last_occurrence << std::endl;
    // 		++i;
    // 	}

    ASSERT_EQ(L.get_euler_tour().size(), 2*G.num_vertices() - 1);
    ASSERT_EQ(L.get_height_map().size(), 2*G.num_vertices() - 1);
}

TEST(TreeAlgorithms, LCARMQ)
{
    for (int i = 0; i < 100; ++i)
    {
        int n = random_int(1, 40);
        auto G = graphs::RandomTree(n);
        int root = random_int(0, n);

        LCAWithRMQ LCAR(G, root);
        LCAWithPowersOfTwo LCA2(G, root);

        for (int w = 0; w < 100; ++w)
        {
            int u = random_int(0, n);
            int v = random_int(0, n);
            auto rmq_lca = LCAR.FindLCA(u, v);
            auto pow2_lca = LCA2.FindLCA(u, v);

            ASSERT_EQ(rmq_lca, pow2_lca);
        }
    }
}
