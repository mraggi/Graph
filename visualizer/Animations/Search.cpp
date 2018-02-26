#include "GraphApp.hpp"

void AnimateDFS()
{
	const real animation_speed = 0.3;

	using Edge = Graph::Edge;
	using vertex_t = Graph::vertex_t;

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

	std::vector<char> explored(n, false);
	explored[0] = true;

	std::vector<vertex_t> frontier(1, 0); // starts with only vertex 0

	DFS.AddScene(APP.vertex_colors[0], green, animation_speed)
	  ->AddStartMessage(APP.GUI, "Adding vertex 0 to frontier", green);

	while (!frontier.empty())
	{
		vertex_t v = frontier.back();
		frontier.pop_back();
		DFS.AddScene(APP.vertex_colors[v], blue, animation_speed)
		  ->AddStartMessage(APP.GUI, "Exploring vertex " + std::to_string(v), blue);

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
			  ->AddStartMessage(
				APP.GUI, "Putting vertex " + std::to_string(u) + " in frontier", green);
			explored[u] = true;
			frontier.push_back(u);
		}
	}

	DFS.AddScene(APP.default_edge_color, black, 0.000001)
	  ->AddFinishMessage(APP.GUI, "Done with DFS!");
}

void AnimateBFS()
{
	const real animation_speed = 0.3;

	using Edge = Graph::Edge;
	using vertex_t = Graph::vertex_t;

	APP.ClearToDefaults();

	APP.GUI.AddMessage("Starting BFS. Press [Space] to continue!");

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
}
