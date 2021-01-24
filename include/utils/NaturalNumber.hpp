#pragma once
#include "Misc.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

//////////////////////////////////////////
/// \brief In set theory, a common way of defining a natural number is. n :=
/// {0,1,2,...,n-1}, with 0 = {}.
//////////////////////////////////////////
template <class IntType>
class basic_natural_number
{
public:
    using difference_type = std::int64_t;
    using size_type = IntType;
    using value_type = IntType;
    class iterator;
    using const_iterator = iterator;

public:
    explicit basic_natural_number(IntType n) : m_n(n) {}

    class iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = IntType;
        using difference_type = std::int64_t;
        using pointer = IntType const*;
        using reference = const IntType&;

        explicit iterator(IntType t = 0) : m_ID(t) {}

        inline iterator& operator++()
        {
            ++m_ID;
            return *this;
        }

        inline iterator& operator--()
        {
            --m_ID;
            return *this;
        }

        inline const IntType& operator*() const { return m_ID; }

        inline iterator& operator+=(difference_type n)
        {
            m_ID += n;
            return *this;
        }

        inline iterator& operator-=(difference_type n)
        {
            return operator+=(-n);
        }

        inline bool operator==(const iterator& it) { return *it == m_ID; }

        inline bool operator!=(const iterator& it) { return *it != m_ID; }

        inline difference_type operator-(const iterator& it)
        {
            return m_ID - *it;
        }

    private:
        IntType m_ID{0};
    }; // end class iterator

    iterator begin() const { return iterator(0); }
    iterator end() const { return iterator(m_n); }

    IntType operator[](size_type m) const { return m; }
    size_type size() const { return m_n; }

    // Returns the first natural number (between 0 and size()) for which Pred is
    // false and *end() otherwise.
    template <class Pred>
    IntType partition_point(Pred p)
    {
        return *std::partition_point(begin(), end(), p);
    }

    explicit operator std::vector<IntType>() const
    {
        return std::vector<IntType>(begin(), end());
    }

    auto to_vector() const { return std::vector<IntType>(*this); };

private:
    IntType m_n;
}; // end class basic_natural_number

template <class IntType>
inline typename basic_natural_number<IntType>::iterator
operator+(typename basic_natural_number<IntType>::iterator it,
          typename basic_natural_number<IntType>::difference_type n)
{
    it += n;
    return it;
}

template <class IntType>
inline typename basic_natural_number<IntType>::iterator
operator-(typename basic_natural_number<IntType>::iterator it,
          typename basic_natural_number<IntType>::difference_type n)
{
    it -= n;
    return it;
}

using natural_number = basic_natural_number<int>;
using big_natural_number = basic_natural_number<std::int64_t>;

template <class IntType>
class basic_natural_number_range
{
public:
    using difference_type = std::int64_t;
    using size_type = IntType;
    using value_type = IntType;
    using iterator = typename basic_natural_number<IntType>::iterator;
    using const_iterator = iterator;

    explicit basic_natural_number_range(IntType n) : m_end(n)
    {
        if (m_end < 0)
            m_end = 0;
    }

    basic_natural_number_range(IntType a, IntType b) : m_start(a), m_end(b)
    {
        if (m_end < m_start)
            m_end = m_start;
    }

    iterator begin() const { return iterator(m_start); }
    iterator end() const { return iterator(m_end); }

    IntType operator[](size_type m) const { return m_start + m; }
    IntType size() const { return m_end - m_start; }

    template <class Pred>
    IntType partition_point(Pred p)
    {
        return *std::partition_point(begin(), end(), p);
    }

    auto to_vector() const { return std::vector<IntType>(*this); };

    explicit operator std::vector<IntType>() const
    {
        return std::vector<IntType>(begin(), end());
    }

private:
    IntType m_start{0};
    IntType m_end;
};

template <class Container, class T = typename Container::size_type>
auto indices(const Container& C)
{
    return basic_natural_number<T>(C.size());
}

template <class IntType>
auto NN(IntType n)
{
    return basic_natural_number<IntType>{n};
}

template <class IntType>
auto NN(IntType from, IntType to)
{
    return basic_natural_number_range<IntType>(from, to);
}

template <class IntType>
auto operator-(const basic_natural_number<IntType>& A,
               const basic_natural_number<IntType>& B)
{
    return NN(B.size(), A.size());
}
