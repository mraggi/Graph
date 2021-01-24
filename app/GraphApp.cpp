#include "GraphApp.hpp"
#include "CommonGraphs.hpp"
#include "Graph.hpp"
#include "Probability.hpp"

using Base = GraphApp::Base;

GraphApp::GraphApp(const std::string& name) : Base(name)
{
    SetGraph(Graph(0));

    CreateGUI();
}

void GraphApp::CreateGUI()
{
    auto intructions_color = sf::Color(100, 255, 100);

    GUI.AddText("To add/remove vertex, LCtrl + [Left/Right] Mouse Button",
                intructions_color);
    GUI.AddText("To add edge, LShift + Left Mouse", intructions_color);

    GUI.AddWatcher(num_verts, "Number of Vertices", intructions_color);
    GUI.AddWatcher(num_edges, "Number of Edges", intructions_color);

    GUI.AddSpacer();

    GUI.AddAction(
      "Fit Graph to Screen",
      sf::Keyboard::Return,
      [this]() { FitGraphToScreen(); },
      sf::Color::Blue);

    GUI.AddSpacer();

    GUI.AddCheckbox(P.turn_physics_on, "Physics", sf::Keyboard::P);
    GUI.AddCheckbox(
      P.attract_to_center, "Attract toward center", sf::Keyboard::A);
    GUI.AddCheckbox(P.repulsion_on, "Repulsion", sf::Keyboard::R);
    GUI.AddCheckbox(show_labels, "Show Vertex Labels", sf::Keyboard::L);
    GUI.AddCheckbox(show_edge_labels, "Show Edge Labels", sf::Keyboard::E);

    // 	GUI.AddWatcher(m_animations);

    GUI.AddSpacer();

    GUI.AddController(default_vertex_size,
                      "Vertex Size",
                      0.5,
                      sf::Keyboard::I,
                      sf::Keyboard::O);
    GUI.AddController(default_edge_thickness,
                      "Edge Thickness",
                      0.25,
                      sf::Keyboard::T,
                      sf::Keyboard::Y);

    GUI.AddAction(
      "Sort neighbors",
      sf::Keyboard::S,
      [this]() { P.sort_neighbors(); },
      sf::Color::Magenta);

    GUI.AddSpacer();
    GUI.AddText("Create graphs");

    GUI.AddAction(
      "Clear Graph", sf::Keyboard::Num1, [this]() { SetGraph(Graph(0)); });

    auto dark_orange = sf::Color(255, 100, 0);

    GUI.AddController(num_rand_verts,
                      "Num vertices for generator",
                      1,
                      sf::Keyboard::G,
                      sf::Keyboard::H,
                      dark_orange);

    GUI.AddAction("Path Graph", sf::Keyboard::Num2, [this]() {
        SetGraph(graphs::Path(num_rand_verts));
    });

    GUI.AddAction("Cycle Graph", sf::Keyboard::Num3, [this]() {
        SetGraph(graphs::Cycle(num_rand_verts));
    });

    GUI.AddAction("Complete Graph", sf::Keyboard::Num4, [this]() {
        if (num_rand_verts > 100)
        {
            num_rand_verts = 100;
            GUI.AddMessage("Capping complete graph at 100 vertices");
        }
        SetGraph(graphs::Complete(num_rand_verts));
    });

    // Fill here with path and cycle with shortcuts 2 and 3, respectively!

    GUI.AddAction("Petersen Graph", sf::Keyboard::Num5, [this]() {
        SetGraph(graphs::Petersen());
    });

    GUI.AddController(avg_degree,
                      "Average degree for random",
                      0.1,
                      sf::Keyboard::LBracket,
                      sf::Keyboard::RBracket,
                      dark_orange);

    GUI.AddAction("Random Graph", sf::Keyboard::Num6, [this]() {
        SetGraph(
          graphs::RandomWeighted(num_rand_verts, avg_degree/num_rand_verts));
    });

    GUI.AddAction("Grid Graph", sf::Keyboard::Num7, [this]() {
        int n = std::sqrt(num_rand_verts);
        SetGraph(graphs::Grid(n, n));
    });

    GUI.AddAction("Random Tree", sf::Keyboard::Num8, [this]() {
        SetGraph(graphs::RandomTree(num_rand_verts));
    });

    GUI.AddAction("Random BinaryTree", sf::Keyboard::Num9, [this]() {
        SetGraph(graphs::RandomBinaryTree(num_rand_verts));
    });

    GUI.AddAction("Albert Barabanasi", sf::Keyboard::Num0, [this]() {
        SetGraph(graphs::AlbertBarabanasi(num_rand_verts, 2));
    });

    GUI.AddSpacer();

    GUI.AddText("Available Shortcuts: " + GUI.AvailableShortcuts(),
                sf::Color(40, 40, 50));
    GUI.AddSpacer();
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
        RenderSegment(P[edge_start],
                      MousePosition(),
                      created_edge_color,
                      default_edge_thickness);
    }
}

void GraphApp::DrawGraph()
{
    for (auto e : P.edges())
    {
        Base::RenderSegment(
          P[e.from], P[e.to], edge_colors(e), edge_thicknesses(e));
        if (show_edge_labels)
        {
            auto edge_label_col = sf::Color(255, 255, 100);
            auto Center = (P[e.from] + P[e.to])/2;
            auto ls = edge_thicknesses(e)*8;
            Render(std::to_string(e.weight()),
                   Center - Point(ls, ls)/2,
                   edge_label_col,
                   ls);
        }
    }

    for (auto v : P.vertices())
    {
        sf::Color vcol = vertex_colors(v);

        if (selected_vertex == v)
            vcol = selected_vertex_color;
        else if (IsMouseOverVertex(v))
            vcol = hover_vertex_color;

        if (show_labels)
        {
            Point pos =
              P[v] - Point(label_size(v)*0.45, label_size(v)*1.2)/2;
            Base::Render(std::to_string(v), pos, vcol, label_size(v));
        }
        else
        {
            Base::Render(P[v], vcol, vertex_sizes(v));
        }
    }
}

bool GraphApp::IsMouseOverVertex(Vertex v) const
{
    auto MP = MousePosition();
    double vs = vertex_sizes(v) + 3; // leave 3 pixels to grab the vertex
    double vs2 = vs*vs;
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
            edge_start == Graph::INVALID_VERTEX)
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
                P.remove_vertex(v);
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

GraphApp::Vertex GraphApp::VertexUnderMouse() const
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
        return Box({0, 0}, {1000, 1000});

    real minX = 9999999;
    real minY = 9999999;
    real maxX = -9999999;
    real maxY = -9999999;

    for (auto v : P.vertices())
    {
        auto p = P[v];

        minX = std::min(minX, p.x);
        minY = std::min(minY, p.y);
        maxX = std::max(maxX, p.x);
        maxY = std::max(maxY, p.y);
    }

    real b = 5 + 2*default_vertex_size;
    Point border(b, b);

    Box B(Point(minX, minY) - border, Point(maxX, maxY) + border);

    return B;
}
