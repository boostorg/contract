
#ifndef BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// TODO: Document that even with variadic templates there's a hard limit to function max args (18 works, but MAX_ARGS=19 does not). This limit comes from Boost.MPL (vector, push_back, etc.), Boost.FunctionTypes, and other Boost algorithm that do not currently have a variadic template implementation. However, re-impl all these Boost alg would be too much work for this lib, plus the 19 max args limit seems high enough, and it would eventually be removed if Boost.MPL, Boost.FunctionTypes are ever ported to impl that use variadic templates.

// TODO: Document that not using variadic templates (i.e., using pp meta-programming impl instead) does not increase compilation times (I measured this with the max_arg test program).

#include <boost/contract/detail/all_core_headers.hpp>
#include <boost/contract/detail/decl.hpp>
#include <boost/contract/detail/tvariadic.hpp>
#ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #include <boost/contract/detail/operation/public_static_function.hpp>
    #include <boost/contract/detail/operation/public_function.hpp>
    #include <boost/contract/detail/type_traits/optional.hpp>
    #include <boost/contract/detail/none.hpp>
    #include <boost/function_types/result_type.hpp>
    #include <boost/function_types/function_arity.hpp>
    #include <boost/optional.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/type_traits/is_same.hpp>
    #include <boost/static_assert.hpp>
    #include <boost/preprocessor/tuple/eat.hpp>
#endif
#if !BOOST_CONTRACT_DETAIL_TVARIADIC
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/arithmetic/sub.hpp>
    #include <boost/preprocessor/arithmetic/inc.hpp>
#endif
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

