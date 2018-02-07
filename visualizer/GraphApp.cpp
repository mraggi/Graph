#include "GraphApp.hpp"
#include "CommonGraphs.hpp"
#include "Graph.hpp"
#include "Probability.hpp"

using Base = GraphApp::Base;

GraphApp::GraphApp(const string& name) : Base(name), P()
{
	SetGraph(Graph(0));

	CreateGUI();

	auto start_edge_color   = default_edge_color;
	auto new_edge_color		= sf::Color::Green;
	auto start_vertex_color = default_vertex_color;
	auto new_vertex_color   = sf::Color::Red;

	auto& A = CreateAnimation(true);
	A.SetLoop(true);

	auto t = A.AddScene(default_edge_color, start_edge_color, new_edge_color, 5.0);
	t->SetStartMessage("Changing color!", new_edge_color);
	t->SetFinishMessage("Finished changing color!", new_edge_color);

	auto r = A.AddScene(default_edge_color, new_edge_color, start_edge_color, 5.0);

	r->SetStartMessage("Going back!", start_edge_color);
	r->SetFinishMessage("Finished going back!", start_edge_color);

	auto& A2 = CreateAnimation(true);
	A2.SetLoop(true);
	A2.AddScene(default_vertex_color, start_vertex_color, new_vertex_color, 5.0);
	A2.AddScene(default_vertex_color, new_vertex_color, start_vertex_color, 5.0);

	auto& B = CreateAnimation();
	B.SetLoop(true);
	B.AddScene(vertex_colors[0], sf::Color::Red, sf::Color::Yellow, 1.0);
	B.AddScene(vertex_colors[0], sf::Color::Yellow, sf::Color::Red, 1.0);
}

void GraphApp::CreateGUI()
{
	auto intructions_color = sf::Color(100, 255, 100);

	GUI.AddText("To add/remove vertex, LCtrl + [Left/Right] Mouse Button", intructions_color);
	GUI.AddText("To add edge, LShift + Left Mouse", intructions_color);

	GUI.AddWatcher(num_verts, "Number of Vertices", intructions_color);
	GUI.AddWatcher(num_edges, "Number of Edges", intructions_color);

	GUI.AddSpacer();

	GUI.AddAction(
	  "Toggle Fullscreen", sf::Keyboard::F, [this]() { ToggleFullScreen(); }, sf::Color::Blue);

	GUI.AddAction("Fit Graph to Screen",
				  sf::Keyboard::Return,
				  [this]() { FitGraphToScreen(); },
				  sf::Color::Blue);

	GUI.AddSpacer();

	GUI.AddCheckbox(P.turn_physics_on, "Physics", sf::Keyboard::P);
	GUI.AddCheckbox(P.attract_to_center, "Attract toward center", sf::Keyboard::A);
	GUI.AddCheckbox(P.repulsion_on, "Repulsion", sf::Keyboard::R);
	GUI.AddCheckbox(show_labels, "Show Vertex Labels", sf::Keyboard::L);

	GUI.AddSpacer();

	GUI.AddController(vertex_size, "Vertex Size", 1.0, sf::Keyboard::I, sf::Keyboard::O);
	GUI.AddController(edge_thickness, "Edge Thickness", 1.0, sf::Keyboard::T, sf::Keyboard::Y);

	GUI.AddAction(
	  "Sort neighbors", sf::Keyboard::S, [this]() { P.sort_neighbors(); }, sf::Color::Magenta);

	GUI.AddSpacer();
	GUI.AddText("Create graphs");

	GUI.AddAction("Clear Graph", sf::Keyboard::Num1, [this]() { SetGraph(Graph(0)); });

	// Fill here with path and cycle with shortcuts 2 and 3, respectively!

	GUI.AddAction("Petersen Graph", sf::Keyboard::Num4, [this]() { SetGraph(graphs::Petersen()); });

	GUI.AddSpacer();

	GUI.AddController(num_rand_verts,
					  "Random graph size",
					  10,
					  sf::Keyboard::Subtract,
					  sf::Keyboard::Add,
					  sf::Color(255, 100, 0));
	GUI.AddController(avg_degree,
					  "Average degree to generate random",
					  0.1,
					  sf::Keyboard::LBracket,
					  sf::Keyboard::RBracket,
					  sf::Color(255, 100, 0));

	GUI.AddAction("Random Graph", sf::Keyboard::Num5, [this]() {
		Graph G(num_rand_verts);
		real  p = avg_degree / num_rand_verts;

		for (auto i : G.vertices())
		{
			for (int j = i + 1; j < G.num_vertices(); ++j)
			{
				if (probability_of_true(p))
					G.add_edge(i, j);
			}
		}

		SetGraph(G);
	});

	GUI.AddSpacer();

	GUI.AddText("Available Shortcuts: " + GUI.AvailableShortcuts(), sf::Color(50, 50, 50));

	GUI.AddAction("Print Message", sf::Keyboard::Tab, [this]() {
		GUI.AddMessage("Hola mundo!", sf::Color::Red);
	});
}

