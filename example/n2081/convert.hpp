
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_convert_header
// File: convert.hpp
#ifndef CONVERT_HPP_
#define CONVERT_HPP_

#include <contract.hpp>
#include <boost/concept_check.hpp>

CONTRACT_FUNCTION(
    template( typename To, typename From )
        requires( (boost::Convertible<From, To>) )
    (To) (convert) ( (From const&) from )
) {
    return from;
}

#endif // #include guard
//]

