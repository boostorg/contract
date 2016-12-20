
#ifndef BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program contracts for public member functions.
Overloads are provided to handle static, virtual void, virtual non-void,
overriding void, and override non-void public functions.
*/

#include <boost/contract/detail/all_core_headers.hpp>
// Needed within macro expansions below instead of defined(...) (PRIVATE macro).
#if     defined(BOOST_CONTRACT_STATIC_LINK) || \
        !defined(BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS)
    #define BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_ 1
#else
    #define BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_ 0
#endif
#include <boost/contract/detail/decl.hpp>
#include <boost/contract/detail/tvariadic.hpp>
#if BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_
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

// NOTE: Override and (optionally) VirtualResult allowed only when v is present
// because:
// * An overriding func must override a base func declared virtual so with
//   v extra param, thus the overriding func must also always have v (i.e.,
//   Override might be present only if v is also present). However, the first
//   appearing virtual func (e.g., in root class) will not override any
//   previously declared virtual func so does not need Override (i.e., Override
//   always optional).
//   Furthermore, F needs to be specified only together with Override.
// * VirtualResult is only used for virtual functions (i.e., VirtualResult might
//   be present only if v is also present).
//   However, VirtualResult is never specified, not even for virtual functions,
//   when the return type is void (i.e., VirtualResult always optional).

/**
Program contracts for static public functions.
This is used to specify preconditions, postconditions, old value assignments at
body, and check static class invariants for static public functions.

For optimization, this can be omitted for static public functions that do not
have preconditions and postconditions when the enclosing class has no static
invariants.
@see @RefSect{tutorial, Tutorial}
@tparam Class   The class of the contracted member function. This template
                parameter must be explicitly specified for static public
                functions (because they have no object @c this so there is no
                function argument from which this type template parameter can be
                automatically deduced).
@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::guard} declared locally just before the body
        of the contracted function (otherwise this library will generate a
        run-time error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_GUARD}).
*/
template<class Class>
specify_precondition_old_postcondition_except<> public_function() {
    #if BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_
        return specify_precondition_old_postcondition_except<>(
            new boost::contract::detail::public_static_function<Class>());
    #else
        return specify_precondition_old_postcondition_except<>();
    #endif
}

