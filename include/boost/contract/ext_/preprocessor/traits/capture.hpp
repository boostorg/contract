
#ifndef BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/capture/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/capture/type.hpp>

// TODO: Review all assertion files to use DECL_TRAITS instead of these
// TRAITS INIT, DONE, and PUSH_BACK directly.

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_DONE_(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

/* PUBLIC */

// Precondition: decl = `[wrapped-type] name`.
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_PARSE_D_L(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_PARSE_D(d, \
        (decl BOOST_PP_NIL, BOOST_CONTRACT_EXT_PP_TRAITS_INIT) \
    )))

#endif // #include guard

