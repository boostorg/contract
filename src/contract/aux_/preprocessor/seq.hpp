// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SEQ_HPP_
#define CONTRACT_AUX_PP_SEQ_HPP_

#include <boost/preprocessor.hpp>

// Sequence manipulation in addition to Boost.Preprocessor ones.

// Return element in the back.
#define CONTRACT_AUX_PP_SEQ_BACK(seq) \
    BOOST_PP_SEQ_ELEM(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(seq), 1), seq)

// Conver last n elements of specified sequence into a tuple and
// conactenates it with first n elements for
// (t0)...(tn-2)( (tn-1, tn) ) (to support (copyable, type) ).
#define CONTRACT_AUX_PP_SEQ_REST_N_TO_TUPLE_(n, seq) \
    /* sequence of first n elems (t0)...(tn-2) */ \
    BOOST_PP_SEQ_FIRST_N(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(seq), n), \
            seq) \
    /* concatenate with tuple from last n elems ( (tn-1, tn) ) */ \
    ( BOOST_PP_SEQ_TO_TUPLE(BOOST_PP_SEQ_REST_N(BOOST_PP_SUB( \
            BOOST_PP_SEQ_SIZE(seq), n), seq)) )


#endif // #include guard

