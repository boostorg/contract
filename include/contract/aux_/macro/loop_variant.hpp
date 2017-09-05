
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_MACRO_LOOP_VARIANT_HPP_
#define CONTRACT_AUX_MACRO_LOOP_VARIANT_HPP_

#include <contract/aux_/macro/code_/loop_variant.hpp>

// PRIVATE //

#define CONTRACT_AUX_LOOP_VARIANT_(id, tpl, expr) \
    CONTRACT_AUX_CODE_LOOP_VARIANT(id, tpl, BOOST_PP_SEQ_HEAD(expr))

// PUBLIC //

#define CONTRACT_AUX_LOOP_VARIANT(id, tpl, expr) \
    BOOST_PP_IIF(BOOST_PP_COMPL(CONTRACT_AUX_CONFIG_LOOP_VARIANTS_01), \
        BOOST_PP_TUPLE_EAT(3) \
    , BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(expr), 1), \
        CONTRACT_AUX_LOOP_VARIANT_ \
    , \
        CONTRACT_AUX_MPL_ASSERT_MSG(false, \
                ERROR_too_many_loop_variant_parameters, ()); \
        BOOST_PP_TUPLE_EAT(3) \
    ))(id, tpl, expr)

#endif // #include guard

