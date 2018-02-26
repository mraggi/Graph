#include "Animations/MST.hpp"
#include "Animations/ResetDefaultColors.hpp"
#include "Animations/Search.hpp"
#include "GraphApp.hpp"

int main()
{
	// 	APP.GUI.AddAction("Run Prim's Algorithm", sf::Keyboard::Q, AnimatePrim);
	// 	APP.GUI.AddAction("Run Kruskal's Algorithm", sf::Keyboard::W, AnimateKruskal);

	APP.GUI.AddAction("Run DFS", sf::Keyboard::Q, AnimateDFS);
	APP.GUI.AddAction("Run BFS", sf::Keyboard::W, AnimateBFS);
	APP.GUI.AddSpacer();

	APP.GUI.AddAction("Reset Default Colors", sf::Keyboard::Numpad0, ResetDefaultColors);

	APP.Run();

	return 0;
}
