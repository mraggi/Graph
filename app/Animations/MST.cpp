#include "MST.hpp"
#include "CommonGraphs.hpp"
#include "Graph.hpp"
#include "GraphApp.hpp"
#include "Misc.hpp"
#include "PrintUtils.hpp"
#include "Probability.hpp"
#include "disjoint_sets.hpp"

#include <queue>

struct by_reverse_weight
{
    using Edge = Graph::Edge;
    bool operator()(const Edge& a, const Edge& b)
    {
        return a.weight() > b.weight();
    }
};

std::vector<sf::Color> neighbor_colors(const Graph& G, Graph::Vertex v)
{
    std::vector<sf::Color> result;
    for (auto u : G.neighbors(v))
    {
        Graph::Edge E(v, u, u.weight());
        result.emplace_back(APP.edge_colors[E]);
    }
    return result;
}

void AnimatePrim()
{
    const real animation_speed = 0.03;

    using Edge = Graph::Edge;
    // 	using Vertex = Graph::Vertex;

    APP.ClearToDefaults();

    APP.GUI.AddMessage("Starting Prim's Algorithm. Press [Space] to continue!");

    auto G = APP.GetGraph().GetGraph();

    auto& Prim = APP.CreateAnimation();
    Prim.PauseAfterEveryScene(true);

    const auto grey = sf::Color(120, 120, 120);
    const auto black = sf::Color(36, 36, 36);
    APP.default_edge_color = grey;
    APP.default_vertex_color = grey;

    auto n = G.num_vertices();
    auto num_tree_edges = n - 1;

    if (n == 0)
        return;

    std::vector<char> explored(n, 0);

    std::priority_queue<Edge, std::vector<Edge>, by_reverse_weight>
      EdgesToExplore;

    explored[0] = 1;

    Prim.AddScene(APP.vertex_colors[0], sf::Color::Blue, animation_speed)
      ->AddStartMessage(APP.GUI, "Considering vertex 0", sf::Color::Blue);

    // 	auto E0 = neighbor_colors(G,0);
    // 	auto E1 = std::vector<sf::Color>(E0.size(),sf::Color::Yellow);
    // 	Prim.AddScene(E0,E1,5.0);

    for (auto v : G.neighbors(0))
    {
        // 		auto E = Edge(0, v, v.weight());
        EdgesToExplore.emplace(0, v, v.weight());
    }

    while (!EdgesToExplore.empty())
    {
        Edge s = EdgesToExplore.top();
        EdgesToExplore.pop();
        auto S =
          Prim.AddScene(APP.edge_colors[s], sf::Color::Green, animation_speed);
        S->AddStartMessage(
          APP.GUI, "Considering edge " + to_string(s), sf::Color::Green);
        if (explored[s.to] != 0)
        {
            auto T = Prim.AddScene(APP.edge_colors[s], black, animation_speed);
            T->AddStartMessage(APP.GUI,
                               "Discarding " + to_string(s) +
                                 " because node was already explored");
            continue;
        }
        // 		T.emplace_back(s.from,s.to,s.weight());

        auto T =
          Prim.AddScene(APP.edge_colors[s], sf::Color::Red, animation_speed);
        T->AddStartMessage(
          APP.GUI, "Adding " + to_string(s) + " to tree!", sf::Color::Red);
        --num_tree_edges;
        if (num_tree_edges == 0)
            break;
        explored[s.to] = 1;
        auto V = Prim.AddScene(
          APP.vertex_colors[s.to], sf::Color::Blue, animation_speed);
        V->AddStartMessage(APP.GUI,
                           "Marking vertex " + std::to_string(s.to) +
                             " as explored",
                           sf::Color::Blue);
        for (auto v : G.neighbors(s.to))
        {
            if (explored[v] == 0)
                EdgesToExplore.push(Edge(s.to, v, v.weight()));
        }
    }
    auto Finish = Prim.AddScene(APP.default_edge_color, black, animation_speed);
    Finish->AddFinishMessage(
      APP.GUI, "Done with Prim", sf::Color(255, 100, 200));
    // return T;
}

void AnimateKruskal()
{
    using Edge = Graph::Edge;
    using Vertex = Graph::Vertex;

    const real animation_speed = 0.03;

    APP.ClearToDefaults();
    APP.GUI.AddMessage(
      "Starting Kruskal's Algorithm. Press [Space] to continue!");

    auto G = APP.GetGraph().GetGraph();

    auto E = G.edges();

    std::sort(E.begin(), E.end(), [](const Edge& a, const Edge& b) {
        if (a.weight() != b.weight())
            return a.weight() < b.weight();
        if (a.from != b.from)
            return a.from < b.from;
        return a.to < b.to;
    });

    disjoint_sets D(G.num_vertices());

    auto& Kruskal = APP.CreateAnimation();
    Kruskal.PauseAfterEveryScene(true);

    const auto grey = sf::Color(120, 120, 120);
    const auto black = sf::Color(36, 36, 36);
    const auto consider = sf::Color::Green;
    const auto tree = sf::Color::Red;
    APP.default_edge_color = grey;
    APP.default_vertex_color = grey;

    auto num_tree_edges = G.num_vertices() - 1;

    for (auto& e : E)
    {
        Vertex a = e.from;
        Vertex b = e.to;

        auto S =
          Kruskal.AddScene(APP.edge_colors[e], consider, animation_speed);
        S->AddStartMessage(
          APP.GUI, "Considering edge " + to_string(e), consider);

        if (D.are_in_same_connected_component(a, b))
        {
            auto NA =
              Kruskal.AddScene(APP.edge_colors[e], black, animation_speed);
            NA->AddStartMessage(
              APP.GUI, "Not adding " + to_string(e), sf::Color::White);
        }
        else
        {
            auto A =
              Kruskal.AddScene(APP.edge_colors[e], tree, animation_speed);
            A->AddStartMessage(APP.GUI, "Adding " + to_string(e), tree);
            --num_tree_edges;
            if (num_tree_edges == 0)
                break;
            D.merge(a, b);
        }
    }
    auto Finish =
      Kruskal.AddScene(APP.default_edge_color, black, animation_speed);
    Finish->AddFinishMessage(
      APP.GUI, "Done with Kruskal", sf::Color(255, 100, 200));
    Kruskal.AddScene(
      APP.default_vertex_color, sf::Color(255, 100, 200), animation_speed);
}
