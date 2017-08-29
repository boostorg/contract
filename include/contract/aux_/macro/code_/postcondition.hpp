
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_POSTCONDITION_HPP_
#define CONTRACT_AUX_CODE_POSTCONDITION_HPP_

#include <contract/aux_/identity_equal.hpp>
#include <contract/aux_/uninitialized.hpp>
#include <contract/aux_/macro/code_/assertion_func.hpp>
#include <contract/aux_/macro/code_/oldof.hpp>
#include <contract/aux_/macro/code_/assert.hpp>
#include <contract/detail/preprocessor/traits/oldof.hpp> // o
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/list/filter.hpp>

// PRIVATE //

// NOTE: Transform an assignment `var =` into an equality comparison `var ==`
// to internally deal with trailing `=` symbol of old-of and result which
// cannot be remove by pp (the equality comparison is done with a special
// identity_equal type `var == identity_equal()` which redefines == to return a
// const& to var itself).
#define CONTRACT_AUX_CODE_POSTCONDITION_ASSIGNMENT_TO_CONSTREF_(assignment) \
    /* it is legal to pp-cat `= ## =` to `==` (see C++03 standard) */ \
    BOOST_PP_CAT(assignment, =) ::contract::aux::identity_equal()

#define CONTRACT_AUX_CODE_POSTCONDITION_COMMA_OLDOF_AUTO_PARAM_DECL_( \
        r, typename01, i, o) \
    , \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    ::contract::aux::arg_const< \
            CONTRACT_AUX_CODE_OLDOF_TYPE(typename01, o, i) >::type \
    CONTRACT_DETAIL_PP_OLDOF_TRAITS_ASSIGNMENT(o) \
    /* old-of assignment syntax has trailing `=` (which cannot be removed */ \
    /* by pp) so it must be handled as a default param and it is set to */ \
    /* uninitialized data to avoid requiring a default constructor for the */ \
    /* old-of type-- this is OK because this default param value is never */ \
    /* used (func call always specify this param) */ \
    ::contract::aux::uninitialized< \
        CONTRACT_AUX_CODE_OLDOF_TYPE(typename01, o, i) \
    >::value()

#define CONTRACT_AUX_CODE_POSTCONDITION_COMMA_OLDOF_AUTO_PARAM_CONSTREF_( \
        r, tpl, i, o) \
    , \
    CONTRACT_AUX_CODE_POSTCONDITION_ASSIGNMENT_TO_CONSTREF_( \
            CONTRACT_DETAIL_PP_OLDOF_TRAITS_ASSIGNMENT(o))

#define CONTRACT_AUX_CODE_POSTCONDITION_COMMA_PARAM_DECL_(r, tpl_f, p) \
    , \
    CONTRACT_AUX_CODE_FUNC_TYPENAME(BOOST_PP_TUPLE_ELEM(2, 0, tpl_f), \
            BOOST_PP_TUPLE_ELEM(2, 1, tpl_f)) \
    ::contract::aux::arg_const< \
        BOOST_PP_ARRAY_ENUM(CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p)) \
    >::type \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define CONTRACT_AUX_CODE_POSTCONDITION_COMMA_PARAM_NAME_(r, tpl, p) \
    , \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define CONTRACT_AUX_CODE_POSTCONDITION_TPARAM_DECL_ENUM_(r, unused, i, type) \
    BOOST_PP_COMMA_IF(i) \
    typename type

#define CONTRACT_AUX_CODE_POSTCONDITION_TPARAM_NAME_ENUM_(r, unused, i, type) \
    BOOST_PP_COMMA_IF(i) \
    type

#define CONTRACT_AUX_CODE_POSTCONDITION_RESULT_PARAM_DECL_(id, tpl, k, f) \
    /* type (it is void_result for void result type) */ \
    CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
    ::contract::aux::result_const< \
        CONTRACT_AUX_CODE_RESULT_TYPE(f, 0 /* don't allow empty result */) \
    >::type \
    /* result parameter name and assignment */ \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_RESULT_ASSIGNMENT( \
            f)), \
        CONTRACT_AUX_SYMBOL( (unused_result)(id) ) \
        = /* must have trailing assignment symbol */ \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_RESULT_ASSIGNMENT \
    )(f) \
    /* result assignment syntax has trailing `=` (which cannot be removed */ \
    /* by pp) so it must be handled as a default param and it is set to */ \
    /* uninitialized date to avoid requiring a default constructor for the */ \
    /* result type-- this is OK because this default param value is never */ \
    /* used (func call always specify this param) */ \
    ::contract::aux::uninitialized< \
        CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
        ::contract::aux::result_const< \
            CONTRACT_AUX_CODE_RESULT_TYPE(f, 0 /* don't allow empty result */) \
        >::type \
    >::value()

