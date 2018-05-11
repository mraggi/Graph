#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

inline VVI AdjacencyMatrix(const BipartiteGraph& B)
{
    VVI A(B.num_verticesX(), VI(B.num_verticesY(), 0));

    for (auto v : B.verticesX())
    {
        for (auto u : B.neighborsX(v))
        {
            A[v][u] = 1;
        }
    }
    return A;
}

inline bool FindMatch(int i, const VVI& w, VI& mr, VI& mc, VI& seen)
{
    for (int j = 0; j < int(w[i].size()); j++)
    {
        if (w[i][j] && !seen[j])
        {
            seen[j] = true;
            if (mc[j] < 0 || FindMatch(mc[j], w, mr, mc, seen))
            {
                mr[i] = j;
                mc[j] = i;
                return true;
            }
        }
    }
    return false;
}

inline int BipartiteMatching(const VVI& w, VI& mr, VI& mc)
{
    mr = VI(w.size(), -1);
    mc = VI(w[0].size(), -1);

    int ct = 0;
    for (int i = 0; i < int(w.size()); i++)
    {
        VI seen(w[0].size());
        if (FindMatch(i, w, mr, mc, seen))
            ct++;
    }
    return ct;
}
