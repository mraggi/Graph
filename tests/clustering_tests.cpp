#include "Clustering.hpp"
#include "CommonGraphs.hpp"
#include <gtest/gtest.h>
#include <iostream>

void assert_are_same_float(const std::vector<double>& A, const std::vector<double>& B)
{
	ASSERT_EQ(A.size(), B.size());
	for (auto i : indices(A))
	{
		ASSERT_FLOAT_EQ(A[i], B[i]);
	}
}

TEST(Clustering, Empty3)
{
	Graph G(3);

	ASSERT_EQ(num_triangles(G), 0);

	ASSERT_EQ(clustering_global(G), 0);

	std::vector<double> cl = {0, 0, 0};
	assert_are_same_float(clustering_local(G), cl);
}

TEST(Clustering, K3)
{
	Graph G = graphs::Complete(3);

	ASSERT_EQ(num_triangles(G), 1);

	ASSERT_EQ(clustering_global(G), 1);

	std::vector<double> cl = {1, 1, 1};
	assert_are_same_float(clustering_local(G), cl);
}

TEST(Clustering, K4minusedge)
{
	Graph G = graphs::Complete(4);
	G.remove_edge(1, 3);

	ASSERT_EQ(num_triangles(G), 2);

	ASSERT_EQ(clustering_global(G), 0.75);

	std::vector<double> cl = {2.0 / 3.0, 1, 2.0 / 3.0, 1};
	assert_are_same_float(clustering_local(G), cl);
}

TEST(Clustering, Petersen)
{
	Graph G = graphs::Petersen();
	std::vector<double> cl = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	ASSERT_EQ(num_triangles(G), 0);

	ASSERT_EQ(clustering_global(G), 0);
	assert_are_same_float(clustering_local(G), cl);
}