#define CONTRACT_AUX_CODE_POSTCONDITION_RESULT_PARAM_CONSTREF_(id, tpl, k, f) \
    CONTRACT_AUX_CODE_POSTCONDITION_ASSIGNMENT_TO_CONSTREF_( \
        BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
                CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_RESULT_ASSIGNMENT(\
                        f)), \
            CONTRACT_AUX_SYMBOL( (unused_result)(id) ) \
            = /* must have trailing assignment symbol */ \
            BOOST_PP_TUPLE_EAT(1) \
        , \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_RESULT_ASSIGNMENT \
        )(f) \
    ) 

#define CONTRACT_AUX_CODE_POSTCONDITION_VALIDATE_RESULT_DECL_(id, tpl, k, f) \
    /* statically assert that auto `result = return` can be specified */ \
    /* only if result type is not void */ \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_RESULT_ASSIGNMENT(f)),\
        BOOST_PP_TUPLE_EAT(3) \
    , \
        CONTRACT_AUX_MPL_ASSERT_MSG \
    )( \
        /* extra paren around static assert condition wrap eventual commas */ \
        ( !::boost::is_void< \
            /* this type will always be void if no result type is */ \
            /* specified in func decl (e.g., for ctor) but it might or */ \
            /* not be void otherwise */ \
            CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) :: \
                    result_type \
        >::value ) \
    , \
        BOOST_PP_CAT(ERROR_postconditions_cannot_access_return_value_for_function_returning_void_at_line_, id) \
    , \
        (types< CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
                CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) :: \
                result_type >) \
    ); /* MPL assert requires trailing `;` */

#define CONTRACT_AUX_CODE_POSTCONDITION_FUNC_DECL_TOKENS_(id, tpl, k, f, \
        oldof_auto_types, function_name, is_assertion, dispatch_param) \
    BOOST_PP_TUPLE_TO_LIST( /* pp-list for tparams unwrapped commas */ \
        BOOST_PP_MAX(1, BOOST_PP_ADD( /* always at least 1 elem in tuple */ \
              BOOST_PP_ADD(BOOST_PP_LIST_SIZE(oldof_auto_types) \
            , CONTRACT_AUX_CODE_TEMPLATE_COUNT( \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f)))) \
            , is_assertion /* add 1 if true, 0 otherwise */ \
        )) \
    , ( \
        BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), private:) \
        BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(is_assertion, BOOST_PP_BITOR( \
                BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f))), \
            template< \
        ) \
            /* old-of tparams */ \
            BOOST_PP_LIST_FOR_EACH_I( \
                    CONTRACT_AUX_CODE_POSTCONDITION_TPARAM_DECL_ENUM_, ~, \
                    oldof_auto_types) \
            /* actual tparams */ \
            BOOST_PP_COMMA_IF(BOOST_PP_BITAND( \
                    BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                    BOOST_PP_LIST_IS_CONS( \
                            CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS( \
                            f))))) \
            CONTRACT_AUX_CODE_TEMPLATE_DECL(0, /* no `template<` and `>` */ \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
            /* unused tparam to delay assertion-func compilation */ \
            BOOST_PP_COMMA_IF(BOOST_PP_BITAND(is_assertion, BOOST_PP_BITOR( \
                    BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                    BOOST_PP_LIST_IS_CONS( \
                            CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS( \
                            f)))))) \
            BOOST_PP_EXPR_IIF(is_assertion, \
                typename CONTRACT_AUX_SYMBOL( (Unused)(id) ) \
            ) \
        BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(is_assertion, BOOST_PP_BITOR( \
                BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f))), \
            > \
        ) \
        BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_PP_BITOR( \
                  CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(k, f) \
                , CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k))), \
            /* static unless non-static member function or constructor */ \
            static \
        ) \
        void function_name \
        ( \
            /* extra param for type-dispatching based on ass. requirements */ \
            /* (can't go at the end because of default parameters) */\
            BOOST_PP_EXPR_IIF(is_assertion, dispatch_param) \
            BOOST_PP_COMMA_IF(is_assertion) /* next param always there */ \
            /* function_type for a dummy param used to resolve overloading */ \
            /* (because pre add const to args and obj so it might have same */ \
            /* signature as of overloaded func with const arg and obj) */ \
            /* not named so it cannot be used by mistake */ \
            CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f)::body_type \
            /* all params are const (and ref) for const-correctness */ \
            BOOST_PP_LIST_FOR_EACH( \
                    CONTRACT_AUX_CODE_POSTCONDITION_COMMA_PARAM_DECL_, \
                    (tpl, f), \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
            /* all old-ofs are const (and ref) for const-correctness */ \
            BOOST_PP_LIST_FOR_EACH_I( \
  CONTRACT_AUX_CODE_POSTCONDITION_COMMA_OLDOF_AUTO_PARAM_DECL_, \
                    /* use typename keyword if tpl or there are */ \
                    /* auto-typed old-ofs (because this is tpl in that case) */\
                    BOOST_PP_BITOR(tpl, BOOST_PP_BITOR( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
                            BOOST_PP_LIST_IS_CONS(oldof_auto_types))), \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS(f)) \
            /* result is const (and ref) for const-reoccrectness */ \
            , CONTRACT_AUX_CODE_POSTCONDITION_RESULT_PARAM_DECL_(id, tpl, k, f)\
        ) \
        BOOST_PP_EXPR_IIF(BOOST_PP_BITOR( \
                  CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(k, f) \
                , CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k)), \
            /* object `this` is const for const-correctness (unless static) */ \
            const \
        ) \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE(f) \
    ) )

