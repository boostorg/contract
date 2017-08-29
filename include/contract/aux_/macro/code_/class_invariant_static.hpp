
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_HPP_
#define CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_HPP_

#include <contract/aux_/symbol.hpp>
#include <contract/aux_/subcontract/class_invariant.hpp>
#include <contract/aux_/subcontract/static_class_invariant.hpp>
#include <contract/aux_/macro/code_/assert.hpp>

// PRIVATE //

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_COMMA_BASE_TYPE_(z, n, id) \
    , CONTRACT_AUX_CODE_SUBCONTRACTED_BASE_TYPE(id, n)

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_COMMA_BASE_FUNC_( \
        z, n, id) \
    , & CONTRACT_AUX_CODE_SUBCONTRACTED_BASE_TYPE(id, n) :: \
            CONTRACT_AUX_CODE_SUBCONTRACTED_CLASS_INVARIANT_STATIC_FUNC

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_DECL_TOKENS_( \
        id, tpl, function_name, is_assertion, dispatch_param) \
    ( /* pp-list */ \
        /* unused tparam to delay assertion-func compilation */ \
        BOOST_PP_EXPR_IIF(is_assertion, \
            template< typename CONTRACT_AUX_SYMBOL( (Unused)(id) ) > \
        ) \
        static void function_name( \
            /* extra param for type-dispatching based on ass. requirements */ \
            /* (can't go at the end because of default parameters) */\
            BOOST_PP_EXPR_IIF(is_assertion, dispatch_param) \
        ) \
    , \
        BOOST_PP_NIL \
    )

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_(id, a) \
    CONTRACT_AUX_SYMBOL( (static_class_invariant_assertion) \
            (CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)) (id) )

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_DECL_TOKENS_(\
        d, id, tpl, unused, dispatch_param, a) \
    CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_DECL_TOKENS_( \
            id, tpl, \
            CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_(a, id), \
            1 /* yes for assertion */, dispatch_param)

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_CALL_( \
        d, id, tpl, unused, a) \
    CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_(id, a) \
    <void> /* unused tparam to delay assertion func compilation */ \
    ( \
        BOOST_PP_EXPR_IIF(tpl, typename) \
                /* NOTE: extra param for assertion func dispatch based on */ \
                /* requirements-- mpl::true_ iff assertion requirements */ \
                /* are met at compile-time */ \
                ::boost::mpl::bool_< \
                    CONTRACT_DETAIL_PP_ASSERTION_TRAITS_REQUIREMENT(a) \
                >::type() \
    );

// PUBLIC //

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC \
    CONTRACT_AUX_SYMBOL( (static_class_invariant) )

#define CONTRACT_AUX_CODE_SUBCONTRACTED_CLASS_INVARIANT_STATIC_FUNC \
    CONTRACT_AUX_SYMBOL( (subcontracted_static_class_invariant) )

#define CONTRACT_AUX_CODE_SUBCONTRACTED_CLASS_INVARIANT_STATIC(id, tpl) \
    static void CONTRACT_AUX_CODE_SUBCONTRACTED_CLASS_INVARIANT_STATIC_FUNC() \
    { \
        ::contract::aux::subcontract_static_class_invariant< \
            CONTRACT_AUX_CODE_CLASS_TYPE \
            BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX, \
                    CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_COMMA_BASE_TYPE_, \
                    id) \
        >( \
            & CONTRACT_AUX_CODE_CLASS_TYPE :: \
                    CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC \
            BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX, \
                    CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_COMMA_BASE_FUNC_, \
                    id) \
        ); \
    }

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC(id, tpl, v) \
    CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF(id, tpl, \
            static_class_invariant, \
  CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_DECL_TOKENS_,\
            ~, CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_STATIC(v)) \
    BOOST_PP_LIST_ENUM(CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_DECL_TOKENS_( \
            id, tpl, \
            CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC, \
            0 /* not for assertion */, ~ /* no dispatch param */)) \
    { \
        CONTRACT_AUX_CODE_ASSERT(id, tpl, static_class_invariant, \
                CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_CALL_, \
                /* POLICY: by default, no static class inv if not specified */ \
                ~, CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_STATIC(v)) \
    }

#endif // #include guard

