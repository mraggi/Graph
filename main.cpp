#include "Graph.hpp"
#include "Misc.hpp"
#include "Probability.hpp"

using namespace std;

int main()
{
	Graph G(4);
	G.add_edge(0, 1);
	G.add_edge(0, 3);
	for (auto a : G.vertices())
	{
		cout << "Here are the neighbors of " << a << ": ";
		for (auto b : G.neighbors(a))
		{
			cout << b << ' ';
		}
		cout << endl;
	}

	return 0;
}
