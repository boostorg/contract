
#ifndef BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM_HPP_
#define BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM_HPP_

#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// TODO: Use this macro in all tests that need to remove type's parenthesis.

// Expand `(x)` to x, but `x` (no parenthesis) to `x` and `(x, ...)` (tuple
// size > `) to `(x, ...)`.
#define BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM(tuple) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tuple), \
        BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM_ \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(tuple)

/* PRIVATE */

#define BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM_(tuple) \
    BOOST_PP_EXPAND( \
        BOOST_PP_EXPR_IIF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(tuple), 1), \
            BOOST_PP_TUPLE_REM(1) \
        ) \
        tuple \
    )

#endif // #include guard