#define CONTRACT_AUX_CODE_POSTCONDITION_ASSERTION_FUNC_(id, a) \
    CONTRACT_AUX_SYMBOL( (postcondition_assertion) \
            (CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)) (id) )

#define CONTRACT_AUX_CODE_POSTCONDITION_ASSERTION_FUNC_DECL_TOKENS_( \
        d, id, tpl, k_f_oldofautotypes, dispatch_param, a) \
    CONTRACT_AUX_CODE_POSTCONDITION_FUNC_DECL_TOKENS_(id, tpl, \
            BOOST_PP_TUPLE_ELEM(3, 0, k_f_oldofautotypes), \
            BOOST_PP_TUPLE_ELEM(3, 1, k_f_oldofautotypes), \
            BOOST_PP_TUPLE_ELEM(3, 2, k_f_oldofautotypes), \
            CONTRACT_AUX_CODE_POSTCONDITION_ASSERTION_FUNC_(id, a), \
            1 /* yes for assertion */, dispatch_param)

#define CONTRACT_AUX_CODE_POSTCONDITION_ASSERTION_FUNC_CALL_DATA_( \
        id, tpl, k, f, oldof_auto_types, a) \
    /* NOTE: Extra parens (assertion_func<...>(...)); wrap tparam commas */ \
    (CONTRACT_AUX_CODE_POSTCONDITION_ASSERTION_FUNC_(id, a) \
    < /* always a tpl because of extra Unused tparam */ \
        BOOST_PP_LIST_FOR_EACH_I( \
                CONTRACT_AUX_CODE_POSTCONDITION_TPARAM_NAME_ENUM_, ~, \
                oldof_auto_types) \
        BOOST_PP_COMMA_IF(BOOST_PP_BITAND( \
                    BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                    BOOST_PP_LIST_IS_CONS( \
                            CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS( \
                            f))))) \
        CONTRACT_AUX_CODE_TEMPLATE_PARAM_NAME_ENUM( \
                CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
        BOOST_PP_COMMA_IF(BOOST_PP_BITOR( \
                BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                BOOST_PP_LIST_IS_CONS( \
                        CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))))) \
        void /* unused tparam to disable assertion func compilation */ \
    > \
    ( \
        CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
                /* NOTE: extra param for assertion func dispatch based on */ \
                /* requirements-- mpl::true_ iff assertion requirements */ \
                /* are met at compile-time */ \
                ::boost::mpl::bool_< \
                    CONTRACT_DETAIL_PP_ASSERTION_TRAITS_REQUIREMENT(a) \
                >::type() \
        , CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
                CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f):: \
                body_type() \
        BOOST_PP_LIST_FOR_EACH( \
                CONTRACT_AUX_CODE_POSTCONDITION_COMMA_PARAM_NAME_, \
                tpl, \
                CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
        BOOST_PP_LIST_FOR_EACH_I( \
  CONTRACT_AUX_CODE_POSTCONDITION_COMMA_OLDOF_AUTO_PARAM_CONSTREF_, \
                ~, CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS(f)) \
        , CONTRACT_AUX_CODE_POSTCONDITION_RESULT_PARAM_CONSTREF_(id, tpl, k, f)\
    ));

