
#ifndef BOOST_CONTRACT_OVERRIDE_HPP_
#define BOOST_CONTRACT_OVERRIDE_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/all_core_headers.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */
    
#ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #include <boost/contract/detail/type_traits/introspection.hpp>
    #include <boost/contract/detail/none.hpp>
    #include <boost/contract/detail/tvariadic.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_(z, arity, arity_compl, f) \
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
            BOOST_CONTRACT_DETAIL_NAME1(B)::f( \
                BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, \
                        BOOST_CONTRACT_DETAIL_NAME1(args)) \
                BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
                BOOST_CONTRACT_DETAIL_NAME1(v) \
            ); \
        }

    #if BOOST_CONTRACT_DETAIL_TVARIADIC
        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(f) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_(1, ~, ~, f)
    #else
        #include <boost/preprocessor/repetition/repeat.hpp>
        #include <boost/preprocessor/arithmetic/inc.hpp>
        #include <boost/preprocessor/arithmetic/sub.hpp>

        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(f) \
            BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_MAX_ARGS), \
                    BOOST_CONTRACT_OVERRIDE_CALL_BASE_ARITY_, f) \
        
        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_ARITY_(z, arity, f) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_(z, arity, \
                    BOOST_PP_SUB(BOOST_CONTRACT_MAX_ARGS, arity), f)
    #endif

/* PUBLIC */

    #define BOOST_CONTRACT_OVERRIDE_TRAIT(trait, f) \
        struct trait { \
            BOOST_CONTRACT_DETAIL_INTROSPECTION_HAS_MEMBER_FUNCTION( \
                    BOOST_CONTRACT_DETAIL_NAME1(has_member_function), f) \
            \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(f) \
        };
#else
    #define BOOST_CONTRACT_OVERRIDE_TRAIT(trait, f) \
        struct trait {}; /* empty trait type (won't be actually used) */
#endif

#define BOOST_CONTRACT_OVERRIDE(f) \
    BOOST_CONTRACT_OVERRIDE_TRAIT(BOOST_PP_CAT(override_, f), f)

#endif // #include guard

