#pragma once

#include "Client.hpp"
#include "PhysicalGraph.hpp"

class GraphApp : public Client<GraphApp> // using CRTP
{
public:
    using Base     = Client<GraphApp>;
    using vertex_t = Graph::vertex_t;

    // options
    real vertex_size{7.0};
    real edge_thickness{2.0};
    real label_size{30.0};

    sf::Color default_vertex_color{sf::Color::Cyan};
    sf::Color default_edge_color{sf::Color::Magenta};

    bool show_labels{false};

    GraphApp(const string& name = "Graph");

    void SetGraph(const Graph& G)
    {
        P.SetGraph(G);
        FitGraphToScreen();
    }
    PhysicalGraph& GetGraph() { return P; }

    void Update(real time);

    void RenderWorld();
    void RenderGUI() {}

    void OnKeyPress(sf::Keyboard::Key key);
    void OnKeyRelease(sf::Keyboard::Key key) {}

    void OnMouseButtonPress(sf::Mouse::Button btn);
    void OnMouseButtonRelease(sf::Mouse::Button btn);

    void OnMouseWheelMoved(int delta) {}
    void OnMouseMoved() {}

    void OnEvent(const sf::Event& evt) {} // key presses and stuff are handled in other functions.
    // This is for all "rare" events (joysticks?)

    vertex_t GetVertexUnderMouse() const;
    void     FitGraphToScreen();

private:
    void DrawGraph();

    PhysicalGraph P;

    Box  GetBoundingBoxOfGraph() const;
    bool IsMouseOverVertex(vertex_t v) const;

    vertex_t selected_vertex{Graph::INVALID_VERTEX};
    vertex_t edge_start{Graph::INVALID_VERTEX};
};
