#pragma once

#include "Client.hpp"
#include "PhysicalGraph.hpp"

class GraphApp : public Client<GraphApp> // using CRTP
{
public:
	using Base = Client<GraphApp>;
	using vertex_t = Graph::vertex_t;

	// options
	real default_vertex_size{7.0};
	real default_edge_thickness{2.0};

	sf::Color default_vertex_color{sf::Color(0, 200, 0, 220)};
	sf::Color hover_vertex_color{sf::Color(100, 200, 255, 220)};
	sf::Color selected_vertex_color{sf::Color(255, 0, 0, 220)};
	sf::Color default_edge_color{sf::Color(130, 0, 255, 220)};
	sf::Color created_edge_color{sf::Color(255, 90, 0, 220)};

	bool show_labels{false};
	bool show_edge_labels{false};

	explicit GraphApp(const string& name = "Graph");

	void SetGraph(const Graph& G)
	{
		std::cout << "Set graph with " << G.num_vertices() << " vertices and " << G.num_edges()
				  << " edges." << std::endl;
		P.SetGraph(G);
		FitGraphToScreen();
		if (G.num_edges() > 100000)
		{
			P.turn_physics_on = false;
			GUI.AddMessage("Turning physics off because there are too many edges");
		}
	}

	PhysicalGraph& GetGraph() { return P; }

	void Update(real time);

	void RenderWorld();
	void RenderGUIPanel() {}

	void OnKeyPress(sf::Keyboard::Key key);
	void OnKeyRelease(sf::Keyboard::Key key) {}

	void OnMouseButtonPress(sf::Mouse::Button btn);
	void OnMouseButtonRelease(sf::Mouse::Button btn);

	void OnMouseWheelMoved(int delta) {}
	void OnMouseMoved() {}

	void OnEvent(const sf::Event& evt) {} // key presses and stuff are handled in other functions.
	// This is for all "rare" events (joysticks?)

	vertex_t VertexUnderMouse() const;
	bool IsMouseOverVertex(vertex_t v) const;

	void FitGraphToScreen();

	static GraphApp& GlobalInstance()
	{
		static GraphApp GA("Graph");
		return GA;
	}

	void ClearToDefaults()
	{
		ClearAnimations();
		vertex_colors.clear();
		vertex_sizes.clear();
		edge_colors.clear();
		edge_thicknesses.clear();
	}

	struct edge_hash
	{
		size_t operator()(const Graph::Edge& E) const
		{
			long long a = E.from;
			long long b = E.to;
			if (a > b)
				std::swap(a, b);

			return a + (1LL << 24) * b + (1LL << 48) * E.weight();
		}
	};

	map_with_default_by_ref<vertex_t, sf::Color> vertex_colors{default_vertex_color};
	map_with_default_by_ref<vertex_t, real> vertex_sizes{default_vertex_size};

	map_with_default_by_ref<Graph::Edge, sf::Color, edge_hash> edge_colors{default_edge_color};
	map_with_default_by_ref<Graph::Edge, real, edge_hash> edge_thicknesses{default_edge_thickness};

private:
	PhysicalGraph P;

	vertex_t selected_vertex{Graph::INVALID_VERTEX};
	vertex_t edge_start{Graph::INVALID_VERTEX};

	int num_rand_verts{50};
	real avg_degree{1.1};

	void DrawGraph();
	Box GetBoundingBoxOfGraph() const;

	void CreateGUI();

	real label_size(vertex_t i) const { return vertex_sizes(i) * 3.8; }

	// Temp while I add a proper watcher
	int num_edges{0};
	int num_verts{0};
};

#define APP (GraphApp::GlobalInstance())
