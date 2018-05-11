#include "CommonGraphs.hpp"
#include "ConnectedComponents.hpp"
#include "VectorHelpers.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(ConnectedComponents, Graph0)
{
    Graph G(0);
    auto CC = connected_components(G);
    ASSERT_TRUE(CC.empty());
    ASSERT_TRUE(is_connected(G));
    ASSERT_EQ(num_connected_components(G), 0);
}

TEST(ConnectedComponents, Graph1)
{
    Graph G(1);
    auto CC = connected_components(G);
    ASSERT_EQ(CC[0], 0);
    ASSERT_EQ(CC.size(), 1);
    ASSERT_TRUE(is_connected(G));
    ASSERT_EQ(num_connected_components(G), 1);
}

TEST(ConnectedComponents, Graph5)
{
    Graph G(5);
    G.add_edge(0, 1);
    G.add_edge(2, 3);
    auto CC = connected_components(G);
    std::vector<int> correcto = {0, 0, 1, 1, 2};
    ASSERT_EQ(CC, correcto);
    ASSERT_EQ(num_connected_components(G), 3);
    ASSERT_FALSE(is_connected(G));
}

TEST(ConnectedComponents, Graph5Vacio)
{
    Graph G(5);
    auto CC = connected_components(G);
    std::vector<int> correcto = {0, 1, 2, 3, 4};
    ASSERT_EQ(CC, correcto);
    ASSERT_EQ(num_connected_components(G), 5);
    ASSERT_FALSE(is_connected(G));
}

TEST(ConnectedComponents, Petersen)
{
    Graph G = graphs::Petersen();
    auto CC = connected_components(G);
    std::vector<int> correcto(10, 0);
    ASSERT_EQ(CC, correcto);
    ASSERT_EQ(num_connected_components(G), 1);
    ASSERT_TRUE(is_connected(G));
}

TEST(ConnectedComponents, Path)
{
    Graph G = graphs::Path(4);
    auto CC = connected_components(G);
    ASSERT_EQ(num_connected_components(G), 1);
    ASSERT_TRUE(is_connected(G));
}

TEST(ConnectedComponents, Cycle)
{
    Graph G = graphs::Cycle(4);
    auto CC = connected_components(G);
    ASSERT_EQ(num_connected_components(G), 1);
    ASSERT_TRUE(is_connected(G));
}

TEST(ConnectedComponents, Tree)
{
    for (int n = 1; n < 8; ++n)
    {
        Graph G = graphs::RandomTree(n);
        auto CC = connected_components(G);
        ASSERT_EQ(num_connected_components(G), 1);
        ASSERT_TRUE(is_connected(G));
    }
}
