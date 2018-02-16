#include "PhysicalGraph.hpp"
#include "Probability.hpp"

PhysicalGraph::PhysicalGraph(const Graph& g) : G(g), E(g.edges()), M(g.num_vertices()) {}

PhysicalGraph::PhysicalGraph(vertex_t num_verts) : G(num_verts), E(num_verts), M(num_verts) {}

void PhysicalGraph::SetGraph(const Graph& g)
{
	G = g;
	E = g.edges();
	M.resize(g.num_vertices());
}

void PhysicalGraph::AttractToCenter()
{
	Point CenterOfMass(0, 0);

	for (auto x : vertices())
		CenterOfMass += p(x);

	CenterOfMass /= num_vertices();

	for (auto x : vertices())
	{
		a(x) = (CenterOfMass - p(x)) * force_toward_center;
	}
}

void PhysicalGraph::Repell()
{
	real r2 = repelling_force * repelling_force;
	for (auto x : vertices())
	{
		for (vertex_t y = x + 1; y < num_vertices(); ++y)
		{
			auto F = p(x) - p(y);
			auto f2 = F.LengthSq();

			if (std::abs(f2) < 0.0001)
			{
				F += Point::RandomPoint(2); // perturb a little bit
				f2 = F.LengthSq();
			}

			if (f2 > 10e10) // they are too far away
				continue;

			F.SetLengthSq(r2 / (0.001 + f2));
			a(x) += F;
			a(y) -= F;
		}
	}
}

void PhysicalGraph::Spring()
{
	for (auto e : edges())
	{
		auto x = e.from;
		auto y = e.to;

		auto W = p(x) - p(y);
		auto R = W.WithLength(W.Length() - ideal_edge_size);
		auto F = R * hook_constant;

		a(y) += F;
		a(x) -= F;
	}
}

void PhysicalGraph::Update(real time)
{
	if (!turn_physics_on)
		return;

	const real t = 1.0 / 60.0;
	time_since_last_update += time;

	if (time_since_last_update < t)
		return;

	time_since_last_update = 0.0;

	if (attract_to_center)
	{
		AttractToCenter();
	}
	else
	{
		for (auto x : vertices())
			a(x).Zero();
	}

	// Repelling force
	if (repulsion_on)
		Repell();

	Spring();

	for (auto x : vertices())
	{

		v(x) += a(x) * t;
		v(x).Truncate(max_speed);
		v(x) *= damping;
		p(x) += v(x) * t;
	}
}
