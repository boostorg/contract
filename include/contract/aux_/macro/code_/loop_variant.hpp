
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_LOOP_VARIANT_HPP_
#define CONTRACT_AUX_CODE_LOOP_VARIANT_HPP_

#include <contract/broken.hpp>
#include <contract/aux_/symbol.hpp>
#include <contract/aux_/call/globals.hpp>
#include <contract/aux_/macro/code_/const_expr.hpp>
#include <contract/detail/preprocessor/keyword/const.hpp>

// PRIVATE //

#define CONTRACT_AUX_CODE_LOOP_VARIANT_VAR_ \
    /* NOTE: this name should not be made unique (using id, etc) so to */ \
    /* give error is multiple loop variants used within same loop */ \
    /* (only 1 loop invariant for loop because that's theoretically correct */ \
    /* and because there is only 1 old loop variant variable) */ \
    CONTRACT_AUX_SYMBOL( (loop_variant) )

#define CONTRACT_AUX_CODE_LOOP_VARIANT_FUNC_(id) \
    CONTRACT_AUX_SYMBOL( (loop_variant_func)(id) )

#define CONTRACT_AUX_CODE_LOOP_VARIANT_CHECK_AND_UPDATE_(expr) \
    try { \
        ::contract::aux::call_globals<>::is_checking_contract = true; \
        /* assert loop variant never negative (but can be zero) */ \
        if(!(CONTRACT_AUX_CODE_LOOP_VARIANT_VAR_ >= 0)) \
            throw ::contract::broken(__FILE__, __LINE__, \
                    BOOST_PP_STRINGIZE(expr) " >= 0 " \
                    " /* non-negative loop variant */"); \
        /* assert either 1st iteration (old loop variant not initialized */ \
        /* yet) or loop variant monotonically decreasing */ \
        if(!( \
            CONTRACT_AUX_CODE_LOOP_VARIANT_OLD_VAR.value == \
                    ::contract::aux::loop_variant::uninitialized \
            || CONTRACT_AUX_CODE_LOOP_VARIANT_VAR_ < \
                    CONTRACT_AUX_CODE_LOOP_VARIANT_OLD_VAR.value \
        )) throw ::contract::broken(__FILE__, __LINE__, \
                BOOST_PP_STRINGIZE(expr) " < oldof " BOOST_PP_STRINGIZE(expr) \
                " /* monotonically decreasing loop variant */"); \
        ::contract::aux::call_globals<>::is_checking_contract = false; \
    } catch(...) { \
        ::contract::aux::call_globals<>::is_checking_contract = false; \
        ::contract::loop_variant_broken(::contract::FROM_BODY); \
    } \
    /* update old loop variant with variant calc in this iteration */ \
    CONTRACT_AUX_CODE_LOOP_VARIANT_OLD_VAR.value = \
            CONTRACT_AUX_CODE_LOOP_VARIANT_VAR_;

#define CONTRACT_AUX_CODE_LOOP_VARIANT_CONST_(id, tpl, const_expr) \
    BOOST_PP_LIST_ENUM(CONTRACT_AUX_CODE_CONST_EXPR_TOKENS(id, tpl, \
            ::contract::aux::loop_variant::value_type, \
            CONTRACT_AUX_CODE_LOOP_VARIANT_FUNC_(id), const_expr)) \
    ::contract::aux::loop_variant::value_type \
            CONTRACT_AUX_CODE_LOOP_VARIANT_VAR_ = \
            CONTRACT_AUX_CODE_LOOP_VARIANT_FUNC_(id)(); \
    CONTRACT_AUX_CODE_LOOP_VARIANT_CHECK_AND_UPDATE_( \
            CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_EXPR( \
                    CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS(const_expr)))

#define CONTRACT_AUX_CODE_LOOP_VARIANT_(id, tpl, expr) \
    ::contract::aux::loop_variant::value_type \
            CONTRACT_AUX_CODE_LOOP_VARIANT_VAR_ = expr; \
    CONTRACT_AUX_CODE_LOOP_VARIANT_CHECK_AND_UPDATE_(expr)

// PUBLIC //

#define CONTRACT_AUX_CODE_LOOP_VARIANT_OLD_VAR \
    CONTRACT_AUX_SYMBOL( (loop_variant_old) )

#define CONTRACT_AUX_CODE_LOOP_VARIANT(id, tpl, expr) \
    /* loop variant cannot be a compile-time static expression */ \
    /* (metafunction) because it must dynamically decrease at run-time */ \
    /* but const-expr allowed for variant expr */ \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_FRONT(expr), \
        CONTRACT_AUX_CODE_LOOP_VARIANT_CONST_ \
    , \
        CONTRACT_AUX_CODE_LOOP_VARIANT_ \
    )(id, tpl, expr)

#endif // #include guard

