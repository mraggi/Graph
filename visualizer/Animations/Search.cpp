#include "GraphApp.hpp"
#include <stack>

void AnimateDFS()
{
    const real animation_speed = 0.3;

    using Edge = Graph::Edge;
    using Vertex = Graph::Vertex;

    APP.ClearToDefaults();

    APP.GUI.AddMessage("Starting DFS. Press [Space] to continue!");

    auto G = APP.GetGraph().GetGraph();

    auto& DFS = APP.CreateAnimation();
    DFS.PauseAfterEveryScene(true);

    const auto grey = sf::Color(120, 120, 120);
    const auto black = sf::Color(36, 36, 36);
    const auto blue = sf::Color::Blue;
    const auto red = sf::Color::Red;
    const auto green = sf::Color::Green;

    APP.default_edge_color = grey;
    APP.default_vertex_color = grey;

    auto n = G.num_vertices();

    if (n == 0)
        return;

    using Boolean = char;
    std::vector<Boolean> explored(n, false);
    explored[0] = true;

    std::stack<Vertex> frontier; // starts with only vertex 0

    frontier.push(0);

    DFS.AddScene(APP.vertex_colors[0], green, animation_speed)
      ->AddStartMessage(APP.GUI, "Adding vertex 0 to frontier", green);

    while (!frontier.empty())
    {
        Vertex v = frontier.top();
        frontier.pop();
        DFS.AddScene(APP.vertex_colors[v], blue, animation_speed)
          ->AddStartMessage(
            APP.GUI, "Exploring vertex " + std::to_string(v), blue);

        explored[v] = true;
        for (auto u : G.neighbors(v))
        {
            auto E = Edge(v, u);
            if (explored[u])
            {
                continue;
            }

            DFS.AddScene(APP.edge_colors[E], red, animation_speed)
              ->AddStartMessage(APP.GUI, "Exploring new avenue", red);

            DFS.AddScene(APP.vertex_colors[u], green, animation_speed)
              ->AddStartMessage(APP.GUI,
                                "Putting vertex " + std::to_string(u) +
                                  " in frontier",
                                green);
            explored[u] = true;
            frontier.push(u);
        }
    }

    DFS.AddScene(APP.default_edge_color, black, 0.000001)
      ->AddFinishMessage(APP.GUI, "Done with DFS!");
}

void AnimateBFS()
{
    const real animation_speed = 0.3;

    using Edge = Graph::Edge;
    using Vertex = Graph::Vertex;

    APP.ClearToDefaults();

    APP.GUI.AddMessage("Starting BFS. Press [Space] to continue!");

    auto G = APP.GetGraph().GetGraph();

    auto& BFS = APP.CreateAnimation();
    BFS.PauseAfterEveryScene(true);

    const auto grey = sf::Color(120, 120, 120);
    const auto black = sf::Color(36, 36, 36);
    const auto blue = sf::Color::Blue;
    const auto red = sf::Color::Red;
    const auto green = sf::Color::Green;

    APP.default_edge_color = grey;
    APP.default_vertex_color = grey;

    auto n = G.num_vertices();

    if (n == 0)
        return;

    using Boolean = char;
    std::vector<Boolean> explored(n, false);
    explored[0] = true;

    std::queue<Vertex> frontier; // starts with only vertex 0

    frontier.push(0);

    BFS.AddScene(APP.vertex_colors[0], green, animation_speed)
      ->AddStartMessage(APP.GUI, "Adding vertex 0 to frontier", green);

    while (!frontier.empty())
    {
        Vertex v = frontier.front();
        frontier.pop();
        BFS.AddScene(APP.vertex_colors[v], blue, animation_speed)
          ->AddStartMessage(
            APP.GUI, "Exploring vertex " + std::to_string(v), blue);

        explored[v] = true;
        for (auto u : G.neighbors(v))
        {
            auto E = Edge(v, u);
            if (explored[u])
            {
                continue;
            }

            BFS.AddScene(APP.edge_colors[E], red, animation_speed)
              ->AddStartMessage(APP.GUI, "Exploring new avenue", red);

            BFS.AddScene(APP.vertex_colors[u], green, animation_speed)
              ->AddStartMessage(APP.GUI,
                                "Putting vertex " + std::to_string(u) +
                                  " in frontier",
                                green);
            explored[u] = true;
            frontier.push(u);
        }
    }

    BFS.AddScene(APP.default_edge_color, black, 0.000001)
      ->AddFinishMessage(APP.GUI, "Done with BFS!");
}
