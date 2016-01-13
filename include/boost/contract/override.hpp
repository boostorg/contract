
#ifndef BOOST_CONTRACT_OVERRIDE_HPP_
#define BOOST_CONTRACT_OVERRIDE_HPP_

/** @file */

/* PUBLIC */

#include <boost/preprocessor/cat.hpp>
#define BOOST_CONTRACT_OVERRIDE(f) \
    BOOST_CONTRACT_OVERRIDE_TRAIT(BOOST_PP_CAT(override_, f), f)

#if !BOOST_CONTRACT_PRECONDITIONS && !BOOST_CONTRACT_POSTCONDITIONS && \
        !BOOST_CONTRACT_INVARIANTS
    #define BOOST_CONTRACT_OVERRIDE_TRAIT(trait, f) \
        struct trait {}; /* empty trait type (won't be actually used) */
#else
    #include <boost/contract/core/virtual.hpp>
    #include <boost/contract/aux_/type_traits/introspection.hpp>
    #include <boost/contract/aux_/none.hpp>
    #include <boost/contract/aux_/name.hpp>
    #define BOOST_CONTRACT_OVERRIDE_TRAIT(trait, f) \
        struct trait { \
            BOOST_CONTRACT_AUX_INTROSPECTION_HAS_MEMBER_FUNCTION( \
                    BOOST_CONTRACT_AUX_NAME1(has_member_function), f) \
            /* arity = 0 */ \
            template< \
                class BOOST_CONTRACT_AUX_NAME1(B), \
                class BOOST_CONTRACT_AUX_NAME1(C) \
            > \
            static void BOOST_CONTRACT_AUX_NAME1(call_base)( \
                BOOST_CONTRACT_AUX_NAME1(C)* BOOST_CONTRACT_AUX_NAME1(obj), \
                boost::contract::aux::none&, \
                boost::contract::aux::none&, \
                boost::contract::virtual_* BOOST_CONTRACT_AUX_NAME1(v) \
            ) { \
                BOOST_CONTRACT_AUX_NAME1(obj)->BOOST_CONTRACT_AUX_NAME1(B)::f( \
                    BOOST_CONTRACT_AUX_NAME1(v) \
                ); \
            } \
            /* arity = 1 */ \
            template< \
                class BOOST_CONTRACT_AUX_NAME1(B), \
                class BOOST_CONTRACT_AUX_NAME1(C), \
                typename BOOST_CONTRACT_AUX_NAME1(A0) \
            > \
            static void BOOST_CONTRACT_AUX_NAME1(call_base)( \
                BOOST_CONTRACT_AUX_NAME1(C)* BOOST_CONTRACT_AUX_NAME1(obj), \
                BOOST_CONTRACT_AUX_NAME1(A0)& BOOST_CONTRACT_AUX_NAME1(a0), \
                boost::contract::aux::none&, \
                boost::contract::virtual_* BOOST_CONTRACT_AUX_NAME1(v) \
            ) { \
                BOOST_CONTRACT_AUX_NAME1(obj)->BOOST_CONTRACT_AUX_NAME1(B)::f( \
                    BOOST_CONTRACT_AUX_NAME1(a0), \
                    BOOST_CONTRACT_AUX_NAME1(v) \
                ); \
            } \
            /* arity = 2 */ \
            template< \
                class BOOST_CONTRACT_AUX_NAME1(B), \
                class BOOST_CONTRACT_AUX_NAME1(C), \
                typename BOOST_CONTRACT_AUX_NAME1(A0), \
                typename BOOST_CONTRACT_AUX_NAME1(A1) \
            > \
            static void BOOST_CONTRACT_AUX_NAME1(call_base)( \
                BOOST_CONTRACT_AUX_NAME1(C)* BOOST_CONTRACT_AUX_NAME1(obj), \
                BOOST_CONTRACT_AUX_NAME1(A0)& BOOST_CONTRACT_AUX_NAME1(a0), \
                BOOST_CONTRACT_AUX_NAME1(A1)& BOOST_CONTRACT_AUX_NAME1(a1), \
                boost::contract::virtual_* BOOST_CONTRACT_AUX_NAME1(v) \
            ) { \
                BOOST_CONTRACT_AUX_NAME1(obj)->BOOST_CONTRACT_AUX_NAME1(B)::f( \
                    BOOST_CONTRACT_AUX_NAME1(a0), \
                    BOOST_CONTRACT_AUX_NAME1(a1), \
                    BOOST_CONTRACT_AUX_NAME1(v) \
                ); \
            } \
        };
#endif

#endif // #include guard

