
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_advance
// File: advance.cpp
#include <contract.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>
#include <list>
#include <iterator>

namespace aux { // Tag dispatch helpers (in a private namespace).

template< typename InputIterator, typename Distance >
void myadvance_dispatch ( InputIterator& i, Distance n,
        std::input_iterator_tag )
{
    CONTRACT_LOOP( while(n--) ) {
        CONTRACT_LOOP_VARIANT_TPL( const( n ) n )
        ++i;
    }
}

template< typename BidirectionalIterator, typename Distance >
void myadvance_dispatch ( BidirectionalIterator& i, Distance n,
        std::bidirectional_iterator_tag )
{
    if(n >= 0) {
        CONTRACT_LOOP( while(n--) ) {
            CONTRACT_LOOP_VARIANT_TPL( const( n ) n )
            ++i;
        }
    } else {
#ifndef CONTRACT_CONFIG_NO_LOOP_VARIANTS
        // Avoid unused variable warning when loop invariants are disabled.
        Distance n_max = n;
#endif
        CONTRACT_LOOP( while(n++) ) {
            CONTRACT_LOOP_VARIANT_TPL( const( n_max, n ) n_max - n )
            --i;
        }
    }
}

template< typename RandomAccessIterator, typename Distance >
void myadvance_dispatch ( RandomAccessIterator& i, Distance n,
        std::random_access_iterator_tag )
{
    i += n;
}

} // namespace aux

// Contract helper meta-function.
template< typename T > struct is_input_iterator : boost::mpl::false_ {};
template< > struct is_input_iterator<std::input_iterator_tag> :
        boost::mpl::true_ {};

CONTRACT_FUNCTION(
    template( typename InputIterator, typename Distance )
    void (myadvance) ( (InputIterator&) i, (Distance) n )
        precondition(
            // range [i, i + n] is non-singular.
            if(is_input_iterator<typename std::iterator_traits<InputIterator>::
                    iterator_category>::value) (
                n > 0 // if input iterator, n positive
            )
        )
        postcondition(
            auto old_i = CONTRACT_OLDOF i,
            std::distance(old_i, i) == n // iterator advanced of n
        )
) {
    aux::myadvance_dispatch(i, n, typename 
            std::iterator_traits<InputIterator>:: iterator_category());
}

int main ( void )
{
    std::vector<int> v(10);
    v[2] = 123; v[3] = -123;
    std::vector<int>::iterator r = v.begin(); // Random iterator.
    myadvance(r, 3);
    BOOST_TEST(*r == -123);
    
    std::list<int> l(v.begin(), v.end());
    std::list<int>::iterator b = l.begin(); // Bidirectional and not random.
    myadvance(b, 2);
    BOOST_TEST(*b == 123);
    return boost::report_errors();
}
//]

