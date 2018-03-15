#include "Graph.hpp"
#include "VectorHelpers.hpp"

using Vertex = Graph::Vertex;
using weight_t = Graph::weight_t;
using size_type = Graph::size_type;
using sumweight_t = Graph::sumweight_t;
using Neighbor = Graph::Neighbor;
using Edge = Graph::Edge;
using neighbor_iterator = Graph::neighbor_iterator;
using neighbor_const_iterator = Graph::neighbor_const_iterator;

Graph::Graph(Vertex numberOfVertices)
	: m_numvertices(std::max<Vertex>(0, numberOfVertices)), m_graph(m_numvertices)
{}

// Graph modification functions
void Graph::add_edge(Vertex from, Vertex to, weight_t w)
{
	m_graph[from].emplace_back(to, w);
	m_graph[to].emplace_back(from, w);
	++m_numedges;
	m_neighbors_sorted = false;
}

void Graph::add_edge(const Edge& e) { add_edge(e.from, e.to, e.weight()); }

bool Graph::add_edge_no_repeat(Vertex from, Vertex to, weight_t w)
{
	if (is_neighbor(from, to))
		return false;

	add_edge(from, to, w);
	return true;
}

void Graph::add_edges(const std::initializer_list<Edge>& edges)
{
	for (auto& e : edges)
		add_edge(e);
}

Vertex Graph::add_vertex()
{
	m_graph.emplace_back(); // empty vector
	return m_numvertices++;
}

std::vector<Edge> Graph::edges() const
{
	std::vector<Edge> total;

	for (auto u : vertices())
	{
		for (auto v : m_graph[u])
		{
			if (v > u)
				total.emplace_back(u, v, v.weight());
		}
	}

	return total;
}

void Graph::sort_neighbors()
{
	if (m_neighbors_sorted)
		return;

	for (auto& adj_list : m_graph)
		sort(adj_list.begin(), adj_list.end());

	m_neighbors_sorted = true;
}

bool Graph::is_neighbor(Vertex from, Vertex to) const
{
	if (degree(from) > degree(to))
		std::swap(from, to);

	auto& NF = neighbors(from);

	if (m_neighbors_sorted)
		return std::binary_search(NF.begin(), NF.end(), to);

	for (auto& a : NF)
	{
		if (a == to)
			return true;
	}

	return false;
}

neighbor_iterator Graph::get_neighbor(Vertex from, Vertex to)
{
	auto first = m_graph[from].begin();
	auto last = m_graph[from].end();

	if (m_neighbors_sorted)
		return find_binary(first, last, to);

	return std::find(first, last, to);
}

neighbor_const_iterator Graph::get_neighbor(Vertex from, Vertex to) const
{
	auto first = m_graph[from].begin();
	auto last = m_graph[from].end();

	if (m_neighbors_sorted)
		return find_binary(first, last, to);

	return std::find(first, last, to);
}

weight_t Graph::edge_value(Vertex from, Vertex to) const
{
	if (degree(from) > degree(to))
		std::swap(from, to);

	auto neigh = get_neighbor(from, to);

	if (neigh == neighbors(from).end() || *neigh != to)
		return 0;

	return neigh->weight();
}

void Graph::delete_loops()
{
	for (auto v : vertices())
	{
		auto& NV = m_graph[v];
		auto newend = std::remove(NV.begin(), NV.end(), v);
		NV.erase(newend, NV.end());
	}
}

void Graph::delete_repeated_edges()
{
	sort_neighbors();

	for (auto& adj_list : m_graph)
	{
		auto newend = std::unique(adj_list.begin(), adj_list.end());
		adj_list.erase(newend, adj_list.end());
	}
}

void Graph::make_simple()
{
	delete_loops();
	delete_repeated_edges();
}

void Graph::remove_edge(Vertex v, Vertex u)
{
	m_neighbors_sorted = false;

	auto it = get_neighbor(v, u);
	remove_unordered(m_graph[v], it);

	auto it2 = get_neighbor(u, v);
	remove_unordered(m_graph[u], it2);

	--m_numedges;
}

void Graph::remove_vertex(Vertex v)
{
	assert(v >= 0 && v < num_vertices());
	Vertex last_vertex = num_vertices() - 1;

	for (auto u : neighbors(v))
	{
		auto& X = m_graph[u];
		auto it = std::remove(X.begin(), X.end(), v);
		m_numedges -= X.end() - it;
		X.erase(it, X.end());
	}

	if (v != last_vertex)
	{
		// Replace all occurrences of last_vertex to now be v
		for (auto u : neighbors(last_vertex))
		{
			for (auto& w : m_graph[u])
			{
				if (w.vertex == last_vertex)
					w.vertex = v;
			}
		}

		m_graph[v] = m_graph[last_vertex];
	}

	m_graph.pop_back();
	--m_numvertices;
	m_neighbors_sorted = false;
}
