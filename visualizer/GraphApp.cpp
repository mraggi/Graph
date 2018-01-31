#include "GraphApp.hpp"
#include "Graph.hpp"
#include "CommonGraphs.hpp"
#include "Probability.hpp"

using Base = GraphApp::Base;

GraphApp::GraphApp(const string& name) : Base(name)
									   , P()
{
	SetGraph(Graph(0));
	
	
	PA.AddCheckbox(P.turn_physics_on, "Physics", sf::Keyboard::P);

	PA.AddCheckbox(P.attract_to_center, "Attract toward center", sf::Keyboard::A);
	PA.AddCheckbox(P.repulsion_on, "Repulsion", sf::Keyboard::R);
	PA.AddCheckbox(show_labels, "Show Vertex Labels", sf::Keyboard::L);
	PA.AddSlider(P.max_speed, "Max Speed",  10, sf::Keyboard::G, sf::Keyboard::H);
	PA.AddSlider(vertex_size,"Vertex Size", 1, sf::Keyboard::I, sf::Keyboard::O);
	PA.AddSlider(edge_thickness,"Edge Thickness", 1, sf::Keyboard::T, sf::Keyboard::Y);
	PA.AddButton("Clear Graph",sf::Keyboard::C,[this](){ SetGraph(Graph(0)); });
	PA.AddButton("Petersen Graph",sf::Keyboard::S,[this](){ SetGraph(graphs::Petersen()); });
	PA.AddButton("Random Graph",sf::Keyboard::D,[this]()
	{ 
		Graph G(1000);
		for (auto i : G.vertices())
		{
			for (int j = i+1; j < G.num_vertices(); ++j)
			{
				if (probability_of_true(1.05/G.num_vertices()))
					G.add_edge(i,j);
			}
		}
		SetGraph(G); 
		
	});
	
// 	PA.AddElement(label_size,"Label Size", 1, sf::Keyboard::N, sf::Keyboard::M);
}



void GraphApp::Update(real time)
{
	if (selected_vertex != Graph::INVALID_VERTEX)
	{
		P[selected_vertex] = MousePosition();
	}
	P.Update(time);
	
	PA.Watch("To fit graph to screen, press [Enter]");
	PA.Watch("Toggle fullscreen with [F]");
	PA.Watch("To add vertex, press CTRL+Left mouse button");
	PA.Watch("To add edge, press SHIFT+Left mouse button");
	PA.Watch(P.num_vertices(), "Num vertices");
	PA.Watch(P.num_edges(), "Num edges");
	
}

void GraphApp::RenderWorld() 
{ 
	DrawGraph(); 
	if (edge_start != Graph::INVALID_VERTEX)
	{
		Render(Segment(P[edge_start],MousePosition()),sf::Color::Blue,edge_thickness);
	}
}


void GraphApp::DrawGraph() 
{
	for (auto e : P.edges())
	{
		Base::Render(Segment(P[e.from], P[e.to]), default_edge_color, edge_thickness);
	}
	
	for (auto v : P.vertices())
	{
		sf::Color vcol = default_vertex_color;
		
		if (selected_vertex == v)
			vcol = sf::Color::Yellow;
		else if (IsMouseOverVertex(v))
			vcol = sf::Color(100,200,255);
		
		if (show_labels)
			Base::Render(std::to_string(v),P[v] - Point(label_size*0.45,label_size*1.2)/2, vcol, label_size);
		else
			Base::Render(P[v], vcol, vertex_size);	
	}
	
}

bool GraphApp::IsMouseOverVertex(vertex_t v) const
{
	auto MP = MousePosition();
	double vs = vertex_size+3; //leave 3 pixels to grab the vertex
	double vs2 = vs*vs;
	return distancesq(MP,P[v]) < vs2;
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
			edge_start = GetVertexUnderMouse();
			return;
		}
			
		selected_vertex = GetVertexUnderMouse();
	}
	
}

void GraphApp::OnMouseButtonRelease(sf::Mouse::Button btn)  
{  
	selected_vertex = Graph::INVALID_VERTEX;
	if (btn == sf::Mouse::Left)
	{
		if (edge_start != Graph::INVALID_VERTEX)
		{
			auto edge_end = GetVertexUnderMouse();
			if (edge_end != Graph::INVALID_VERTEX && edge_end != edge_start)
			{
				P.add_edge_no_repeat(edge_start,edge_end);
				edge_end = Graph::INVALID_VERTEX;
			}
			
			if (edge_end != edge_start)
			{
				edge_start = Graph::INVALID_VERTEX;
			}
		}
	}
	
	if (btn == sf::Mouse::Right)
	{
		edge_start = Graph::INVALID_VERTEX;
	}
	
}

GraphApp::vertex_t GraphApp::GetVertexUnderMouse() const
{
	for (auto v : P.vertices())
	{
		if (IsMouseOverVertex(v))
		{
			return v;
		}
	}
	return Graph::INVALID_VERTEX;
}


void GraphApp::FitGraphToScreen()
{
	m_Camera = GetBoundingBoxOfGraph();
	FixAspectRatio();
	SynchronizeCameraWithView();
}

void GraphApp::OnKeyPress(sf::Keyboard::Key key) 
{
	if (key == sf::Keyboard::Return)
	{
		FitGraphToScreen();
	}
}

Box GraphApp::GetBoundingBoxOfGraph() const
{
	if (P.num_vertices() == 0)
	{
		return Box({0,0},{1000,1000});
	}
	real minX = 9999999;
	real minY = 9999999;
	real maxX = -9999999;
	real maxY = -9999999;
	
	for (auto v : P.vertices())
	{
		auto p = P[v];
		minX = min(minX,p.x);
		minY = min(minY,p.y);
		maxX = max(maxX,p.x);
		maxY = max(maxY,p.y);
	}
	Point border = Point(5+2*vertex_size,5+2*vertex_size);
	Box B(Point(minX,minY)-border,Point(maxX,maxY)+border);
	return B;
}
