
#ifndef BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/bool/expr.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/key.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>

/* PUBLIC */

// ASSERTION_TRAITS_KEY(traits) expands to `bool` for this assertion.

// Precondition: decl = `...` (includes `(,,,)`, `bool(,,,)`, etc.).
#define BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_EXPR_PARSE( \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KEY_PARSE(bool, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))

#endif // #include guard

