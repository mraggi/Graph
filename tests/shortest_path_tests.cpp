#include "CommonGraphs.hpp"
#include "Probability.hpp"
#include "ShortestPaths.hpp"
#include <gtest/gtest.h>
#include <iostream>

template <class Path>
void check_path(const Graph& G, const Path& P)
{
    for (size_t i = 0; i + 1 < P.size(); ++i)
    {
        auto u = P[i];
        auto v = P[i + 1];

        ASSERT_TRUE(G.is_neighbor(u, v));
        ASSERT_GE(u.weight(), 0);
        ASSERT_GE(v.weight(), 0);
    }
}

template <class Path>
long TotalWeight(const Path& P)
{
    long w = 0;
    for (auto p : P)
    {
        w += p.weight();
    }
    return w;
}

void check_dijkstra(const Graph& G,
                    Vertex origin,
                    std::vector<Distance> expected_distances)
{
    DijkstraSearcher DS(G, origin);
    ASSERT_EQ(expected_distances.size(), G.num_vertices());
    ASSERT_EQ(expected_distances, DS.Distances());

    for (auto v : G.vertices())
    {
        auto P = DS.GetPath(v);
        ASSERT_EQ(P.front(), origin);
        ASSERT_EQ(P.back(), v);
        check_path(G, P);
        auto pathweight = TotalWeight(P);
        auto expected_weight = DS.Distances()[v];
        ASSERT_TRUE((pathweight == 0 && expected_weight == INF) ||
                    (pathweight == expected_weight));
    }
}

TEST(ShortestPaths, Graph1)
{
    Graph G(1);
    check_dijkstra(G, 0, {0});
}

TEST(ShortestPaths, Graph2)
{
    Graph G(2);
    G.add_edge(0, 1, 78);
    check_dijkstra(G, 0, {0, 78});
    check_dijkstra(G, 1, {78, 0});
}

TEST(ShortestPaths, Graph3)
{
    Graph G(3);
    G.add_edge(0, 1, 10);
    G.add_edge(1, 2, 10);
    G.add_edge(0, 2, 25);

    check_dijkstra(G, 0, {0, 10, 20});
    check_dijkstra(G, 1, {10, 0, 10});
    check_dijkstra(G, 2, {20, 10, 0});
}

TEST(ShortestPaths, Graph3b)
{
    Graph G(3);
    G.add_edge(0, 1, 10);
    G.add_edge(1, 2, 10);
    G.add_edge(0, 2, 15);

    check_dijkstra(G, 0, {0, 10, 15});
    check_dijkstra(G, 1, {10, 0, 10});
    check_dijkstra(G, 2, {15, 10, 0});
}

TEST(ShortestPaths, GridGraph)
{
    int n = 5;
    Graph G = graphs::Grid(n - 1, n - 1);

    auto DS = DijkstraSearcher(G, 0);

    auto D = DS.Distances();
    for (int i = 0; i < n; ++i)
    {
        auto P = DS.GetPath(i);
        check_path(G, P);
        ASSERT_EQ(TotalWeight(P), D[i]);
        ASSERT_EQ(P.front(), 0);
        ASSERT_EQ(P.back(), i);
    }
    int i = 0;
    for (auto d : D)
    {
        std::cout << i << ' ' << d << std::endl;
        ++i;
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

    check_dijkstra(G, 0, {0, 5, 3, 6, 11});
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
        ASSERT_EQ(TotalWeight(P),
                  std::min(std::abs(u - v), n - std::abs(u - v)));
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

TEST(ShortestPaths, Astar)
{
    for (int i = 0; i < 100; ++i)
    {
        int n = random_int(15, 25);
        double p = random_real(0.0, 1.0);
        Graph G = graphs::RandomWeighted(n, p);
        Vertex u = random_int(0, n);
        Vertex v = random_int(0, n);
        auto P = Dijkstra(G, u, v);
        auto Astar = AstarSearcher(G, u, v, [](Vertex w) { return 0; });
        auto P2 = Astar.GetPath();

        check_path(G, P2);
        ASSERT_EQ(TotalWeight(P), TotalWeight(P2));
        if (Astar.Distances()[v] != INF)
        {
            ASSERT_EQ(TotalWeight(P), Astar.Distances()[v]);
        }
    }
}
