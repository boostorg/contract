
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_LIST_TO_ARRAY_HPP_
#define CONTRACT_DETAIL_PP_LIST_TO_ARRAY_HPP_

#include <boost/preprocessor/list/fold_left.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/array/push_back.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_LIST_TO_ARRAY_ELEM_(d, array, elem) \
    /* don't use ARRAY_SIZE instead of TUPLE_ELEM(2, 0, ...) because when */ \
    /* size is 0 ARRAY_SIZE is undefined */ \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, array), \
        BOOST_PP_ARRAY_PUSH_BACK \
    , \
        (1, (elem)) BOOST_PP_TUPLE_EAT(2) \
    )(array, elem)

// PUBLIC //

// Precondition: list != NIL
#define CONTRACT_DETAIL_PP_LIST_TO_ARRAY_D(d, list) \
    BOOST_PP_LIST_FOLD_LEFT_ ## d(CONTRACT_DETAIL_PP_LIST_TO_ARRAY_ELEM_, \
            (0, ()), list)

// Precondition: list != NIL
#define CONTRACT_DETAIL_PP_LIST_TO_ARRAY(list) \
    CONTRACT_DETAIL_PP_LIST_TO_ARRAY_D(1, list)

#endif // #include guard

