#include "PhysicalGraph.hpp"

void PhysicalGraph::Update(double time)
{

    auto gradient = [this](const MultiDimVector& X) -> MultiDimVector {
        MultiDimVector R(X.size());
        double d2 = ideal_edge_size*ideal_edge_size;

        for (auto a : vertices())
        {
            for (Vertex b = a + 1; b < num_vertices(); ++b)
            {
                auto P = p(a);
                auto Q = p(b);

                double dx = P.x - Q.x;
                double dy = P.y - Q.y;

                double dist2 = dx*dx + dy*dy;

                double rx = 0.0;
                double ry = 0.0;

                if (A[a][b] == 1)
                {
                    rx = (dist2 - d2)*(dx);
                    ry = (dist2 - d2)*(dy);
                }
                else
                {
                    double t = repelling_threshold;
                    double t2 = t*t;
                    if (dist2 < t2)
                    {
                        rx = repelling_force*dist2/(dx + 0.00001);
                        ry = repelling_force*dist2/(dy + 0.00001);
                    }
                }

                double maxval = 1000000;

                rx = clamp(rx, -maxval, maxval);
                ry = clamp(ry, -maxval, maxval);

                R[a*2] += rx;
                R[a*2 + 1] += ry;
                R[b*2] -= rx;
                R[b*2 + 1] -= ry;
            }
        }

        return R;
    };

    // 	double currvalue = cost(X);

    GradientStep(X, gradient, alpha*time);

    // 	if (cost(X) > currvalue)
    // 		alpha /= 2;
    // 	PA.AddElement(cost(X),"Cost");
    PA.AddElement(alpha, "Alpha");

    auto G = gradient(X);
    for (auto v : vertices())
    {
        PA.AddElement(G[2*v], "Gx[" + to_string(v) + "]");
        PA.AddElement(G[2*v + 1], "Gy[" + to_string(v) + "]");
    }
}

// auto cost = [this](const MultiDimVector& X) -> double
// 	{
// 		double result = 0;
//
// 		double d = ideal_edge_size;
//
// 		for (auto& e : edges())
// 		{
// 			auto a = e.from;
// 			auto b = e.to;
//
// 			auto A = p(a);
// 			auto B = p(b);
//
// 			double diff = A.Distance(B) - d;
//
// 			result += (diff)*(diff);
// 		}
//
// 		return result;
// 	};
