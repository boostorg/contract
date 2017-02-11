
#ifndef BOOST_CONTRACT_OVERRIDE_HPP_
#define BOOST_CONTRACT_OVERRIDE_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Facilities to specify contracts for overriding public functions (to support
subcontracting).
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>

#ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #include <boost/contract/core/virtual.hpp>
    #include <boost/contract/detail/type_traits/introspection.hpp>
    #include <boost/contract/detail/tvariadic.hpp>
    #include <boost/contract/detail/none.hpp>
    #include <boost/contract/detail/name.hpp>

    /* PRIVATE */

    #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_(z, \
            arity, arity_compl, function_name) \
        template< \
            class BOOST_CONTRACT_DETAIL_NAME1(B), \
            class BOOST_CONTRACT_DETAIL_NAME1(C) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAMS_Z(z, arity, \
                    BOOST_CONTRACT_DETAIL_NAME1(Args)) \
        > \
        static void BOOST_CONTRACT_DETAIL_NAME1(call_base)( \
            boost::contract::virtual_* BOOST_CONTRACT_DETAIL_NAME1(v), \
            BOOST_CONTRACT_DETAIL_NAME1(C)* BOOST_CONTRACT_DETAIL_NAME1(obj) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAMS_Z(z, arity, \
                BOOST_CONTRACT_DETAIL_NAME1(Args), \
                &, \
                BOOST_CONTRACT_DETAIL_NAME1(args) \
            ) \
            BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(arity_compl) \
            BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(z, arity_compl, \
                    boost::contract::detail::none&) \
        ) { \
            BOOST_CONTRACT_DETAIL_NAME1(obj)-> \
            BOOST_CONTRACT_DETAIL_NAME1(B)::function_name( \
                BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, \
                        BOOST_CONTRACT_DETAIL_NAME1(args)) \
                BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
                BOOST_CONTRACT_DETAIL_NAME1(v) \
            ); \
        }

    #if BOOST_CONTRACT_DETAIL_TVARIADIC
        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(function_name) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_(1, ~, ~, function_name)
    #else
        #include <boost/preprocessor/repetition/repeat.hpp>
        #include <boost/preprocessor/arithmetic/inc.hpp>
        #include <boost/preprocessor/arithmetic/sub.hpp>

        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(function_name) \
            BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_MAX_ARGS), \
                    BOOST_CONTRACT_OVERRIDE_CALL_BASE_ARITY_, function_name) \
        
        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_ARITY_(z, arity, \
                function_name) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_(z, arity, \
                    BOOST_PP_SUB(BOOST_CONTRACT_MAX_ARGS, arity), function_name)
    #endif

    /* PUBLIC */

    #define BOOST_CONTRACT_NAMED_OVERRIDE(override_name, function_name) \
        struct override_name { \
            BOOST_CONTRACT_DETAIL_INTROSPECTION_HAS_MEMBER_FUNCTION( \
                BOOST_CONTRACT_DETAIL_NAME1(has_member_function), \
                function_name \
            ) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(function_name) \
        };
#else
    /**
    Declare an override type with an arbitrary name.
    Declare the override type to be passed as an explicit template parameter to
    @RefFunc{boost::contract::public_function} for overriding public functions.
    @see @RefSect{tutorial, Tutorial}
    @param override_name Name of override type to declare.
    @param function_name    Name of the overriding public function. This macro
                            is called just once even if the function name is
                            overloaded and the same override type can be used
                            for all functions in the same overload set (see
                            @RefSect{advanced_topics, Advanced Topics}).
    */
    #define BOOST_CONTRACT_NAMED_OVERRIDE(override_name, function_name) \
            struct override_name {}; /* empty (not used), just to compile */
#endif
    
/* PUBLIC */

/**
Declare an override type naming it <c>override_<i>function_name</i></c>.
Declare the override type to be passed as an explicit template parameter to
@RefFunc{boost::contract::public_function} for overriding public functions.
@see @RefSect{tutorial, Tutorial}
@param function_name    Name of the overriding public function. This macro
                        is called just once even if the function name is
                        overloaded and the same override type can be used
                        for all functions in the same overload set (see
                        @RefSect{advanced_topics, Advanced Topics}).
*/
#define BOOST_CONTRACT_OVERRIDE(function_name) \
    BOOST_CONTRACT_NAMED_OVERRIDE(BOOST_PP_CAT(override_, function_name), \
            function_name)
    
#if BOOST_PP_VARIADICS
    #include <boost/preprocessor/seq/for_each.hpp>
    #include <boost/preprocessor/variadic/to_seq.hpp>
    
    /* PRIVATE */

    /** @cond */
    #define BOOST_CONTRACT_OVERRIDES_SEQ_(r, unused, function_name) \
        BOOST_CONTRACT_OVERRIDE(function_name)
    /** @endcond */

    /* PUBLIC */

    /**
    Declare multiple override types at once naming them <c>override_...</c> (for
    convenience).
    This is a variadic macro. On compilers that do not support variadic macros,
    the override types can be programmed one-by-one calling
    @RefMacro{BOOST_CONTRACT_OVERRIDE} for each function name.
    @see @RefSect{tutorial, Tutorial}
    @param ...  A comma separated list of one or more names of overriding
                public functions.
    */
    #define BOOST_CONTRACT_OVERRIDES(...) \
        BOOST_PP_SEQ_FOR_EACH(BOOST_CONTRACT_OVERRIDES_SEQ_, ~, \
                BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#else
    #define BOOST_CONTRACT_OVERRIDES \
BOOST_CONTRACT_ERROR_macro_OVERRIDES_requires_variadic_macros_otherwise_manually_repeat_OVERRIDE_macro
#endif

#endif // #include guard

