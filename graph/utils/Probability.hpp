#pragma once

#include "Misc.hpp"
#include <algorithm>
#include <ctime>
#include <random>
// Who came up with the dumb C++11 way of getting random stuff?
// It's obviously missing some utility functions. Here they are.

/**
 *@brief Just a helper function to get the default random engine
 */
inline std::default_random_engine& random_engine()
{
    using RE = std::default_random_engine;
    using result_type = RE::result_type;
    static RE e(static_cast<result_type>(time(nullptr)));
    return e;
}

/**
 *@brief Returns true with probability p and false with probability 1-p
 *@return true or false according to probability p, which must be a number
 *between 0 and 1.
 */
inline bool probability_of_true(double p)
{
    std::bernoulli_distribution d(p);
    return d(random_engine());
}

/**
 *@brief "I just wanted a random integer!
 *@return A random integer in the range [from,thru), with uniform probability
 *distribution
 */
template <class IntType = int>
IntType random_int(IntType from, IntType thru)
{
    std::uniform_int_distribution<IntType> d{};
    using parm_t = typename decltype(d)::param_type;
    return d(random_engine(), parm_t{from, --thru});
}

/**
 *@brief "I just wanted a random float!
 *@return A random float number in the range [from,thru), with uniform
 *probability distribution
 */
template <class FloatType = double>
FloatType random_real(FloatType from, FloatType upto)
{
    std::uniform_real_distribution<> d{};
    using parm_t = decltype(d)::param_type;
    return d(random_engine(), parm_t{from, upto});
}

template <class RAContainer>
auto random_sample_array(const RAContainer& population, int k)
{
    using T = typename RAContainer::value_type;
    int n = population.size();
    std::vector<T> sample;
    sample.reserve(k);
    std::vector<char> explored(n, 0);

    while (k > 0)
    {
        auto i = random_int<size_t>(0, n);

        if (explored[i] == 0)
        {
            explored[i] = 1;
            sample.emplace_back(population[i]);
            --k;
        }
    }

    return sample;
}

template <class RAContainer>
auto random_sample_shuffle(const RAContainer& population, int k)
{
    using T = typename RAContainer::value_type;

    int n = population.size();

    std::vector<T> sample(population.begin(), population.end());
    for (int i = 0; i < k; ++i)
    {
        int j = random_int(i, n);
        std::swap(sample[i], sample[j]);
    }

    sample.erase(sample.begin() + k, sample.end());
    return sample;
}

template <class RAContainer>
auto random_sample(const RAContainer& population, int k)
{
    using T = typename RAContainer::value_type;
    int n = population.size();

    if (k > n)
        k = n;

    // 	double factor = linear_convert(sizeof(T), 0, 200, 0.0, 0.9);
    // 	factor = std::min(factor,0.95);
    double factor = 0.5;
    if (std::is_trivially_copyable<T>::value)
    {
        factor = 0.1;
    }

    if (k < factor*n)
        return random_sample_array(population, k);

    return random_sample_shuffle(population, k);
}

template <class RAContainer>
auto random_choice(const RAContainer& population)
{
    auto n = population.size();
    return population[random_int<decltype(n)>(0, n)];
}

template <class RAContainer>
auto random_order(const RAContainer& C)
{
    using T = typename RAContainer::value_type;
    std::vector<T> X(C.begin(), C.end());

    std::shuffle(X.begin(), X.end(), random_engine());

    return X;
}

template <class T>
auto random_order(const std::initializer_list<T>& C)
{
    std::vector<T> X(C.begin(), C.end());

    std::shuffle(X.begin(), X.end(), random_engine());

    return X;
}
