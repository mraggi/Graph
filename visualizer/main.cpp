#include "Animations/MST.hpp"
#include "Animations/ResetDefaultColors.hpp"
#include "Animations/Search.hpp"
#include "GraphApp.hpp"

int main()
{
	APP.GUI.AddAction("Run Prim's Algorithm", sf::Keyboard::Q, AnimatePrim);
	APP.GUI.AddAction("Run Kruskal's Algorithm", sf::Keyboard::W, AnimateKruskal);

	// 	APP.GUI.AddAction("Run DFS", sf::Keyboard::Q, AnimateDFS);
	// 	APP.GUI.AddAction("Run BFS", sf::Keyboard::W, AnimateBFS);

	APP.GUI.AddSpacer();

	APP.GUI.AddAction("Reset Default Colors", sf::Keyboard::Numpad0, ResetDefaultColors);

	APP.Run();

	return 0;
}

bool dominates(const Point& P, const Point& Q) { return P.x < Q.x && P.y > Q.y; }

PhysicalGraph PumGraph(const vector<Point>& P)
{
	PhysicalGraph G(P.size());
	for (auto v : G.vertices())
	{
		for (auto u : G.vertices())
		{
			if (u == v)
				continue;
			if (dominates(P[u], P[v]))
			{
				G.add_edge(u, v);
			}
		}
	}
	return G;
}

void dumb()
{
	APP.GUI.AddAction("Construct thingy", sf::Keyboard::Q, []() {
		auto& G = APP.GetGraph();
		for (auto v : G.vertices())
		{
			for (auto u : G.vertices())
			{
				if (u == v)
					continue;
				if (dominates(G[u], G[v]))
				{
					G.add_edge(u, v);
				}
			}
		}
	});
}
