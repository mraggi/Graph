#include "CommonGraphs.hpp"
#include "Graph.hpp"
#include "GraphApp.hpp"
#include "Misc.hpp"
#include "Probability.hpp"
#include "disjoint_sets.hpp"

#include <queue>

void SetUpAnimationExamples();

void AnimatePrim();
void AnimateKruskal();

int main()
{
// 	AnimatePrim();
	APP.Run();

	return 0;
}

struct by_reverse_weight
{
	using Edge = Graph::Edge;
	bool operator()(const Edge& a, const Edge& b) { return a.weight() > b.weight(); }
};

std::vector<sf::Color*> neighbor_colors(const Graph& G, Graph::vertex_t v)
{
	std::vector<sf::Color*> result;
	for (auto u : G.neighbors(v))
	{
		Graph::Edge E(v,u,u.weight());
		result.emplace_back(&APP.edge_colors[E]);
	}
	return result;
}

void AnimatePrim()
{
	using Edge	 = Graph::Edge;
	using vertex_t = Graph::vertex_t;

	Graph G = graphs::RandomWeightedGraph(7, 0.7);

	APP.SetGraph(G);

	auto& Prim = APP.CreateAnimation();
		Prim.PauseAfterEveryScene(true);

	const auto grey			 = sf::Color(120, 120, 120);
	const auto black		 = sf::Color(36, 36, 36);
	APP.default_edge_color   = grey;
	APP.default_vertex_color = grey;

	auto n = G.num_vertices();

	if (n == 0)
		return;

	std::vector<char> explored(n, 0);

	std::priority_queue<Edge, std::vector<Edge>, by_reverse_weight> EdgesToExplore;

	explored[0] = true;

	Prim.AddScene(APP.vertex_colors[0], sf::Color::Blue, 0.5)
	  ->AddStartMessage(APP.GUI, "Considering vertex 0", sf::Color::Blue);
	
// 	auto E0 = neighbor_colors(G,0);
// 	auto E1 = std::vector<sf::Color>(E0.size(),sf::Color::Yellow);
// 	Prim.AddScene(E0,E1,5.0);
	
	for (auto v : G.neighbors(0))
	{
		auto E = Edge(0, v, v.weight());
		EdgesToExplore.push(Edge(0, v, v.weight()));
	}

	while (!EdgesToExplore.empty())
	{
		Edge s = EdgesToExplore.top();
		EdgesToExplore.pop();
		auto S = Prim.AddScene(APP.edge_colors[s], sf::Color::Green, 0.5);
		S->AddStartMessage(APP.GUI, "Considering edge", sf::Color::Green);
		if (explored[s.to])
		{
			auto T = Prim.AddScene(APP.edge_colors[s], black, 0.5);
			T->AddStartMessage(APP.GUI, "Discarding because node was already explored");
			continue;
		}
		// 		T.emplace_back(s.from,s.to,s.weight());

		auto T = Prim.AddScene(APP.edge_colors[s], sf::Color::Red, 0.5);
		T->AddStartMessage(APP.GUI, "Adding to tree!", sf::Color::Red);
		explored[s.to] = true;
		auto V		   = Prim.AddScene(APP.vertex_colors[s.to], sf::Color::Blue, 0.5);
		V->AddStartMessage(APP.GUI, "Marking vertex as explored", sf::Color::Blue);
		for (auto v : G.neighbors(s.to))
		{
			if (explored[v] == 0)
				EdgesToExplore.push(Edge(s.to, v, v.weight()));
		}
	}
	//     return T;
}

void AnimateKruskal()
{
	using Edge	 = Graph::Edge;
	using vertex_t = Graph::vertex_t;

	Graph G = graphs::RandomWeightedGraph(7, 0.7);

	APP.SetGraph(G);
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

	const auto grey		   = sf::Color(120, 120, 120);
	const auto black	   = sf::Color(26, 26, 26);
	APP.default_edge_color = grey;

	for (auto& e : E)
	{
		vertex_t a = e.from;
		vertex_t b = e.to;

		auto S = Kruskal.AddScene(APP.edge_colors[e], sf::Color::Green, 0.5);
		S->AddStartMessage(APP.GUI,
						   "Considering edge " + to_string(a) + "-" + to_string(b) + " with weight "
							 + to_string(e.weight()),
						   sf::Color::Green);

		if (D.are_in_same_connected_component(a, b))
		{
			auto NA = Kruskal.AddScene(APP.edge_colors[e], sf::Color::Green, black, 0.5);
			NA->AddStartMessage(
			  APP.GUI, "Not adding " + to_string(a) + "-" + to_string(b), sf::Color::White);
		}
		else
		{
			auto A = Kruskal.AddScene(APP.edge_colors[e], sf::Color::Green, sf::Color::Red, 0.5);
			A->AddStartMessage(
			  APP.GUI, "Adding " + to_string(a) + "-" + to_string(b), sf::Color::Red);
			D.merge(a, b);
		}
	}
}

void SetUpAnimationExamples()
{
	auto start_edge_color   = APP.default_edge_color;
	auto new_edge_color		= sf::Color::Green;
	auto start_vertex_color = APP.default_vertex_color;
	auto new_vertex_color   = sf::Color::Red;

	auto& A = APP.CreateAnimation();
	A.PauseAfterEveryScene(false);
	A.SetLoop(true);

	auto t = A.AddScene(APP.default_edge_color, start_edge_color, new_edge_color, 5.0);
	t->AddStartMessage(APP.GUI, "Changing color!", new_edge_color);
	t->AddFinishMessage(APP.GUI, "Finished changing color!", new_edge_color);

	auto r = A.AddScene(APP.default_edge_color, new_edge_color, start_edge_color, 5.0);

	r->AddStartMessage(APP.GUI, "Going back!", start_edge_color);
	r->AddFinishMessage(APP.GUI, "Finished going back!", start_edge_color);

	auto& A2 = APP.CreateAnimation();
	A2.PauseAfterEveryScene(true);
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
