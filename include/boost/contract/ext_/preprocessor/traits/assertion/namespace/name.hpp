
#ifndef BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/utility/nil.hpp>

/* PUBLIC */

// Expand to `name`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_AUX_NAME_INDEX, \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME_PARSE( \
        decl_traits) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME_PARSE_ARGS_ \
    decl_traits
    
/* PRIVATE */

// Precondition: decl = `name NIL`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME_PARSE_ARGS_( \
        decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK(decl)) \
    )

#endif // #include guard    

