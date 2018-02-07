#pragma once
#include "GUI.hpp"
#include "Geometry/Point.hpp"
#include "Graph.hpp"
#include "Probability.hpp"
#include "SimpleGradientDescent.hpp"
#include "TimeHelpers.hpp"
using Row	= std::vector<char>;
using Matrix = std::vector<Row>;

inline Matrix adjacency_matrix(const Graph& G)
{
	int	n = G.num_vertices();
	Matrix A(n, Row(n, 0));
	for (auto& e : G.edges())
	{
		A[e.from][e.to] = 1;
		A[e.to][e.from] = 1;
	}
	return A;
}

class PhysicalGraph
{
public:
	using vertex_t = Graph::vertex_t;

	PhysicalGraph(const Graph& g) : A(adjacency_matrix(g)), X(g.num_vertices() * 2), E(g.edges())
	{
		PA.AddElement(repelling_force, "Repelling Force", 0.1, sf::Keyboard::T, sf::Keyboard::Y);
		std::generate(X.begin(), X.end(), []() { return random_real(0.0, 500.0); });
	}

	PhysicalGraph()
	{
		PA.AddElement(repelling_force, "Repelling Force", 1, sf::Keyboard::T, sf::Keyboard::Y);
		PA.AddElement(repelling_threshold, "Repelling Thresh", 1, sf::Keyboard::G, sf::Keyboard::H);
	}

	void SetGraph(const Graph& g)
	{
		A = adjacency_matrix(g);
		X.resize(2 * g.num_vertices());
		std::generate(X.begin(), X.end(), []() { return random_real(0.0, 500.0); });
		E = g.edges();
	}

	void Update(double time);

	Point operator[](vertex_t v) const { return p(v); }

	const std::vector<Graph::Edge>& edges() const { return E; }

	using all_vertices = basic_natural_number<vertex_t>;
	all_vertices vertices() const { return all_vertices(A.size()); }

	size_t num_vertices() const { return A.size(); }

	// private:

	Point p(vertex_t v) const { return Point(X[2 * v], X[2 * v + 1]); }

	Matrix				A;
	MultiDimVector		X;
	vector<Graph::Edge> E;

	double TimeSinceLastDamp() const
	{
		static Chronometer C;
		return C.Reset();
	}

	// constants of motion
	real repelling_force{16.0};
	real ideal_edge_size{200.0};
	real repelling_threshold{150.0};
	real hook_constant{1.0};
	real max_speed{100.0};
	real damping{0.99};

	real alpha{0.0001};
};
