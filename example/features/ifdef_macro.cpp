
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <vector>
#include <memory>
#include <utility>
#include <limits>
#include <cassert>

//[ifdef_macro_function
#include <boost/contract_macro.hpp>

std::pair<int, int> inc(std::pair<int, int>& p) {
    std::pair<int, int> result;
    BOOST_CONTRACT_OLD_PTR(std::pair<int, int>)(old_pt, p);
    BOOST_CONTRACT_FUNCTION()
        BOOST_CONTRACT_PRECONDITION([&] {
            BOOST_CONTRACT_ASSERT(p.first < std::numeric_limits<int>::max());
            BOOST_CONTRACT_ASSERT(p.second < std::numeric_limits<int>::max());
        })
        BOOST_CONTRACT_POSTCONDITION([&] {
            BOOST_CONTRACT_ASSERT(p.first == old_pt->first + 1);
            BOOST_CONTRACT_ASSERT(p.second == old_pt->second + 1);
            BOOST_CONTRACT_ASSERT(result.first == old_pt->first);
            BOOST_CONTRACT_ASSERT(result.second == old_pt->second);
        })
    ;

    result = p;
    ++p.first;
    ++p.second;
    return result;
}
//]

template<typename T, typename U>
class pushable {
    friend class boost::contract::access; // OK to always leave this in code.

    BOOST_CONTRACT_INVARIANT({
        BOOST_CONTRACT_ASSERT(capacity() <= max_size());
    })

public:
    virtual void push_back(
        std::pair<T, U> const& p,
        boost::contract::virtual_* v = 0 // OK to always leave this in code.
    ) = 0;

protected:
    virtual unsigned capacity() const = 0;
    virtual unsigned max_size() const = 0;
};

template<typename T, typename U> // Contract for pure virtual function.
void pushable<T, U>::push_back(std::pair<T, U> const& p,
        boost::contract::virtual_* v) {
    BOOST_CONTRACT_OLD_PTR(unsigned)(v, old_capacity, capacity());
    BOOST_CONTRACT_PUBLIC_FUNCTION(v, this)
        BOOST_CONTRACT_PRECONDITION([&] {
            BOOST_CONTRACT_ASSERT(capacity() < max_size());
        })
        BOOST_CONTRACT_POSTCONDITION([&] {
            BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
        })
    ;
    assert(false); // Shall never execute this body.
}

//[ifdef_macro_class
template<typename Int, class Alloc = std::allocator<Int> >
class integers
    #define BASES public pushable<Int, Int>
    :
        private boost::contract::constructor_precondition<
                integers<Int, Alloc> >, // OK to always leave this in code.
        BASES
{
    // These can be left in the code.
    friend class boost::contract::access;
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;

    BOOST_CONTRACT_INVARIANT({
        BOOST_CONTRACT_ASSERT(size() <= capacity());
    })

public:
    integers(Int from, Int to) :
        BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(integers)([&] {
            BOOST_CONTRACT_ASSERT(from <= to);
        }),
        vect_(to - from + 1)
    {
        BOOST_CONTRACT_CONSTRUCTOR(this)
            BOOST_CONTRACT_POSTCONDITION([&] {
                BOOST_CONTRACT_ASSERT(int(size()) == (to - from + 1));
            })
        ;

        for(Int x = from; x <= to; ++x) {
            vect_.at(x - from) = std::pair<Int, Int>(x, x);
        }
    }
    
    virtual ~integers() {
        BOOST_CONTRACT_DESTRUCTOR(this); // Check invariants.
    }

    virtual void push_back(
        std::pair<Int, Int> const& p,
        boost::contract::virtual_* v = 0 // OK to always leave this in code.
    ) /* override */ {
        BOOST_CONTRACT_OLD_PTR(unsigned)(old_size);
        BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(override_push_back)(v,
                &integers::push_back, this, p)
            BOOST_CONTRACT_PRECONDITION([&] {
                BOOST_CONTRACT_ASSERT(size() < max_size());
            })
            BOOST_CONTRACT_OLD([&] {
                old_size = BOOST_CONTRACT_OLDOF(v, size());
            })
            BOOST_CONTRACT_POSTCONDITION([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
            })
            BOOST_CONTRACT_EXCEPT([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size);
            })
        ;

        vect_.push_back(p);
    }

private:
    BOOST_CONTRACT_OVERRIDE(push_back) // OK to always leave this in code.

    /* ... */
//]

public: // Could program contracts for these too...
    unsigned size() const { return vect_.size(); }
    unsigned max_size() const { return vect_.max_size(); }
    unsigned capacity() const { return vect_.capacity(); }

private:
    std::vector<std::pair<Int, Int>, Alloc> vect_;
};

int main() {
    std::pair<int, int> p(123, 456);
    std::pair<int, int> q = inc(p);
    BOOST_CONTRACT_CHECK(p.first == 124);
    BOOST_CONTRACT_CHECK(p.second == 457);
    BOOST_CONTRACT_CHECK(q.first == 123);
    BOOST_CONTRACT_CHECK(q.second == 456);

    integers<int> i(1, 10);
    i.push_back(inc(q));
    BOOST_CONTRACT_CHECK(q.first == 124);
    BOOST_CONTRACT_CHECK(q.second == 457);
    BOOST_CONTRACT_CHECK(i.size() == 11);
    return 0;
}

