#include "PhysicalGraph.hpp"


PhysicalGraph::PhysicalGraph(const Graph& g) : G(g), E(g.edges()), M(g.num_vertices()) 
{
}

PhysicalGraph::PhysicalGraph(vertex_t num_verts) : G(num_verts), E(num_verts), M(num_verts) 
{
	
}

void PhysicalGraph::SetGraph(const Graph& g)
{
	G = g;
	E = g.edges();
	M.resize(g.num_vertices());
}

void PhysicalGraph::Update(double time)
{
	const double maxt = 1.0/60.0;
	const double t = time_since_last_update.Peek();
	
	if (t < maxt)
		return;
	
	time_since_last_update.Reset();
	
	if (!turn_physics_on)
		return;
	
	if (attract_to_center)
	{
		Point CenterOfMass(0,0);
		for (auto x : vertices())
			CenterOfMass += p(x);
		CenterOfMass /= num_vertices();
		
		for (auto x : vertices())
		{
			a(x) = (CenterOfMass - p(x))*force_toward_center; //give a slight pull toward the center
		}
	} else
	{
		for (auto x : vertices())
			a(x).Zero();
	}
	//Repelling force
	if (repulsion_on)
	{
		for (auto x : vertices())
		{
			for (vertex_t y = x+1; y < num_vertices(); ++y)
			{
				auto F = p(x)-p(y);
				auto f2 = F.LengthSq();
				if (f2 == 0)
					F += Point::RandomPoint(2); // perturb a little bit
				if (f2 > 10000000)
					continue;
				F.SetLength(repelling_force/(0.001+sqrt(f2)));
				a(x) += F;
				a(y) -= F;
			}
		}
	}
	
	for (auto e : edges())
	{
		auto x = e.from;
		auto y = e.to;
		
		auto W = p(x)-p(y);
		auto R = W.WithLength(W.Length()-ideal_edge_size);
		auto F = R*hook_constant;
		
		a(y) += F;
		a(x) -= F;
	}
	
	for (auto x : vertices())
	{
		
		v(x) += a(x)*t;
		v(x).Truncate(max_speed);
		p(x) += v(x)*t;
		v(x) *= damping;
	}
	
}

