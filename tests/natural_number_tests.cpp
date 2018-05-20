#include "NaturalNumber.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(NaturalNumber, Creation)
{
    for (int n = 0; n < 10; ++n)
    {
        natural_number N(n);
        int i = 0;
        for (auto a : N)
        {
            ASSERT_EQ(a, i);
            ASSERT_EQ(a, N[i]);
            ++i;
        }
        i = 0;
        for (auto a : NN(n))
        {
            ASSERT_EQ(a, i);
            ++i;
        }
    }
}

TEST(NaturalNumber, IteratorOperators)
{
    auto N = NN(10);
    auto it = N.begin();

    ASSERT_EQ(*it, 0);
    it += 5;
    ASSERT_EQ(*it, 5);
    it += 3;
    ASSERT_EQ(*it, 8);
    it -= 4;
    ASSERT_EQ(*it, 4);
    ++it;
    ASSERT_EQ(*it, 5);
    ++it;
    ASSERT_EQ(*it, 6);
    --it;
    ASSERT_EQ(*it, 5);
    --it;
    ASSERT_EQ(*it, 4);
    std::advance(it, 1000);
    ASSERT_EQ(*it, 1004);
    auto itprev = std::prev(it);
    ASSERT_EQ(*itprev, 1003);
    auto itnext = std::next(it);
    ASSERT_EQ(*itnext, 1005);
}

TEST(NaturalNumber, NumberRange)
{
    for (int a = 0; a < 10; ++a)
    {
        for (int b = 0; b < 10; ++b)
        {
            auto C = NN(a, b);
            auto D = NN(b) - NN(a);
            ASSERT_EQ(C.size(), D.size());

            ASSERT_TRUE(std::equal(C.begin(), C.end(), D.begin(), D.end()));
            int w = a;
            for (auto x : C)
            {
                ASSERT_EQ(x, w);
                ++w;
            }
            ASSERT_EQ(C.size(), w - a);
            ASSERT_EQ(C.size(), std::max(0, b - a));
        }
    }
}

TEST(NaturalNumber, ToVector)
{
    for (int n = 0; n < 10; ++n)
    {
        auto A = NN(n).to_vector();
        std::vector<int> B(n);
        std::iota(B.begin(), B.end(), 0);
        ASSERT_EQ(A, B);
        for (int m = n; m < 10; ++m)
        {
            auto C = NN(n, m).to_vector();
            std::vector<int> D(m - n);
            std::iota(D.begin(), D.end(), n);
            ASSERT_EQ(C, D);
        }
    }
}

TEST(NaturalNumber, PartitionPoint)
{
    auto gauss = [](long i) { return (i*(i - 1))/2; };

    auto N = NN(100000000000L);

    constexpr long breakpoint = 10000;

    auto x =
      N.partition_point([&gauss](long i) { return gauss(i) < breakpoint; });

    ASSERT_GE(gauss(x), breakpoint);
    ASSERT_LT(gauss(x - 1), breakpoint);

    auto NR = NN(1000, 10000);
    auto y = NR.partition_point([](int i) { return i < 3000; });

    ASSERT_EQ(y, 3000);

    auto z = NR.partition_point([](int i) { return i < 10000000; });
    ASSERT_EQ(z, *NR.end());
}
