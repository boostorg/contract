
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
bool random_binary_search(RandomIter first, RandomIter last, T const& value) {
    boost::contract::check c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(first <= last);
            // Expensive O(n) assertion so marked "audit".
            CONTRACT_ASSERT_AUDIT(std::is_sorted(first, last));
        })
    ;

    /* ... */
//]

    while(first < last) {
        RandomIter middle = first + ((last - first) >> 1);
        BOOST_CONTRACT_CHECK(*first <= *middle || value < *middle ||
                *middle < value);
        
        if(value < *middle) last = middle;
        else if(value > *middle) first = middle + 1;
        else return true;
    }
    return false;
}

int main() {
    std::vector<char> i(3);
    i[0] = 'a'; i[1] = 'b'; i[2] = 'c';
    assert(random_binary_search(i.begin(), i.end(), 'b'));
    return 0;
}

