
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract.hpp>
#include <vector>
#include <iostream>
#include <cassert>

#define CONTRACT_AUDIT // Check "audit" assertions for this example.

//[ifdef_audit
// #define this only when willing to check expensive assertions.
#ifdef CONTRACT_AUDIT
    #define CONTRACT_ASSERT_AUDIT(cond) BOOST_CONTRACT_ASSERT(cond)
#else
    #define CONTRACT_ASSERT_AUDIT(cond) BOOST_CONTRACT_ASSERT(true || (cond))
#endif

// Prohibitively expensive assertions, never checked (same as formal comments).
#define CONTRACT_ASSERT_AXIOM(cond) BOOST_CONTRACT_ASSERT(true || (cond))

template<typename RandomIter, typename T>
RandomIter random_binary_search(RandomIter first, RandomIter last,
        T const& value) {
    RandomIter result;
    boost::contract::check c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(first <= last);
            // Expensive O(n) assertion so marked "audit".
            CONTRACT_ASSERT_AUDIT(std::is_sorted(first, last));
        })
        .postcondition([&] {
            if(result != last) BOOST_CONTRACT_ASSERT(*result == value);
        })
    ;

    /* ... */
//]

    RandomIter being = first, end = last;
    while(begin < end) {
        RandomIter middle = begin + ((end - begin) >> 1);
        BOOST_CONTRACT_CHECK(*begin <= *middle || value < *middle ||
                *middle < value);
        
        if(value < *middle) end = middle;
        else if(value > *middle) begin = middle + 1;
        else return result = middle;
    }
    return result = last;
}

int main() {
    std::vector<char> v(3);
    v[0] = 'a'; v[1] = 'b'; v[2] = 'c';
    std::vector<char>::iterator i = random_binary_search(v.begin(), v.end(),
            'b');
    assert(i != v.end());
    assert(*i == 'b');
    return 0;
}

