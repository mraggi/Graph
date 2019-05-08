#include "CommonGraphs.hpp"
#include "Probability.hpp"
#include <unordered_set>

namespace graphs
{

using Vertex = Graph::Vertex;

Graph Petersen()
{
    Graph G(10);

    G.add_edges({{0, 1},
                 {0, 4},
                 {0, 5},
                 {1, 2},
                 {1, 6},
                 {2, 3},
                 {2, 7},
                 {3, 4},
                 {3, 8},
                 {4, 9},
                 {5, 7},
                 {5, 8},
                 {6, 8},
                 {6, 9},
                 {7, 9}});

    return G;
}

Graph Path(int n)
{
    Graph G(n + 1);
    for (Vertex i = 0; i < n; ++i)
        G.add_edge(i, i + 1);
    return G;
}

Graph Cycle(int n)
{
    Graph G = Path(n - 1);
    if (n > 2)
    {
        G.add_edge(0, n - 1);
    }
    return G;
}

Graph Complete(int n)
{
    Graph G(n);

    for (Vertex i = 0; i + 1 < n; ++i)
    {
        for (Vertex j = i + 1; j < n; ++j)
        {
            G.add_edge(i, j);
        }
    }

    return G;
}

Graph Random(int n, double p)
{
    Graph G(n);

    for (auto i : G.vertices())
    {
        for (int j = i + 1; j < G.num_vertices(); ++j)
        {
            if (probability_of_true(p))
                G.add_edge(i, j);
        }
    }
    return G;
}

Graph RandomWeighted(int n, double p)
{
    Graph G(n);

    for (auto u : G.vertices())
    {
        for (Vertex v = u + 1; v < G.num_vertices(); ++v)
        {
            if (probability_of_true(p))
            {
                G.add_edge(u, v, random_int(0, 100));
            }
        }
    }
    return G;
}

struct paircommutativehash
{
public:
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U>& x) const
    {
        return std::hash<T>()(x.first)^std::hash<U>()(x.second);
    }
};

struct paircommutativeequal
{
public:
    template <typename T, typename U>
    bool operator()(const std::pair<T, U>& A, const std::pair<T, U>& B) const
    {
        return (A.first == B.first && A.second == B.second) ||
          (A.first == B.second && A.second == B.first);
    }
};

Graph RandomWithSpecifiedNumEdges(int num_verts, int num_edges)
{
    Graph G(num_verts);

    std::int64_t total = std::int64_t(num_verts)*(num_verts - 1)/2;

    if (num_edges > total)
        return G; // error!!

    if (num_edges < total/2)
    {
        std::unordered_set<std::pair<int, int>,
                           paircommutativehash,
                           paircommutativeequal>
          AddedAlready;
        while (G.num_edges() < num_edges)
        {
            auto u = random_int<Vertex>(0, num_verts);
            auto v = random_int<Vertex>(0, num_verts);
            if (u == v)
                continue;
            if (AddedAlready.emplace(u, v).second)
            {
                G.add_edge(u, v);
            }
        }
    }
    else
    {
        using edge = std::pair<Vertex, Vertex>;
        std::vector<edge> all;
        all.reserve(total);
        for (Vertex u = 0; u < num_verts; ++u)
        {
            for (Vertex v = u + 1; v < num_verts; ++v)
            {
                all.emplace_back(u, v);
            }
        }

        std::shuffle(all.begin(), all.end(), random_engine());
        for (int i = 0; i < num_edges; ++i)
            G.add_edge(all[i].first, all[i].second);
    }

    return G;
}

Graph Grid(int n, int m)
{
    Graph G((n + 1)*(m + 1));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            Vertex v = i*(m + 1) + j;
            G.add_edge(v, v + 1, random_int(0,1000));
            G.add_edge(v, v + m + 1, random_int(0,1000));
        }
    }

    for (int j = 0; j < m; ++j)
    {
        Vertex v = n*(m + 1) + j;
        G.add_edge(v, v + 1, random_int(0,1000));
    }

    for (int i = 0; i < n; ++i)
    {
        Vertex v = i*(m + 1) + m;
        G.add_edge(v, v + m + 1, random_int(0,1000));
    }

    return G;
}

Graph WeightedGrid(int n, int m)
{
    Graph G((n + 1)*(m + 1));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            Vertex v = i*(m + 1) + j;
            G.add_edge(v, v + 1, random_int(0, 100));
            G.add_edge(v, v + m + 1, random_int(0, 100));
        }
    }

    for (int j = 0; j < m; ++j)
    {
        Vertex v = n*(m + 1) + j;
        G.add_edge(v, v + 1, random_int(0, 100));
    }

    for (int i = 0; i < n; ++i)
    {
        Vertex v = i*(m + 1) + m;
        G.add_edge(v, v + m + 1, random_int(0, 100));
    }

    return G;
}

Graph RandomTree(int n)
{
    Graph G(n);

    if (n < 2)
        return G;

    G.add_edge(0, 1);

    for (Vertex v = 2; v < n; ++v)
    {
        auto u = random_int<Vertex>(0, v);
        G.add_edge(u, v);
    }

    return G;
}

Graph CompleteBipartite(int n, int m)
{
    Graph G(n + m);
    for (Vertex x = 0; x < n; ++x)
    {
        for (Vertex y = n; y < m + n; ++y)
        {
            G.add_edge(x, y);
        }
    }
    return G;
}

void ProduceRandomBinaryTreeEdges(Graph* G, Vertex start, Vertex end)
{
    if (end - start < 2)
        return;

    Vertex mid = random_int(start + 1, end);

    // [start+1,mid)----- start ----- [mid,end)

    if (mid != start + 1)
    {
        G->add_edge(start, start + 1);
        ProduceRandomBinaryTreeEdges(G, start + 1, mid);
    }

    if (mid != end)
    {
        G->add_edge(start, mid);
        ProduceRandomBinaryTreeEdges(G, mid, end);
    }
    // 	G->make_simple();
}

Graph RandomBinaryTree(int n)
{
    Graph G(n);
    ProduceRandomBinaryTreeEdges(&G, 0, n);
    return G;
}

Graph AlbertBarabanasi(int n, int k)
{
    Graph G(n);

    // complete graph in [0,k)
    for (int i = 0; i < k; ++i)
    {
        for (int j = i + 1; j < k; ++j)
        {
            G.add_edge(i, j);
        }
    }

    std::vector<int> population(k);
    population.reserve(n);

    std::iota(population.begin(), population.end(), 0);

    for (int i = k; i < n; ++i)
    {
        auto Neighs = random_sample(population, k);

        for (auto j : Neighs)
            G.add_edge(i, j);
        population.emplace_back(i);
    }

    return G;
}

Graph BalancedBinaryTree(int n)
{
    Graph G(n);
    auto left_child = [](Vertex v) { return 2*v + 1; };
    auto right_child = [](Vertex v) { return 2*v + 2; };

    for (auto v : G.vertices())
    {
        auto L = left_child(v);
        auto R = right_child(v);
        if (L < G.num_vertices())
            G.add_edge(v, L);
        if (R < G.num_vertices())
            G.add_edge(v, R);
    }

    return G;
}

BipartiteGraph RandomBipartite(int n, int m, double p)
{
    BipartiteGraph B(n, m);

    for (auto x : B.verticesX())
    {
        for (auto y : B.verticesY())
        {
            if (probability_of_true(p))
                B.add_edge(x, y);
        }
    }

    return B;
}

} // namespace graphs