#define CONTRACT_AUX_CODE_POSTCONDITION_ASSERTION_FUNC_CALL_( \
        d, id, tpl, k_f_oldofautotypes, a) \
    CONTRACT_AUX_CODE_POSTCONDITION_ASSERTION_FUNC_CALL_DATA_(id, tpl, \
            BOOST_PP_TUPLE_ELEM(3, 0, k_f_oldofautotypes), \
            BOOST_PP_TUPLE_ELEM(3, 1, k_f_oldofautotypes), \
            BOOST_PP_TUPLE_ELEM(3, 2, k_f_oldofautotypes), \
            a)

#define CONTRACT_AUX_CODE_POSTCONDITION_(id, tpl, k, f, oldof_auto_types) \
    CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF(id, tpl, postcondition, \
            CONTRACT_AUX_CODE_POSTCONDITION_ASSERTION_FUNC_DECL_TOKENS_, \
            (k, f, oldof_auto_types), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS(f)) \
    BOOST_PP_LIST_ENUM(CONTRACT_AUX_CODE_POSTCONDITION_FUNC_DECL_TOKENS_( \
            id, tpl, k, f, oldof_auto_types, \
            CONTRACT_AUX_CODE_POSTCONDITION_FUNC(id, tpl, k, f), \
            0 /* not for assertion */, ~ /* no dispatch param */)) \
    { \
        CONTRACT_AUX_CODE_ASSERT(id, \
                BOOST_PP_BITOR(tpl, BOOST_PP_LIST_IS_CONS(oldof_auto_types)), \
                postcondition, \
                CONTRACT_AUX_CODE_POSTCONDITION_ASSERTION_FUNC_CALL_, \
                (k, f, oldof_auto_types), \
                CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS(f)) \
        /* ensure that postcondition of void func do not attempt to access */ \
        /* result value (note, this does not automatically error because */ \
        /* the special type void_result and not void is used to handle void */ \
        /* func) this check needs to be done within the func for tpl so */ \
        /* to access the instantiated result type in case it depends on a */ \
        /* tparam but... (continue below) */ \
        BOOST_PP_IIF(CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            CONTRACT_AUX_CODE_POSTCONDITION_VALIDATE_RESULT_DECL_ \
        , \
            BOOST_PP_TUPLE_EAT(4) \
        )(id, tpl, k, f) \
    } \
    /* (continued from above) ...the check needs to be done outside the */ \
    /* func def for non-tpl to avoid linker errors on some compilers (MSVC) */ \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
        BOOST_PP_TUPLE_EAT(4) \
    , \
        CONTRACT_AUX_CODE_POSTCONDITION_VALIDATE_RESULT_DECL_ \
    )(id, tpl, k, f)

// PUBLIC //

#define CONTRACT_AUX_CODE_POSTCONDITION_FUNC(id, tpl, k, f) \
    CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f), \
            (postcondition))

#define CONTRACT_AUX_CODE_POSTCONDITION(id, tpl, k, f) \
    BOOST_PP_IIF(CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
        BOOST_PP_TUPLE_EAT(5) \
    , \
        CONTRACT_AUX_CODE_POSTCONDITION_ \
    )(id, tpl, k, f, CONTRACT_AUX_CODE_OLDOF_AUTO_TYPES( \
            CONTRACT_AUX_CODE_FUNC_TYPENAME01(tpl, f), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS(f)))

#endif // #include guard

