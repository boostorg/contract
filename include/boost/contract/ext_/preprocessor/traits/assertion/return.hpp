
#ifndef BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/return/assign.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/return/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/kind.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_DONE_(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

/* PUBLIC */

// Precondition: decl = `typedef wrapped-type new-name`.
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN_PARSE( \
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_TYPE_PARSE_D(d, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE(return, \
        (decl BOOST_PP_NIL, BOOST_CONTRACT_EXT_PP_TRAITS_INIT) \
    ))))

// ASSERTION_TRAITS_KIND(traits) expands to `return` for this assertion.

#endif // #include guard

