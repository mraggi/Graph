#include "CommonGraphs.hpp"
#include "ShortestPaths.hpp"
#include <gtest/gtest.h>
#include <iostream>

void check_path(const Graph& G, const Path& P)
{
	for (int i = 0; i + 1 < P.size(); ++i)
	{
		auto u = P[i];
		auto v = P[i + 1];

		ASSERT_TRUE(G.is_neighbor(u, v));
	}
}

TEST(ShortestPaths, Graph1)
{
	Graph G(1);
	auto D = DijkstraCost(G, 0);
	ASSERT_EQ(D.size(), 1);
	ASSERT_EQ(D[0], 0);

	auto P = Dijkstra(G, 0, 0);
	ASSERT_EQ(P.size(), 1);
	ASSERT_EQ(P.back(), 0);
}

TEST(ShortestPaths, Graph2)
{
	Graph G(2);
	G.add_edge(0, 1, 78);
	auto D = DijkstraCost(G, 0);
	ASSERT_EQ(D.size(), 2);
	ASSERT_EQ(D[0], 0);
	ASSERT_EQ(D[1], 78);

	auto P = Dijkstra(G, 0, 1);
	ASSERT_EQ(P.size(), 2);
	ASSERT_EQ(P.front(), 0);
	ASSERT_EQ(P.back(), 1);
}

TEST(ShortestPaths, Graph3)
{
	Graph G(3);
	G.add_edge(0, 1, 10);
	G.add_edge(1, 2, 10);
	G.add_edge(0, 2, 25);

	auto D0 = DijkstraCost(G, 0, 2);

	ASSERT_EQ(D0.size(), 3);
	ASSERT_EQ(D0[0], 0);
	ASSERT_EQ(D0[1], 10);
	ASSERT_EQ(D0[2], 20);

	auto D1 = DijkstraCost(G, 1);

	ASSERT_EQ(D1.size(), 3);
	ASSERT_EQ(D1[0], 10);
	ASSERT_EQ(D1[1], 0);
	ASSERT_EQ(D1[2], 10);

	auto D2 = DijkstraCost(G, 2);

	ASSERT_EQ(D2.size(), 3);
	ASSERT_EQ(D2[0], 20);
	ASSERT_EQ(D2[1], 10);
	ASSERT_EQ(D2[2], 0);
}

TEST(ShortestPaths, Graph3b)
{
	Graph G(3);
	G.add_edge(0, 1, 10);
	G.add_edge(1, 2, 10);
	G.add_edge(0, 2, 15);

	auto D0 = DijkstraCost(G, 0, 2);

	ASSERT_EQ(D0.size(), 3);
	ASSERT_EQ(D0[0], 0);
	ASSERT_EQ(D0[1], 10);
	ASSERT_EQ(D0[2], 15);

	auto D1 = DijkstraCost(G, 1);

	ASSERT_EQ(D1.size(), 3);
	ASSERT_EQ(D1[0], 10);
	ASSERT_EQ(D1[1], 0);
	ASSERT_EQ(D1[2], 10);

	auto D2 = DijkstraCost(G, 2);

	ASSERT_EQ(D2.size(), 3);
	ASSERT_EQ(D2[0], 15);
	ASSERT_EQ(D2[1], 10);
	ASSERT_EQ(D2[2], 0);
}

long TotalWeight(const Path& P)
{
	long w = 0;
	for (auto p : P)
	{
		w += p.weight();
	}
	return w;
}

TEST(ShortestPaths, GridGraph)
{
	using std::cout;
	using std::endl;
	int n = 5;
	Graph G = graphs::Grid(n - 1, n - 1);

	auto D = DijkstraCost(G, 0);

	for (int i = 0; i < n; ++i)
	{
		auto P = Dijkstra(G, 0, i);
		check_path(G, P);
		ASSERT_EQ(TotalWeight(P), D[i]);
		ASSERT_EQ(P.front(), 0);
		ASSERT_EQ(P.back(), i);
	}

	for (int i = 0; i < n; ++i)
	{
		ASSERT_EQ(std::count(D.begin(), D.end(), i), i + 1);
	}
}

// TEST(ShortestPaths, MediumGraph)
// {
// 	Graph G(8);
// 	G.add_edge(0,1,2);
// }
