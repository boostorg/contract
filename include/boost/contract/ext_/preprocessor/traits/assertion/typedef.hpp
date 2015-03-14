
#ifndef BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/typedef/new_name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/typedef/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/key.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>

/* PUBLIC */

// ASSERTION_TRAITS_KEY(traits) expands to `typedef` for this assertion.

// Precondition: decl = `typedef wrapped-type new-name`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_DONE( \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NEW_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_PARSE_D(d, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KEY_PARSE(typedef, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_INIT( \
        decl BOOST_PP_NIL \
    )))))

#endif // #include guard

