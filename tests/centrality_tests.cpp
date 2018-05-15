#include "Centrality.hpp"
#include "NaturalNumber.hpp"
#include "Probability.hpp"
#include "VectorHelpers.hpp"
#include <gtest/gtest.h>
#include <iostream>

Graph GRR()
{
    Graph G(14);
    G.add_edges({{0, 2},  {0, 4},  {0, 6},  {0, 8},  {0, 11},  {1, 3},
                 {1, 5},  {1, 10}, {2, 4},  {2, 5},  {2, 12},  {3, 7},
                 {3, 8},  {3, 9},  {3, 12}, {3, 13}, {4, 7},   {4, 8},
                 {4, 10}, {4, 12}, {4, 13}, {5, 6},  {5, 8},   {5, 9},
                 {5, 11}, {6, 7},  {6, 12}, {6, 13}, {7, 10},  {7, 12},
                 {7, 13}, {8, 11}, {8, 13}, {9, 10}, {10, 11}, {11, 13}});

    return G;
}

Graph H()
{
    Graph G(6);
    G.add_edges({{0, 1}, {1, 2}, {3, 4}, {4, 5}, {1, 4}});

    return G;
}

Graph HourGlass()
{
    Graph G(5);
    G.add_edges({
      {0, 1},
      {0, 2},
      {1, 2},
      {2, 3},
      {2, 4},
      {3, 4},
    });

    return G;
}

using namespace std;

void vecfloat_equal(std::vector<double> A, std::vector<double> B)
{
    ASSERT_EQ(A.size(), B.size());
    for (auto i : indices(A))
    {
        ASSERT_FLOAT_EQ(A[i], B[i]);
    }
}

TEST(Centrality, H)
{
    Graph G = H();
    auto n = G.num_vertices();
    auto e = n - 1;
    vecfloat_equal(centrality::degree(G),
                   {1.0/e, 3.0/e, 1.0/e, 1.0/e, 3.0/e, 1.0/e});

    double r = 0.45454545454545453;
    double s = 0.7142857142857143;

    vecfloat_equal(centrality::closeness(G), {r, s, r, r, s, r});

    double t = 0;
    double q = 0.7;

    vecfloat_equal(centrality::betweenness(G), {t, q, t, t, q, t});
}

TEST(Centrality, HourGlass)
{
    Graph G = HourGlass();

    vecfloat_equal(centrality::degree(G), {0.5, 0.5, 1.0, 0.5, 0.5});

    vecfloat_equal(centrality::closeness(G),
                   {2.0/3.0, 2.0/3.0, 1.0, 2.0/3.0, 2.0/3.0});

    vecfloat_equal(centrality::betweenness(G), {0, 0, 2.0/3.0, 0, 0});
}

TEST(Centrality, Random)
{
    Graph G = GRR();
    vecfloat_equal(centrality::closeness(G),
                   {0.5652173913043478,
                    0.5416666666666666,
                    0.5909090909090909,
                    0.65,
                    0.6842105263157895,
                    0.65,
                    0.6190476190476191,
                    0.65,
                    0.65,
                    0.5416666666666666,
                    0.6190476190476191,
                    0.5909090909090909,
                    0.5909090909090909,
                    0.65});

    vecfloat_equal(centrality::betweenness(G),
                   {0.03287310979618672,
                    0.01282051282051282,
                    0.025934535549920163,
                    0.10072086033624494,
                    0.09521461444538368,
                    0.12132525594064053,
                    0.05042500234807927,
                    0.04363905325443787,
                    0.05630694092232553,
                    0.01282051282051282,
                    0.0744693340847187,
                    0.039377289377289376,
                    0.034188034188034185,
                    0.04347468770545693});
}
