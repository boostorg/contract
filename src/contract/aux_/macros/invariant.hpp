// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_INVARIANT_HPP_
#define CONTRACT_AUX_INVARIANT_HPP_

#include "code_invariant.hpp"
#include "code_/static_error.hpp"
#include "../preprocessor/keyword/is_static.hpp"
#include <boost/preprocessor.hpp>

// Seq size 3 for: CONTRACT_INVARIANT( 
// (static)(static_invariants_code_block) (invariants_code_block) )
#define CONTRACT_AUX_INVARIANT_3(seq) \
    BOOST_PP_IF(CONTRACT_AUX_PP_KEYWORD_IS_STATIC( \
            BOOST_PP_SEQ_ELEM(0, seq)), \
        CONTRACT_AUX_CODE_INVARIANT \
    , /* else */ \
        CONTRACT_AUX_CODE_STATIC_ERROR(CONTRACT_ERROR_expected_static_keyword_as_1st_parameter_of_invariant_definition) \
        BOOST_PP_TUPLE_EAT(2) \
    ) /* endif */ ( \
        BOOST_PP_SEQ_ELEM(1, seq), /* static invariants */ \
        BOOST_PP_SEQ_ELEM(2, seq) /* invariants */ \
    )

// Seq size 2 for: CONTRACT_INVARIANT( 
// (static)(static_invariants_code_block) )
#define CONTRACT_AUX_INVARIANT_2(seq) \
    BOOST_PP_IF(CONTRACT_AUX_PP_KEYWORD_IS_STATIC( \
            BOOST_PP_SEQ_ELEM(0, seq)), \
        CONTRACT_AUX_CODE_INVARIANT \
    , /* else */ \
        CONTRACT_AUX_CODE_STATIC_ERROR(CONTRACT_ERROR_expected_static_keyword_as_1st_parameter_of_invariant_definition) \
        BOOST_PP_TUPLE_EAT(2) \
    ) /* endif */ ( \
        BOOST_PP_SEQ_ELEM(1, seq), /* static invariants */ \
        {} /* invariants */ \
    )

// Seq size 1 for: CONTRACT_INVARIANT( (invariants_code_block) )
#define CONTRACT_AUX_INVARIANT_1(seq) \
    CONTRACT_AUX_CODE_INVARIANT( \
            {}, /* static invariants */ \
            BOOST_PP_SEQ_ELEM(0, seq) /* invariants */ \
            )

// Seq size 0 for: CONTRACT_INVARIANT( ) -- only C99 or later version.
#define CONTRACT_AUX_INVARIANT_0(seq) \
    CONTRACT_AUX_CODE_INVARIANT( \
            {}, /* static invariants */ \
            {} /* invariants */ \
            )

#define CONTRACT_AUX_INVARIANT(seq) \
    /* Handles seq size 0 but that only works on C99 or later. */ \
    BOOST_PP_IF(BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(seq), 3), \
        CONTRACT_AUX_CODE_STATIC_ERROR(CONTRACT_ERROR_too_many_parameters_in_invariant_definition) \
        BOOST_PP_TUPLE_EAT(1) \
    , /* else */ \
        BOOST_PP_CAT(CONTRACT_AUX_INVARIANT_, \
                BOOST_PP_SEQ_SIZE(seq)) \
    ) /* endif */ (seq)

#endif // #include guard

