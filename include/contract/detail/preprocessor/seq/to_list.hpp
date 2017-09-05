
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_SEQ_TO_LIST_HPP_
#define CONTRACT_DETAIL_PP_SEQ_TO_LIST_HPP_

#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/to_tuple.hpp>
#include <boost/preprocessor/seq/seq.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_SEQ_TO_LIST_NOT_EMPTY_(is_head_empty_macro, seq) \
    BOOST_PP_TUPLE_TO_LIST(BOOST_PP_SEQ_SIZE(seq), BOOST_PP_SEQ_TO_TUPLE(seq))

#define CONTRACT_DETAIL_PP_SEQ_TO_LIST_EMPTY_(is_head_empty_macro, seq) \
    BOOST_PP_NIL

// Precondition: size(seq) == 1
#define CONTRACT_DETAIL_PP_SEQ_TO_LIST_MAYBE_EMPTY_(is_head_empty_macro, seq) \
    BOOST_PP_IIF(is_head_empty_macro(BOOST_PP_SEQ_HEAD(seq)), \
        CONTRACT_DETAIL_PP_SEQ_TO_LIST_EMPTY_ \
    , \
        CONTRACT_DETAIL_PP_SEQ_TO_LIST_NOT_EMPTY_ \
    )(is_head_empty_macro, seq)

// PUBLIC //

// Expand to PP_NIL list if is_head_empty_macro(SEQ_HEAD(seq)).
#define CONTRACT_DETAIL_PP_SEQ_TO_LIST(is_head_empty_macro, seq) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(seq), 1), \
        CONTRACT_DETAIL_PP_SEQ_TO_LIST_MAYBE_EMPTY_ \
    , \
        CONTRACT_DETAIL_PP_SEQ_TO_LIST_NOT_EMPTY_ \
    )(is_head_empty_macro, seq)

// Never expand to PP_NIL list.
#define CONTRACT_DETAIL_PP_SEQ_TO_LIST_NEVER_EMPTY(seq) \
    CONTRACT_DETAIL_PP_SEQ_TO_LIST_NOT_EMPTY_(~, seq)

#endif // #include guard

