
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_HPP_
#define CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_HPP_

#include <contract/aux_/symbol.hpp>
#include <contract/aux_/subcontract/class_invariant.hpp>
#include <contract/aux_/subcontract/static_class_invariant.hpp>
#include <contract/aux_/macro/code_/assert.hpp>

// PRIVATE //

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_COMMA_BASE_TYPE_( \
        z, n, id) \
    , CONTRACT_AUX_CODE_SUBCONTRACTED_BASE_TYPE(id, n)

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_COMMA_BASE_( \
        z, n, id_tpl) \
    , dynamic_cast< \
        CONTRACT_AUX_CODE_SUBCONTRACTED_BASE_TYPE(BOOST_PP_TUPLE_ELEM( \
                2, 0, id_tpl), n) \
        const volatile* const \
      >(this) \
    , & CONTRACT_AUX_CODE_SUBCONTRACTED_BASE_TYPE(BOOST_PP_TUPLE_ELEM( \
            2, 0, id_tpl), n) :: \
      BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(2, 1, id_tpl), \
        template \
      ) \
      CONTRACT_AUX_CODE_SUBCONTRACTED_CLASS_INVARIANT_CONST_VOLATILE_FUNC< \
            void> /* extra template param to delay compilation */

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_TRAITS_(v) \
    /* POLICY: by default, volatile class inv same as dyn if not specified */ \
    /* (this is likely what the user would want but it could generate */ \
    /* compile-time error because dyn inv use non volatile obj in which */ \
    /* case user will specify volatile inv */ \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_HAS_CONST_VOLATILE( \
            v), /* has_volatile iff volatile are specified */ \
        CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST_VOLATILE \
    , \
        CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST \
    )(v)

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_CHECK_STATIC_VAR_(id) \
    CONTRACT_AUX_SYMBOL( (check_static_class_invariant)(id) )

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_DECL_TOKENS_( \
        id, tpl, function_name, is_assertion, dispatch_param) \
    ( /* pp-list */ \
        /* NOTE: this tparam is also used to disable compilation */ \
        /* of the volatile class invariant lazily until an actual volatile */ \
        /* member function is used (this is because volatile class inv */ \
        /* are defined to match the normal class inv by default and that */ \
        /* errors at compile-time but only when volatile member are used */ \
        template< bool \
  CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_CHECK_STATIC_VAR_(id) \
        > \
        void function_name( \
            /* extra param for type-dispatching based on ass. requirements */ \
            /* (can't go at the end because of default parameters) */\
            BOOST_PP_EXPR_IIF(is_assertion, dispatch_param) \
        ) const volatile \
    , \
        BOOST_PP_NIL \
    )

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_( \
        id, a) \
    CONTRACT_AUX_SYMBOL( (volatile_class_invariant_assertion) \
            (CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)) (id) )

#define \
CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_DECL_TOKENS_( \
        d, id, tpl, unused, dispatch_param, a) \
    CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_DECL_TOKENS_( \
            id, tpl, \
            CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_( \
                    id, a), \
            1 /* yes for assertion */, dispatch_param)

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_CALL_( \
        d, id, tpl, unused, a) \
    CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_(id, a) \
    <false> /* unused tparam to delay assertion func compilation */ \
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

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_FUNC \
    CONTRACT_AUX_SYMBOL( (volatile_class_invariant) )

#define CONTRACT_AUX_CODE_SUBCONTRACTED_CLASS_INVARIANT_CONST_VOLATILE_FUNC \
    CONTRACT_AUX_SYMBOL( (subcontracted_volatile_class_invariant) )

#define CONTRACT_AUX_CODE_SUBCONTRACTED_CLASS_INVARIANT_CONST_VOLATILE( \
        id, tpl) \
    /* NOTE: volatile subcontracted class invariants must be a template so */ \
    /* to not compile unless volatile member actually contracted so to */ \
    /* avoid volatile qualifier errors until because volatile class */ \
    /* invariants defaulted to dynamic ones if not specified (so tpl = 1 */ \
    /* forced here) */ \
    template< typename CONTRACT_AUX_SYMBOL( (Unused) ) > /* always template */ \
    void CONTRACT_AUX_CODE_SUBCONTRACTED_CLASS_INVARIANT_CONST_VOLATILE_FUNC() \
            const volatile { \
        ::contract::aux::subcontract_class_invariant< \
            CONTRACT_AUX_CODE_CLASS_TYPE \
            BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX, \
  CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_COMMA_BASE_TYPE_, \
                    id) \
        >( \
              this \
            , & CONTRACT_AUX_CODE_CLASS_TYPE :: \
              template /* always a template (tpl = 1 forced) */ \
              CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_FUNC< \
                    true /* check static class inv */> \
            BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX, \
  CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_COMMA_BASE_, \
                    (id, 1 /* always a template (tpl = 1 forced) */)) \
        ); \
    }

#define CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE(id, tpl, v) \
    CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF(id, tpl, \
            volatile_class_invariant, \
  CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_DECL_TOKENS_,\
            ~, CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_TRAITS_(v)) \
    BOOST_PP_LIST_ENUM( \
            CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_DECL_TOKENS_( \
                    id, tpl, \
                    CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_FUNC, \
                    0 /* not for assertion */, ~ /* no dispatch param */)) \
    { \
        /* first always check static class invariants (bool var is used */ \
        /* to not check static inv twice when dyn inv call volatile inv) */ \
        if(CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_CHECK_STATIC_VAR_( \
                id)) { \
            CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC(); \
        } \
        /* then check volatile class invariants (in AND with static) */ \
        CONTRACT_AUX_CODE_ASSERT(id, tpl, volatile_class_invariant, \
  CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_CALL_, \
                ~, CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_TRAITS_(v))\
    }

#endif // #include guard

