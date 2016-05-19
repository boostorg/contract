
#ifndef BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program contracts for public member functions.
Different overloads are provided to handle static, virtual void/non-void, and
overriding void/non-void public functions.
*/

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

/**
Program contracts for static public functions.
Used to specify preconditions, postconditions, old value assignments, and check
static class invariants for static public functions.
@see @RefSect{tutorial, Tutorial}.
@tparam C   Class of contracted member function. This template parameter must
            be explicitly specified for static public functions (because they
            have no object so this template parameter cannot be automatically
            deduced).
@return The result of this function must be assigned to a local variable of type
        @RefClass{boost::contract::guard} declared at the beginning of the
        static public function definition (after declaring old value pointers
        if they are present).
*/
template<class C>
set_precondition_old_postcondition<> public_function() {
    #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
        return set_precondition_old_postcondition<>(
            new boost::contract::detail::public_static_function<C>());
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

/**
Program contracts for non-static, non-virtual, and not overriding public
functions.
Used to specify preconditions, postconditions, old value assignments, and to
check class invariants for public functions that are not static, not virtual,
and do not override.
@see @RefSect{tutorial, Tutorial}.
@param obj  The public function's object @c this. It will be @c const and/or
            @c volatile depending on the cv-qualifier for the contracted public
            function (volatile public functions will check volatile class
            invariants, see also @RefSect{advanced_topics, Advanced Topics}).
@return The result of this function must be assigned to a local variable of type
        @RefClass{boost::contract::guard} declared at the beginning of the
        static public function definition (after declaring old value pointers
        if they are present).
*/
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

/** @cond */

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

/** @endcond */
    
#ifdef DOXYGEN
    /**
    Program contracts for virtual but not overriding public functions returning
    void.
    Used to specify preconditions, postconditions, old value assignments, and
    to check class invariants for public functions that are virtual, do not
    override, and return @c void.
    @see @RefSect{tutorial, Tutorial}.
    @param v    The contracted virtual function extra trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and with default
                value @c 0.
    @param obj  The public function's object @c this. It will be @c const and/or
                @c volatile depending on the cv-qualifier for the contracted
                public function (volatile public functions will check volatile
                class invariants, see also
                @RefSect{advanced_topics, Advanced Topics}).
    @return The result of this function must be assigned to a local variable of
            type @RefClass{boost::contract::guard} declared at the beginning of
            the static public function definition (after declaring old value
            pointers if they are present).
    */
    template<class C>
    set_precondition_old_postcondition<> public_function(virtual_* v, C* obj);
    
    /**
    Program contracts for virtual but not overriding public functions returning
    non-void.
    Used to specify preconditions, postconditions, old value assignments, and
    to check class invariants for public functions that are virtual, do not
    override, and do not return @c void.
    @see @RefSect{tutorial, Tutorial}.
    @param v    The contracted virtual function extra trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and with default
                value @c 0.
    @param r    A reference to the contracted virtual function return value.
                (This could be a variable local to the contracted function
                scope, but it must be set by programmers at each function
                @c return statement.)
    @param obj  The public function's object @c this. It will be @c const and/or
                @c volatile depending on the cv-qualifier for the contracted
                public function (volatile public functions will check volatile
                class invariants, see also
                @RefSect{advanced_topics, Advanced Topics}).
    @return The result of this function must be assigned to a local variable of
            type @RefClass{boost::contract::guard} declared at the beginning of
            the static public function definition (after declaring old value
            pointers if they are present).
    */
    template<typename R, class C>
    set_precondition_old_postcondition<R> public_function(
            virtual_* v, R& r, C* obj);
#else
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_(/* has_result = */ 0)
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_(/* has_result = */ 1)
#endif

/** @cond */

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

/** @endcond */

#ifdef DOXYGEN
    /**
    Program contracts for overriding (virtual or not) public functions returning
    void.
    Used to specify preconditions, postconditions, old value assignments, and
    to check class invariants for public functions that are virtual, do not
    override, and return @c void.
    @see @RefSect{tutorial, Tutorial}.
    @param v    The contracted virtual function extra trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and with default
                value @c 0.
    @param f    A pointer to the contracted function.
    @param obj  The public function's object @c this. It will be @c const and/or
                @c volatile depending on the cv-qualifier for the contracted
                public function (volatile public functions will check volatile
                class invariants, see also
                @RefSect{advanced_topics, Advanced Topics}).
    @param args The contracted function formal parameters (by reference and in
                the oder they appear in the contracted function declaration).
                On compilers that do not support variadic templates, this
                library internally implements this function using preprocessor
                meta-programming (in this case, the maximum number of supported
                arguments @p args is defined by
                @RefMacro{BOOST_CONTRACT_MAX_ARGS}).
    @tparam O   The overriding type @c override_... declared invoking the
                @RefMacro{BOOST_CONTRACT_OVERRIDE} (or similar) macro with the
                contracted function name. This template parameter must be
                explicitly specified (because it is not used in this function
                formal parameter so it cannot be automatically deduced).
    @return The result of this function must be assigned to a local variable of
            type @RefClass{boost::contract::guard} declared at the beginning of
            the static public function definition (after declaring old value
            pointers if they are present).
    */
    template<class O, typename F, class C, typename... Args>
    set_precondition_old_postcondition<> public_function(
            virtual_* v, F f, C* obj, Args&... args);

    /**
    Program contracts for overriding (virtual or not) public functions returning
    non-void.
    Used to specify preconditions, postconditions, old value assignments, and
    to check class invariants for public functions that are virtual, do not
    override, and do not return @c void.
    @see @RefSect{tutorial, Tutorial}.
    @param v    The contracted virtual function extra trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and with default
                value @c 0.
    @param r    A reference to the contracted virtual function return value.
                (This could be a variable local to the contracted function
                scope, but it must be set by programmers at each function
                @c return statement.)
    @param f    A pointer to the contracted function.
    @param obj  The public function's object @c this. It will be @c const and/or
                @c volatile depending on the cv-qualifier for the contracted
                public function (volatile public functions will check volatile
                class invariants, see also
                @RefSect{advanced_topics, Advanced Topics}).
    @param args The contracted function formal parameters (by reference and in
                the oder they appear in the contracted function declaration).
                On compilers that do not support variadic templates, this
                library internally implements this function using preprocessor
                meta-programming (in this case, the maximum number of supported
                arguments @p args is defined by
                @RefMacro{BOOST_CONTRACT_MAX_ARGS}).
    @tparam O   The overriding type @c override_... declared invoking the
                @RefMacro{BOOST_CONTRACT_OVERRIDE} (or similar) macro with the
                contracted function name. This template parameter must be
                explicitly specified (because it is not used in this function
                formal parameter so it cannot be automatically deduced).
    @return The result of this function must be assigned to a local variable of
            type @RefClass{boost::contract::guard} declared at the beginning of
            the static public function definition (after declaring old value
            pointers if they are present).
    */
    template<class O, typename R, typename F, class C, typename... Args>
    set_precondition_old_postcondition<R> public_function(
            virtual_* v, R& r, F f, C* obj, Args&... args);
#elif BOOST_CONTRACT_DETAIL_TVARIADIC
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