/**
Program contracts for non-static, non-virtual, and not overriding public
functions.
This is used to specify preconditions, postconditions, old value assignments at
body, and check class invariants for public functions that are not static, not
virtual, and do not override.

For optimization, this can be omitted for public functions that do not have
preconditions and postconditions when the enclosing class has no (non-static)
invariants.
@see @RefSect{tutorial, Tutorial}
@param obj  The object @c this from the scope of the contracted function. This
            object can be @c const and @c volatile depending on the
            cv-qualifier for the contracted function (volatile public functions
            will check volatile class invariants, see also
            @RefSect{advanced_topics, Advanced Topics}).
@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::guard} declared locally just before the body
        of the contracted function (otherwise this library will generate a
        run-time error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_GUARD}).
*/
template<class Class>
specify_precondition_old_postcondition_except<> public_function(Class* obj) {
    #if BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_
        return specify_precondition_old_postcondition_except<>(
            new boost::contract::detail::public_function<
                boost::contract::detail::none,
                boost::contract::detail::none,
                boost::contract::detail::none,
                Class
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
        return specify_precondition_old_postcondition_except<>();
    #endif
}

/** @cond */

// For non-static, virtual, and non-overriding public functions (PRIVATE macro).
#define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_( \
        has_virtual_result) \
    template< \
        BOOST_PP_EXPR_IIF(has_virtual_result, typename VirtualResult) \
        BOOST_PP_COMMA_IF(has_virtual_result) \
        class Class \
    > \
    specify_precondition_old_postcondition_except< \
            BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult)> \
    public_function( \
        virtual_* v \
        BOOST_PP_COMMA_IF(has_virtual_result) \
        BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult& r) \
        , Class* obj \
    ) { \
        BOOST_PP_IIF(BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_, \
            /* no F... so cannot enforce contracted F returns VirtualResult */ \
            return (specify_precondition_old_postcondition_except< \
                    BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult)>( \
                new boost::contract::detail::public_function< \
                    boost::contract::detail::none, \
                    BOOST_PP_IIF(has_virtual_result, \
                        VirtualResult \
                    , \
                        boost::contract::detail::none \
                    ), \
                    boost::contract::detail::none, \
                    Class \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA( \
                            BOOST_CONTRACT_MAX_ARGS) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(1, \
                        BOOST_CONTRACT_MAX_ARGS, \
                        boost::contract::detail::none \
                    ) \
                >( \
                    v, \
                    obj, \
                    BOOST_PP_IIF(has_virtual_result, \
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
            return specify_precondition_old_postcondition_except< \
                    BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult)>(); \
        ) \
    }

/** @endcond */
    
#ifdef DOXYGEN
    /**
    Program contracts for virtual, not overriding public functions returning
    void.
    This is used to specify preconditions, postconditions, old value assignments
    at body, and check class invariants for public functions that are virtual,
    do not override, and return @c void.

    For optimization, this can be omitted for public functions that do not have
    preconditions and postconditions when the enclosing class has no
    (non-static) invariants.
    @see @RefSect{tutorial, Tutorial}
    @param v    The contracted virtual function extra trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and with default
                value @c 0.
    @param obj  The object @c this from the scope of the contracted function.
                This object can be @c const and @c volatile depending on the
                cv-qualifier for the contracted function (volatile public
                functions will check volatile class invariants, see also
                @RefSect{advanced_topics, Advanced Topics}).
    @return The result of this function must be assigned to a variable of type
            @RefClass{boost::contract::guard} declared locally just before the
            body of the contracted function (otherwise this library will
            generate a run-time error, see
            @RefMacro{BOOST_CONTRACT_ON_MISSING_GUARD}).
    */
    template<class Class>
    specify_precondition_old_postcondition_except<> public_function(
            virtual_* v, Class* obj);
    
    /**
    Program contracts for virtual, not overriding public functions returning
    non-void.
    This is used to specify preconditions, postconditions, old value assignments
    at body, and check class invariants for public functions that are virtual,
    do not override, and do not return @c void.

    For optimization, this can be omitted for public functions that do not have
    preconditions and postconditions when the enclosing class has no
    (non-static) invariants.
    @see @RefSect{tutorial, Tutorial}
    @param v    The contracted virtual function extra trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and with default
                value @c 0.
    @param r    A reference to the contracted virtual function return value
                (this can be a local variable within the contracted function
                scope, but it must be set by programmers at each function
                @c return statement). The type of this parameter must be the
                same as (or compatible with) the contracted function return type
                (this library might not be able to raise a compile-time error
                if that is not the case (because this function does not take a
                pointer to the contracted function or similar), but in general
                such a type mismatch will cause a run-time error or undefined
                behaviour). Alternatively,
                <c>boost::optional<<i>return_type</i>></c> can be used here (see
                @RefSect{advanced_topics, Advanced Topics}).
    @param obj  The object @c this from the scope of the contracted function.
                This object can be @c const and @c volatile depending on the
                cv-qualifier for the contracted function (volatile public
                functions will check volatile class invariants, see also
                @RefSect{advanced_topics, Advanced Topics}).
    @return The result of this function must be assigned to a variable of type
            @RefClass{boost::contract::guard} declared locally just before the
            body of the contracted function (otherwise this library will
            generate a run-time error, see
            @RefMacro{BOOST_CONTRACT_ON_MISSING_GUARD}).
    */
    template<typename VirtualResult, class Class>
    specify_precondition_old_postcondition_except<VirtualResult>
    public_function(virtual_* v, VirtualResult& r, Class* obj);
#else
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_(
            /* has_virtual_result = */ 0)
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NO_OVERRIDE_(
            /* has_virtual_result = */ 1)
#endif

/** @cond */

// For non-static, virtual, and overriding public functions (PRIVATE macro).
#define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_( \
        z, arity, arity_compl, has_virtual_result) \
    BOOST_CONTRACT_DETAIL_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
        arity, /* is_friend = */ 0, has_virtual_result, \
        Override, VirtualResult, F, Class, Args, \
        v, r, f, obj, args \
    ) { \
        BOOST_PP_IIF(BOOST_CONTRACT_PUBLIC_FUNCTIONS_IMPL_, \
            /* this assert not strictly necessary as compilation will fail */ \
            /* anyways, but helps limiting cryptic compiler's errors */ \
            BOOST_STATIC_ASSERT_MSG( \
                /* -2 for both `this` and `virtual_*` extra parameters */ \
                boost::function_types::function_arity<F>::value - 2 == \
                        BOOST_CONTRACT_DETAIL_TVARIADIC_SIZEOF(arity, Args), \
                "missing one or more arguments for specified function" \
            ); \
            /* assert consistency of F's result type and VirtualResult */ \
            BOOST_PP_IIF(has_virtual_result, \
                BOOST_STATIC_ASSERT_MSG \
            , \
                BOOST_PP_TUPLE_EAT(2) \
            )( \
                (boost::is_same< \
                    typename boost::remove_reference<typename boost:: \
                            function_types::result_type<F>::type>::type, \
                    typename boost::contract::detail:: \
                        remove_value_reference_if_optional<VirtualResult>::type\
                >::value), \
                "mismatching result type for specified function" \
            ); \
            /* assert this so lib can check and enforce override */ \
            BOOST_STATIC_ASSERT_MSG( \
                boost::contract::access::has_base_types<Class>::value, \
                "enclosing class missing 'base-types' typedef" \
            ); \
            return (specify_precondition_old_postcondition_except< \
                    BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult)>( \
                new boost::contract::detail::public_function< \
                    Override, \
                    BOOST_PP_IIF(has_virtual_result, \
                        VirtualResult \
                    , \
                        boost::contract::detail::none \
                    ), \
                    F, \
                    Class \
                    BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
                    BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, Args) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(arity_compl) \
                    BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(z, arity_compl, \
                            boost::contract::detail::none) \
                >( \
                    v, \
                    obj, \
                    BOOST_PP_IIF(has_virtual_result, \
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
            return specify_precondition_old_postcondition_except< \
                    BOOST_PP_EXPR_IIF(has_virtual_result, VirtualResult)>(); \
        ) \
    }

/** @endcond */

#ifdef DOXYGEN
    /**
    Program contracts for overriding public functions (virtual or not) returning
    void.
    This is used to specify preconditions, postconditions, old value assignments
    at body, and check class invariants for overriding public functions (virtual
    or not) that return @c void.

    For optimization, this can be omitted for public functions that do not have
    preconditions and postconditions when the enclosing class has no
    (non-static) invariants.
    @see @RefSect{tutorial, Tutorial}
    @param v    The contracted virtual function extra trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and with default
                value @c 0.
    @param f    A pointer to the contracted function.
    @param obj  The object @c this from the scope of the contracted function.
                This object can be @c const and @c volatile depending on the
                cv-qualifier for the contracted function (volatile public
                functions will check volatile class invariants, see also
                @RefSect{advanced_topics, Advanced Topics}).
    @param args The contracted function arguments (by reference and in the oder
                they appear in the contracted function declaration). On
                compilers that do not support variadic templates, this library
                internally implements this function using preprocessor
                meta-programming (in this case, the maximum number of supported
                arguments @p args is defined by
                @RefMacro{BOOST_CONTRACT_MAX_ARGS}).
    @tparam Override    The type @c override_... declared using the
                        @RefMacro{BOOST_CONTRACT_OVERRIDE} (or similar) macro
                        using the contracted function name. This template
                        parameter must be explicitly specified (because there is
                        no function arguments from which this type template
                        parameter can be automatically deduced).
    @return The result of this function must be assigned to a variable of type
            @RefClass{boost::contract::guard} declared locally just before the
            body of the contracted function (otherwise this library will
            generate a run-time error, see
            @RefMacro{BOOST_CONTRACT_ON_MISSING_GUARD}).
    */
    template<class Override, typename F, class Class, typename... Args>
    specify_precondition_old_postcondition_except<> public_function(
            virtual_* v, F f, Class* obj, Args&... args);

    /**
    Program contracts for overriding public functions (virtual or not) returning
    non-void.
    This is used to specify preconditions, postconditions, old value assignments
    at body, and check class invariants for overriding public functions (virtual
    or not) that do not return @c void.

    For optimization, this can be omitted for public functions that do not have
    preconditions and postconditions when the enclosing class has no
    (non-static) invariants.
    @see @RefSect{tutorial, Tutorial}
    @param v    The contracted virtual function extra trailing parameter of type
                @RefClass{boost::contract::virtual_}<c>*</c> and with default
                value @c 0.
    @param r    A reference to the contracted virtual function return value
                (this can be a local variable within the contracted function
                scope, but it must be set by programmers at each function
                @c return statement). The type of this parameter must be the
                same as (or compatible with) the contracted function return type
                as specified by @c F (this library will generate a compile-time
                error otherwise) Alternatively,
                <c>boost::optional<<i>return_type</i>></c> can be used here (see
                @RefSect{advanced_topics, Advanced Topics}).
    @param f    A pointer to the contracted function.
    @param obj  The object @c this from the scope of the contracted function.
                This object can be @c const and @c volatile depending on the
                cv-qualifier for the contracted function (volatile public
                functions will check volatile class invariants, see also
                @RefSect{advanced_topics, Advanced Topics}).
    @param args The contracted function arguments (by reference and in the oder
                they appear in the contracted function declaration). On
                compilers that do not support variadic templates, this library
                internally implements this function using preprocessor
                meta-programming (in this case, the maximum number of supported
                arguments @p args is defined by
                @RefMacro{BOOST_CONTRACT_MAX_ARGS}).
    @tparam Override    The type @c override_... declared using the
                        @RefMacro{BOOST_CONTRACT_OVERRIDE} (or similar) macro
                        using the contracted function name. This template
                        parameter must be explicitly specified (because there is
                        no function arguments from which this type template
                        parameter can be automatically deduced).
    @return The result of this function must be assigned to a variable of type
            @RefClass{boost::contract::guard} declared locally just before the
            body of the contracted function (otherwise this library will
            generate a run-time error, see
            @RefMacro{BOOST_CONTRACT_ON_MISSING_GUARD}).
    */
    template<class Override, typename VirtualResult, typename F, class Class,
            typename... Args>
    specify_precondition_old_postcondition_except<VirtualResult>
    public_function(virtual_* v, VirtualResult& r, F f, Class* obj,
            Args&... args);
#elif BOOST_CONTRACT_DETAIL_TVARIADIC
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(1, /* arity = */ ~,
            /* arity_compl = */ ~, /* has_virtual_result = */ 0)
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(1, /* arity = */ ~,
            /* arity_compl = */ ~, /* has_virtual_result = */ 1)
#else
    /* PRIVATE */

    #define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_ARITY_( \
            z, arity, unused) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDES_(z, arity, \
                BOOST_PP_SUB(BOOST_CONTRACT_MAX_ARGS, arity), ~)
    
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDES_(z, \
            arity, arity_compl, unused) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(z, \
                arity, arity_compl, /* has_virtual_result = */ 0) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(z, \
                arity, arity_compl, /* has_virtual_result = */ 1)

    /* CODE */

    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_MAX_ARGS),
            BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_ARITY_, ~)
#endif

} } // namespace

#endif // #include guard

