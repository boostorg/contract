
#ifndef BOOST_CONTRACT_EXT_PP_IS_EMPTY_HPP_
#define BOOST_CONTRACT_EXT_PP_IS_EMPTY_HPP_

#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/variadic/size.hpp>

// NOTE: Variadics (and trailing EMPTY()) are used to handle empty arguments on
// all compilers (including MSVC).

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_IS_EMPTY_NO_(...) 0

#define BOOST_CONTRACT_EXT_PP_IS_EMPTY_MAYBE_(...) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(__VA_ARGS__ \
            BOOST_PP_EMPTY()), \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY_NO_ \
    , \
        BOOST_PP_IS_EMPTY \
    )(__VA_ARGS__ BOOST_PP_EMPTY())

/* PUBLIC */

// Only IS_EMPTY() expands to 1.
// Handle arguments with parenthesis and commas, BOOST_PP_EMPTY does not
// (e.g., IS_EMPTY(x), IS_EMPTY(()), IS_EMPTY(x, y), IS_EMPTY((), ()) all
// expand to 0).
#define BOOST_CONTRACT_EXT_PP_IS_EMPTY(...) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(1, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY_MAYBE_ \
    , \
        BOOST_CONTRACT_EXT_PP_IS_EMPTY_NO_ \
    )(__VA_ARGS__)

#endif // #include guard

