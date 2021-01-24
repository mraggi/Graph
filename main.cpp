#include "Graph.hpp"
#include "Misc.hpp"
#include "NaturalNumber.hpp"
#include "Probability.hpp"
#include "VectorHelpers.hpp"

#include "BipartiteMatching.hpp"

int main()
{
    using std::cout;
    using std::endl;

    BipartiteGraph G(5, 5);

    G.add_edges({{0, 0},
                 {0, 1},
                 {0, 2},
                 {1, 0},
                 {1, 3},
                 {2, 2},
                 {2, 4},
                 {3, 0},
                 {3, 1},
                 {3, 4}});

    BipartiteMatcher M(G);

    return 0;
}
