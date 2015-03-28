
#ifndef BOOST_CONTRACT_EXT_PP_PARENTHESIZE_HPP_
#define BOOST_CONTRACT_EXT_PP_PARENTHESIZE_HPP_

#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PUBLIC */

// NOTE: tokens can be EMPTY().
#define BOOST_CONTRACT_EXT_PP_PARENTHESIZE(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), tokens, (tokens))

// NOTE: tokens can be EMPTY().
#define BOOST_CONTRACT_EXT_PP_UNPARENTHESIZE(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), \
        BOOST_PP_TUPLE_REM_CTOR \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(tokens)

#endif // #include guard

