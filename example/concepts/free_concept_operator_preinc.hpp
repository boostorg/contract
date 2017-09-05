
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef FREE_CONCEPT_OPERATOR_PREINC_HPP_
#define FREE_CONCEPT_OPERATOR_PREINC_HPP_

#include <contract.hpp>
#include <boost/concept_check.hpp>
#include <boost/type_traits/has_equal_to.hpp>

//[free_concept_operator_preinc
template< typename T >
struct Addable // New concept defined and implemented using Boost.ConceptCheck.
{
    BOOST_CONCEPT_USAGE(Addable)
    {
        return_type(x + y);
    }

private:
    void return_type ( T ) {}
    static T const& x;
    static T const& y;
};

CONTRACT_FUNCTION(
    template( typename T )
        requires(
            boost::Assignable<T>,   // Check both predefined and
            Addable<T>              // newly defined concepts.
        )
    (T&) operator(++)(preinc) ( (T&) value )
        postcondition(
            auto result = return,
            auto old_value = CONTRACT_OLDOF value,
            value == old_value + T(1), requires boost::has_equal_to<T>::value
            result == value, requires boost::has_equal_to<T>::value
        )
) {
    return value = value + T(1);
}
//]

#endif // #include guard

