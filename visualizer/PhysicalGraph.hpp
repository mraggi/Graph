#pragma once
#include "GUIPanel.hpp"
#include "Geometry/Point.hpp"
#include "Graph.hpp"
#include "TimeHelpers.hpp"

class PhysicalGraph
{
public:
	using vertex_t = Graph::vertex_t;
	using weight_t = Graph::weight_t;
	using Edge	 = Graph::Edge;

	PhysicalGraph(const Graph& g);

	explicit PhysicalGraph(vertex_t num_verts = 0);

	void SetGraph(const Graph& g);

	void Update(double time);

	Point  operator[](size_t i) const { return M[i].position; }
	Point& operator[](size_t i) { return M[i].position; }

	const std::vector<Graph::Edge>& edges() const { return E; }

	using all_vertices = basic_natural_number<vertex_t>;
	all_vertices vertices() const { return all_vertices(num_vertices()); }

	vertex_t		 num_vertices() const { return G.num_vertices(); }
	Graph::size_type num_edges() const { return G.num_edges(); }

	// Graph modification functions
	vertex_t add_vertex()
	{
		M.emplace_back();
		return G.add_vertex();
	}

	void sort_neighbors() { G.sort_neighbors(); }

	void remove_vertex(vertex_t v)
	{
		vertex_t last = num_vertices() - 1;
		M[v]		  = M[last];
		M.pop_back();
		G.remove_vertex(v);
		E = G.edges();
	}

	// Graph modification functions
	vertex_t add_vertex(const Point& position)
	{
		cout << "Adding vertex at " << position << endl;
		M.emplace_back(position, Point(), Point());
		return G.add_vertex();
	}

	void add_edge(vertex_t from, vertex_t to, weight_t w = 1)
	{
		E.emplace_back(Edge(from, to, w));
		G.add_edge(from, to, w);
	}

	void add_edge_no_repeat(vertex_t from, vertex_t to, weight_t w = 1)
	{
		if (G.add_edge_no_repeat(from, to, w))
			E.emplace_back(Edge(from, to, w));
	}

	const Graph& GetGraph() const { return G; }

	bool turn_physics_on{true};
	bool attract_to_center{true};
	bool repulsion_on{true};

	// constants of motion
	real repelling_force{150000.0};
	real ideal_edge_size{200.0};
	real hook_constant{15.0};
	real force_toward_center{2.0};
	real max_speed{10000.0};
	real damping{0.95};

private:
	struct Motion
	{
		Motion() : position(Point::RandomPoint(200)) {}
		Motion(const Point& pos, const Point& vel, const Point& accel)
			: position(pos), velocity(vel), acceleration(accel)
		{}
		Point position;
		Point velocity;
		Point acceleration;
	};

	Point& p(vertex_t v) { return M[v].position; }
	Point& v(vertex_t v) { return M[v].velocity; }
	Point& a(vertex_t v) { return M[v].acceleration; }

	Point p(vertex_t v) const { return M[v].position; }
	Point v(vertex_t v) const { return M[v].velocity; }
	Point a(vertex_t v) const { return M[v].acceleration; }

	Graph				G;
	std::vector<Edge>   E;
	std::vector<Motion> M;

	real time_since_last_update{0.0}; // this is so it runs at fixed fps
};