namespace boost { namespace contract {

// NOTE: O and (optionally) R allowed only when v is present because:
// * An overriding func must override a base func declared virtual so with
//   v extra param, thus the overriding func must also always have v (i.e., O
//   might be present only if v is also present).
//   However, the first appearing virtual func (e.g., in root class) will not
//   override any previously declared virtual func so does not need O (i.e., O
//   always optional).
//   Furthermore, F needs to be specified only together with O.
// * R is only used for virtual functions (i.e., R might be present only if v
//   is also present).
//   However, R is never specified, not even for virtual functions, when the
//   return type is void (i.e., R always optional).

// For static public functions.
template<class C>
set_precondition_old_postcondition<> public_function() {
    #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
        return set_precondition_old_postcondition<>(
            new boost::contract::detail::public_static_function<C>());
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

// For non-static, non-virtual, and non-overriding public functions.
template<class C>
set_precondition_old_postcondition<> public_function(C* obj) {
    #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
        return set_precondition_old_postcondition<>(
            new boost::contract::detail::public_function<
                boost::contract::detail::none,
                boost::contract::detail::none,
                boost::contract::detail::none,
                C
                BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(
                        BOOST_CONTRACT_MAX_ARGS)
                BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(1,
                    BOOST_CONTRACT_MAX_ARGS,
                    boost::contract::detail::none
                )
            >(
                static_cast<boost::contract::virtual_*>(0),
                obj,
                boost::contract::detail::none::value()
                BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(
                        BOOST_CONTRACT_MAX_ARGS)
                BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(1,
                    BOOST_CONTRACT_MAX_ARGS,
                    boost::contract::detail::none::value()
                )
            )
        );
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

// To use within macro expansions instead of defined(...) (PRIVATE macro).
#ifdef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #define BOOST_CONTRACT_PUBLIC_FUNCTIONS_ 0
#else
    #define BOOST_CONTRACT_PUBLIC_FUNCTIONS_ 1
#endif

// TODO: Document no F here so cannot check consistency between R and actual func's result type... up to user to pass the right R...
// For non-static, virtual, and non-overriding public functions (PRIVATE macro).
#define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_(has_result) \
    template< \
        BOOST_PP_EXPR_IIF(has_result, typename R) \
        BOOST_PP_COMMA_IF(has_result) \
        class C \
    > \
    set_precondition_old_postcondition<BOOST_PP_EXPR_IIF(has_result, R)> \
    public_function( \
        virtual_* v \
        BOOST_PP_COMMA_IF(has_result) \
        BOOST_PP_EXPR_IIF(has_result, R& r) \
        , C* obj \
    ) { \
        BOOST_PP_IIF(BOOST_CONTRACT_PUBLIC_FUNCTIONS_, \
            /* no F... so cannot enforce contracted F ret R (up to user) */ \
            return (set_precondition_old_postcondition< \
                    BOOST_PP_EXPR_IIF(has_result, R)>( \
                new boost::contract::detail::public_function< \
                    boost::contract::detail::none, \
                    BOOST_PP_IIF(has_result, \
                        R \
                    , \
                        boost::contract::detail::none \
                    ), \
                    boost::contract::detail::none, \
                    C \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA( \
                            BOOST_CONTRACT_MAX_ARGS) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(1, \
                        BOOST_CONTRACT_MAX_ARGS, \
                        boost::contract::detail::none \
                    ) \
                >( \
                    v, \
                    obj, \
                    BOOST_PP_IIF(has_result, \
                        r \
                    , \
                        boost::contract::detail::none::value() \
                    ) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA( \
                            BOOST_CONTRACT_MAX_ARGS) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(1, \
                        BOOST_CONTRACT_MAX_ARGS, \
                        boost::contract::detail::none::value() \
                    ) \
                ) \
            )); \
        , \
            return set_precondition_old_postcondition< \
                    BOOST_PP_EXPR_IIF(has_result, R)>(); \
        ) \
    }

BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_(/* has_result = */ 0)
BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_(/* has_result = */ 1)

// For non-static, virtual, and overriding public functions (PRIVATE macro).
#define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_( \
        z, arity, arity_compl, has_result) \
    BOOST_CONTRACT_DETAIL_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
        arity, /* is_friend = */ 0, has_result, \
        O, R, F, C, Args, \
        v, r, f, obj, args \
    ) { \
        BOOST_PP_IIF(BOOST_CONTRACT_PUBLIC_FUNCTIONS_, \
            /* this assert not strictly necessary as compilation will fail */ \
            /* anyways, but helps limiting cryptic compiler's errors */ \
            BOOST_STATIC_ASSERT_MSG( \
                /* -2 for both `this` and `virtual_*` extra parameters */ \
                boost::function_types::function_arity<F>::value - 2 == \
                        BOOST_CONTRACT_DETAIL_TVARIADIC_SIZEOF(arity, Args), \
                "missing one or more arguments for specified function" \
            ); \
            /* assert consistency of F's result type and R (if has_result) */ \
            BOOST_PP_IIF(has_result, \
                BOOST_STATIC_ASSERT_MSG \
            , \
                BOOST_PP_TUPLE_EAT(2) \
            )( \
                (boost::is_same< \
                    typename boost::remove_reference<typename boost:: \
                            function_types::result_type<F>::type>::type, \
                    typename boost::contract::detail:: \
                            remove_value_reference_if_optional<R>::type \
                >::value), \
                "mismatching result type for specified function" \
            ); \
            /* assert this so lib can check and enforce override */ \
            BOOST_STATIC_ASSERT_MSG( \
                boost::contract::access::has_base_types<C>::value, \
                "enclosing class missing 'base-types' typedef" \
            ); \
            return (set_precondition_old_postcondition< \
                    BOOST_PP_EXPR_IIF(has_result, R)>( \
                new boost::contract::detail::public_function< \
                    O, \
                    BOOST_PP_IIF(has_result, \
                        R \
                    , \
                        boost::contract::detail::none \
                    ), \
                    F, \
                    C \
                    BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
                    BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, Args) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(arity_compl) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(z, arity_compl, \
                            boost::contract::detail::none) \
                >( \
                    v, \
                    obj, \
                    BOOST_PP_IIF(has_result, \
                        r \
                    , \
                        boost::contract::detail::none::value() \
                    ) \
                    BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
                    BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, args) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(arity_compl) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(z, arity_compl, \
                            boost::contract::detail::none::value()) \
                ) \
            )); \
        , \
            return set_precondition_old_postcondition< \
                    BOOST_PP_EXPR_IIF(has_result, R)>(); \
        ) \
    }

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(1,
            /* arity = */ ~, /* arity_compl = */ ~, /* has_result = */ 0)
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(1,
            /* arity = */ ~, /* arity_compl = */ ~, /* has_result = */ 1)
#else
    /* PRIVATE */

    #define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_ARITY_( \
            z, arity, unused) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDES_(z, arity, \
                BOOST_PP_SUB(BOOST_CONTRACT_MAX_ARGS, arity), ~)
    
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDES_(z, \
            arity, arity_compl, unused) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(z, \
                arity, arity_compl, /* has_result = */ 0) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(z, \
                arity, arity_compl, /* has_result = */ 1)

    /* CODE */

    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_MAX_ARGS),
            BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_ARITY_, ~)
#endif

} } // namespace

#endif // #include guard

