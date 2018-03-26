#include "CommonGraphs.hpp"
#include "Probability.hpp"
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
		ASSERT_GE(u.weight(), 0);
		ASSERT_GE(v.weight(), 0);
	}
}

TEST(ShortestPaths, Graph1)
{
	Graph G(1);
	auto D = DijkstraDistance(G, 0).distance;
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
	auto D = DijkstraDistance(G, 0).distance;
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

	auto D0 = DijkstraDistance(G, 0, 2).distance;

	ASSERT_EQ(D0.size(), 3);
	ASSERT_EQ(D0[0], 0);
	ASSERT_EQ(D0[1], 10);
	ASSERT_EQ(D0[2], 20);

	auto D1 = DijkstraDistance(G, 1).distance;

	ASSERT_EQ(D1.size(), 3);
	ASSERT_EQ(D1[0], 10);
	ASSERT_EQ(D1[1], 0);
	ASSERT_EQ(D1[2], 10);

	auto D2 = DijkstraDistance(G, 2).distance;

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

	auto D0 = DijkstraDistance(G, 0, 2).distance;

	ASSERT_EQ(D0.size(), 3);
	ASSERT_EQ(D0[0], 0);
	ASSERT_EQ(D0[1], 10);
	ASSERT_EQ(D0[2], 15);

	auto D1 = DijkstraDistance(G, 1).distance;

	ASSERT_EQ(D1.size(), 3);
	ASSERT_EQ(D1[0], 10);
	ASSERT_EQ(D1[1], 0);
	ASSERT_EQ(D1[2], 10);

	auto D2 = DijkstraDistance(G, 2).distance;

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
	int n = 5;
	Graph G = graphs::Grid(n - 1, n - 1);

	auto D = DijkstraDistance(G, 0).distance;

	for (int i = 0; i < n; ++i)
	{
		// 		std::cout << "i = " << i << std::endl;
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

TEST(ShortestPaths, MediumGraph)
{
	Graph G(5);
	G.add_edge(0, 1, 6);
	G.add_edge(0, 2, 3);
	G.add_edge(1, 2, 2);
	G.add_edge(2, 3, 4);
	G.add_edge(1, 3, 1);
	G.add_edge(3, 4, 5);

	auto D = DijkstraDistance(G, 0).distance;
	ASSERT_EQ(D.size(), G.num_vertices());
	ASSERT_EQ(D[0], 0);
	ASSERT_EQ(D[1], 5);
	ASSERT_EQ(D[2], 3);
	ASSERT_EQ(D[3], 6);
	ASSERT_EQ(D[4], 11);

	auto p = DijkstraDistance(G, 0).parent;
	ASSERT_EQ(p.size(), G.num_vertices());
	ASSERT_EQ(p[1], 2);
	ASSERT_EQ(p[2], 0);
	ASSERT_EQ(p[3], 1);
	ASSERT_EQ(p[4], 3);

	auto path = Dijkstra(G, 0, 4);
	ASSERT_EQ(path.size(), 5);
	ASSERT_EQ(path[0], 0);
	ASSERT_EQ(path[1], 2);
	ASSERT_EQ(path[2], 1);
	ASSERT_EQ(path[3], 3);
	ASSERT_EQ(path[4], 4);
}

TEST(ShotestPaths, Cycle)
{
	for (int i = 0; i < 100; ++i)
	{
		int n = random_int(15, 25);
		Graph G = graphs::Cycle(n);

		int u = random_int(0, n);
		int v = random_int(0, n);

		auto P = Dijkstra(G, u, v);

		ASSERT_EQ(P.front(), u);
		ASSERT_EQ(P.back(), v);
		ASSERT_EQ(TotalWeight(P), std::min(std::abs(u - v), n - std::abs(u - v)));
	}
}

TEST(ShotestPaths, Path)
{
	for (int i = 0; i < 100; ++i)
	{
		int n = random_int(15, 25);
		Graph G = graphs::Path(n);

		int u = random_int(0, n);
		int v = random_int(0, n);

		auto P = Dijkstra(G, u, v);

		ASSERT_EQ(P.front(), u);
		ASSERT_EQ(P.back(), v);
		ASSERT_EQ(TotalWeight(P), std::abs(u - v));
	}
}
