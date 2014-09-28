
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_find_header
// File: find.hpp
#ifndef FIND_HPP_
#define FIND_HPP_

#include <contract.hpp>
#include <boost/concept_check.hpp>

CONTRACT_FUNCTION(
    template( typename Iterator )
        requires(
            boost::InputIterator<Iterator>,
            boost::EqualityComparable< // Equality needed to find value.
                    typename boost::InputIterator<Iterator>::value_type>
        )
    (Iterator) (myfind) ( (Iterator) first, (Iterator) last,
            (typename boost::InputIterator<Iterator>::value_type const&) value )
        // precondition: range [first, last) is valid
        postcondition(
            auto result = return,
            if(result != last) (
                value == *result // if result not last, value found
            )
        )
) {
    CONTRACT_LOOP( while(first != last && *first != value) ) {
        CONTRACT_LOOP_VARIANT_TPL(
                const( first, last ) std::distance(first, last) )
        ++first;
    }
    return first;
}

#endif // #include guard
//]

