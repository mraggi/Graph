#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

template <typename RAContainer,
          typename Compare = std::less<typename RAContainer::value_type>>
class range_min_query
{
    using index_type = std::make_signed_t<size_t>;
    using Row = std::vector<index_type>;
    using value_type = typename RAContainer::value_type;

public:
    range_min_query(const RAContainer& A,
                    Compare comp = std::less<value_type>())
        : A_(A), T(A.size(), Row(std::log2(A.size()) + 1, -1)), comp_(comp)
    {
        index_type n = A.size();
        index_type max_h = T[0].size();

        for (index_type x = 0; x < n; ++x)
        {
            T[x][0] = x;
        }

        for (index_type h = 1; h < max_h; ++h)
        {
            for (index_type x = 0; x < n; ++x)
            {
                if (x + (1 << h) <= n)
                {
                    index_type mid = x + (1 << (h - 1));
                    T[x][h] = best(T[x][h - 1], T[mid][h - 1]);
                }
            }
        }
    }

    // Get min index in range [L,R)
    index_type GetMinIndex(index_type L, index_type R) const
    {
        assert(0 <= L && L < R && R <= index_type(A_.size()));
        index_type h = std::log2(R - L);

        index_type min_index_starting_at_L = T[L][h];
        index_type min_index_ending_at_R = BestEndingAt(R - 1, h);

        return best(min_index_starting_at_L, min_index_ending_at_R);
    }

private:
    // A reference to the original container
    const RAContainer& A_;

    // T[x][i] contains the index of the
    // minimum of range [x,x+1,...,x+2^i)
    std::vector<Row> T;

    Compare comp_;

    index_type best(index_type i, index_type j) const
    {
        if (comp_(A_[j], A_[i]))
            return j;
        return i;
    }

    index_type BestEndingAt(index_type R, index_type h) const
    {
        return T[R - (1 << h) + 1][h];
    }
};

// This function is deprecated with C++17, but useful in c++14 and 11
template <typename RAContainer,
          typename Compare = std::less<typename RAContainer::value_type>>
range_min_query<RAContainer, Compare> make_range_min_query(
  const RAContainer& A,
  Compare comp = std::less<typename RAContainer::value_type>())
{
    return range_min_query<RAContainer, Compare>(A, comp);
}
