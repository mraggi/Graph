#include "Graph.hpp"

using vertex_t = Graph::vertex_t;
using weight_t = Graph::weight_t;
using size_type = Graph::size_type;
using sumweight_t = Graph::sumweight_t;
using Neighbor = Graph::Neighbor;
using Edge = Graph::Edge;
using neighbor_iterator = Graph::neighbor_iterator;

Graph::Graph(vertex_t numberOfVertices):
		m_numvertices(numberOfVertices),
		m_graph(numberOfVertices)
{
}

// Graph modification functions
void Graph::add_edge(vertex_t from, vertex_t to, weight_t w)
{
	m_graph[from].emplace_back(to,w);
	m_graph[to].emplace_back(from,w);
	++m_numedges;
	m_neighbors_sorted = false;
}

void Graph::add_edge(const Edge& e)
{
	add_edge(e.from,e.to,e.weight());
}

bool Graph::add_edge_no_repeat(vertex_t from, vertex_t to, weight_t w)
{
	if (is_neighbor(from,to))
		return false;
	
	add_edge(from,to,w);
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
	m_graph.emplace_back(); //empty vector
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
				total.emplace_back(u,v,v.weight());
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
		std::swap(from,to);
	
	if (m_neighbors_sorted)
	{
		return std::binary_search(neighbors(from).begin(), neighbors(from).end(),to);
	} else
	{
		for (auto& a : neighbors(from))
		{
			if (a == to)
				return true;
		}
		return false;
	}
}


neighbor_iterator Graph::get_neighbor(vertex_t from, vertex_t to) const
{
	if (m_neighbors_sorted)
	{
		return std::partition_point(neighbors(from).begin(), neighbors(from).end(), [to](const vertex_t& a)
		{
			return vertex_t(a) < to;
		});
		
	} else
	{
		auto it = neighbors(from).begin();
		for ( ; it != neighbors(from).end(); ++it)
		{
			if (*it == to)
				return it;
		}
		return it;
	}
}

weight_t Graph::edge_value(vertex_t from, vertex_t to) const 
{
	if (degree(from) > degree(to))
		std::swap(from,to);
	
	auto neigh = get_neighbor(from,to);
	
	if (neigh == neighbors(from).end() || *neigh != to)
		return 0;
	
	return neigh->weight();
}

