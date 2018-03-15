#include "TreeAlgorithms.hpp"
#include "ConnectedComponents.hpp"
#include <unordered_set>

bool is_tree(const Graph& G) { return G.num_edges() + 1 == G.num_vertices() && is_connected(G); }

// std::vector<Graph::Vertex> set_root(const Graph& G, Graph::Vertex root)
// {
//     FILL HERE!!
// }
