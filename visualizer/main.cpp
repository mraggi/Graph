#include "Graph.hpp"
#include "GraphApp.hpp"
#include "Misc.hpp"
#include "Probability.hpp"

void SetUpAnimationExamples();

int main()
{
//     SetUpAnimationExamples();
	APP.Run();

	return 0;
}

void SetUpAnimationExamples()
{
    auto start_edge_color   = APP.default_edge_color;
	auto new_edge_color		= sf::Color::Green;
	auto start_vertex_color = APP.default_vertex_color;
	auto new_vertex_color   = sf::Color::Red;

	auto& A = APP.CreateAnimation(false);
	A.SetLoop(true);

	auto t = A.AddScene(APP.default_edge_color, start_edge_color, new_edge_color, 5.0);
	t->SetStartMessage("Changing color!", new_edge_color);
	t->SetFinishMessage("Finished changing color!", new_edge_color);

	auto r = A.AddScene(APP.default_edge_color, new_edge_color, start_edge_color, 5.0);

	r->SetStartMessage("Going back!", start_edge_color);
	r->SetFinishMessage("Finished going back!", start_edge_color);

	auto& A2 = APP.CreateAnimation(true);
	A2.SetLoop(true);
	A2.AddScene(APP.default_vertex_color, start_vertex_color, new_vertex_color, 5.0);
	A2.AddScene(APP.default_vertex_color, new_vertex_color, start_vertex_color, 5.0);

	auto& B = APP.CreateAnimation();
	B.SetLoop(true);
	B.AddScene(APP.vertex_colors[0], sf::Color::Red, sf::Color::Yellow, 1.0);
	B.AddScene(APP.vertex_colors[0], sf::Color::Yellow, sf::Color::Red, 1.0);
	
    APP.GUI.AddAction("Print Message", sf::Keyboard::Tab, []() {
		APP.GUI.AddMessage("Hola mundo!", sf::Color::Red);
	});
    
// 	auto& C = APP.CreateAnimation();
// 	C.SetLoop(true);
// 	C.AddScene(APP.default_vertex_size, 0.0, 100.0, 3.0);
// 	C.AddScene(APP.default_vertex_size, 100.0, 0.0, 3.0);
    
}
