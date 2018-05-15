#include <cmath>
#include <iostream>
#include <vector>

#include "VectorHelpers.hpp"
#include <set>

template <typename Iter, typename Compare = std::less<std::iterator_traits<Iter>::value_type>>
class RangeMinQuery
{
	using index_type = std::int64_t;
	using Row = std::vector<Iter>;
	using value_type = typename std::iterator_traits<Iter>::value_type > ;

public:
	RangeMinQuery(Iter first, Iter last, Compare comp = std::less<value_type>())
		: first_(first)
		, last_(last)
		, Start_(Initialize(last - first))
		, End_(Initialize(last - first))
		, comp_(comp)
	{
		index_type max_h = Start_[0].size();
		// Initialize Start_ and End_
		for (index_type x = 0; x < A.size(); ++x)
		{
			Start_[x][0] = x;
			End_[x][0] = x;
		}

		for (index_type h = 1; h < max_h; ++h)
		{
			for (index_type x = 0; x < A.size(); ++x)
			{
				if (x + (1 << h) <= A.size())
				{
					index_type mid = x + (1 << (h - 1));
					Start_[x][h] = best(Start_[x][h - 1], Start_[mid][h - 1]);
				}

				if (x - (1 << h) >= -1)
				{
					index_type mid = x - (1 << (h - 1));
					End_[x][h] = best(End_[x][h - 1], End_[mid][h - 1]);
				}
			}
		}

		using namespace std;
		cout << "A = " << A << endl;
		cout << "Start_ = " << Start_ << endl;
		cout << "End_ = " << End_ << endl;
	}

	// Get min index in range [L,R)
	index_type GetMinIndex(index_type L, index_type R)
	{
		index_type h = std::log2(R - L);
		using namespace std;
		cout << "h = " << h << endl;
		index_type min_index_starting_at_L = Start_[L][h];
		cout << "mL = " << min_index_starting_at_L << endl;
		index_type min_index_ending_at_R = End_[R - 1][h];
		cout << "mR = " << min_index_ending_at_R << endl;

		return best(min_index_starting_at_L, min_index_ending_at_R);
	}

private:
	Iter first;
	Iter last;
	// Start_[x][i] contains the index of the minimum of range [x,x+1,...,x+2^i)
	std::vector<Row> Start_;
	// End_[x][i] contains the index of the minimum of range (x-2^i,...,x-1,x]
	std::vector<Row> End_;
	Compare comp_;

	index_type best(index_type i, index_type j)
	{
		if (comp_(A_[i], A_[j]))
			return i;
		return j;
	}

	static std::vector<Row> Initialize(index_type diff)
	{
		return std::vector<Row>(diff, Row(std::log2(diff) + 1));
	}
};

template <typename RAContainer, typename Compare = std::less<typename RAContainer::value_type>>
RangeMinQuery<RAContainer, Compare>
make_range_min_query(const RAContainer& A,
					 Compare comp = std::less<typename RAContainer::value_type>())
{
	return RangeMinQuery<RAContainer, Compare>(A, comp);
}