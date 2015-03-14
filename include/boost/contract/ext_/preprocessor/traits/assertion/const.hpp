
#ifndef BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/const/expr.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/const/captures.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/key.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>

/* PUBLIC */

// ASSERTION_TRAITS_KEY(traits) expands to `const` for this assertion.

// Precondition: decl = `const( [[(wrapped-type)] name, ...] ) expr`.
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_DONE( \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_EXPR_PARSE( \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES_PARSE_D_L(d, l, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KEY_PARSE(const, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_INIT( \
        decl BOOST_PP_NIL \
    )))))

#endif // #include guard

