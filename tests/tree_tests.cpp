#include "CommonGraphs.hpp"
#include "Probability.hpp"
#include "TreeAlgorithms.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(TreeAlgorithms, is_tree)
{
	Graph P = graphs::Path(random_int(1,100));
	Graph C = graphs::Cycle(random_int(1,100));
	Graph T = graphs::RandomTree(random_int(1,100));
	Graph B = graphs::RandomBinaryTree(random_int(1,10));
	
	ASSERT_TRUE(is_tree(P));
	ASSERT_FALSE(is_tree(C));
	ASSERT_TRUE(is_tree(T));
	ASSERT_TRUE(is_tree(B));
}

TEST(TreeAlgorithms, SetRootPath)
{
	Graph P = graphs::Path(random_int(1,100));
	
	auto parents = set_root(P,0);

	for (auto v : P.vertices())
	{
		if (v == 0)
			continue;
		ASSERT_EQ(parents[v],v-1);
	}
	
}

TEST(TreeAlgorithms, SetRootStar)
{
	Graph G(10);
	for (int i = 0; i < 10; ++i)
	{
		if (i != 4)
			G.add_edge(i,4);
	}
	
	auto parents = set_root(G,4);
	
	for (auto v : G.vertices())
	{
		if (v == 4)
			continue;
		ASSERT_EQ(parents[v],4);
	}
	
}


