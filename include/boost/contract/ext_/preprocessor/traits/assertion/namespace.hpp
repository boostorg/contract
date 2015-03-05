
#ifndef BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/namespace/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/namespace/new_name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/kind.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>

/* PUBLIC */

// ASSERTION_TRAITS_KIND(traits) expands to `namespace` for this assertion.

// Precondition: decl = `namespace (new-name) as name`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE(namespace, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    )))))

#endif // #include guard

