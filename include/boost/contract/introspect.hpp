
#ifndef BOOST_CONTRACT_INTROSPECT_HPP_
#define BOOST_CONTRACT_INTROSPECT_HPP_

/** @file */

#include <boost/contract/aux_/type_traits/introspection.hpp>
#include <boost/contract/aux_/name.hpp>
/** @cond */
#include <boost/preprocessor/cat.hpp>
/** @endcond */

/* PUBLIC */

#define BOOST_CONTRACT_INTROSPECT(function_name) \
    BOOST_CONTRACT_INTROSPECT_TRAIT(BOOST_PP_CAT(introspect_, function_name), \
            function_name)

#define BOOST_CONTRACT_INTROSPECT_TRAIT(trait_name, function_name) \
    struct trait_name { \
        BOOST_CONTRACT_AUX_INTROSPECTION_HAS_MEMBER_FUNCTION( \
                has_member_function, function_name) \
    \
        template<class BOOST_CONTRACT_AUX_NAME1(C), \
                typename BOOST_CONTRACT_AUX_NAME1(F)> \
        static BOOST_CONTRACT_AUX_NAME1(F) member_function_address() { \
            return &BOOST_CONTRACT_AUX_NAME1(C)::function_name; \
        } \
    };

#endif // #include guard

