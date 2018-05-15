#include "Clustering.hpp"
#include "CommonGraphs.hpp"
#include "ConnectedComponents.hpp"
#include "Graph.hpp"
#include "IsSimple.hpp"
#include "TreeAlgorithms.hpp"
#include "sanity_check.hpp"
#include "MinSpanningTree.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(CommonGraphs, ErdosRenyi)
{
    Graph G = graphs::Random(18,0.3);
    ASSERT_EQ(G.num_vertices(),18);
}

TEST(CommonGraphs, RandomNumEdges)
{
    Graph G = graphs::RandomWithSpecifiedNumEdges(10, 8);
    ASSERT_EQ(G.num_edges(), 8);
    ASSERT_EQ(G.num_vertices(), 10);
    ASSERT_TRUE(is_simple(G));

    Graph H = graphs::RandomWithSpecifiedNumEdges(10, 43);
    ASSERT_EQ(H.num_edges(), 43);
    ASSERT_EQ(H.num_vertices(), 10);
    ASSERT_TRUE(is_simple(H));
}

TEST(CommonGraphs, RandomTree)
{
    Graph G = graphs::RandomTree(100);

    ASSERT_EQ(G.num_edges(), 99);
    ASSERT_TRUE(is_tree(G));
    ASSERT_TRUE(is_simple(G));
}

TEST(CommonGraphs, RandomBinaryTree)
{
    Graph G = graphs::RandomBinaryTree(100);

    ASSERT_TRUE(check_graph(G));
    ASSERT_EQ(G.num_edges(), 99);
    ASSERT_TRUE(is_tree(G));
    ASSERT_TRUE(is_simple(G));
}

TEST(CommonGraphs, Complete)
{
    Graph G = graphs::Complete(7);
    ASSERT_EQ(G.num_edges(), 21);
    ASSERT_TRUE(is_simple(G));
}

TEST(CommonGraphs, Path)
{
    Graph G = graphs::Path(8);
    ASSERT_TRUE(is_tree(G));
    for (auto v : G.vertices())
        ASSERT_LE(G.degree(v), 2);
}

TEST(CommonGraphs, Cycle)
{
    Graph G = graphs::Cycle(8);
    ASSERT_TRUE(is_connected(G));
    ASSERT_FALSE(is_tree(G));
    for (auto v : G.vertices())
        ASSERT_LE(G.degree(v), 2);
}

TEST(CommonGraphs, CompleteBipartite)
{
    Graph G = graphs::CompleteBipartite(8, 7);
    ASSERT_TRUE(is_connected(G));
    ASSERT_FALSE(is_tree(G));
    for (auto v : G.vertices())
    {
        ASSERT_LE(G.degree(v), 8);
        ASSERT_GE(G.degree(v), 7);
    }
    ASSERT_EQ(num_triangles(G), 0);
    ASSERT_EQ(G.num_edges(), 7*8);
}

TEST(CommonGraphs,WeightedGrid)
{
    int n = 5;
    int m = 8;
    Graph G = graphs::WeightedGrid(n,m);
    ASSERT_EQ(G.num_vertices(),(n+1)*(m+1));
    ASSERT_EQ(G.num_edges(), n*(m+1) + m*(n+1));
}

TEST(CommonGraphs, AlbertBarabanasi)
{
    int n = 30;
    int k = 3;
    Graph G = graphs::AlbertBarabanasi(n,k);
    ASSERT_EQ(G.num_vertices(),n);
    ASSERT_EQ(G.num_edges(),k*(k-1)/2 + (n-k)*k);
}
