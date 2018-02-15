#include "Graph.hpp"
#include "VectorHelpers.hpp"

using vertex_t				  = Graph::vertex_t;
using weight_t				  = Graph::weight_t;
using size_type				  = Graph::size_type;
using sumweight_t			  = Graph::sumweight_t;
using Neighbor				  = Graph::Neighbor;
using Edge					  = Graph::Edge;
using neighbor_iterator		  = Graph::neighbor_iterator;
using neighbor_const_iterator = Graph::neighbor_const_iterator;

Graph::Graph(vertex_t numberOfVertices)
	: m_numvertices(std::max(vertex_t(0), numberOfVertices)), m_graph(m_numvertices)
{}

// Graph modification functions
void Graph::add_edge(vertex_t from, vertex_t to, weight_t w)
{
	m_graph[from].emplace_back(to, w);
	m_graph[to].emplace_back(from, w);
	++m_numedges;
	m_neighbors_sorted = false;
}

void Graph::add_edge(const Edge& e) { add_edge(e.from, e.to, e.weight()); }

bool Graph::add_edge_no_repeat(vertex_t from, vertex_t to, weight_t w)
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

vertex_t Graph::add_vertex()
{
	vertex_t r = m_numvertices;
	++m_numvertices;
	m_graph.emplace_back(); // empty vector
	return r;
}

// void Graph::remove_edge(vertex_t a, vertex_t b)
// {
//
// }

std::vector<Edge> Graph::edges() const
{
	std::vector<Edge> total;

	for (vertex_t u = 0; u < m_numvertices; ++u)
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

	for (auto v : vertices())
	{
		sort(m_graph[v].begin(), m_graph[v].end());
	}

	m_neighbors_sorted = true;
}

bool Graph::is_neighbor(vertex_t from, vertex_t to) const
{
	if (degree(from) > degree(to))
		std::swap(from, to);

	if (m_neighbors_sorted)
	{
		return std::binary_search(neighbors(from).begin(), neighbors(from).end(), to);
	}
	else
	{
		for (auto& a : neighbors(from))
		{
			if (a == to)
				return true;
		}

		return false;
	}
}

neighbor_iterator Graph::get_neighbor(vertex_t from, vertex_t to)
{
	auto first = m_graph[from].begin();
	auto last  = m_graph[from].end();

	if (m_neighbors_sorted)
	{
		return find_binary(first, last, to);
	}
	else
	{
		return std::find(first, last, to);
	}
}

neighbor_const_iterator Graph::get_neighbor(vertex_t from, vertex_t to) const
{
	if (m_neighbors_sorted)
	{
		auto it = std::partition_point(m_graph[from].begin(),
									   m_graph[from].end(),
									   [to](const vertex_t& a) { return vertex_t(a) < to; });

		if (it == m_graph[from].end() || *it != to)
			return m_graph[from].end();

		return it;
	}
	else
	{
		return std::find_if(
		  m_graph[from].begin(), m_graph[from].end(), [to](auto& N) { return vertex_t(N) == to; });
	}
}

weight_t Graph::edge_value(vertex_t from, vertex_t to) const
{
	if (degree(from) > degree(to))
		std::swap(from, to);

	auto neigh = get_neighbor(from, to);

	if (neigh == neighbors(from).end() || vertex_t(*neigh) != to)
	{
		return 0;
	}

	return neigh->weight();
}

void Graph::delete_loops()
{
	for (auto v : vertices())
	{
		auto newend = std::remove(m_graph[v].begin(), m_graph[v].end(), v);
		m_graph[v].erase(newend, m_graph[v].end());
	}
}

void Graph::delete_repeated_edges()
{
	sort_neighbors();

	for (auto v : vertices())
	{
		auto newend = std::unique(m_graph[v].begin(), m_graph[v].end());
		m_graph[v].erase(newend, neighbors(v).end());
	}
}

void Graph::make_simple()
{
	delete_loops();
	delete_repeated_edges();
}

void Graph::remove_edge(vertex_t v, vertex_t u)
{
	auto it = get_neighbor(v, u);
	remove_unordered(m_graph[v], it);
	m_neighbors_sorted = false;

	auto it2 = get_neighbor(u, v);
	remove_unordered(m_graph[u], it2);
	m_neighbors_sorted = false;
	--m_numedges;
}

void Graph::remove_vertex(vertex_t v)
{
	assert(v >= 0 && v < num_vertices());
	vertex_t last_vertex = num_vertices() - 1;

	for (auto u : neighbors(v))
	{
		auto& X  = m_graph[u];
		auto  it = std::remove_if(X.begin(), X.end(), [v](auto& t) { return vertex_t(t) == v; });
		m_numedges -= X.end() - it;
		X.erase(it, X.end());
	}

	if (v != last_vertex)
	{
		for (auto u : neighbors(last_vertex))
		{
			for (auto& w : m_graph[u])
			{
				if (w.vertex == last_vertex)
				{
					w.vertex = v;
				}
			}
		}

		m_graph[v] = m_graph[last_vertex];
	}

	m_graph.pop_back();
	--m_numvertices;
	m_neighbors_sorted = false;
}
