#pragma once
#include <cassert>
#include <cmath>
#include <vector>

template <class Vector, class Gradient>
void GradientStep(Vector& X, Gradient g, double alpha = 0.001)
{
	X -= alpha * g(X);
}

template <class Vector, class Function, class Gradient>
Vector GradientDescent(const Vector& InitialPoint, Function f, Gradient g)
{
	double alpha	 = 1.0;
	Vector X		 = InitialPoint;
	double currvalue = f(X);

	const long max_num_times = 100000;

	for (long num_times = 0; (alpha > 0.00001) && (num_times < max_num_times); ++num_times)
	{
		GradientStep(X, g, alpha);
		if (f(X) >= currvalue)
		{
			GradientStep(X, g, -alpha); // return to previous!
			alpha /= 2;
		}
	}
	return X;
}

// just a silly interface to std::vector
class MultiDimVector
{
public:
	using size_type = long long;
	explicit MultiDimVector(int n = 0) : data(n, 0.0) {}

	MultiDimVector(const std::vector<double>& V) : data(V) {} // implicit!!

	double  operator[](size_t i) const { return data[i]; }
	double& operator[](size_t i) { return data[i]; }

	size_type size() const { return data.size(); }

	void operator+=(const MultiDimVector& X)
	{
		assert(size() == X.size());
		for (size_t i = 0; i < size(); ++i)
		{
			data[i] += X[i];
		}
	}

	void operator-=(const MultiDimVector& X)
	{
		assert(size() == X.size());
		for (size_t i = 0; i < size(); ++i)
		{
			data[i] -= X[i];
		}
	}

	void operator*=(double a)
	{
		assert(size() == X.size());
		for (size_t i = 0; i < size(); ++i)
		{
			data[i] *= a;
		}
	}

	void operator/=(double a)
	{
		assert(size() == X.size());
		for (size_t i = 0; i < size(); ++i)
		{
			data[i] /= a;
		}
	}

	void resize(int k) { data.resize(k); }

	using const_iterator = std::vector<double>::const_iterator;
	using iterator		 = std::vector<double>::iterator;

	const_iterator begin() const { return data.cbegin(); }
	const_iterator end() const { return data.cend(); }

	iterator begin() { return data.begin(); }
	iterator end() { return data.end(); }

private:
	std::vector<double> data;
};

inline MultiDimVector operator*(double a, const MultiDimVector& X)
{
	auto R = X;
	R *= a;
	return R;
}

//////////////////////////////////////////
/// \brief This function of x is just the linear function from [a,b] to [u,v]
/// (extended to all reals, of course). \return f(x), where f:[a,b]->[u,v] is
/// the only linear, monotone, biyective function.
//////////////////////////////////////////
inline double linear_interpolate(double x, double a, double b, double u, double v)
{
	return (v - u) * (x - a) / (b - a) + u;
}

template <class T, class Compare>
T clamp(const T& v, const T& lo, const T& hi, Compare comp)
{
	return assert(!comp(hi, lo)), comp(v, lo) ? lo : comp(hi, v) ? hi : v;
}

template <class T>
T clamp(const T& v, const T& lo, const T& hi)
{
	return clamp(v, lo, hi, std::less<>());
}