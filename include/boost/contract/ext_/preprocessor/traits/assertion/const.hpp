
#ifndef BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/const/expr.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/const/captures.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/kind.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_DONE_(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

/* PUBLIC */

// Precondition: decl = `const( [[(wrapped-type)] name, ...] ) expr`.
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_EXPR_PARSE( \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES_PARSE_D(d, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE(const, \
        (decl BOOST_PP_NIL, BOOST_CONTRACT_EXT_PP_TRAITS_INIT) \
    ))))

// ASSERTION_TRAITS_KIND(traits) expands to `const` for this assertion.

#endif // #include guard

