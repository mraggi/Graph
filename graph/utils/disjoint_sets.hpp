#pragma once

#include <numeric>
#include <vector>

class disjoint_sets
{
public:
	disjoint_sets(long n) : parent(n) { std::iota(parent.begin(), parent.end(), 0); }

	long find_root(long t)
	{
		std::vector<long> branch;
		branch.emplace_back(t);
		while (t != parent[t])
		{
			t = parent[t];
			branch.emplace_back(t);
		}
		for (auto u : branch)
			parent[u] = t;
		return t;
	}

	void merge(long a, long b)
	{
		long ra = find_root(a);
		set_parent(b, ra);
	}

	bool are_in_same_connected_component(long a, long b) { return find_root(a) == find_root(b); }

	long size() const { return parent.size(); }

	// private:

	void set_parent(long x, long p)
	{
		while (x != parent[x])
		{
			long t	= parent[x];
			parent[x] = p;
			x		  = t;
		}
		parent[x] = p;
	}

	std::vector<long> parent;
};
