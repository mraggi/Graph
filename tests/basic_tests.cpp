#include "CommonGraphs.hpp"
#include "Graph.hpp"
#include "VectorHelpers.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(Graph, Creation)
{
	Graph G(5);
	ASSERT_EQ(G.num_vertices(), 5);
	auto new_vertex = G.add_vertex();
	ASSERT_EQ(new_vertex, 5);
	for (auto v : G.vertices())
		ASSERT_EQ(G.degree(v), 0);
}

TEST(Graph, Degree)
{
	Graph G(5);
	for (auto v : G.vertices())
		ASSERT_EQ(G.degree(v), 0);

	G.add_edge(0, 1);
	G.add_edge(0, 2);
	G.add_edge(0, 3);

	ASSERT_EQ(G.degree(0), 3);
	ASSERT_EQ(G.degree(1), 1);
	ASSERT_EQ(G.degree(2), 1);
	ASSERT_EQ(G.degree(3), 1);
}

TEST(Graph, AddEdge)
{
	Graph G(3);
	G.add_edge(0, 1);
	ASSERT_EQ(G.num_edges(), 1);

	G.add_edge_no_repeat(0, 1);
	ASSERT_EQ(G.num_edges(), 1);

	G.add_edge(0, 1);
	ASSERT_EQ(G.num_edges(), 2);

	G.add_edge_no_repeat(0, 1);
	ASSERT_EQ(G.num_edges(), 2);
}

TEST(Graph, Vertices)
{
	Graph G(10);
	int i = 0;
	for (auto v : G.vertices())
	{
		ASSERT_EQ(v, i);
		++i;
	}
}

TEST(Graph, Weights)
{
	Graph G(4);
	G.add_edge(0, 1, 10);
	G.add_edge(1, 2, 11);
	G.add_edge(2, 3, 12);

	ASSERT_EQ(G.edge_value(0, 1), 10);
	ASSERT_EQ(G.edge_value(1, 0), 10);

	ASSERT_EQ(G.edge_value(1, 2), 11);
	ASSERT_EQ(G.edge_value(2, 1), 11);

	ASSERT_EQ(G.edge_value(2, 3), 12);
	ASSERT_EQ(G.edge_value(3, 2), 12);
}

TEST(Graph, Sort)
{
	Graph G = graphs::Petersen(); // replace by "random graph"
	G.sort_neighbors();
	for (auto v : G.vertices())
	{
		ASSERT_TRUE(std::is_sorted(G.neighbors(v).begin(), G.neighbors(v).end()));
	}
}

TEST(Graph, MakeSimple)
{
	Graph G(5); // replace by "random graph"
	G.add_edge(0, 1);
	G.add_edge(0, 1);
	G.add_edge(1, 0);
	G.add_edge(2, 1);
	G.add_edge(4, 1);
	G.add_edge(1, 4);
	G.add_edge(0, 1);
	G.add_edge(2, 3);
	G.add_edge(3, 2);
	G.add_edge(3, 2);
	G.add_edge(4, 0);
	G.add_edge(0, 0);
	G.add_edge(0, 0);
	G.add_edge(1, 1);
	G.add_edge(2, 2);
	G.add_edge(3, 3);

	G.make_simple();

	for (auto v : G.vertices())
	{
		std::set<int> neighbors;
		for (auto u : G.neighbors(v))
		{
			ASSERT_TRUE(u != v); // no loops
			neighbors.insert(u);
		}
		ASSERT_EQ(neighbors.size(), G.degree(v));
	}
}

TEST(Graph, GetNeighbor)
{
	// 	Graph G = graphs::RandomGraph(20,0.5);

	Graph G = graphs::Petersen();
	G.add_edges({{1, 0}, {0, 2}, {2, 4}, {3, 5}, {3, 1}, {8, 4}, {1, 9}});

	for (auto v : G.vertices())
	{
		for (auto u : G.vertices())
		{
			auto it = G.get_neighbor(u, v);
			if (G.is_neighbor(u, v))
			{
				ASSERT_EQ(*it, v);
			}
			else
			{
				ASSERT_EQ(it, G.neighbors(u).end());
			}
		}
	}

	auto sortedG = G;

	sortedG.sort_neighbors();

	for (auto v : sortedG.vertices())
	{
		for (auto u : sortedG.vertices())
		{
			auto it = sortedG.get_neighbor(u, v);
			if (sortedG.is_neighbor(u, v))
			{
				ASSERT_EQ(*it, v);
			}
			else
			{
				ASSERT_EQ(it, sortedG.neighbors(u).end());
			}
		}
	}
}

TEST(Graph, PetersenGraph)
{
	auto G = graphs::Petersen();

	for (auto v : G.vertices())
		ASSERT_EQ(G.degree(v), 3);
}