void GraphApp::Update(real time)
{
	if (selected_vertex != Graph::INVALID_VERTEX)
	{
		P[selected_vertex] = MousePosition();
	}

	P.Update(time);
	num_edges = P.num_edges();
	num_verts = P.num_vertices();
}

void GraphApp::RenderWorld()
{
	DrawGraph();

	if (edge_start != Graph::INVALID_VERTEX)
	{
		Render(Segment(P[edge_start], MousePosition()), created_edge_color, edge_thickness);
	}
}

void GraphApp::DrawGraph()
{
	for (auto e : P.edges())
	{
		Base::Render(Segment(P[e.from], P[e.to]), edge_colors(e), edge_thickness);
	}

	for (auto v : P.vertices())
	{
		sf::Color vcol = vertex_colors(v);

		if (selected_vertex == v)
			vcol = selected_vertex_color;
		else if (IsMouseOverVertex(v))
			vcol = hover_vertex_color;

		if (show_labels)
			Base::Render(std::to_string(v),
						 P[v] - Point(label_size() * 0.45, label_size() * 1.2) / 2,
						 vcol,
						 label_size());
		else
			Base::Render(P[v], vcol, vertex_size);
	}
}

bool GraphApp::IsMouseOverVertex(vertex_t v) const
{
	auto   MP  = MousePosition();
	double vs  = vertex_size + 3; // leave 3 pixels to grab the vertex
	double vs2 = vs * vs;
	return distancesq(MP, P[v]) < vs2;
}

void GraphApp::OnMouseButtonPress(sf::Mouse::Button btn)
{
	if (btn == sf::Mouse::Left)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			selected_vertex = P.add_vertex(MousePosition());
			return;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && edge_start == Graph::INVALID_VERTEX)
		{
			edge_start = VertexUnderMouse();
			return;
		}

		selected_vertex = VertexUnderMouse();
	}

	if (btn == sf::Mouse::Right)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			auto v = VertexUnderMouse();

			if (v != Graph::INVALID_VERTEX)
			{
				P.remove_vertex(v);
			}
		}
	}
}

void GraphApp::OnMouseButtonRelease(sf::Mouse::Button btn)
{
	selected_vertex = Graph::INVALID_VERTEX;

	if (btn == sf::Mouse::Left)
	{
		if (edge_start != Graph::INVALID_VERTEX)
		{
			auto edge_end = VertexUnderMouse();

			if (edge_end != Graph::INVALID_VERTEX && edge_end != edge_start)
			{
				P.add_edge_no_repeat(edge_start, edge_end);
				edge_end = Graph::INVALID_VERTEX;
			}

			if (edge_end != edge_start)
				edge_start = Graph::INVALID_VERTEX;
		}
	}

	if (btn == sf::Mouse::Right)
		edge_start = Graph::INVALID_VERTEX;
}

GraphApp::vertex_t GraphApp::VertexUnderMouse() const
{
	for (auto v : P.vertices())
	{
		if (IsMouseOverVertex(v))
			return v;
	}

	return Graph::INVALID_VERTEX;
}

void GraphApp::FitGraphToScreen()
{
	m_Camera = GetBoundingBoxOfGraph();
	FixAspectRatio();
	SynchronizeCameraWithView();
}

void GraphApp::OnKeyPress(sf::Keyboard::Key key) {}

Box GraphApp::GetBoundingBoxOfGraph() const
{
	if (P.num_vertices() == 0)
	{
		return Box({0, 0}, {1000, 1000});
	}

	real minX = 9999999;
	real minY = 9999999;
	real maxX = -9999999;
	real maxY = -9999999;

	for (auto v : P.vertices())
	{
		auto p = P[v];
		minX   = min(minX, p.x);
		minY   = min(minY, p.y);
		maxX   = max(maxX, p.x);
		maxY   = max(maxY, p.y);
	}

	Point border = Point(5 + 2 * vertex_size, 5 + 2 * vertex_size);
	Box   B(Point(minX, minY) - border, Point(maxX, maxY) + border);
	return B;
}

// sf::Color& GraphApp::GetVertexColor(vertex_t v)
// {
//  auto it = vertex_colors.find(v);
//  if (it != vertex_colors.end())
//      return it->second;
//  auto t = vertex_colors.insert({v,default_vertex_color}).first;
//  return t->second;
// }
//
// sf::Color GraphApp::GetVertexColor(vertex_t v) const
// {
//  auto it = vertex_colors.find(v);
//  if (it != vertex_colors.end())
//      return it->second;
//  return default_vertex_color;
// }
//
// void GraphApp::SetVertexColor(vertex_t v, const sf::Color& color)
// {
//  vertex_colors[v] = color;
// }
