#include "GraphDrawing.hpp"

vector<Point> CalculateForces(size_t n, const vector<edge_t>& E, double R, const vector<Point>& P)
{
	const double k = 0.005;
	vector<Point> toReturn(n);
	for (auto e : E)
	{
		vertex_t a = e[0];
		vertex_t b = e[1];
		Point A = P[a];
		Point B = P[b];
		double D = A.Distance(B);
		Point F = k * (D - R) * (B - A) / D;
		toReturn[a] += F;
		toReturn[b] -= F;
	}
	const double c = 1000;
	for (int a = 0; a < n; ++a)
	{
		for (int b = a + 1; b < n; ++b)
		{
			double D2 = (P[a] - P[b]).LengthSq();
			Point F = (P[a] - P[b]) * c / D2;
			toReturn[a] += F;
			toReturn[b] -= F;
		}
	}

	return toReturn;
}

vector<Point> CircularDrawing(int n, double R)
{
	VP P(n);

	for (int i = 0; i < n; ++i)
		P[i].SetPolar(R, i * 2 * pi / n);

	return P;
}

vector<Point> GridGraphDrawing(int n, int m, double R)
{
	vector<Point> toReturn;
	toReturn.reserve((n + 1) * (m + 1));
	for (int x = 0; x <= n; ++x)
	{
		for (int y = 0; y <= m; ++y)
		{
			toReturn.push_back(R * Point(x, y));
		}
	}
	return toReturn;
}

vector<Point> GoodDrawing(const Graph& G, double R)
{
	auto n = G.num_vertices();
	VP P(n);

	// 	for (int i = 0; i < n; ++i)
	// 		P[i] = Point::RandomPoint(0,R*n/2.0);
	// 	vector<edge_t> E = G.edges();
	//
	// 	const int numtimes = 100;
	// 	const double frame = 1.0/numtimes;
	//
	// 	for (int i = 0; i < numtimes; ++i)
	// 	{
	// 		auto F = CalculateForces(n,E,R,P);
	// 		cout << "F = " << F << endl;
	// 		cout << "\tP = " << P << endl;
	// 		for (size_t v = 0; v < n; ++v)
	// 		{
	// 			P[v] += frame*F[v];
	// 		}
	// 		cout << "\tP = " << P << endl;
	// 	}

	return P;
}

vector<Point> TreeDrawing(const Graph& G, int start, double R)
{
	auto n = G.num_vertices();
	VP P(n);

	// TODO

	return P;
}

void DrawGraph(Client& C, const Graph& G, const vector<Point>& P, const sf::Color& color)
{
	for (vertex_t n = 0; n < G.num_vertices(); ++n)
	{
		for (auto u : G.neighbors(n))
		{
			Segment S(P[n], P[u]);
			C.Render(S, sf::Color::Blue, 2);
		}
	}

	for (vertex_t n = 0; n < G.num_vertices(); ++n)
	{
		C.Render(P[n], color, 10);
	}
}

void DrawGraph(Client& C,
			   const Graph& G,
			   const vector<Point>& P,
			   const vector<sf::Color>& vertex_colors)
{
	for (vertex_t n = 0; n < G.num_vertices(); ++n)
	{
		for (auto u : G.neighbors(n))
		{
			Segment S(P[n], P[u]);
			C.Render(S, sf::Color::Blue, 2);
		}
	}

	for (vertex_t n = 0; n < G.num_vertices(); ++n)
	{
		C.Render(P[n], vertex_colors[n], 10);
	}
}

void DrawGraph(Client& C, const DiGraph& G, const vector<Point>& P, const sf::Color& color)
{
	for (vertex_t n = 0; n < G.num_vertices(); ++n)
	{
		for (auto u : G.outneighbors(n))
		{
			Segment S(P[n], P[u]);
			C.Render(S, sf::Color::Blue, 2, true);
		}
	}

	for (vertex_t n = 0; n < G.num_vertices(); ++n)
	{
		C.Render(P[n], color, 10);
	}
}

void DrawGraph(Client& C,
			   const DiGraph& G,
			   const vector<Point>& P,
			   const vector<sf::Color>& vertex_colors)
{
	for (vertex_t n = 0; n < G.num_vertices(); ++n)
	{
		for (auto u : G.outneighbors(n))
		{
			Segment S(P[n], P[u]);
			C.Render(S, sf::Color::Blue, 2, true);
		}
	}

	for (vertex_t n = 0; n < G.num_vertices(); ++n)
	{
		C.Render(P[n], vertex_colors[n], 10);
	}
}
