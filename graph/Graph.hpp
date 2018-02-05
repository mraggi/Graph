#pragma once

#include "Misc.hpp"
#include "NaturalNumber.hpp"
#include <algorithm>
#include <unordered_map>

// simple undirected graph
class Graph
{
public:
	using size_type = long;
	using vertex_t  = long;
	static const vertex_t INVALID_VERTEX{-1};

	using weight_t = long;

	// something larger than weight_t, for when you have that weight_t doesn't
	// properly hold a sum of weight_t (for example, if weight_t = char).
	using sumweight_t = long long;

	struct Neighbor; // Represents a half-edge with a vertex and (possibly) a
	// weight
	struct Edge; // Represents an edge, with two vertices and (possibly) a
	// weight.

	using neighbor_list			  = std::vector<Neighbor>;
	using neighbor_const_iterator = neighbor_list::const_iterator;
	using neighbor_iterator		  = neighbor_list::iterator;

	// Constructor
	explicit Graph(vertex_t num_vertices = 0);

	size_type degree(vertex_t a) const { return m_graph[a].size(); }

	// Graph modification functions
	vertex_t add_vertex();
	void	 add_edge(vertex_t from, vertex_t to, weight_t w = 1);
	void	 add_edge(const Edge& e);
	void	 add_edges(const std::initializer_list<Edge>& edges);

	bool add_edge_no_repeat(vertex_t from,
							vertex_t to,
							weight_t w
							= 1); // only add if not already present. Returns true if added.

	void sort_neighbors(); // sorts them so that searching can later be done in
	// log time

	void remove_vertex(vertex_t v);			  // TODO
	void remove_edge(vertex_t v, vertex_t u); // TODO

	void delete_loops();
	void delete_repeated_edges();
	void make_simple();

	// Get Graph Info
	vertex_t  num_vertices() const { return m_numvertices; }
	size_type num_edges() const { return m_numedges; }

	inline const std::vector<Neighbor>& neighbors(vertex_t n) const { return m_graph[n]; }
	inline const std::vector<Neighbor>& outneighbors(vertex_t n) const { return m_graph[n]; }
	inline const std::vector<Neighbor>& inneighbors(vertex_t n) const { return m_graph[n]; }

	using all_vertices = basic_natural_number<vertex_t>;
	all_vertices vertices() const { return all_vertices(num_vertices()); }

	std::vector<Edge> edges() const; // TODO: make this lazy

	bool is_neighbor(vertex_t from, vertex_t to) const;

	weight_t edge_value(vertex_t from, vertex_t to) const;

	neighbor_const_iterator get_neighbor(vertex_t from, vertex_t to) const;
	neighbor_iterator		get_neighbor(vertex_t from, vertex_t to);

	// Start class definitions
	struct Neighbor
	{
		explicit Neighbor() : vertex(INVALID_VERTEX), m_weight(0) {}

		explicit Neighbor(vertex_t v, weight_t w = 1) : vertex(v), m_weight(w) {}

		inline operator vertex_t() const { return vertex; }

		weight_t weight() const { return m_weight; }

		void set_weight(weight_t w) { m_weight = w; }

		vertex_t vertex{INVALID_VERTEX};

	private:
		// comment out if not needed, and make set_weight do nothing, and make
		// weight() return 1
		weight_t m_weight{1};
	};

	struct Edge
	{
		Edge() : from(INVALID_VERTEX), to(INVALID_VERTEX), m_weight(0) {}
		Edge(vertex_t f, vertex_t t, weight_t w = 1) : from(f), to(t), m_weight(w) {}

		vertex_t operator[](bool i) const { return i ? to : from; }

		// replace by return 1 if weight doesn't exist
		weight_t weight() const { return m_weight; }

		vertex_t from;
		vertex_t to;

		bool operator==(const Edge& E) const { return from == E.from && to == E.to; }

	private:
		weight_t m_weight{1};
	};

private:
	// Graph insides
	size_type m_numvertices;
	size_type m_numedges{0};

	std::vector<neighbor_list> m_graph;
	bool					   m_neighbors_sorted{false};
};
