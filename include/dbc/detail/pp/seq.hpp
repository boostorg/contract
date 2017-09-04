/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_SEQ_HPP_
#define DBC_PP_SEQ_HPP_

#include <boost/preprocessor.hpp>

/** Conver last n elem of specified seq into a tuple. */
#define DBC_PP_SEQ_REST_N_TO_TUPLE_(n, seq) \
    BOOST_PP_SEQ_FIRST_N(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(seq), n), seq) \
    /* seq (t0)...(tk-2) concatenated w/ (tk-1, tk) for (copyalbe, type) */ \
    ( BOOST_PP_SEQ_TO_TUPLE(BOOST_PP_SEQ_REST_N(BOOST_PP_SUB( \
            BOOST_PP_SEQ_SIZE(seq), n), seq)) )

#endif // DBC_PP_SEQ_HPP_

