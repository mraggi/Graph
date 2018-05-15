#include "Bipartite.hpp"
#include "CommonGraphs.hpp"
#include "VectorHelpers.hpp"
#include "IsSimple.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(Bipartite, Creation)
{
    BipartiteGraph B(5, 5);
    B.add_edge(0, 0);
    B.add_edge(1, 1);
    ASSERT_EQ(B.num_vertices(), 10);
    // 	ASSERT_EQ(B.num_edges(), 2);
    ASSERT_EQ(B.degreeX(0), 1);
    ASSERT_EQ(B.degreeY(0), 1);
    ASSERT_EQ(B.degreeX(1), 1);
    ASSERT_EQ(B.degreeY(1), 1);
    ASSERT_EQ(B.degreeX(3), 0);
}

TEST(Bipartite, Complete)
{
    Graph G = graphs::CompleteBipartite(4, 8);
    BipartiteGraph B(G);

    ASSERT_EQ(B.num_vertices(), 12);
    for (auto v : B.verticesX())
    {
        ASSERT_EQ(B.degreeX(v), B.num_verticesY());
        ASSERT_EQ(8, B.num_verticesY());
    }

    for (auto v : B.verticesY())
    {
        ASSERT_EQ(B.degreeY(v), B.num_verticesX());
        ASSERT_EQ(4, B.num_verticesX());
    }
    
    Graph W = B.GetGraph();
    
    ASSERT_EQ(W.num_vertices(),12);
    ASSERT_EQ(W.num_edges(),32);
    ASSERT_TRUE(is_simple(W));
    
    for (auto x : B.verticesX())
    {
        for (auto y : B.neighborsY(x))
        {
            ASSERT_TRUE(W.get_neighbor(x,y+B.num_verticesX()) != W.neighbors(x).end());
        }
    }
    
}

TEST(Bipartite, SortNeighbors)
{
    BipartiteGraph G(4,5);
    G.add_edge(0,3);
    G.add_edge(2,4);
    G.add_edge(1,1);
    G.add_edge(3,1);
    G.add_edge(2,3);
    G.add_edge(2,2);
    G.add_edge(2,1);
    G.add_edge(0,4);
    
    G.sort_neighbors();
    
    for (auto x : G.verticesX())
    {
        ASSERT_TRUE(std::is_sorted(G.neighborsX(x).begin(), G.neighborsX(x).end()));
    }
    
    for (auto y : G.verticesY())
    {
        ASSERT_TRUE(std::is_sorted(G.neighborsY(y).begin(), G.neighborsY(y).end()));
    }
}
