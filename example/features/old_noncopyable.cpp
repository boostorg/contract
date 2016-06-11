
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract.hpp>
#include <cassert>

//[old_noncopyable
template<typename T>
void accumulate(T& total, T const& x) {
    // No compiler error if T has no copy constructor...
    boost::contract::old_ptr_noncopyable<T> old_total =
            BOOST_CONTRACT_OLDOF(total);
    boost::contract::guard c = boost::contract::function()
        .postcondition([&] {
            // ...but old value null if T has no copy constructor.
            if(old_total) BOOST_CONTRACT_ASSERT(total == *old_total + x);
        })
    ;
    
    total += x;
}
//]

struct n {
    int value;

    n() : value(0) {}
    n operator+(n const& r) const { n x; x.value = value + r.value; return x; }
    n& operator+=(n const& r) { value = value + r.value; return *this; }
    bool operator==(n const& r) const { return value == r.value; }
private:
    n(n const&) {} // Hide copy constructor (non copy-constructible).
};

// Specialize `boost::is_copy_constructible<n>` trait (not needed on C++11):

int main() {
    n j, k;
    j.value = 1;
    k.value = 2;
    accumulate(j, k);
    assert(j.value == 3);

    int i = 1;
    accumulate(i, 2);
    assert(i == 3);

    return 0;
}

