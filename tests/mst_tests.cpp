#include "MinSpanningTree.hpp"
#include "VectorHelpers.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(MST, Prim0)
{
	Graph G(0);
	auto  T = prim(G);
	ASSERT_TRUE(T.empty());
}

TEST(MST, Prim1)
{
	Graph G(1);
	auto  T = prim(G);
	ASSERT_TRUE(T.empty());
}

TEST(MST, Prim2)
{
	Graph G(2);
	G.add_edge(0, 1, 17);
	auto T = prim(G);
	ASSERT_EQ(T.size(), G.num_vertices() - 1);
	ASSERT_EQ(T.back(), Graph::Edge(0, 1, 17));
}

TEST(MST, Prim5)
{
	Graph G(5);
	G.add_edges(
	  {{0, 1, 4}, {0, 4, 2}, {0, 3, 3}, {2, 3, 6}, {2, 1, 5}, {2, 4, 1}, {4, 1, 8}, {3, 4, 7}});
	auto T = prim(G);
	ASSERT_EQ(T.size(), G.num_vertices() - 1);

	std::vector<Graph::Edge> Correct = {{2, 4, 1}, {4, 0, 2}, {3, 0, 3}, {0, 1, 4}};
	ASSERT_EQ(T.size(), Correct.size());
	for (auto& e : T)
	{
		auto it = std::find(Correct.begin(), Correct.end(), e);
		ASSERT_NE(it, Correct.end());
	}
}
