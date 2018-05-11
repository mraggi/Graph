#include "Probability.hpp"
#include "RangeMinQuery.hpp"
#include "VectorHelpers.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(RMQ, Compilation)
{
    std::vector<int> A(1, 0);
    auto RMQ = make_range_min_query(A);

    ASSERT_EQ(RMQ.GetMinIndex(0, 1), 0);
}

TEST(RMQ, SmallCase)
{
    std::vector<int> A = {1, 0, 3, 4};
    auto RMQ = make_range_min_query(A);

    ASSERT_EQ(RMQ.GetMinIndex(0, 3), 1);
    ASSERT_EQ(RMQ.GetMinIndex(2, 4), 2);
    ASSERT_EQ(RMQ.GetMinIndex(0, 1), 0);
    ASSERT_EQ(RMQ.GetMinIndex(1, 2), 1);
    ASSERT_EQ(RMQ.GetMinIndex(2, 3), 2);
    ASSERT_EQ(RMQ.GetMinIndex(3, 4), 3);
}

template <class Container>
int brute_force_rmq(const Container& A, int L, int R)
{
    int best = L;
    for (; L < R; ++L)
    {
        if (A[L] < A[best])
            best = L;
    }
    return best;
}

TEST(RMQ, MedCase)
{
    std::vector<int> A = {7, 2, 3, 0, 5, 10, 3, 12, 18};
    auto RMQ = make_range_min_query(A);

    ASSERT_EQ(RMQ.GetMinIndex(0, 5), 3);
    ASSERT_EQ(RMQ.GetMinIndex(4, 8), 6);
    ASSERT_EQ(RMQ.GetMinIndex(7, 9), 7);
    ASSERT_EQ(RMQ.GetMinIndex(1, 5), 3);
}

TEST(RMQ, MedCaseOtherComparison)
{
    std::vector<int> A = {87, 92, 53, 70, 15, 40, 23, 52, 28};
    auto RMQ =
      make_range_min_query(A, [](int a, int b) { return a%10 < b%10; });

    ASSERT_EQ(RMQ.GetMinIndex(0, 3), 1);
    ASSERT_EQ(RMQ.GetMinIndex(5, 8), 5);
    ASSERT_EQ(RMQ.GetMinIndex(6, 8), 7);
}

TEST(RMQ, BigCase)
{
    for (int i = 0; i < 200; ++i)
    {
        std::vector<int> A(random_int(1, 50));

        std::generate(A.begin(), A.end(), []() { return random_int(0, 10); });

        auto RMQ = make_range_min_query(A);

        for (size_t L = 0; L < A.size(); ++L)
        {
            for (size_t R = L + 1; R < A.size(); ++R)
            {
                auto fast_rmq = RMQ.GetMinIndex(L, R);
                auto slow_rmq = brute_force_rmq(A, L, R);

                ASSERT_EQ(fast_rmq, slow_rmq);
            }
        }
    }
}
