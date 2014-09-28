
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_add_header
// File: add.hpp
#ifndef ADD_HPP
#define ADD_HPP

#include <contract.hpp>
#include <boost/concept_check.hpp>
#include <boost/type_traits/has_equal_to.hpp>

template< typename T >
struct Addable // User-defined concept.
{
    BOOST_CONCEPT_USAGE(Addable)
    {
        return_type(x + y); // Check addition `T operator+(T x, T y)`.
    }

private:
    void return_type ( T const& ) {} // Used to check addition returns type `T`.
    
    T const& x;
    T const& y;
};

CONTRACT_FUNCTION(
    template( typename T ) requires( Addable<T> )
    (T) (add) ( (T const&) x, (T const&) y )
        postcondition(
            auto result = return,
            result == x + y, requires boost::has_equal_to<T>::value
        )
) {
    return x + y;
}

#endif // #include guard
//]

